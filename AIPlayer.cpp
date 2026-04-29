// AIPlayer.cpp
#include "AIPlayer.h"
#include "Board.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

AIPlayer::AIPlayer(int id, const std::string& name, int depth)
    : Player(id, name), rng(std::random_device{}()), maxDepth(depth) {
}

int AIPlayer::chooseMove(const Board& board) {
    auto validMoves = getValidMoves(board);
    if (validMoves.empty()) {
        return -1;
    }

    int bestMove = validMoves[0];
    int bestValue = INT_MIN;

    std::cout << name << " анализирует позицию...\n";

    // Перебираем все возможные ходы
    for (int move : validMoves) {
        Board tempBoard = board; // Создаем копию доски
        bool extraTurn = tempBoard.makeMove(id, move);

        // Если это не дополнительный ход, то следующий игрок — противник
        int currentValue = minimax(tempBoard, maxDepth - 1, !extraTurn, INT_MIN, INT_MAX);

        if (currentValue > bestValue) {
            bestValue = currentValue;
            bestMove = move;
        }
    }

    std::cout << name << " выбирает лунку " << (bestMove + 1) << " (оценка: " << bestValue << ")\n";
    return bestMove;
}

int AIPlayer::minimax(const Board& board, int depth, bool isMaximizing, int alpha, int beta) const {
    // Базовый случай: игра окончена или достигнута максимальная глубина
    if (board.isGameOver() || depth == 0) {
        return evaluate(board);
    }

    auto validMoves = getValidMoves(board);
    if (validMoves.empty()) {
        return evaluate(board); // Нет ходов — оцениваем текущую позицию
    }

    if (isMaximizing) {
        int maxValue = INT_MIN;
        for (int move : validMoves) {
            Board tempBoard = board;
            bool extraTurn = tempBoard.makeMove(id, move);

            int value = minimax(tempBoard, depth - 1, !extraTurn, alpha, beta);
            maxValue = std::max(maxValue, value);
            alpha = std::max(alpha, maxValue);

            // Альфа-бета отсечение
            if (beta <= alpha) {
                break;
            }
        }
        return maxValue;
    }
    else {
        int minValue = INT_MAX;
        for (int move : validMoves) {
            Board tempBoard = board;
            bool extraTurn = tempBoard.makeMove(1 - id, move); // Ходит противник

            int value = minimax(tempBoard, depth - 1, !extraTurn, alpha, beta);
            minValue = std::min(minValue, value);
            beta = std::min(beta, minValue);

            // Альфа-бета отсечение
            if (beta <= alpha) {
                break;
            }
        }
        return minValue;
    }
}

int AIPlayer::evaluate(const Board& board) const {
    // Статическая оценочная функция: разница очков между игроком и противником
    int myScore = board.getPlayerScore(id);
    int opponentScore = board.getPlayerScore(1 - id);

    // Дополнительно можно учитывать количество камней в малых лунках,
    // но для начала простая разница работает хорошо.
    return myScore - opponentScore;
}

std::vector<int> AIPlayer::getValidMoves(const Board& board) const {
    std::vector<int> moves;
    for (int i = 0; i < 6; ++i) {
        int idx = (id == 0) ? i : (i + 7);
        if (board.pits[idx] > 0) {
            moves.push_back(i);
        }
    }
    return moves;
}
