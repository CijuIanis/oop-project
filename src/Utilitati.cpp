#include "Utilitati.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

namespace Utilitati {

    bool isValidPosition(const std::string& position) {
        return position == "PG" || position == "SG" || position == "SF" ||
               position == "PF" || position == "C";
    }

    bool isValidSeason(const std::string& season) {
        // Format asteptat(ex: "1995-96")
        if (season.size() != 7) return false;
        if (season[4] != '-') return false;
        for (int i = 0; i < 4; i++)
            if (season[i] < '0' || season[i] > '9') return false;
        for (int i = 5; i < 7; i++)
            if (season[i] < '0' || season[i] > '9') return false;
        return true;
    }

    bool isValidSalary(double salary) {
        return salary > 0.0;
    }

    bool isValidContractType(const std::string& type) {
        return type == "MAX" || type == "MID" || type == "ROOKIE" || type == "MINIMUM";
    }

    std::string formatSalary(double salary) {
        std::ostringstream oss;
        oss << "$" << std::fixed << std::setprecision(2) << salary << "M";
        return oss.str();
    }

    std::string formatStatLine(double ppg, double apg, double rpg) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1)
            << ppg << "pts | " << apg << "ast | " << rpg << "reb";
        return oss.str();
    }

}