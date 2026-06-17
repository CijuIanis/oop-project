#pragma once
#include <vector>
#include <string>
#include "Sezon.h"

// Singleton: punctul central de acces la toate sezoanele ligii.
class NBALeague {
private:
    std::vector<Sezon> sezoane;
    bool incarcat = false;

    NBALeague() = default;

public:
    NBALeague(const NBALeague&) = delete;
    NBALeague& operator=(const NBALeague&) = delete;
    NBALeague(NBALeague&&) = delete;
    NBALeague& operator=(NBALeague&&) = delete;

    static NBALeague& getInstance();

    // incarc toate sezoanele o singura data
    void incarcaSezoane(const std::string& folder = "data/seasons/");

    const std::vector<Sezon>& getSezoane() const;
    const Sezon* gasesteSezon(const std::string& an) const;
};