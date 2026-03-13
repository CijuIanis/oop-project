#include <iostream>
#include <vector>
#include <string>
#include "Sezon.h"
#include "SezonLoader.h"

int main() {
    std::vector<std::string> fisiere = {
        "data/seasons/1965-66.json",
        "data/seasons/1971-72.json",
        "data/seasons/1985-86.json",
        "data/seasons/1990-91.json",
        "data/seasons/1995-96.json",
        "data/seasons/1997-98.json",
        "data/seasons/1999-00.json",
        "data/seasons/2007-08.json",
        "data/seasons/2012-13.json",
        "data/seasons/2015-16.json",
        "data/seasons/2018-19.json",
        "data/seasons/2020-21.json",
        "data/seasons/2022-23.json"
    };

    std::vector<Sezon> season;
    for (const auto& fisier : fisiere) {
        try {
            season.push_back(SezonLoader::incarcaDinFisier(fisier));
        } catch (const std::exception& e) {
            std::cerr << "[SKIP] " << e.what() << "\n";
        }
    }

    while (true) {
        std::cout << "\n=== Simulator NBA ===\n";
        std::cout << "Sezoane disponibile:\n";
        for (int i = 0; i < (int)season.size(); i++)
            std::cout << "  " << season[i].getAn() << "\n";
        std::cout << "\nIntroduceti anul sezonului (ex: 1995-96) sau 'exit' pentru iesire: ";

        std::string input;
        std::cin >> input;

        if (input == "exit") break;

        bool gasit = false;
        for (auto& sezon : season) {
            if (sezon.getAn() == input) {
                gasit = true;
                std::cout << "\n" << sezon << "\n";
                sezon.afiseazaClassament();
                std::cout << "\nCel mai bun jucator: "
                          << sezon.getCelMaiBunJucatorDinSezon().getName() << "\n";
                std::cout << "Favorita la titlu: "
                          << sezon.getEchipaFavorita().getNume() << "\n";
                break;
            }
        }

        if (!gasit)
            std::cout << "Sezonul '" << input << "' nu a fost gasit!\n";
    }

    std::cout << "\n--- Test Contract copy ---\n";
    Contract c1(30.14, 1, "MAX");
    Contract c2 = c1;
    Contract c3(1.0, 1, "ROOKIE");
    c3 = c1;

    return 0;
}