//
// Created by Eran on 5/4/2021.
//

#include "Disc.h"

Disc::Disc(const Disc& disc1){
    this->p.setX(disc1.p.getX()); this->p.setY(disc1.p.getY());
    this->v.setX(disc1.v.getX()); this->v.setY(disc1.v.getY());
    this->r = disc1.r;
}
Disc::~Disc(){}

ostream& operator<<(ostream& out, const Disc& disc1){
    //  return out<<"[P"<<disc1.p<<"; V"<<disc1.v<<"; R("<<disc1.r<<")]";
    return out<<"(" << disc1.getPos().getX() << "," << disc1.getPos().getY() << ")" << "/" << disc1.getRadius();
}
Disc& Disc::operator=(const Disc& disc1){
    if (this == &disc1){
        return *this;
    }
    this->setPos(disc1.getPos().getX(), disc1.getPos().getY());
    this->setVel(disc1.getVel().getX(), disc1.getVel().getY());
    this->r = disc1.r;
    this->m = disc1.m;
    this->crushedFlag = disc1.crushedFlag;
    this->crushesCounter = disc1.crushesCounter;
    return *this;
}