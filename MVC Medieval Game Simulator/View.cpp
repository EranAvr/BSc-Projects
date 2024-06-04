//
// Created by Eran on 6/11/2023.
//

#include <iostream>
#include "View.h"
#include "Model.h"

using namespace std;

View::View(Model& m)
    : model(m), origin{MyGeoSpace::Point()}, mapSize{DEF_MAP_SIZE}, scale{DEF_SCALE} {
    //cout << "View created: " << this << " with model: " << &model << endl;
}

View::~View(){
    //cout << "View destroyed: " << this << endl;
}

void View::reset(){
    origin = MyGeoSpace::Point();
    mapSize = DEF_MAP_SIZE;
    scale = DEF_SCALE;
}
void View::setSize(int s) {
    mapSize = s;
}
void View::setScale(float s) {
    scale = s;
}
void View::setOrigin(MyGeoSpace::Point o) {
    origin = o;
}
void View::printStats(ostream& out){
    out << "Display size: " << mapSize << ", scale: "
    << setiosflags(std::ios::fixed) << std::setprecision(2) << scale
    << ", origin: " << origin << endl;
}
void View::printMap(ostream& out) {
    printStats(out);
    // build mapMatrix:
    string mapMatrix[mapSize][mapSize];
    for (int i=0 ; i < mapSize ; i++){
        for (int j=0 ; j < mapSize ; j++){
            mapMatrix[i][j] = DEF_EMPTY_CELL;
        }
    }

    // update observable entities:
    MyGeoSpace::Point ur = MyGeoSpace::Point(origin.x + (mapSize-1)*(int)(scale), origin.y + (mapSize-1)*(int)(scale));
    vector<std::weak_ptr<SimEntity>> vec = model.getEntitiesInRect(origin, ur); // produce visible entities vector
    for (auto& wptr : vec){
        auto sPtr = wptr.lock();
        size_t i = (mapSize-1) - (int)((sPtr->getLocation().y - origin.y) / scale);
        size_t j = (int)((sPtr->getLocation().x - origin.x) / scale);
        mapMatrix[i][j] = sPtr->getSymbol();
    }

    // print mapMatrix to screen:
    size_t headLength = calcLineHeaderLength();
    for (int i=0 ; i < mapSize ; i++){
        // handle lines coords-
        out << createLineHeader(headLength, i);

        // handle mapMatrix values-
        for (int j=0 ; j < mapSize ; j++){
            out << mapMatrix[i][j];
        }
        out << endl;
    }

    // print x-axis coords:
    char xAxis[mapSize * 2];
    for(int i=0; i<(mapSize * 2); i++) {xAxis[i] = ' ';}
    out << string(headLength+1, ' ');
    for (int i=0 ; i < mapSize ; i++) {
        if ((mapSize - 1 - i) % INDICES_GAP == 0) {
            string crd = to_string( (int)(origin.x + ((i / INDICES_GAP) * INDICES_GAP * scale)) );
            //out << crd << (to_string(crd).size()==1 ? " " : "");
            memcpy(xAxis+(int)(i*scale)-crd.size()+1, crd.c_str(), crd.size());
        }
        else
            ;
    }
    out << string(xAxis) << endl;
}

size_t View::calcLineHeaderLength() const{
    size_t lineHeadLength = 0;
    for (int i=0 ; i < mapSize ; i++){
        if((mapSize - 1 - i) % INDICES_GAP == 0){
            size_t newSize = to_string((int)(origin.y + (((mapSize-i-1) / INDICES_GAP) * INDICES_GAP * scale)) ).size();
            if (newSize > lineHeadLength)
                lineHeadLength = newSize;
        }
    }
    return lineHeadLength;
}
std::string View::createLineHeader(size_t lineHeadLength, int rowIndex) const{
    string lineHeader(lineHeadLength + 1, ' ');
    if((mapSize - 1 - rowIndex) % INDICES_GAP == 0){
        string idx = to_string((int)(origin.y + (((mapSize-rowIndex-1) / INDICES_GAP) * INDICES_GAP * scale)));
        copy(idx.begin(), idx.end(), lineHeader.end() - idx.size() - 1);
    }
    return lineHeader;
}