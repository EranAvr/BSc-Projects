//
// Created by Eran on 6/9/2023.
//

#ifndef HW3_KNIGHT_H
#define HW3_KNIGHT_H

#include <memory>
#include <utility>
#include <vector>
#include <map>
#include "Agent.h"

class Site;

class Knight : public Agent{
public:
    static const int DEF_KNIGHT_STRENGTH{INT32_MAX};
    static const int DEF_KNIGHT_SPEED{10};

    Knight() = delete;
    Knight(std::string _name, MyGeoSpace::Point _loc, const std::string& _site);

    ~Knight() override;
    Knight(const Knight&);
    Knight& operator=(const Knight&);
    Knight(Knight&&) noexcept;
    Knight& operator=(Knight&&) noexcept;

    // Agent methods override:
    /*
    void setTargetPosition(float x, float y) override;
    void setTargetCourse(float angle) override;*/
    void makeMove(int time) override;

    // SimEntity methods override:
    void update(int timeSteps) override;
    std::string getStatus() override;

    // Knight original methods:
    void buildTrip(const std::map<std::string, std::shared_ptr<Site>>&);
    void updateTrip(const std::weak_ptr<Site>&);
    void calcTripNext();
    void setTargetSite(const std::string& siteName);
    const std::string& getTargetSite();
    inline void printTrip() { std::for_each(trip.begin(), trip.end(), [](std::weak_ptr<Site> wPtr){std::cout << wPtr.lock()->getName() << std::endl;});}
protected:
    std::string targetSiteName;
    std::weak_ptr<Site> homeSite;
    std::vector<std::weak_ptr<Site>> trip;
};

#endif //HW3_KNIGHT_H
