//
// Created by Eran on 6/9/2023.
//

#ifndef HW3_CONTROLLER_H
#define HW3_CONTROLLER_H

#include "Model.h"
#include "View.h"

/*
 * This class is in charge of UI,
 * and other external communication.
 */
class Controller{
public:
    Controller();
    Controller(Model&, View&);
    /*
    Controller(const Controller& c);
    Controller& operator=(const Controller& c);
    Controller(Controller&& c);
    Controller& operator=(Controller&& c);*/
    ~Controller();
    void runUI();
private:
    Model& model;
    View& view;
};

#endif //HW3_CONTROLLER_H
