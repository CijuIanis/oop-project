#pragma once
#include <string>
#include <ostream>
#include "Contract.h"

class Player {
private:
    std::string name;
    int age;
    std::string position;
    double pointsPerGame;
    double assistsPerGame;
    double reboundsPerGame;
    Contract contract;

    double calculateEfficiencyRating() const;

public:

    Player(const std::string& name, int age, const std::string& position,
           double ppg, double apg, double rpg, const Contract& contract);

    const std::string& getName() const;
    int getAge() const;
    const std::string& getPosition() const;
    double getPointsPerGame() const;
    double getAssistsPerGame() const;
    double getReboundsPerGame() const;
    const Contract& getContract() const;

    double getImpactScore() const;
    bool isAllStar() const;
    std::string getStatLine() const;

    friend std::ostream& operator<<(std::ostream& os, const Player& player);
};