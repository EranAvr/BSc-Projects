//
// Created by Eran on 6/9/2023.
//

#ifndef HW3_SIMENTITY_H
#define HW3_SIMENTITY_H

#include <iostream>
#include <utility>
#include "MyGeoSpace.h"

class SimEntity{
public:
    SimEntity() = delete;
    inline explicit SimEntity(std::string _name) : name{std::move(_name)} {}
    inline explicit SimEntity(std::string _name, MyGeoSpace::Point _loc) : name{std::move(_name)}, location{_loc} {
        setSymbol(name);
    }
    virtual ~SimEntity() = default;
    SimEntity(const SimEntity& rhs) = default;
    SimEntity& operator=(const SimEntity&) = default;
    SimEntity(SimEntity&& rhs) = default;
    SimEntity& operator=(SimEntity&&) = default;

    // pure-virtual methods:
    virtual void update(int timeSteps) = 0;
    virtual std::string getStatus() = 0;

    // General public SimEntity methods:
    inline void setName(const std::string& _name) { name = _name; }
    inline const std::string& getName() const { return name; }
    inline void setLocation(MyGeoSpace::Point _loc)  { location = _loc; }
    inline const MyGeoSpace::Point& getLocation() const { return location; }
    inline const std::string& getSymbol() const { return symbol; }
    inline void setSymbol(const std::string& _name) {
        symbol = _name.substr(0, 2);
    }

protected:
    std::string name;
    MyGeoSpace::Point location;
    std::string symbol;
};

#endif //HW3_SIMENTITY_H
