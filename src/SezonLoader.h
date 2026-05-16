#pragma once
#include <string>
#include "Sezon.h"

class SezonLoader {
public:
    Sezon incarcaDinFisier(const std::string& caleFisier) const;
};