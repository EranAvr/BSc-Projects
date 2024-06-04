//
// Created by Eran on 6/13/2023.
//

#include "Model.h"
#include "Knight.h"
#include "Farm.h"
#include "Castle.h"
#include "MyExceptions.h"

using namespace std;

Knight::Knight(std::string _name, MyGeoSpace::Point _loc, const std::string& _site)
    : Agent(std::move(_name), _loc) {
    if (auto ptr = Model::getInstance().getSite(_site))
        homeSite = ptr;
    else
        throw MyExceptions::SiteDoesntExistException(_site);

    Agent::setSpeed(DEF_KNIGHT_SPEED);
    buildTrip(Model::getInstance().getSites());
    //cout << "Knight created: " << this << endl;
}

// Rule of five:
Knight::~Knight() {
    //cout << "Knight destroyed: " << this << endl;
}

Knight::Knight(const Knight& k)
    : Agent(k), targetSiteName{k.targetSiteName}, homeSite{k.homeSite}, trip{k.trip} {

    //cout << "Knight (copy c`tor) created: " << this << endl;
}
Knight& Knight::operator=(const Knight& k){
    if(this == &k)
        return *this;
    Agent::operator=(k);

    targetSiteName = k.targetSiteName;
    homeSite = k.homeSite;
    trip = k.trip;

    return *this;
}
Knight::Knight(Knight&& k) noexcept : Agent(move(k)), targetSiteName{move(k.targetSiteName)},
                                      homeSite{move(k.homeSite)}, trip{move(k.trip)} {

    //cout << "Knight (move c`tor) created: " << this << endl;
}
Knight& Knight::operator=(Knight&& k) noexcept{
    //startingSiteName = move(k.startingSiteName);
    targetSiteName = move(k.targetSiteName);
    homeSite = move(k.homeSite);
    trip = move(k.trip);
    Agent::operator=(move(k));

    return *this;
}

// Agent methods override:

// SimEntity methods override:
void Knight::update(int timeSteps) {
    if (state == STOPPED || state == DEAD){
        return;
    }
    else if (state == MOVING)
        makeMove(timeSteps);
}

std::string Knight::getStatus() {
    string stateMessage;
    if(state == DEAD)
        stateMessage = "Dead";
    else if(state == STOPPED)
        stateMessage = "Stopped";
    else
        stateMessage = "Heading to " + targetSiteName + ", speed " + MyGeoSpace::formatDecimalFrac(getSpeed()) + " km/h";
    return "Knight " + getName() + " at " + getLocation().toString() + ", starting site "
           + homeSite.lock()->getName() + ", " + stateMessage;
}
void Knight::makeMove(int time){

    setTargetPosition(Model::getInstance().getSite(targetSiteName)->getLocation());

    float stepLength = time * speed;   // calculate next possible distance to move
    if(MyGeoSpace::distanceBetweenPoints(location, destPos) <= stepLength){ // reached site
        setLocation(destPos);
        trip.erase(std::find_if(trip.begin(), trip.end(), [&](const weak_ptr<Site>& ptr){
            return ptr.lock()->getName()==targetSiteName;
        }));
        if(targetSiteName == homeSite.lock()->getName())  // reached back to original starting site
            setState(STOPPED);
        else{     // reached middle way destination site
            calcTripNext(); // update destPos to next new target location
        }
    }
    else {  // on its way to destination point
        destCourse = MyGeoSpace::Vector(location, destPos).getRescaledVector(stepLength);
        setLocation(location + destCourse);
    }
}

// Knight original methods:
void Knight::buildTrip(const std::map<std::string, std::shared_ptr<Site>>& mp){
    for(const auto& itr : mp){
        // map automatically stores pairs by lexical order of keys,
        // so the vector is being built in the same order.
        if(itr.first == homeSite.lock()->getName())
            homeSite = itr.second;
        trip.emplace_back(itr.second);
    }

    calcTripNext(); // load first destination
}
void Knight::updateTrip(const std::weak_ptr<Site>& sPtr){
    if (std::find_if(trip.begin(), trip.end(), [&](const weak_ptr<Site>& ptr){
        return ptr.lock()->getName() == sPtr.lock()->getName();
    }) == trip.end())
        trip.emplace_back(sPtr);

    // TODO replace patch-
    // This is a temporary 'patch' in order for knight to always
    // hold homeSite in trip list. that way he will always come back home.
    if (std::find_if(trip.begin(), trip.end(), [&](const weak_ptr<Site>& ptr){
        return ptr.lock()->getName() == homeSite.lock()->getName();
    }) == trip.end())
        trip.emplace_back(homeSite);
}
void Knight::calcTripNext(){
    if(trip.size() <= 1){   // trip contains homeSite or empty. assume knight has finished and send him back to start
        targetSiteName = homeSite.lock()->getName();
        setTargetPosition(homeSite.lock()->getLocation());
        return;
    }
    weak_ptr<Site> res;
    double minDis = INT32_MAX;
    for(auto itr = trip.begin(); itr != trip.end();) {
        if(itr->lock()->getName() == homeSite.lock()->getName())
        {
            ++itr;
            continue;
        }
        double dis = MyGeoSpace::distanceBetweenPoints(location, itr->lock()->getLocation());
        if (dis < minDis) { // take only improvements (closer sites)
            minDis = dis;
            res = itr->lock();
        }
        ++itr;
    }

    setTargetSite(res.lock()->getName());
    setTargetPosition(res.lock()->getLocation());  // setting next destination
}
void Knight::setTargetSite(const std::string& siteName){
    updateTrip(Model::getInstance().getSite(siteName));
    targetSiteName = siteName;
    setState(MOVING);
    setMovingState(DESTINATION);
}
const std::string& Knight::getTargetSite(){
    return targetSiteName;
}