//
// Created by Eran on 6/13/2023.
//

#include "Peasant.h"

#include <utility>
#include "Farm.h"
#include "Castle.h"

using namespace std;

Peasant::Peasant(std::string _name, MyGeoSpace::Point _loc)
    : Agent(std::move(_name), _loc), boxes{0}, carryingBoxes{0} {
    setSpeed(DEF_PEASANT_SPEED);
    setStrength(DEF_PEASANT_STRENGTH);
    //setMovingState(POSITION);
    //cout << "Peasant created: " << this << endl;
}

// Rule of five:
Peasant::~Peasant() {
    //cout << "Peasant destroyed: " << this << endl;
}

Peasant::Peasant(const Peasant& p) : Agent(p),
boxes{p.boxes}, carryingBoxes{p.carryingBoxes}, source{p.source}, target{p.target} {
    //cout << "Peasant (copy c`tor) created: " << this << endl;
}
Peasant& Peasant::operator=(const Peasant& p){
    if(this == &p)
        return *this;
    Agent::operator=(p);

    boxes = p.boxes;
    carryingBoxes = p.carryingBoxes;
    source = p.source;
    target = p.target;

    return *this;
}
Peasant::Peasant(Peasant&& p) noexcept : Agent(move(p)),
boxes{p.boxes}, carryingBoxes{p.carryingBoxes}, source{move(p.source)}, target{move(p.target)}  {
    //cout << "Peasant (move c`tor) created: " << this << endl;
}
Peasant& Peasant::operator=(Peasant&& p) noexcept{
    boxes = p.boxes;
    carryingBoxes = p.carryingBoxes;
    source = move(p.source);
    target = move(p.target);
    Agent::operator=(move(p));

    return *this;
}

// Agent methods override:
void Peasant::setStrength(int sn) {
    if (sn > MAX_PEASANT_STRENGTH)
        sn = MAX_PEASANT_STRENGTH;
    if (sn <= 0){
        sn = 0;
        setState(DEAD);
    }
    strength = sn;
}

// SimEntity methods override:
void Peasant::update(int timeSteps) {
    if (state == STOPPED || state == DEAD){
        return;
    }
    // 1. choose destination-
    if(isCarryingBoxes()) {
        // make way to castle.
        setTargetPosition(target.lock()->getLocation());
    }
    else {
        // make way to farm.
        setTargetPosition(source.lock()->getLocation());
    }
    // 2. make next step-
    makeMove(timeSteps);
}
std::string Peasant::getStatus() {
    string stateMessage;
    if(state == DEAD){
        stateMessage = "Dead";
    }
    else if(state == STOPPED){
        stateMessage = "Stopped";
    }
    else {
        stateMessage = "Heading to " + (isCarryingBoxes() ? target : source).lock()->getName()
                       + ", speed " + MyGeoSpace::formatDecimalFrac(getSpeed()) + " km/h";
    }
    return "Peasant " + getName() + " at " + getLocation().toString() + ", carrying " + to_string(boxes)
    + " boxes, health is " + to_string(strength) + ", " + stateMessage;
}
void Peasant::makeMove(int time){
    float stepLength = time * speed;
    if(MyGeoSpace::distanceBetweenPoints(location, destPos) <= stepLength){
        setLocation(destPos);
        if(isCarryingBoxes()){  // reached (back) to target castle
            target.lock()->addToStock(unloadBoxes());
            setState(STOPPED);
            setStrength(getStrength() + 1);
        }
        else {  // reached to source farm
            loadBoxes(source.lock()->takeFromStock(MAX_PEASANT_CARRY_CAPACITY));
            carryingBoxes = true;
        }
    }
    else {
        destCourse = MyGeoSpace::Vector(location, destPos).getRescaledVector(stepLength);
        setLocation(location + destCourse);
    }
}

// Peasant original methods:
void Peasant::start_working(std::weak_ptr<Site> farm, std::weak_ptr<Site> castle){
    if (state == DEAD){
        return;
    }
    // TODO create move constructor for Site
    source = std::move(farm);
    target = std::move(castle);
    setTargetPosition(source.lock()->getLocation());
    carryingBoxes = false;
}
void Peasant::loadBoxes(int amount) {
    if (amount > 0)
        boxes += amount;
}
int Peasant::unloadBoxes() {
    int temp = boxes;
    boxes = 0;
    return temp;
}