//
// Created by Eran on 6/9/2023.
//

#ifndef HW3_VIEW_H
#define HW3_VIEW_H

#include "MyGeoSpace.h"
#include "SimEntity.h"

class Model;

/*
 * Represents what the user can see,
 * communicates with the Controller element.
 */

class View{
public:
    constexpr static const int DEF_MAP_SIZE{25};
    constexpr static const int MIN_MAP_SIZE{6};
    constexpr static const int MAX_MAP_SIZE{30};
    constexpr static const float DEF_SCALE{2.0};
    constexpr static const int INDICES_GAP{3};

    constexpr static char* DEF_EMPTY_CELL{const_cast<char*>(". ")};

    View() = delete;
    explicit View(Model& m);
    ~View();


    void reset();
    void setSize(int s);
    void setScale(float s);
    void setOrigin(MyGeoSpace::Point o);
    void printStats(std::ostream& out = std::cout);  // print to screen
    void printMap(std::ostream& out = std::cout);  // print to screen
    inline friend std::ostream& operator<<(std::ostream& out, const View& v){
        return out << "View: " << &v;
    }

private:
    Model& model;
    MyGeoSpace::Point origin;
    int mapSize;
    float scale;

    size_t calcLineHeaderLength() const;
    std::string createLineHeader(size_t lineHeadLength, int rowIndex) const;
};

#endif //HW3_VIEW_H
