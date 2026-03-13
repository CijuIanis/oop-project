#pragma once
#include <string>
#include <vector>
#include <ostream>
#include "Player.h"

class Echipa {
private:
    std::string nume;
    std::string oras;
    std::string conferinta;
    double salaryCap;
    std::vector<Player> roster;

    double calculeazaSalariiTotale() const;

public:
    Echipa(const std::string& nume, const std::string& oras,
           const std::string& conferinta, double salaryCap);

    const std::string& getNume() const;
    const std::string& getOras() const;
    const std::string& getConferinta() const;
    double getSalaryCap() const;
    const std::vector<Player>& getRoster() const;

    void adaugaJucator(const Player& player);
    double getScorImpact() const;
    bool esteSubSalaryCap() const;
    const Player& getCelMaiBunJucator() const;

    friend std::ostream& operator<<(std::ostream& os, const Echipa& echipa);
};