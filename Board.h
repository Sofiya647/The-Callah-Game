#pragma once
#include <vector>
#include <iostream>

class Board {
public:
    static const int PITS_PER_PLAYER = 6;
    static const int TOTAL_PITS = 14;
    static const int KALAH_0 = 6;   // калах игрока 0
    static const int KALAH_1 = 13;  // калах игрока 1

    std::vector<int> pits;

    Board(); // по умолчанию — 4 камня в каждой малой лунке

    void printBoard(std::ostream& out) const;
    bool isGameOver() const;
    int getPlayerScore(int player) const;
    bool makeMove(int player, int pitIndex);
    void collectRemaining();
};
