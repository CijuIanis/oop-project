#pragma once
#include <stdexcept>
#include <string>

// baza de exceptii NBA
class NBAException : public std::exception {
protected:
    std::string mesaj;
public:
    explicit NBAException(const std::string& mesaj) : mesaj(mesaj) {}
    const char* what() const noexcept override { return mesaj.c_str(); }
};

// eroare la citirea/deschiderea fisierelor JSON
class FisierException : public NBAException {
public:
    explicit FisierException(const std::string& caleFisier)
        : NBAException("Eroare la fisier: " + caleFisier) {}
};

// eroare la datele unui jucator
class JucatorException : public NBAException {
public:
    explicit JucatorException(const std::string& numeJucator, const std::string& motiv)
        : NBAException("Eroare jucator '" + numeJucator + "': " + motiv) {}
};

// eroare un sezon este negasit
class SezonException : public NBAException {
public:
    explicit SezonException(const std::string& an)
        : NBAException("Sezonul '" + an + "' nu a fost gasit!") {}
};