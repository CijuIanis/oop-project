#pragma once
#include <string>

namespace Utilitati {
    bool isValidPosition(const std::string& position);
    bool isValidSeason(const std::string& season);
    bool isValidSalary(double salary);
    bool isValidContractType(const std::string& type);
    //slariu (ex: 30.14 -> "$30.14M")
    std::string formatSalary(double salary);
    // stats (ex: "30.4pts | 4.3ast | 6.6reb")
    std::string formatStatLine(double ppg, double apg, double rpg);
}