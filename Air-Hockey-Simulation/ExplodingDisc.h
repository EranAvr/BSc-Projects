//
// Created by Eran on 6/6/2021.
//

#ifndef HW4_EXPLODINGDISC_H
#define HW4_EXPLODINGDISC_H

#include "Disc.h"

class ExplodingDisc : public Disc{
public:
    ExplodingDisc(double pos_x, double pos_y, double vx, double vy, double r)
            : Disc(pos_x, pos_y, vx, vy, r) {}
    ExplodingDisc(Vector2D p, Vector2D v, double r, double m, int crushes)
            : Disc(p, v, r, m) { this->crushesCounter=crushes;}
    virtual ~ExplodingDisc(){}
    ExplodingDisc& operator=(const ExplodingDisc& disc1);
    void exp(){}
private:
};

#endif //HW4_EXPLODINGDISC_H
