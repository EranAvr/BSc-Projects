//
// Created by Eran on 6/9/2023.
//

#ifndef HW3_MYGEOSPACE_H
#define HW3_MYGEOSPACE_H

#include <algorithm>
#include <cmath>
#include <iomanip>

namespace MyGeoSpace{

    const int DEF_UNIT = 10;    // in kilometers [km]
    const int NORTH_DEG = 0;    // positive y axis
    const int EAST_DEG = 90;    // positive x axis
    const int SOUTH_DEG = 180;    // negative y axis
    const int WEST_DEG = 270;    // negative x axis
    constexpr static const double DEG_TO_RAD_FACTOR {M_PI / 180.0};
    constexpr static const double RAD_TO_DEG_FACTOR {180.0 / M_PI};


    struct Point{
        double x;
        double y;
        Point() : x{0.0}, y{0.0} {}
        Point(double _x, double _y) : x{_x}, y{_y} {}
        inline friend std::ostream& operator<<(std::ostream& out, const Point& p){
            return out << "("
            << setiosflags(std::ios::fixed) << std::setprecision(2) << p.x << ", "
            << setiosflags(std::ios::fixed) << std::setprecision(2) << p.y << ")";
        }
        std::string toString() const{
            char s[20];
            sprintf(s, "(%.2f, %.2f)", x, y);
            return s;
        }
        inline bool isPointInRadius(const Point& p, double r) const{
            return sqrt(pow(x-p.x, 2) + pow(y-p.y, 2)) <= r;
        }
    };


    struct Vector{
        double X;
        double Y;

        Vector() : X{0.0}, Y{1.0} {}
        Vector(double x_dir, double y_dir) : X{x_dir}, Y{y_dir} {}
        Vector(Point from, Point to) : X{to.x-from.x}, Y{to.y-from.y} {}
        explicit Vector(double deg) {
            deg = (90.0 - deg) * DEG_TO_RAD_FACTOR; // transform cartesian degree into our arrange for degrees (north=90)
            X = cos(deg);
            Y = sin(deg);
        }

        double getAngleDeg() const{
            return 90 - std::atan(Y / X) * RAD_TO_DEG_FACTOR;
        }
        double getAngleRad() const{
            return (M_PI / 2) - std::atan(Y / X) * DEG_TO_RAD_FACTOR;
        }
        double getLength() const{
            return std::sqrt(pow(X, 2) + pow(Y, 2));
        }
        Vector getUnitVector() const{
            double l = getLength();
            return {X / l, Y / l};
        }
        Vector getRescaledVector(float newLength) const{
            double l = getLength();
            return {newLength * X / l, newLength * Y / l};
        }

        friend std::ostream& operator<<(std::ostream& out, const Vector& v){
            return out << "[" << v.X << ", " << v.Y << "]";
        }
        Vector operator+(const Vector& v) const{
            return {X+v.X, Y+v.Y};
        }
        friend Point operator+(const Point& p, const Vector& v){
            return {p.x+v.X, p.y+v.Y};
        }
    };



    static double distanceBetweenPoints(const Point& p1, const Point& p2) {
        return sqrt(pow(p1.x-p2.x, 2) + pow(p1.y-p2.y, 2));
    }
    static Point parsePointFromString(std::string ps) {
        auto itr = remove(ps.begin(), ps.end(), ' ');
        double x = stod( ps.substr(1, ps.find(',')-1) );
        double y = stod( ps.substr(ps.find(',')+1, ps.find(')')-ps.find(',')) );
        Point p(x,y);
        return p;
    }
    static std::string formatDecimalFrac(double d, int fractionalPartLength=2){
        std::string res = std::to_string(d);
        return res.substr(0, res.find('.') + 1 + fractionalPartLength);
    }
}

#endif //HW3_MYGEOSPACE_H
