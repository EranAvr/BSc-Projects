//
// Created by Eran on 6/6/2021.
//

#ifndef HW4_SHRINKINGDISC_H
#define HW4_SHRINKINGDISC_H

#include "Disc.h"

class ShrinkingDisc : public Disc{
public:
    ShrinkingDisc(double pos_x, double pos_y, double vx, double vy, double r)
            : Disc(pos_x, pos_y, vx, vy, r) {}
    ShrinkingDisc(Vector2D p, Vector2D v, double r, double m, int crushes)
            : Disc(p, v, r, m) { this->crushesCounter=crushes;}
    virtual ~ShrinkingDisc(){}
    ShrinkingDisc& operator=(const ShrinkingDisc& disc1);
    void shrink(){ this->r *= 0.9;}
private:
};

#endif //HW4_SHRINKINGDISC_H
