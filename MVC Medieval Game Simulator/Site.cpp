//
// Created by Eran on 6/13/2023.
//

#include "Site.h"

Site::Site(std::string _name, MyGeoSpace::Point _loc, int _stock)
    : SimEntity(std::move(_name), _loc), stock{_stock} {

}

void Site::addToStock(int amount) {
    if (amount > 0)
        stock += amount;
}
int Site::takeFromStock(int amount) {
    if (stock < amount){
        amount = stock;
        stock = 0;
        return amount;
    }

    stock -= amount;
    return amount;
}