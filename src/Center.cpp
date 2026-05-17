#include "Center.h"
#include <sstream>
#include <iomanip>

Center::Center(const std::string& name, int age, const std::string& position,
               double ppg, double apg, double rpg, const Contract& contract,
               double blocksPerGame)
    : Player(name, age, position, ppg, apg, rpg, contract),
      blocksPerGame(blocksPerGame) {}

Center* Center::clone() const {
    return new Center(*this);
}

double Center::calculateRoleScore() const {
    return reboundsPerGame * 2.0 + blocksPerGame * 3.0 + pointsPerGame * 0.5;
}

// cppcheck-suppress unusedFunction
double Center::getBlocksPerGame() const {
    return blocksPerGame;
}

void Center::print(std::ostream& os) const {
    Player::print(os);
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << blocksPerGame;
    os << "\n  [Center] BLK: " << oss.str() << " | Role Score: " << calculateRoleScore();
}