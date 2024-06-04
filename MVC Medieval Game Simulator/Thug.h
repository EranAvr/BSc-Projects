//
// Created by Eran on 6/9/2023.
//

#ifndef HW3_THUG_H
#define HW3_THUG_H

#include <memory>
#include <vector>
#include "Agent.h"

class Thug : public Agent{
public:
    static const int DEF_THUG_STRENGTH{5};
    static const int MAX_THUG_STRENGTH{20};
    static const int DEF_THUG_SPEED{5};
    static const int MAX_THUG_SPEED{30};
    constexpr static const float MAX_THUG_ATTACK_RADIUS{1.0};
    constexpr static const float DEF_THUG_SAFE_RADIUS{2.5};

    Thug() = delete;
    Thug(std::string _name, MyGeoSpace::Point _loc);

    ~Thug() override;
    Thug(const Thug&);
    Thug& operator=(const Thug&);
    Thug(Thug&&) noexcept;
    Thug& operator=(Thug&&) noexcept;

    // Agent methods override:
    void setSpeed(float sp) override;
    void setStrength(int sn) override;

    // SimEntity methods override:
    void update(int timeSteps) override;
    std::string getStatus() override;

    // Agents methods:
    void makeMove(int time) override;

    // Thug original methods:
    void attack(const std::weak_ptr<Agent>&);
protected:
};

#endif //HW3_THUG_H
