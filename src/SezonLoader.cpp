#include "SezonLoader.h"
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Sezon SezonLoader::incarcaDinFisier(const std::string& caleFisier) {
    std::ifstream fisier(caleFisier);
    if (!fisier.is_open())
        throw std::runtime_error("Nu s-a putut deschide fisierul: " + caleFisier);

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
            Contract contract(
                jJson["contract"]["salariu"],
                jJson["contract"]["durata"],
                jJson["contract"]["tip"]
            );

            Player jucator(
                jJson["nume"],
                jJson["varsta"],
                jJson["pozitie"],
                jJson["ppg"],
                jJson["apg"],
                jJson["rpg"],
                contract
            );

            echipa.adaugaJucator(jucator);
        }

        sezon.adaugaEchipa(echipa);
    }

    return sezon;
}