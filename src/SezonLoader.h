#pragma once
#include <string>
#include "Sezon.h"

class SezonLoader {
public:
    static Sezon incarcaDinFisier(const std::string& caleFisier);
};