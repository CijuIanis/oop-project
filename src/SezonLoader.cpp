#include "SezonLoader.h"
#include "Exceptii.h"
#include "Utilitati.h"
#include "Guard.h"
#include "Forward.h"
#include "Center.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Sezon SezonLoader::incarcaDinFisier(const std::string& caleFisier) {
    std::ifstream fisier(caleFisier);
    if (!fisier.is_open())
        throw FisierException(caleFisier);

    json date;
    fisier >> date;

    std::string an = date["an"];
    std::string campioana = date["campioana"];
    Sezon sezon(an, campioana);

    for (const auto& eJson : date["echipe"]) {
        Echipa echipa(
            eJson["nume"],
            eJson["oras"],
            eJson["conferinta"],
            eJson["salaryCap"]
        );

        for (const auto& jJson : eJson["jucatori"]) {
            std::string pozitie = jJson["pozitie"];
            if (!Utilitati::isValidPosition(pozitie))
                throw JucatorException(jJson["nume"], "pozitie invalida: " + pozitie);

            double salariu = jJson["contract"]["salariu"];
            if (!Utilitati::isValidSalary(salariu))
                throw JucatorException(jJson["nume"], "salariu invalid");

            Contract contract(
                salariu,
                jJson["contract"]["durata"],
                jJson["contract"]["tip"]
            );

            // Cream Guard, Forward sau Center in functie de pozitie
            if (pozitie == "PG" || pozitie == "SG") {
                echipa.adaugaJucator(Guard(
                    jJson["nume"], jJson["varsta"], pozitie,
                    jJson["ppg"], jJson["apg"], jJson["rpg"],
                    contract, 0.36
                ));
            } else if (pozitie == "SF" || pozitie == "PF") {
                echipa.adaugaJucator(Forward(
                    jJson["nume"], jJson["varsta"], pozitie,
                    jJson["ppg"], jJson["apg"], jJson["rpg"],
                    contract, 0.48
                ));
            } else {
                echipa.adaugaJucator(Center(
                    jJson["nume"], jJson["varsta"], pozitie,
                    jJson["ppg"], jJson["apg"], jJson["rpg"],
                    contract, 1.2
                ));
            }
        }

        sezon.adaugaEchipa(echipa);
    }

    return sezon;
}