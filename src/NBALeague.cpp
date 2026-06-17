#include "NBALeague.h"
#include "SezonLoader.h"
#include "Exceptii.h"
#include <filesystem>
#include <algorithm>
#include <iostream>

// cppcheck-suppress unusedFunction
NBALeague& NBALeague::getInstance() {
    static NBALeague instanta;
    return instanta;
}

// cppcheck-suppress unusedFunction
void NBALeague::incarcaSezoane(const std::string& folder) {
    if (incarcat)
        return;  // deja incarcate, nu reincarca

    std::vector<std::string> fisiere;
    for (const auto& entry : std::filesystem::directory_iterator(folder)) {
        if (entry.path().extension() == ".json")
            fisiere.push_back(entry.path().string());
    }
    std::sort(fisiere.begin(), fisiere.end());

    for (const auto& fisier : fisiere) {
        try {
            sezoane.push_back(SezonLoader::incarcaDinFisier(fisier));
        } catch (const FisierException& e) {
            std::cerr << "[SKIP] " << e.what() << "\n";
        } catch (const JucatorException& e) {
            std::cerr << "[SKIP] " << e.what() << "\n";
        }
    }

    incarcat = true;
}

// cppcheck-suppress unusedFunction
const std::vector<Sezon>& NBALeague::getSezoane() const {
    return sezoane;
}

// cppcheck-suppress unusedFunction
const Sezon* NBALeague::gasesteSezon(const std::string& an) const {
    for (const auto& sezon : sezoane)
        if (sezon.getAn() == an)
            return &sezon;
    return nullptr;
}