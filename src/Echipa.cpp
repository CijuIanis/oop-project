#include "Echipa.h"
#include <stdexcept>

double Echipa::calculeazaSalariiTotale() const {
    double total = 0.0;
    for (const auto& player : roster)
        total += player.getContract().getSalaryPerYear();
    return total;
}

Echipa::Echipa(const std::string& nume, const std::string& oras,
               const std::string& conferinta, double salaryCap)
    : nume(nume), oras(oras), conferinta(conferinta), salaryCap(salaryCap) {}

const std::string& Echipa::getNume() const { return nume; }
const std::string& Echipa::getOras() const { return oras; }
const std::string& Echipa::getConferinta() const { return conferinta; }
double Echipa::getSalaryCap() const { return salaryCap; }
const std::vector<Player>& Echipa::getRoster() const { return roster; }

void Echipa::adaugaJucator(const Player& player) {
    roster.push_back(player);
}

double Echipa::getScorImpact() const {
    double total = 0.0;
    for (const auto& player : roster)
        total += player.getImpactScore();
    return total;
}

bool Echipa::esteSubSalaryCap() const {
    return calculeazaSalariiTotale() <= salaryCap;
}

const Player& Echipa::getCelMaiBunJucator() const {
    if (roster.empty())
        throw std::runtime_error("Echipa nu are jucatori!");

    const Player* best = &roster[0];
    for (const auto& player : roster)
        if (player.getImpactScore() > best->getImpactScore())
            best = &player;
    return *best;
}

std::ostream& operator<<(std::ostream& os, const Echipa& echipa) {
    os << "=== " << echipa.oras << " " << echipa.nume
       << " [" << echipa.conferinta << "] ===\n"
       << "Salary Cap: $" << echipa.salaryCap << "M | "
       << "Salarii totale: $" << echipa.calculeazaSalariiTotale() << "M | "
       << (echipa.esteSubSalaryCap() ? "Sub cap" : "Peste cap") << "\n"
       << "Roster (" << echipa.roster.size() << " jucatori):\n";
    for (const auto& player : echipa.roster)
        os << "  " << player << "\n";
    return os;
}