//
// Created by Eran on 5/3/2021.
//

#ifndef HW3_HOCKEYTABLE_H
#define HW3_HOCKEYTABLE_H

//#include "Disc.h"
#include "ShrinkingDisc.h"
#include "ExplodingDisc.h"
#include "Wall.h"
#include <typeinfo>

class HockeyTable{
public:
    /*
     * In this class we can use the default c'tor, for there are no dynamic allocations
     * for the class variables. Same thing goes for the Copy-c'tor.
     * On the other hand, because we allocate Discs and Walls on the heap for the lists, we MUST
     * delete them (their nodes) in this class's destructor.
     */
    ~HockeyTable();

    void start();

private:
    DiscList discs_list;
    WallList walls_list;

    //  Helper methods
    void simulate(double T, double dt);
    void updateDiscPos(Disc& d1, double time);
    bool isCrushing(const Disc& d1, const Disc& d2) const;
    bool isCrushing(const Disc& d1, Wall& w1);
    Vector2D closestPointOnInterval(const Disc& d1, Vector2D p1, Vector2D p2);
    void updateDiscVelAfterWall(Disc& d1, Wall& w1);
    void updateCrushedDiscsVel(Disc& d1, Disc& d2);
};

#endif //HW3_HOCKEYTABLE_H