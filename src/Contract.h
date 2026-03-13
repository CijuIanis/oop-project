#pragma once
#include <string>
#include <ostream>

class Contract {
private:
    double salaryPerYear;
    int durationYears;
    std::string type;

public:
    Contract(double salaryPerYear, int durationYears, const std::string& type);
    Contract(const Contract& other);
    Contract& operator=(const Contract& other);
    ~Contract();

    double getSalaryPerYear() const;
    int getDurationYears() const;
    const std::string& getType() const;
    double getTotalValue() const;

    bool isMaxContract() const;
    double getRemainingValue(int yearsPlayed) const;

    friend std::ostream& operator<<(std::ostream& os, const Contract& contract);
};