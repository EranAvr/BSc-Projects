//
// Created by Eran on 6/9/2023.
//

#ifndef HW3_AGENT_H
#define HW3_AGENT_H

#include <utility>
#include "SimEntity.h"

enum States {STOPPED, DEAD, MOVING};
enum Moving {POSITION, COURSE, DESTINATION};

class Agent : public SimEntity{
public:
    //Agent();
    Agent(std::string _name, MyGeoSpace::Point _loc);
    //Agent(std::string _name, std::string _siteName);
    virtual ~Agent() = default;
    Agent(const Agent&) = default;
    Agent& operator=(const Agent&) = default;
    Agent(Agent&&) = default;
    Agent& operator=(Agent&&) = default;

    // General public agent methods:
    void stopAgent();
    void setState(States st);
    States getState() const;
    void setMovingState(Moving mst);
    Moving getMovingState() const;
    virtual void setSpeed(float sp);
    float getSpeed() const;
    virtual void setStrength(int sn);
    virtual int getStrength() const;

    void update(int timeSteps) override = 0;
    std::string getStatus() override = 0;
    virtual void makeMove(int time) = 0;

    // Agent general methods:
    virtual void setTargetPosition(const MyGeoSpace::Point& dp);
    virtual void setTargetCourse(const MyGeoSpace::Vector& dc);
protected:
    States state;
    Moving movingState;
    int strength;
    float speed;
    MyGeoSpace::Point destPos;
    MyGeoSpace::Vector destCourse;
};

#endif //HW3_AGENT_H
