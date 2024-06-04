//
// Created by Eran on 6/13/2023.
//

#include "Agent.h"

using namespace std;

//Agent::Agent() : SimEntity("Agent", MyGeoSpace::Point()), state{STOPPED}, speed{1}, strength{1} {}
Agent::Agent(std::string _name, MyGeoSpace::Point _loc)
: SimEntity(std::move(_name), _loc), state{STOPPED}, speed{1}, strength{1} {}

void Agent::stopAgent() {
    state = States::STOPPED;
}
void Agent::setState(States st) {
    state = st;
}
States Agent::getState() const {
    return state;
}
void Agent::setMovingState(Moving mst) {
    movingState = mst;
}
Moving Agent::getMovingState() const {
    return movingState;
}
void Agent::setSpeed(float sp) {
    speed = sp;
}
float Agent::getSpeed() const {
    return speed;
}
void Agent::setStrength(int sn) {
    strength = sn;
}
int Agent::getStrength() const {
    return strength;
}
void Agent::setTargetPosition(const MyGeoSpace::Point& dp) {
    if (state == DEAD){
        return;
    }
    destPos = dp;
    setState(MOVING); setMovingState(POSITION);
}
void Agent::setTargetCourse(const MyGeoSpace::Vector& dc) {
    if (state == DEAD){
        return;
    }
    destCourse = dc;
    setState(MOVING); setMovingState(COURSE);
}