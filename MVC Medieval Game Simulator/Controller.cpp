//
// Created by Eran on 6/11/2023.
//

#include <sstream>
#include "Controller.h"
#include "MyExceptions.h"
#include "Peasant.h"
#include "Knight.h"
#include "Thug.h"
#include "Farm.h"
#include "Castle.h"

using namespace std;

Controller::Controller() : model(Model::getInstance()), view(*new View(model)) {
    //cout << "Controller created: " << this << endl;
}
Controller::Controller(Model& m, View& v) : model(m), view(v) {
    //cout << "Controller created: " << this << endl;
}
Controller::~Controller(){
    //cout << "Controller destroyed: " << this << endl;
}

void Controller::runUI() {
    string buff;
    while (true){
        try {
            cout << "Time " << model.getTime() << ": Enter command:";
            getline(cin, buff);
            while(buff[0] == ' ')
                buff.erase(0, 1);
            // View commands:
            if(buff == "exit")
                return;
            else if(buff == "default")
                view.reset();
            else if(buff.find("size") != string::npos)
                view.setSize(stoi(buff.substr(buff.find(' ') + 1)) );
            else if(buff.find("zoom") != string::npos)
                view.setScale(stof(buff.substr(buff.find(' ') + 1)) );
            else if(buff.find("pan") != string::npos){
                view.setOrigin(MyGeoSpace::Point(
                        stod(buff.substr(buff.find(' ') + 1)),
                        stod(buff.substr(buff.rfind(' ') + 1))) );
            }
            else if(buff == "show")
                view.printMap();
                // Model commands:
            else if(buff == "status")
                model.printStatus(cout);
            else if(buff == "go")
                model.go();
            else if(buff.find("create") != string::npos){
                buff = buff.substr(buff.find(' ') + 1);
                stringstream ss;
                ss << buff;
                string name, type, startingPoint;
                ss >> name >> type;
                ss.get(); // to throw away next whitespace
                getline(ss, startingPoint);
                if (name.size() > 16)
                    throw MyExceptions::IllegalAgentNameException();
                if (type == "Peasant"){
                    Peasant p(name, MyGeoSpace::parsePointFromString(startingPoint));
                    model.addAgent(p);
                }
                else if (type == "Knight"){
                    if(auto st = model.getSite(startingPoint)){
                        Knight k(name, st->getLocation(), startingPoint);
                        model.addAgent(k);
                    }
                    else{
                        throw MyExceptions::SiteDoesntExistException(startingPoint);
                    }
                }
                else if (type == "Thug"){
                    Thug t(name, MyGeoSpace::parsePointFromString(startingPoint));
                    model.addAgent(t);
                }
            }
            // Agents commands:
            else if(auto a = model.getAgent(buff.substr(0, buff.find(' ')))){
                if(a->getState() == DEAD)
                    throw MyExceptions::CharacterIsDeadException();
                buff = buff.substr(buff.find(' ') + 1); // cut-off agent name
                stringstream ss;
                string cmd;
                ss << buff;
                ss >> cmd;
                if(cmd == "course" && typeid(*a) != typeid(Peasant)){
                    int deg=0;
                    float speed=0.0;
                    ss >> deg >> speed;
                    if(speed == 0.0 && typeid(*a) == typeid(Thug))
                        throw MyExceptions::SpeedParameterMissingException();
                    a->setTargetCourse(MyGeoSpace::Vector(deg));
                    if(speed != 0.0)
                        a->setSpeed(speed);
                }
                else if(cmd == "position" && typeid(*a) != typeid(Peasant)){
                    float x, y, speed = 0.0;
                    ss >> x >> y >> speed;
                    if(speed == 0.0 && typeid(*a) == typeid(Thug))
                        throw MyExceptions::SpeedParameterMissingException();
                    a->setTargetPosition(MyGeoSpace::Point(x, y));
                    if(speed != 0.0)
                        a->setSpeed(speed);
                }
                else if(cmd == "destination" && typeid(*a) == typeid(Knight)){
                    string siteName;
                    ss >> siteName;
                    if(model.getSite(siteName) != nullptr)
                        dynamic_pointer_cast<Knight>(a)->setTargetSite(siteName);
                    else
                        throw MyExceptions::SiteDoesntExistException(siteName);
                }
                else if(cmd == "stop"){
                    a->stopAgent();
                }
                else if(cmd == "attack" && typeid(*a) == typeid(Thug)){
                    string peasantName;
                    ss >> peasantName;
                    if(auto p=model.getAgent(peasantName)){
                        dynamic_pointer_cast<Thug>(a)->attack(p);
                    }
                    else
                        throw MyExceptions::AgentDoesntExistException(peasantName);
                }
                else if(cmd == "start_working" && typeid(*a) == typeid(Peasant)){
                    string farm, castle;
                    ss >> farm >> castle;
                    auto f=model.getSite(farm);
                    if(!f)
                        throw MyExceptions::SiteDoesntExistException(farm);
                    auto c=model.getSite(castle);
                    if(!c)
                        throw MyExceptions::SiteDoesntExistException(castle);
                    dynamic_pointer_cast<Peasant>(a)->start_working(f, c);
                }
            }
            // developer options for testing:
            else if(buff.substr(0, 3) == "dev") {
                buff = buff.substr(buff.find(' ') + 1); // cut-off agent name
                stringstream ss;
                string cmd;
                ss << buff;
                ss >> cmd;
                if(cmd == "dis" && typeid(*a) != typeid(Peasant)){
                    string from, to;
                    ss >> from >> to;
                    auto f=model.getEntity(from);
                    if(!f)
                        throw MyExceptions::SiteDoesntExistException(from);
                    auto t=model.getEntity(to);
                    if(!t)
                        throw MyExceptions::SiteDoesntExistException(to);
                    cout << MyGeoSpace::distanceBetweenPoints(f->getLocation(), t->getLocation()) << endl;
                }
            }
            else{
                throw MyExceptions::IllegalCommandException(buff);
            }
        }
        catch (MyExceptions::CustomException& ce){
            cout << "Error! " << ce.what() << endl;
        }
        catch (exception& e){
            cerr << e.what() << endl;
            return;
        }
    }
}