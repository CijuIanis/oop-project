#pragma once
#include <string>
#include <ostream>
#include "Contract.h"

class Player {
protected:
    std::string name;
    int age;
    std::string position;
    double pointsPerGame;
    double assistsPerGame;
    double reboundsPerGame;
    Contract contract;

    double calculateEfficiencyRating() const;

    // Afisare virtuala - implementata de fiecare clasa derivata
    virtual void print(std::ostream& os) const;

private:
    static int totalJucatoriCreati;

public:
    Player(const std::string& name, int age, const std::string& position,
           double ppg, double apg, double rpg, const Contract& contract);

    virtual ~Player() = default;

    // Clone - constructor virtual
    virtual Player* clone() const = 0;

    // Functie virtuala pura specifica temei
    virtual double calculateRoleScore() const = 0;

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

    static int getTotalJucatori();

    // Interfata non-virtuala pentru afisare
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
};