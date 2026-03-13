#pragma once
#include <string>
#include <vector>
#include <ostream>
#include "Echipa.h"

class Sezon {
private:
    std::string an;
    std::string campioana;
    int nrEchipe;
    std::vector<Echipa> echipe;

public:
    Sezon(const std::string& an, const std::string& campioana);

    const std::string& getAn() const;
    const std::string& getCampioana() const;
    int getNrEchipe() const;
    const std::vector<Echipa>& getEchipe() const;

    void adaugaEchipa(const Echipa& echipa);
    const Echipa& getEchipaFavorita() const;
    const Player& getCelMaiBunJucatorDinSezon() const;
    void afiseazaClassament() const;

    friend std::ostream& operator<<(std::ostream& os, const Sezon& sezon);
};