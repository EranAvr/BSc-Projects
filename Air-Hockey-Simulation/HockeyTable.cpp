//
// Created by Eran on 5/4/2021.
//

#include "HockeyTable.h"

HockeyTable::~HockeyTable(){
    for (int i = 0; i < discs_list.length(); ++i){
        //delete discs_list.getNode(i);
    }
    for (int i = 0; i < walls_list.length(); ++i) {
        delete walls_list.getNode(i);
    }
}

void HockeyTable::start(){
    string command="";
    while (!cin.eof()){
        cin>>command;    // Read user commands
        if (cin.fail()){
            cerr << "Error: illegal input." << endl;
            return;
        }
        if (command=="disc"){
            double x, y, vx, vy, r;
            cin >> x >> y >> vx >> vy >> r;
            if (cin.eof() || cin.bad() || cin.fail()){
                cerr << "Error: illegal input." << endl;
                return;
            }
            Disc* d = new Disc(x, y, vx, vy, r);
            for (int i = 0; i < discs_list.length(); ++i){
                if (isCrushing(*d,discs_list[i])){
                    cerr << "Error: disc to disc collision detected in initial configuration" << endl;
                    delete d;
                    return;
                }
            }
            for (int i = 0; i < walls_list.length(); ++i) {
                if (isCrushing(*d,walls_list[i])){
                    cerr << "Error: disc to wall collision detected in initial configuration" << endl;
                    delete d;
                    return;
                }
            }
            this->discs_list.addToList(new DiscNode(d));
        }
        else if (command=="exploding_disc"){
            double x, y, vx, vy, r;
            cin >> x >> y >> vx >> vy >> r;
            if (cin.eof() || cin.bad() || cin.fail()){
                cerr << "Error: illegal input." << endl;
                return;
            }
            Disc* d = new ExplodingDisc(x, y, vx, vy, r);
            for (int i = 0; i < discs_list.length(); ++i){
                if (isCrushing(*d,discs_list[i])){
                    cerr << "Error: disc to disc collision detected in initial configuration" << endl;
                    delete d;
                    return;
                }
            }
            for (int i = 0; i < walls_list.length(); ++i) {
                if (isCrushing(*d,walls_list[i])){
                    cerr << "Error: disc to wall collision detected in initial configuration" << endl;
                    delete d;
                    return;
                }
            }
            this->discs_list.addToList(new DiscNode(d));
        }
        else if (command=="shrinking_disc"){
            double x, y, vx, vy, r;
            cin >> x >> y >> vx >> vy >> r;
            if (cin.eof() || cin.bad() || cin.fail()){
                cerr << "Error: illegal input." << endl;
                return;
            }
            Disc* d = new ShrinkingDisc(x, y, vx, vy, r);
            for (int i = 0; i < discs_list.length(); ++i){
                if (isCrushing(*d,discs_list[i])){
                    cerr << "Error: disc to disc collision detected in initial configuration" << endl;
                    delete d;
                    return;
                }
            }
            for (int i = 0; i < walls_list.length(); ++i) {
                if (isCrushing(*d,walls_list[i])){
                    cerr << "Error: disc to wall collision detected in initial configuration" << endl;
                    delete d;
                    return;
                }
            }
            this->discs_list.addToList(new DiscNode(d));
        }
        else if (command=="wall"){
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if (cin.eof() || cin.bad() || cin.fail()){
                cerr << "Error: illegal input." << endl;
                return;
            }
            Wall* w = new Wall(x1, y1, x2, y2);
            for (int i = 0; i < discs_list.length(); ++i){
                if (isCrushing(discs_list[i], *w)){
                    cerr << "Error: disc to wall collision detected in initial configuration" << endl;
                    delete w;
                    return;
                }
            }
            this->walls_list.addToList(new WallNode(w));
        }
        else if (command=="simulate"){
            double T, dt;
            cin >> T >> dt;
            if (cin.eof() || cin.bad() || cin.fail()){
                cerr << "Error: illegal input." << endl;
                return;
            }
            simulate(T, dt);
            return;
        }
        else {
            cerr << "Error: illegal input." << endl;
            return;
        }
    }
}
void HockeyTable::simulate(double T, double dt){
    /*
     * the simulation runs from time 0 to time T in periods of dt.
     * in each iteration:
     * for each disc in discs-
     *  0.1) temporary save last position
     *  1) update disc position.
     *  2.1) check crush with all other discs
     *  2.2) update velocity for both discs
     *  3.1) check crush with wall
     *  3.2) update velocity only for disc
     *  4) if this disc has crushedFlag - then take it back to last position
     */
    double t = 0;

    while (t <= T) {
        // Print output:
        cout << t << ": ";
        // set decimal precision for numbers in output
        cout << fixed;
        for (int i = 0; i < discs_list.length(); ++i) {
            cout << setprecision(4) << discs_list[i] << " ";
        }
        cout << endl;

        // Check for each disc in list:
        for (int i = 0; i < discs_list.length(); ++i) {
            Vector2D tempPos = discs_list[i].getPos();  // save init position
            updateDiscPos(discs_list[i], dt);       // move disc to new location

            bool CRUSH_FLAG = false;
            for (int j = 0; j < discs_list.length(); ++j) {   // checks crush with other discs
                if (j!=i && isCrushing(discs_list[i],discs_list[j])){
                    updateCrushedDiscsVel(discs_list[i],discs_list[j]);
                    CRUSH_FLAG = true;
                    // ex4 addition:
                    discs_list[i].markCrushed();
                    discs_list[j].markCrushed();
                }
            }
            for (int j = 0; j < walls_list.length(); ++j) {     // check crush with walls
                if (isCrushing(discs_list[i],walls_list[j])){
                    updateDiscVelAfterWall(discs_list[i], walls_list[j]);
                    CRUSH_FLAG = true;
                    // ex4 addition:
                    discs_list[i].markCrushed();
                }
            }

            if (CRUSH_FLAG) // if crushedFlag - return disc to last location
                discs_list[i].setPos(tempPos.getX(), tempPos.getY());
        }

        // ex4 addition:
        DiscList tempDiscsList;   // temporary empty list
        for (int j = 0; j < discs_list.length(); ++j) { // fill the temp list
            if (!discs_list[j].hasCrushed()){
                tempDiscsList.addToList(new DiscNode(&discs_list[j]));
            }
            else if(typeid(discs_list[j]) == typeid(Disc)){
                discs_list[j].markNotCrushed();
                tempDiscsList.addToList(new DiscNode(&discs_list[j]));
            }
            else if(typeid(discs_list[j]) == typeid(ShrinkingDisc)){
                discs_list[j].markNotCrushed();
                dynamic_cast<ShrinkingDisc&>(discs_list[j]).shrink();
                discs_list[j].incrementCrushCounter();
                if (discs_list[j].getCrushCount() < 3)
                    tempDiscsList.addToList(new DiscNode(&dynamic_cast<ShrinkingDisc&>(discs_list[j])));
            }
            else if(typeid(discs_list[j]) == typeid(ExplodingDisc)){
                discs_list[j].markNotCrushed();
                discs_list[j].incrementCrushCounter();
                ExplodingDisc* allocExpDisc;
                if (discs_list[j].getCrushCount() < 3){
                    double temp_c = 0.99;
                    double temp_r = ((2*sqrt(3)) - 3) * temp_c * discs_list[j].getRadius();
                    double temp_a = (4 - (2*sqrt(3))) * discs_list[j].getRadius();
                    Vector2D temp_p = discs_list[j].getPos() + Vector2D(0, temp_a);
                    Vector2D temp_v = discs_list[j].getVel() + Vector2D(0, 1);
                    allocExpDisc = new ExplodingDisc(temp_p, temp_v, temp_r, discs_list[j].getMass()/3, discs_list[j].getCrushCount());
                    tempDiscsList.addToList(new DiscNode(allocExpDisc));

                    temp_p = discs_list[j].getPos() + Vector2D(discs_list[j].getRadius()-temp_a, (-1)*temp_a*0.5);
                    temp_v = discs_list[j].getVel() + Vector2D(sqrt(3)/2, -0.5);
                    allocExpDisc = new ExplodingDisc(temp_p, temp_v, temp_r, discs_list[j].getMass()/3, discs_list[j].getCrushCount());
                    tempDiscsList.addToList(new DiscNode(allocExpDisc));

                    temp_p = discs_list[j].getPos() + Vector2D(temp_a-discs_list[j].getRadius(), (-1)*temp_a*0.5);
                    temp_v = discs_list[j].getVel() + Vector2D((-1)*sqrt(3)/2, -0.5);
                    allocExpDisc = new ExplodingDisc(temp_p, temp_v, temp_r, discs_list[j].getMass()/3, discs_list[j].getCrushCount());
                    tempDiscsList.addToList(new DiscNode(allocExpDisc));
                }
            }
        }
        discs_list = tempDiscsList;

        t += dt;
    }
}

//  Helper methods

void HockeyTable::updateDiscPos(Disc& disc1, double time){
    disc1.setPos(disc1.getPos().getX() + disc1.getVel().getX()*time,
                 disc1.getPos().getY() + disc1.getVel().getY()*time);
}
bool HockeyTable::isCrushing(const Disc& d1, const Disc& d2) const {
    return (~(d1.getPos()-d2.getPos()) <= (d1.getRadius() + d2.getRadius()));
}
bool HockeyTable::isCrushing(const Disc& d1, Wall& w1) {
    Vector2D q = closestPointOnInterval(d1, w1.getP1(), w1.getP2());
    return (~(d1.getPos()-q) <= d1.getRadius());
}
Vector2D HockeyTable::closestPointOnInterval(const Disc& d1, Vector2D p1, Vector2D p2) {
    if (p1 == p2) { // segment has length zero
        return p1;
    }
    else {
        double a = ((d1.getPos() - p1) * (p2 - p1)) / pow(~(p1 - p2), 2);
        if (a < 0)
            return p1;
        else if (a > 1)
            return p2;
        else
            return p1 + (a * (p2 - p1));
    }
}
void HockeyTable::updateDiscVelAfterWall(Disc& d1, Wall& w1){
    Vector2D q = closestPointOnInterval(d1, w1.getP1(), w1.getP2());
    Vector2D norm_dir = (1 / ~(d1.getPos() - q)) * (d1.getPos() - q);

    Vector2D new_vel = d1.getVel() - (2*(d1.getVel() * norm_dir) * norm_dir);
    d1.setVel(new_vel.getX(), new_vel.getY());
}
void HockeyTable::updateCrushedDiscsVel(Disc& d1, Disc& d2){
    Vector2D norm_dir = (1 / ~(d1.getPos() - d2.getPos())) * (d1.getPos() - d2.getPos());
    Vector2D delta = ((d1.getVel() - d2.getVel()) * norm_dir) * norm_dir;

    double tot_mass = d1.getMass() + d2.getMass();
    Vector2D new_vel1 = d1.getVel() - (2*d2.getMass()/tot_mass) * delta;
    Vector2D new_vel2 = d2.getVel() + (2*d1.getMass()/tot_mass) * delta;

    d1.setVel(new_vel1.getX(), new_vel1.getY());
    d2.setVel(new_vel2.getX(), new_vel2.getY());
}