//
// Created by Eran on 6/9/2023.
//

#ifndef HW3_MODEL_H
#define HW3_MODEL_H

#include <memory>
#include <vector>
#include <map>
#include "Agent.h"
#include "Site.h"

class View;

/*
 * A Singleton class.
 * The Model element is in charge of:
 * Data related logic
 * Database related interactions (CRUD operations etc..)
 * Communicate with the View element
 */

class Model{
public:
    constexpr static const int DEF_TIME_STEP{1};

    static Model& getInstance();
    static int getTime();
    ~Model();
    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;
    Model(Model&&) = delete;
    Model& operator=(Model&&) = delete;

    // Model interface:
    std::shared_ptr<SimEntity> getEntity(const std::string&) const;
    void addAgent(Agent& agent);
    std::shared_ptr<Agent> getAgent(const std::string&) const;
    void addSite(Site& sitePtr);
    std::shared_ptr<Site> getSite(const std::string&) const;
    const std::map<std::string, std::weak_ptr<SimEntity>>& getEntities() const;
    const std::map<std::string, std::shared_ptr<Agent>>& getAgents() const;
    const std::map<std::string, std::shared_ptr<Site>>& getSites() const;
    std::vector<std::weak_ptr<SimEntity>> getEntitiesInRect(
            const MyGeoSpace::Point& bottomLeft, const MyGeoSpace::Point& upperRight) const;
    std::vector<std::weak_ptr<SimEntity>> getEntitiesInRadius(const MyGeoSpace::Point& center, float R) const;
    void printStatus(std::ostream& out = std::cout);
    void go();
    void goMultiple(int n);

protected:
    static std::unique_ptr<Model> instancePtr;
    static int time;
    std::map<std::string, std::weak_ptr<SimEntity>> entities;
    std::map<std::string, std::shared_ptr<Agent>> agents;
    std::map<std::string, std::shared_ptr<Site>> sites;
    //std::vector<std::weak_ptr<View>> views;
    std::weak_ptr<View> view;

    Model();
};

#endif //HW3_MODEL_H
