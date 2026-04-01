#include "Sezon.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <iomanip>

Sezon::Sezon(const std::string& an, const std::string& campioana)
    : an(an), campioana(campioana), nrEchipe(0) {}

const std::string& Sezon::getAn() const { return an; }
const std::string& Sezon::getCampioana() const { return campioana; }
int Sezon::getNrEchipe() const { return nrEchipe; }
const std::vector<Echipa>& Sezon::getEchipe() const { return echipe; }

void Sezon::adaugaEchipa(const Echipa& echipa) {
    echipe.push_back(echipa);
    nrEchipe++;
}

const Echipa& Sezon::getEchipaFavorita() const {
    if (echipe.empty())
        throw std::runtime_error("Sezonul nu are echipe!");

    const Echipa* favorita = &echipe[0];
    for (const auto& echipa : echipe)
        if (echipa.getScorImpact() > favorita->getScorImpact())
            favorita = &echipa;
    return *favorita;
}

const Player& Sezon::getCelMaiBunJucatorDinSezon() const {
    if (echipe.empty())
        throw std::runtime_error("Sezonul nu are echipe!");

    const Player* best = &echipe[0].getCelMaiBunJucator();
    for (const auto& echipa : echipe) {
        const Player& candidat = echipa.getCelMaiBunJucator();
        if (candidat.getImpactScore() > best->getImpactScore())
            best = &candidat;
    }
    return *best;
}

void Sezon::afiseazaClassament() const {
    std::vector<const Echipa*> sorted;
    for (const auto& echipa : echipe)
        sorted.push_back(&echipa);

    std::sort(sorted.begin(), sorted.end(), [](const Echipa* a, const Echipa* b) {
        return a->getScorImpact() > b->getScorImpact();
    });

    std::cout << "\nClasament Sezon " << an << ":\n";
    std::cout << std::string(50, '-') << "\n";
    for (int i = 0; i < (int)sorted.size(); i++)
    {
        std::cout << (i + 1) << ". "
        << std::setw(25) << std::left << sorted[i]->getNume()
        << " | Impact: " << std::fixed << std::setprecision(1)
        << sorted[i]->getScorImpact() << "\n";
    }
    std::cout << "Campioana reala: " << campioana << "\n";
}

std::ostream& operator<<(std::ostream& os, const Sezon& sezon) {
    os << "Sezon NBA " << sezon.an << "\n"
       << "Echipe: " << sezon.nrEchipe << "\n"
       << "Campioana: " << sezon.campioana << "\n";
    for (const auto& echipa : sezon.echipe)
        os << echipa << "\n";
    return os;
}