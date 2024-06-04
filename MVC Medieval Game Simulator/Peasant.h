//
// Created by Eran on 6/9/2023.
//

#ifndef HW3_PEASANT_H
#define HW3_PEASANT_H

#include <memory>
#include <utility>
#include "Agent.h"

class Site;

class Peasant : public Agent{
public:
    static const int DEF_PEASANT_STRENGTH{10};
    static const int MAX_PEASANT_STRENGTH{20};
    static const int DEF_PEASANT_SPEED{5};
    static const int MAX_PEASANT_CARRY_CAPACITY{5};

    Peasant() = delete;
    Peasant(std::string _name, MyGeoSpace::Point _loc);

    ~Peasant() override;
    Peasant(const Peasant&);
    Peasant& operator=(const Peasant&);
    Peasant(Peasant&&) noexcept ;
    Peasant& operator=(Peasant&&) noexcept ;

    // Agent methods:
    void setDestination(float x, float y) = delete;
    void setCourse(float angle) = delete;
    void setStrength(int sn) override;
    void makeMove(int time) override;

    // SimEntity methods override:
    void update(int timeSteps) override;
    std::string getStatus() override;

    // Peasant original methods:
    void start_working(std::weak_ptr<Site> farm, std::weak_ptr<Site> castle);
    //void switchCarryingStatus() { carryingBoxes = !carryingBoxes; }
    void loadBoxes(int amount);
    int unloadBoxes();
    inline void resetBoxes() { boxes = 0; }
    bool isCarryingBoxes() const { return carryingBoxes; }
protected:
    int boxes;
    bool carryingBoxes;
    std::weak_ptr<Site> source;
    std::weak_ptr<Site> target;
};

#endif //HW3_PEASANT_H
