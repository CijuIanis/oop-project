#pragma once
#include <vector>
#include <string>
#include "Echipa.h"
#include "Player.h"

namespace Stats {

    struct MediaStatistici {
        double mediaPPG;
        double mediaAPG;
        double mediaRPG;
        double mediaImpact;
    };

    struct RezultatComparatie {
        std::string numeEchipa1;
        std::string numeEchipa2;
        double scorImpact1;
        double scorImpact2;
        std::string castigatoare;
    };

    std::vector<const Player*> getTopJucatori(const std::vector<Echipa>& echipe, int n);

    // returneaza top N jucatori All-Star in functie impact score
    std::vector<const Player*> getTopAllStars(const std::vector<Echipa>& echipe, int n);

    // returneaza echipa cu cel mai mare scor de impact
    const Echipa* getEchipaMaxImpact(const std::vector<Echipa>& echipe);
    const Echipa* simulateMeci(const Echipa& e1, const Echipa& e2);
    std::vector<const Echipa*> getEchipeConferinta(const std::vector<Echipa>& echipe, const std::string& conferinta);
    MediaStatistici getMediaStatistici(const std::vector<Echipa>& echipe);
    RezultatComparatie compareEchipe(const Echipa& e1, const Echipa& e2);

}