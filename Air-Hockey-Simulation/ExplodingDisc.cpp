//
// Created by Eran on 6/7/2021.
//

#include "ExplodingDisc.h"

ExplodingDisc& ExplodingDisc::operator=(const ExplodingDisc& disc1){
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