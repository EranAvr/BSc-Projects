//
// Created by Eran on 5/4/2021.
//

#include "Wall.h"

Wall::Wall(const Wall& wall1){
    this->p1.setX(wall1.p1.getX());
    this->p1.setY(wall1.p1.getY());
    this->p2.setX(wall1.p2.getX());
    this->p2.setY(wall1.p2.getY());
}
Wall::~Wall(){}

void Wall::setP1(const Vector2D& vec1){
    this->p1.setX(vec1.getX());
    this->p1.setY(vec1.getY());
}
Vector2D Wall::getP1(){
    return p1;
}
void Wall::setP2(const Vector2D& vec1){
    this->p2.setX(vec1.getX());
    this->p2.setY(vec1.getY());
}
Vector2D Wall::getP2(){
    return p2;
}

ostream& operator<<(ostream& out, const Wall& wall1){
    return out<<(wall1.p1)<<"---"<<(wall1.p2);
}