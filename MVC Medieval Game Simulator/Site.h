//
// Created by Eran on 6/9/2023.
//

#ifndef HW3_SITE_H
#define HW3_SITE_H

#include <utility>
#include "SimEntity.h"

class Site : public SimEntity{
public:
    //Site() : SimEntity("Site", MyGeoSpace::Point()), stock{0} {}
    Site() = delete;
    Site(std::string _name, MyGeoSpace::Point _loc, int _stock);
    virtual ~Site() = default;
    Site(const Site&) = default;
    Site& operator=(const Site&) = default;
    Site(Site&&) = default;
    Site& operator=(Site&&) = default;


    inline int getStock() const { return stock; }
    void addToStock(int amount);
    int takeFromStock(int amount);
protected:
    int stock;
};

#endif //HW3_SITE_H
