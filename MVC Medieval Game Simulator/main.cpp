#include <iostream>
#include <memory>
#include <fstream>
#include "Model.h"
#include "View.h"
#include "Controller.h"
#include "MyExceptions.h"

#include "Peasant.h"
#include "Knight.h"
#include "Thug.h"
#include "Farm.h"
#include "Castle.h"

using namespace std;

void testGeoSpace(){
    MyGeoSpace::Point p1;
    MyGeoSpace::Point p2(3, 4);
    std::cout << MyGeoSpace::distanceBetweenPoints(p1, p2) << std::endl;

    MyGeoSpace::Vector v(p1, p2);
    std::cout << v << std::endl;
    std::cout << v.getLength() << std::endl;
    std::cout << v + MyGeoSpace::Vector(1,1) << std::endl;
    std::cout << MyGeoSpace::Point(5,5) + MyGeoSpace::Vector(1,1) << std::endl;

    std::cout << p1.isPointInRadius(p2, 4.9) << std::endl;
    std::cout << p1.isPointInRadius(p2, 5) << std::endl;

    cout << MyGeoSpace::parsePointFromString("(10.00, 18.97345)") << endl;

    // test Geospace-
    MyGeoSpace::Point pnt1(1,1);
    MyGeoSpace::Vector vec1(3,4);
    MyGeoSpace::Vector vec2(-5, -5);
    cout << pnt1 << endl;
    cout << "vec1: " << vec1 << endl;
    cout << "vec1 length: " << vec1.getLength() << endl;
    cout << "vec1 <unit vector>: " << vec1.getUnitVector() << endl;
    cout << "vec1 scaled to 10: " << vec1.getRescaledVector(10) << endl;
    cout << "vec1 angle: " << vec1.getAngleDeg() << endl;
    cout << "vec2: " << vec2 << endl;
    cout << "vec2 length: " << vec2.getLength() << endl;
    cout << "vec2 <unit vector>: " << vec2.getUnitVector() << endl;
    cout << "vec2 scaled to 10: " << vec2.getRescaledVector(10) << endl;
    cout << "vec2 angle: " << vec2.getAngleDeg() << endl;

    cout << pnt1 << " + " << vec1 << " = " << pnt1 + vec1 << endl;
    cout << pnt1 << " + " << vec2 << " = " << pnt1 + vec2 << endl;

    MyGeoSpace::Vector vecN(0);
    MyGeoSpace::Vector vecE(90);
    MyGeoSpace::Vector vecS(180);
    MyGeoSpace::Vector vecW(270);
    MyGeoSpace::Vector vecSomeDirection(150);
    cout << vecN << endl;
    cout << vecE << endl;
    cout << vecS << endl;
    cout << vecW << endl;
    cout << vecSomeDirection << endl;
}

void testSimEntities(){
    cout << ">> Init Model:" << endl;
    Model& m = Model::getInstance();

    cout << ">> Check agents:" << endl;
    Peasant p("Henry", MyGeoSpace::Point(2, 5));
    Knight k("James", MyGeoSpace::Point(4, 4), "Riverwood");
    Thug t("Bob", MyGeoSpace::Point(7, 10));
    m.addAgent(p);
    m.addAgent(k);
    m.addAgent(t);
    cout << m.getAgent("Henry")->getStatus() << endl;
    cout << m.getAgent("James")->getStatus() << endl;
    cout << m.getAgent("Bob")->getStatus() << endl;

    cout << ">> Check sites:" << endl;
    Farm f1{"HighHill", MyGeoSpace::Point(10, 20), 15, 3};
    Farm f2{"LowVally", MyGeoSpace::Point(-30, 50), 20, 4};
    Castle c1{"FarFarAway", MyGeoSpace::Point(0, 100), 50};
    m.addSite(f1);
    m.addSite(f2);
    m.addSite(c1);
    cout << m.getSite("HighHill")->getStatus() << endl;
    cout << m.getSite("LowVally")->getStatus() << endl;
    cout << m.getSite("FarFarAway")->getStatus() << endl;

    cout << ">> Check dynamic_pointer_cast<Farm> on shared_ptr<Site> object:" << endl;
    cout << "In farm " << dynamic_pointer_cast<Farm>(m.getSite("HighHill"))->getName()
        << " we work in rate of " << dynamic_pointer_cast<Farm>(m.getSite("HighHill"))->getRate() << endl;

    cout << ">> Test finished." << endl;
}

void testMVC() {
    cout << ">> Init MVC:" << endl;
    Model& m = Model::getInstance();
    View v{m};
    Controller c{m, v};

    Farm f2{"LowVally", MyGeoSpace::Point(100, 50), 20, 4};
    Castle c1{"NotFarAway", MyGeoSpace::Point(90, 90), 50};
    Castle c2{"FarFarAway", MyGeoSpace::Point(120, 230), 50};
    m.addSite(f2);
    m.addSite(c1);
    m.addSite(c2);

    Thug t1("Bob", MyGeoSpace::Point(0, 10));
    Thug t2("Gob", MyGeoSpace::Point(19, 100));
    Thug t3("Job", MyGeoSpace::Point(19.9, 219.9));
    Peasant p1("Henry", MyGeoSpace::Point(120, 50));
    Peasant p2("Slow-Joe", MyGeoSpace::Point(20.9, 219.9));
    Knight k1("James", MyGeoSpace::Point(99, 50), "LowVally");
    Knight k2("Richard", MyGeoSpace::Point(19.9, 225), "FarFarAway");
    t3.setStrength(15);
    p2.loadBoxes(4);
    m.addAgent(t1);
    m.addAgent(t2);
    m.addAgent(t3);
    m.addAgent(p1);
    m.addAgent(p2);
    m.addAgent(k1);
    m.addAgent(k2);
    cout << ">> Print status:" << endl;
    m.printStatus();

    v.setSize(25);
    v.setOrigin(MyGeoSpace::Point(-40, -10));
    v.setScale(10);
    //ofstream f("output.txt", ostream::out);
    cout << ">> Map at start:" << endl;
    cout << ">> Activate p1 and k1:" << endl;
    dynamic_pointer_cast<Peasant>(m.getAgent("Henry"))->start_working(m.getSite("LowVally"), m.getSite("NotFarAway"));
    dynamic_pointer_cast<Knight>(m.getAgent("James"))->buildTrip(m.getSites());
    m.printStatus();
    v.printMap();
    cout << ">> Map after step 1:" << endl;
    m.go();
    m.printStatus();
    v.printMap();
    cout << ">> Map after step 5:" << endl;
    m.goMultiple(4);
    m.printStatus();
    v.printMap();
    cout << ">> Map after step 12:" << endl;
    m.goMultiple(7);
    m.printStatus();
    v.printMap();
    cout << ">> Map after step 22:" << endl;
    m.goMultiple(10);
    m.printStatus();
    v.printMap();
    cout << ">> Map after step 42:" << endl;
    m.goMultiple(20);
    m.printStatus();
    v.printMap();

    cout << ">> Check attack:" << endl;
    dynamic_pointer_cast<Thug>(m.getAgent("Job"))->attack(m.getAgent("Slow-Joe"));
    m.printStatus();
    v.printMap();

    cout << ">> Test finished." << endl;
}


int main(int argc, char* argv[]) {
    //testGeoSpace();
    //testSimEntities();
    //testMVC();

    cout << ">> Init MVC" << endl;
    Model& m = Model::getInstance();
    View v{m};
    Controller ctrl{m, v};
    /*
     * Handle program arguments:
     */
    vector<string> inFiles;

    try{
        // check arguments-
        if(argc != 3){
            throw MyExceptions::ArgsCountException();
        }
        // load input files-
        cout << ">> Reading from input files:" << endl;
        string buff, f_name;
        // Read first file:
        f_name = argv[1];
        fstream c_file(f_name, iostream::in);
        cout << f_name << endl;
        while (getline(c_file, buff)){
            //cout << buff << endl;
            size_t delim1 = buff.find(',');
            size_t delim2 = buff.rfind(',');
            Castle c(buff.substr(0, delim1),
                     MyGeoSpace::parsePointFromString(buff.substr(delim1+1, delim2-delim1-1)),
                     stoi(buff.substr(delim2+1))
                     );
            Model::getInstance().addSite(c);
        }
        // Read second file:
        f_name = argv[2];
        fstream f_file(f_name, iostream::in);
        cout << f_name << endl;
        while (getline(f_file, buff)){
            //cout << buff << endl;
            size_t delim1 = buff.find(',');
            size_t delim2 = buff.find(')', delim1) + 1;
            size_t delim3 = buff.rfind(',');
            Farm f(buff.substr(0, delim1),
                   MyGeoSpace::parsePointFromString(buff.substr(delim1+1, delim2-delim1-1)),
                   stoi(buff.substr(delim2+1, delim3-delim2-1)),
                   stoi(buff.substr(delim3+1))
                   );
            Model::getInstance().addSite(f);
        }
        // files are closed at the end of block
    }
    catch(exception& e){
        cout << e.what() << endl;
        exit(-1);
    }

    /*
     * Run user interface:
     */
    cout << ">> Run user interface" << endl;
    ctrl.runUI();

    return 0;
}
