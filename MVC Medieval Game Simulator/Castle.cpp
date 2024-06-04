//
// Created by Eran on 6/13/2023.
//

#include "Castle.h"

using namespace std;

Castle::Castle(std::string _name, MyGeoSpace::Point _loc, int _stock)
        : Site(std::move(_name), _loc, _stock) {
    //cout << "Castle created: " << this << endl;
}

Castle::~Castle() {
    //cout << "Castle destroyed: " << this << endl;
}
/*Castle::Castle(const Castle& c) : Site(c.getName(), c.getLocation(), c.getStock()) {
    cout << "Castle (copy c`tor) created: " << this << endl;
}
Castle& Castle::operator=(const Castle& c) {
    name = c.name;
    location = c.location;
    symbol = c.symbol;
    stock = c.stock;

    return *this;
}
Castle::Castle(Castle&& c) noexcept : Site(c.name, c.getLocation(), c.getStock()) {

}
Castle& Castle::operator=(Castle&& c) noexcept {
    name = move(c.name);
    location = c.location;
    symbol = move(c.symbol);
    stock = c.stock;

    return *this;
}*/

// SimEntity methods override:
void Castle::update(int timeSteps) {

}
std::string Castle::getStatus()  {
    return "Castle " + getName() + " at position "
    + getLocation().toString() + ", Inventory: " + to_string(getStock());
}