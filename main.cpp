#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include "Sezon.h"
#include "SezonLoader.h"
#include "Utilitati.h"
#include "Exceptii.h"
#include "Guard.h"
#include "Forward.h"
#include "Center.h"

int main() {
    std::vector<std::string> fisiere;
    for (const auto& entry : std::filesystem::directory_iterator("data/seasons/")) {
        if (entry.path().extension() == ".json") {
            fisiere.push_back(entry.path().string());
        }
    }
    std::sort(fisiere.begin(), fisiere.end());

    std::vector<Sezon> season;
    for (const auto& fisier : fisiere) {
        try {
            season.push_back(SezonLoader::incarcaDinFisier(fisier));
        } catch (const FisierException& e) {
            std::cerr << "[SKIP] " << e.what() << "\n";
        } catch (const JucatorException& e) {
            std::cerr << "[SKIP] " << e.what() << "\n";
        }
    }

    while (true) {
        std::cout << "\n=== Simulator NBA ===\n";
        std::cout << "Sezoane disponibile:\n";
        for (auto i = 0u; i < season.size(); i++)
            std::cout << "  " << season[i].getAn() << "\n";
        std::cout << "\nIntroduceti anul sezonului (ex: 1995-96) sau 'exit' pentru iesire: ";

        std::string input;
        std::cin >> input;

        if (input == "exit") break;

        try {
            bool gasit = false;
            for (const auto& sezon : season) {
                if (sezon.getAn() == input) {
                    gasit = true;
                    std::cout << "\n" << sezon << "\n";
                    sezon.afiseazaClassament();

                    const Player& best = sezon.getCelMaiBunJucatorDinSezon();
                    std::cout << "\nCel mai bun jucator: " << best.getName() << "\n";

                    // dynamic_cast pentru a afisa informatii specifice pozitiei
                    if (const Guard* g = dynamic_cast<const Guard*>(&best)) {
                        std::cout << "  3PT%: " << g->getThreePointPercentage() * 100.0 << "%"
                                  << " | Role Score: " << g->calculateRoleScore() << "\n";
                    } else if (const Forward* f = dynamic_cast<const Forward*>(&best)) {
                        std::cout << "  FG%: " << f->getFieldGoalPercentage() * 100.0 << "%"
                                  << " | Role Score: " << f->calculateRoleScore() << "\n";
                    } else if (const Center* c = dynamic_cast<const Center*>(&best)) {
                        std::cout << "  BLK: " << c->getBlocksPerGame()
                                  << " | Role Score: " << c->calculateRoleScore() << "\n";
                    }

                    std::cout << "Favorita la titlu: "
                              << sezon.getEchipaFavorita().getNume() << "\n";

                    // STL: afisare echipe dupa conferinta cu std::map
                    auto conferinte = sezon.getEchipeDupaConferinta();
                    std::cout << "\nEchipe dupa conferinta:\n";
                    for (const auto& [conf, echipaList] : conferinte)
                        std::cout << "  " << conf << ": " << echipaList.size() << " echipe\n";

                    break;
                }
            }
            if (!gasit)
                throw SezonException(input);
        } catch (const SezonException& e) {
            std::cerr << e.what() << "\n";
        }
    }

    std::cout << "\n--- Test Contract ---\n";
    Contract c1(30.14, 1, "MAX");
    Contract c2 = c1;
    Contract c3(1.0, 1, "ROOKIE");
    c3 = c1;
    std::cout << "Tip: " << c1.getType() << "\n";
    std::cout << "Durata: " << c1.getDurationYears() << " ani\n";
    std::cout << "Este MAX: " << c1.isMaxContract() << "\n";
    std::cout << "Valoare ramasa: " << c1.getRemainingValue(0) << "\n";
    std::cout << "Salariu/an: " << c1.getSalaryPerYear() << "\n";

    std::cout << "\n--- Test Player ---\n";
    Guard p("Test Player", 25, "PG", 20.0, 5.0, 5.0, c1, 0.38);
    std::cout << "Pozitie: " << p.getPosition() << "\n";
    std::cout << "Puncte: " << p.getPointsPerGame() << "\n";
    std::cout << "Recuperari: " << p.getReboundsPerGame() << "\n";
    std::cout << "Impact score: " << p.getImpactScore() << "\n";
    std::cout << "Contract: " << p.getContract() << "\n";
    std::cout << "Role Score: " << p.calculateRoleScore() << "\n";
    std::cout << "Total jucatori creati: " << Player::getTotalJucatori() << "\n";

    std::cout << "\n--- Test Echipa ---\n";
    if (!season.empty() && !season[0].getEchipe().empty()) {
        const Echipa& e = season[0].getEchipe()[0];
        std::cout << "Oras: " << e.getOras() << "\n";
        std::cout << "Salary Cap: " << e.getSalaryCap() << "\n";
        std::cout << "Nr jucatori: " << e.getRoster().size() << "\n";
    }

    std::cout << "\n--- Test Sezon ---\n";
    if (!season.empty()) {
        std::cout << "Nr echipe: " << season[0].getNrEchipe() << "\n";

        // STL: test getEchipeDupaConferinta
        auto conferinte = season[0].getEchipeDupaConferinta();
        for (const auto& [conf, echipaList] : conferinte)
            std::cout << conf << ": " << echipaList.size() << " echipe\n";
    }
    std::cout << "Varsta: " << p.getAge() << "\n";
    std::cout << "Pase: " << p.getAssistsPerGame() << "\n";

    if (!season.empty()) {
        std::cout << "Campioana: " << season[0].getCampioana() << "\n";
    }
    if (!season.empty() && !season[0].getEchipe().empty()) {
        std::cout << "Conferinta: " << season[0].getEchipe()[0].getConferinta() << "\n";
    }

    std::cout << "\n--- Test Utilitati ---\n";
    std::cout << Utilitati::formatSalary(30.14) << "\n";
    std::cout << Utilitati::formatStatLine(30.4, 4.3, 6.6) << "\n";
    std::cout << "Pozitie valida: " << Utilitati::isValidPosition("PG") << "\n";
    std::cout << "Sezon valid: " << Utilitati::isValidSeason("1995-96") << "\n";
    std::cout << "Salariu valid: " << Utilitati::isValidSalary(30.14) << "\n";
    std::cout << "Tip contract valid: " << Utilitati::isValidContractType("MAX") << "\n";

    std::cout << "\n--- Test Exceptii ---\n";
    try {
        throw JucatorException("Test Player", "pozitie invalida: XX");
    } catch (const NBAException& e) {
        std::cout << "NBAException prins: " << e.what() << "\n";
    }

    try {
        throw FisierException("fisier_inexistent.json");
    } catch (const NBAException& e) {
        std::cout << "NBAException prins: " << e.what() << "\n";
    }

    return 0;
}