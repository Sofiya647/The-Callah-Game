#pragma once
#include "Player.h"
#include <istream>

class HumanPlayer : public Player {
    std::istream& input;
public:
    HumanPlayer(int id, const std::string& name, std::istream& in)
        : Player(id, name), input(in) {
    }
    int chooseMove(const Board& board) override;
};
