#pragma once
#include <string>

class Board;

class Player {
protected:
    int id;
    std::string name;
public:
    Player(int playerId, const std::string& playerName) : id(playerId), name(playerName) {}
    virtual ~Player() = default;
    virtual int chooseMove(const Board& board) = 0;
    int getId() const { return id; }
    const std::string& getName() const { return name; }
};