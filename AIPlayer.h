// AIPlayer.h
#pragma once
#include "Player.h"
#include <random>
#include <vector>

class AIPlayer : public Player {
    mutable std::mt19937 rng;
    int maxDepth; // Максимальная глубина поиска

public:
    AIPlayer(int id, const std::string& name, int depth = 6); // Добавляем параметр глубины
    int chooseMove(const Board& board) override;

private:
    // Вспомогательные функции для минимакса
    int minimax(const Board& board, int depth, bool isMaximizing, int alpha, int beta) const;
    int evaluate(const Board& board) const;
    std::vector<int> getValidMoves(const Board& board) const;
};