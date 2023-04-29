//
// Created by Eran on 6/17/2021.
//

#ifndef HW5_COUNTER_H
#define HW5_COUNTER_H

#include <iostream>
#include <map>
#include <typeinfo>
#include "MyExceptions.h"
using namespace std;

enum KIND{STR, INT};

template<class T>
class Counter{
public:
    KIND k;
    Counter(const string& name, KIND _k) : id(name), k(_k){}
    void clear();
    void add(T val);
    int operator[](T val);
    T most_common() ;
    void add_from_stream(istream& is);
    void print_to_stream(ostream& os) ;
    void print_most_common(ostream& os) ;
    string getId(){ return this->id;}
    int size(){return cMap.size();}
private:
    string id;
    map<T, int> cMap;
};

template<class T>
void Counter<T>::clear(){
    if (typeid(T)==typeid(int))
        this->k = INT;
    else if (typeid(T)==typeid(int))
        this->k = STR;
    cMap.clear();
}

template<class T>
void Counter<T>::add(T val){
    typename map<T, int>::iterator itr;
    for (itr = cMap.begin(); itr != cMap.end() ; itr++) { // search for equivalent value
        if (itr->first == val){ // if value already exists
            itr->second += 1;
            return;
        }
    }
    // else
    cMap.insert(pair<T, int>(val, 1));
}

template<class T>
int Counter<T>::operator[](T val){
    typename map<T, int>::iterator itr = cMap.find(val);
    if (itr == cMap.end())
        return 0;
    // map's [] operator returns the value (int) assigned to the 'val' key, if exists
    return cMap[val];
}

template<class T>
T Counter<T>::most_common() {
    if (this->size()==0){
        throw MyExceptions::xEmptyCounter();
    }
    typename map<T, int>::iterator itr;
    typename map<T, int>::iterator temp_save;
    // scanning the map in a forward direction gives us a lexicographic order
    for (itr = cMap.begin(), temp_save = cMap.begin(); itr != cMap.end() ; itr++) {
        if (itr->second > temp_save->second)
            temp_save = itr;
    }
    return temp_save->first;
}

template<class T>
void Counter<T>::add_from_stream(istream& is){
    T ex;   // extracted value
    while (is >> ex){
        if (is.fail())
            throw MyExceptions::xReadFailure();
        if ((typeid(ex).name()==typeid(int).name() && this->k==STR) || (typeid(ex).name()==typeid(string).name() && this->k==INT)){
            throw MyExceptions::xReadFailure();
        }
        add(ex);
    }
    if(!is.eof()){
        throw MyExceptions::xReadFailure();
    }
}

template<class T>
void Counter<T>::print_to_stream(ostream& os) {
    typename map<T, int>::iterator itr;
    os << "counter " << this->getId() << " = { ";
    for (itr = cMap.begin(); itr != cMap.end() ; itr++) {
        os << itr->first << ":" << itr->second << " ";
    }
    os << "}" << endl;
}

template<class T>
void Counter<T>::print_most_common(ostream& os){
    if (this->size()==0){
        throw MyExceptions::xEmptyCounter();
    }
    T common_key = most_common();
    os << "most common element for counter " << this->getId() << " is " << common_key << ":" << cMap.find(common_key)->second << endl;
}

#endif //HW5_COUNTER_H
