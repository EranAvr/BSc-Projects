//
// Created by Eran on 5/3/2021.
//

#ifndef HW3_WALL_H
#define HW3_WALL_H

#include "Vector2D.h"

class Wall{
public:
    Wall(double x1=0, double y1=0, double x2=0, double y2=0) : p1(x1,y1), p2(x2,y2){}
    Wall(const Wall& wall1);
    ~Wall();
    void setP1(const Vector2D& vec1);
    Vector2D getP1();
    void setP2(const Vector2D& vec1);
    Vector2D getP2();

    friend ostream& operator<<(ostream& out, const Wall& wall1);

private:
    Vector2D p1, p2;
};

struct WallNode{
    /*
     * A simple Linked-List-Node that envelopes
     * a Wall pointer.
     */
    Wall* wallP;
    WallNode* next;
    WallNode(Wall* w) : wallP(w), next(NULL){}
    ~WallNode(){ delete wallP;}
};

struct WallList{
    /*
     * A simple Linked-List implementation that only
     * supports adding new wall to the head of the list, and retrieve
     * walls by index with the [] operator. index=0 means head of list.
     */
private:
    WallNode* head;
    WallNode* tail;
    int wallCount;
public:
    WallList() : head(NULL), wallCount(0){}
    void addToList(WallNode* node){
        if (head==NULL){
            head = tail = node;
        }
        else{
            tail->next = node;
            tail = node;
        }
        wallCount++;
    }
    int length(){return this->wallCount;}
    WallNode* getNode(int i){   // helpful when deleting the list
        if (i >= this->wallCount) {
            cerr << "DiscList's index is out of bound" << endl;
            return NULL;
        }
        WallNode* temp = head;
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

    Wall& operator[](int i){
        if (i >= this->wallCount) {
            cerr << "DiscList's index is out of bound" << endl;
            return *(*this).head->wallP;
        }
        WallNode* temp = head;
        for (int j = 0; j < i; ++j) {
            temp = temp->next;
        }
        return *temp->wallP;
    }
};

#endif //HW3_WALL_H
