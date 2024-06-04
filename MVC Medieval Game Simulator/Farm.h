//
// Created by Eran on 6/9/2023.
//

#ifndef HW3_FARM_H
#define HW3_FARM_H

#include "Site.h"

class Farm : public Site{
public:
    Farm() = delete;
    Farm(std::string _name, MyGeoSpace::Point _loc, int _stock, int _rate);

    ~Farm() override;
    Farm(const Farm&) = default;
    Farm& operator=(const Farm&) = default;
    Farm(Farm&&) = default;
    Farm& operator=(Farm&&) = default;

    // SimEntity methods override:
    void update(int timeSteps) override;
    std::string getStatus() override;

    // Peasant original methods:
    inline int getRate() const { return productionRate; }
protected:
    int productionRate;
};

#endif //HW3_FARM_H
