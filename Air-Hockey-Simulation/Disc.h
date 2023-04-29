//
// Created by Eran on 5/3/2021.
//

#ifndef HW3_DISC_H
#define HW3_DISC_H

#include "Vector2D.h"

class Disc{
public:
    Disc() : r(1), m(c*r*r), crushedFlag(false), crushesCounter(0){}
    Disc(double pos_x, double pos_y, double vx, double vy, double r)
        : p(pos_x, pos_y), v(vx, vy), r(r), m(c*r*r), crushedFlag(false), crushesCounter(0){}
    Disc(const Vector2D& p, const Vector2D& v, double r, double m)
            : p(p.getX(), p.getY()), v(v.getX(), v.getY()), r(r), m(m), crushedFlag(false), crushesCounter(0){}
    Disc(const Disc& disc1);
    virtual ~Disc();

    void setPos(double x1, double y1) {p.setX(x1), p.setY(y1);};
    Vector2D getPos() const {return this->p;};
    void setVel(double vx, double vy) {v.setX(vx), v.setY(vy);};
    Vector2D getVel() const {return this->v;};
    double getRadius() const {return this->r;}
    double getMass() const {return this->m;}

    friend ostream& operator<<(ostream& out, const Disc& disc1);

    // ex4 additions:
    bool hasCrushed() const{return this->crushedFlag;};
    void markCrushed(){ this->crushedFlag = true;}
    void markNotCrushed(){ this->crushedFlag = false;}
    void incrementCrushCounter(){ this->crushesCounter++;}
    int getCrushCount() const{ return this->crushesCounter;}
    Disc& operator=(const Disc& disc1);

protected:
    Vector2D p;
    Vector2D v;
    double r, m;
    static const int c = 1;
    // ex4 additions:
    bool crushedFlag;
    int crushesCounter;
};

struct DiscNode{
    /*
     * A simple Linked-List-Node that envelopes
     * a Disc pointer.
     */
    Disc* discP;
    DiscNode* next;
    DiscNode(Disc* d) : discP(d), next(NULL){}
    ~DiscNode(){}
};

struct DiscList{
    /*
     * A simple Linked-List implementation that only
     * supports adding new disc to the tail of the list, and retrieve
     * discs by index with the [] operator. index=0 means head of list.
     */
private:
    DiscNode* head;
    DiscNode* tail;
    int discCount;
public:
    DiscList() : head(NULL), tail(NULL), discCount(0){}
    ~DiscList(){
        //this->emptyList();
    }
    void addToList(DiscNode* node){
        if (head==NULL){
            head = tail = node;
        }
        else{
            tail->next = node;
            tail = node;
        }
        discCount++;
    }
    void emptyList(){
        if (!head)
            return;
        DiscNode* temp = head;
        while (temp) {
            DiscNode* addressToDelete = temp;
            temp = temp->next;
            delete addressToDelete;
        }
        head = NULL;
        tail = NULL;
        discCount = 0;
    }
    int length() const {return this->discCount;}
    DiscNode* getNode(int i){   // helpful when deleting the list
        if (i >= this->discCount) {
            cerr << "DiscList's index is out of bound" << endl;
            return NULL;
        }
        DiscNode* temp = head;
        for (int j = 0; j < i; ++j) {
            temp = temp->next;
        }
        return temp;
    }

    void print(){
        for (int i = 0 ; i < this->length(); ++i) {
            std::cout << (*this)[i] << std::endl;
        }
    }

    DiscList& operator=(const DiscList& newList){
        if (this == &newList){
            return *this;
        }
        this->emptyList();
        for (int i = 0; i < newList.length(); ++i) {
            this->addToList(new DiscNode(&newList[i]));
        }
        return *this;
    }
    Disc& operator[](int i) const{
        if (i >= this->discCount) {
            cerr << "DiscList's index is out of bound" << endl;
            return *(*this).head->discP;
        }
        DiscNode* temp = head;
        for (int j = 0; j < i; ++j) {
            temp = temp->next;
        }
        return *temp->discP;
    }
};

#endif //HW3_DISC_H
