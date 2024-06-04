//
// Created by Eran on 6/13/2023.
//

#include "Farm.h"

using namespace std;

Farm::Farm(std::string _name, MyGeoSpace::Point _loc, int _stock, int _rate)
: Site(std::move(_name), _loc, _stock), productionRate{_rate} {
    //cout << "Farm created: " << this << endl;
}

Farm::~Farm() {
    //cout << "Farm destroyed: " << this << endl;
}
/*Farm::Farm(const Farm& f) : Site(f.getName(), f.getLocation(), f.getStock()),
    productionRate{f.getRate()} {
    cout << "Farm (copy c`tor) created: " << this << endl;
}
Farm& Farm::operator=(const Farm& f) {
    name = f.name;
    location = f.location;
    symbol = f.symbol;
    stock = f.stock;

    return *this;
}
Farm::Farm(Farm&& f) noexcept : Site(f.name, f.getLocation(), f.getStock()),
    productionRate{f.getRate()} {

}
Farm& Farm::operator=(Farm&& f) noexcept {
    name = move(f.name);
    location = f.location;
    symbol = move(f.symbol);
    stock = f.stock;

    return *this;
}*/

// SimEntity methods override:
void Farm::update(int timeSteps) {
    stock += (productionRate * timeSteps);
}
std::string Farm::getStatus()  {
    return "Farm " + getName() + " at position " + getLocation().toString()
    + ", Inventory: " + to_string(getStock())
    + ", Production rate: " + to_string(getRate());
}