//
// Created by Eran on 6/9/2023.
//

#ifndef HW3_CASTLE_H
#define HW3_CASTLE_H

#include <utility>

#include "Site.h"

class Castle : public Site{
public:
    Castle() = delete;
    Castle(std::string _name, MyGeoSpace::Point _loc, int _stock);

    ~Castle() override;
    Castle(const Castle&) = default;
    Castle& operator=(const Castle&) = default;
    Castle(Castle&&) = default;
    Castle& operator=(Castle&&) = default;

    // SimEntity methods override:
    void update(int timeSteps) override;
    std::string getStatus() override;
protected:
};

#endif //HW3_CASTLE_H
