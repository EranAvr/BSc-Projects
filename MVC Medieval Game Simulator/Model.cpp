//
// Created by Eran on 6/10/2023.
//

#include <iostream>
#include <algorithm>
#include "Model.h"
#include "Peasant.h"
#include "Knight.h"
#include "Thug.h"
#include "Farm.h"
#include "Castle.h"

using namespace std;

std::unique_ptr<Model> Model::instancePtr{nullptr};
int Model::time{0};

Model::Model() {
    //cout << "Model created: " << this << endl;
}

Model& Model::getInstance(){
    if (instancePtr == nullptr)
        instancePtr = std::unique_ptr<Model>(new Model());
    return *Model::instancePtr;
}
int Model::getTime(){
    return time;
}

Model::~Model(){
    //cout << "Model destroyed: " << this << endl;
}

std::shared_ptr<SimEntity> Model::getEntity(const std::string& searchName) const {
    auto itr = entities.find(searchName);
    if(itr != entities.end()) {
        return itr->second.lock();
    }
    return {nullptr};
}
void Model::addAgent(Agent& agent) {
    if(typeid(agent) == typeid(Peasant)){
        agents[agent.getName()] = make_shared<Peasant>(dynamic_cast<Peasant&>(agent));
        entities[agent.getName()] = agents[agent.getName()];
    }
    else if(typeid(agent) == typeid(Knight)){
        agents[agent.getName()] = make_shared<Knight>(dynamic_cast<Knight&>(agent));
        entities[agent.getName()] = agents[agent.getName()];
    }
    else if(typeid(agent) == typeid(Thug)){
        agents[agent.getName()] = make_shared<Thug>(dynamic_cast<Thug&>(agent));
        entities[agent.getName()] = agents[agent.getName()];
    }
}
std::shared_ptr<Agent> Model::getAgent(const std::string& searchName) const {
    auto itr = agents.find(searchName);
    if(itr != agents.end()) {
        return itr->second;
    }
    return {nullptr};
}
void Model::addSite(Site& site) {
    if(typeid(site) == typeid(Farm)){
        sites[site.getName()] = make_shared<Farm>(dynamic_cast<Farm&>(site));
        entities[site.getName()] = sites[site.getName()];
    }
    else if(typeid(site) == typeid(Castle)){
        sites[site.getName()] = make_shared<Castle>(dynamic_cast<Castle&>(site));
        entities[site.getName()] = sites[site.getName()];
    }
}
std::shared_ptr<Site> Model::getSite(const std::string& searchName) const {
    auto itr = sites.find(searchName);
    if(itr != sites.end()) {
        return itr->second;
    }
    return {nullptr};
}

vector<weak_ptr<SimEntity>> Model::getEntitiesInRect(
        const MyGeoSpace::Point& bottomLeft, const MyGeoSpace::Point& upperRight) const {
    vector<weak_ptr<SimEntity>> resVec;
    for (auto& ent : entities){
        //SimEntity& tempEnt = *ent.second.lock();
        // TODO try to move expired checkings to a single function-
        if(ent.second.expired())
            continue;
        auto a = ent.second.lock();
        double x = a->getLocation().x;
        double y = a->getLocation().y;
        if (x >= bottomLeft.x && x <= upperRight.x &&
                y >= bottomLeft.y && y <= upperRight.y){
            resVec.emplace_back(ent.second);
        }
    }
    return resVec;
}
vector<weak_ptr<SimEntity>> Model::getEntitiesInRadius(const MyGeoSpace::Point& center, float R) const {
    vector<weak_ptr<SimEntity>> resVec;
    for (auto& ent : entities){
        //SimEntity& tempEnt = *ent.second.lock();
        // TODO try to move expired checkings to a single function-
        if(ent.second.expired())
            continue;
        auto a = ent.second.lock();
        double checkDistance = MyGeoSpace::distanceBetweenPoints(center, a->getLocation());
        if (0 <= checkDistance && checkDistance <= R){
            resVec.emplace_back(ent.second);
        }
    }
    return resVec;
}

void Model::printStatus(std::ostream& out){
    for(const auto& s : sites)
        out << s.second->getStatus() << endl;
    for(const auto& a : agents)
        out << a.second->getStatus() << endl;
}
void Model::go(){
    for(const auto& s : sites)
        s.second->update(DEF_TIME_STEP);
    for(const auto& a : agents)
        a.second->update(DEF_TIME_STEP);
    ++Model::time;
}
void Model::goMultiple(int n){
    for(int i=0; i<n; i++)
        go();
}

const std::map<std::string, std::weak_ptr<SimEntity>>& Model::getEntities() const {
    return entities;
}
const std::map<std::string, std::shared_ptr<Agent>>& Model::getAgents() const {
    return agents;
}
const std::map<std::string, std::shared_ptr<Site>>& Model::getSites() const {
    return sites;
}