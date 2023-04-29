//
// Created by Eran on 5/3/2021.
//

#ifndef HW3_VECTOR2D_H
#define HW3_VECTOR2D_H

#include "iostream"
#include <cmath>
#include <iomanip>
using namespace std;

class Vector2D{
public:
    /*
     * In this class we have no use for copy-c'tor because
     * there's no use for deep copy here. all fields are primitives.
     * For the same reason we have no use for a special destructor.
     */
    Vector2D(double x1=0, double y1=0) : x(x1), y(y1){};
    void setX(double val) {this->x=val;};
    double getX() const {return x;};
    void setY(double val) {this->y=val;};
    double getY() const {return y;};

    Vector2D operator+(const Vector2D& vec1);
    Vector2D operator-(const Vector2D& vec1);
    double operator~();    // norm
    double operator*(const Vector2D& vec1);    // dot product
    friend ostream& operator<<(ostream& out, const Vector2D& vec1);

private:
    double x, y;
};

Vector2D operator*(double m, const Vector2D& vec1);    // multiplied by integer
bool operator==(const Vector2D& vec1, const Vector2D& vec2);
Vector2D& operator+=(Vector2D& vec1, const Vector2D& vec2);
Vector2D& operator-=(Vector2D& vec1, const Vector2D& vec2);

#endif //HW3_VECTOR2D_H
