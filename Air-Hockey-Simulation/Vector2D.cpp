//
// Created by Eran on 5/4/2021.
//

#include "Vector2D.h"

Vector2D Vector2D::operator+(const Vector2D& vec1){
    return Vector2D(this->x+vec1.x, this->y+vec1.y);
}
Vector2D Vector2D::operator-(const Vector2D& vec1){
    return Vector2D(this->x-vec1.x, this->y-vec1.y);
}

double Vector2D::operator~(){    // norm
    return sqrt((this->x*this->x) + (this->y*this->y));
}
double Vector2D::operator*(const Vector2D& vec1){  // dot product
    return (this->x * vec1.x) + (this->y * vec1.y);
}

ostream& operator<<(ostream& out, const Vector2D& vec1) {
    return out<<"("<<vec1.x<<","<<vec1.y<<")";
}

bool operator==(const Vector2D& vec1, const Vector2D& vec2) {
    return (vec1.getX()==vec2.getX() && vec1.getY()==vec2.getY());
}
Vector2D& operator+=(Vector2D& vec1, const Vector2D& vec2){
    vec1.setX(vec1.getX() + vec2.getX());
    vec1.setY(vec1.getY() + vec2.getY());
    return vec1;
}
Vector2D& operator-=(Vector2D& vec1, const Vector2D& vec2){
    vec1.setX(vec1.getX() - vec2.getX());
    vec1.setY(vec1.getY() - vec2.getY());
    return vec1;
}

Vector2D operator*(double m, const Vector2D& vec1){
    return Vector2D(vec1.getX()*m, vec1.getY()*m);
}