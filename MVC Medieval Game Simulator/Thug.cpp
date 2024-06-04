//
// Created by Eran on 6/13/2023.
//

#include "Model.h"
#include "Thug.h"
#include "Peasant.h"
#include "Knight.h"
#include "MyExceptions.h"

using namespace std;

Thug::Thug(std::string _name, MyGeoSpace::Point _loc)
    : Agent(std::move(_name), _loc) {
    setStrength(DEF_THUG_STRENGTH);
    setMovingState(POSITION);
    //cout << "Thug created: " << this << endl;
}

// Rule of five:
Thug::~Thug() {
    //cout << "Thug destroyed: " << this << endl;
}

Thug::Thug(const Thug& t) : Agent(t) {
    //cout << "Thug (copy c`tor) created: " << this << endl;
}
Thug& Thug::operator=(const Thug& t){
    if(this == &t)
        return *this;
    Agent::operator=(t);

    return *this;
}
Thug::Thug(Thug&& t) noexcept : Agent(move(t)) {
    //cout << "Thug (move c`tor) created: " << this << endl;
}
Thug& Thug::operator=(Thug&& t) noexcept{
    Agent::operator=(move(t));

    return *this;
}

// Agent methods override:
void Thug::setSpeed(float sp) {
    if (sp > MAX_THUG_SPEED)
        sp = MAX_THUG_SPEED;
    else if (sp <= 0){
        sp = 1;
    }
    speed = sp;
}
void Thug::setStrength(int sn) {
    if (sn > MAX_THUG_STRENGTH)
        sn = MAX_THUG_STRENGTH;
    else if (sn <= 0){
        sn = 0;
        setState(DEAD);
    }
    strength = sn;
}

// SimEntity methods override:
void Thug::update(int timeSteps) {
    if (state == STOPPED || state == DEAD){
        return;
    }
    makeMove(timeSteps);
}
std::string Thug::getStatus() {
    string stateMessage;
    if(state == DEAD){
        stateMessage = "Dead";
    }
    else if(state == STOPPED){
        stateMessage = "Stopped";
    }
    else {
        stateMessage = "Heading on course " + MyGeoSpace::formatDecimalFrac(destCourse.getAngleDeg())
                + " deg, speed " + MyGeoSpace::formatDecimalFrac(getSpeed()) + " km/h" ;
    }
    return "Thug " + getName() + " at " + getLocation().toString()
    + ", strength is " + to_string(strength) + ", " + stateMessage;
}

// Thug original methods:
void Thug::makeMove(int time){
    float stepLength = time * speed;
    switch (movingState) {
        case POSITION:
        case DESTINATION:
            setTargetCourse(MyGeoSpace::Vector(location, destPos));
            setLocation(location + destCourse.getRescaledVector(stepLength));
            break;
        case COURSE:
            setLocation(location + destCourse.getRescaledVector(stepLength));
            break;
    }
}
void Thug::attack(const weak_ptr<Agent>& aPtr) {
    if (state == DEAD){
        return;
    }
    auto p = dynamic_pointer_cast<Peasant>(aPtr.lock());
    setState(STOPPED);  // Thug should stop in any case
    // criterion 1-
    if (MyGeoSpace::distanceBetweenPoints(getLocation(), p->getLocation()) > MAX_THUG_ATTACK_RADIUS){
        throw MyExceptions::AttackFailedException("peasant is not close enough.");
    }
    // decrement peasant health if he's at-least close enough to thug.
    p->setStrength(p->getStrength() - 1);

    // criterion 2-
    if(getStrength() <= p->getStrength()){
        setStrength(getStrength() - 1); // decrement thug health
        throw MyExceptions::AttackFailedException("peasant is not weak enough.");
    }
    // criterion 3-
    for(const auto& ent : Model::getInstance().getEntitiesInRadius(getLocation(), Thug::DEF_THUG_SAFE_RADIUS)){
        auto& agnt = *dynamic_pointer_cast<Agent>(ent.lock());
        double checkDistance = MyGeoSpace::distanceBetweenPoints(getLocation(), agnt.getLocation());
        if (typeid(agnt) == typeid(Knight) && checkDistance <= DEF_THUG_SAFE_RADIUS){
            setStrength(getStrength() - 1); // decrement thug health
            throw MyExceptions::AttackFailedException("knight is traveling nearby.");
        }
    }

    // If all criteria passed, attack
    p->resetBoxes();
    p->setState(STOPPED);
    setStrength(getStrength() + 1); // increment thug health
}