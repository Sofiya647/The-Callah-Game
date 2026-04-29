#include "Board.h"
#include <iostream>
#include <cassert>

Board::Board() : pits(TOTAL_PITS, 4) {
    pits[KALAH_0] = 0;
    pits[KALAH_1] = 0;
}

void Board::printBoard(std::ostream& out) const {
    out << "        ";
    for (int i = 12; i >= 7; --i)
        out << "[" << pits[i] << "] ";
    out << "\n";
    out << "[" << pits[KALAH_1] << "]                                  [" << pits[KALAH_0] << "]\n";
    out << "        ";
    for (int i = 0; i < 6; ++i)
        out << "[" << pits[i] << "] ";
    out << "\n\n";
}

bool Board::isGameOver() const {
    bool p0Empty = true, p1Empty = true;
    for (int i = 0; i < 6; ++i)
        if (pits[i] > 0) p0Empty = false;
    for (int i = 7; i < 13; ++i)
        if (pits[i] > 0) p1Empty = false;
    return p0Empty || p1Empty;
}

int Board::getPlayerScore(int player) const {
    return pits[player == 0 ? KALAH_0 : KALAH_1];
}

bool Board::makeMove(int player, int pitIndex) {
    assert(pitIndex >= 0 && pitIndex < 6);
    int start = player == 0 ? pitIndex : pitIndex + 7;
    if (pits[start] == 0) return false;

    int seeds = pits[start];
    pits[start] = 0;
    int pos = start;

    while (seeds > 0) {
        pos = (pos + 1) % TOTAL_PITS; //переход к следующей лунке
        if ((player == 0 && pos == KALAH_1) || (player == 1 && pos == KALAH_0))
            continue;
        pits[pos]++;
        seeds--;
    }

    
    if (player == 0) {
        
        if (pos >= 7 && pos <= 12 && (pits[pos] == 2 || pits[pos] == 3)) {
            pits[KALAH_0] += pits[pos];
            pits[pos] = 0;
        }
    }
    else {
        
        if (pos >= 0 && pos <= 5 && (pits[pos] == 2 || pits[pos] == 3)) {
            pits[KALAH_1] += pits[pos];
            pits[pos] = 0;
        }
    }

    
    bool extraTurn = (player == 0 && pos == KALAH_0) || (player == 1 && pos == KALAH_1);
    return extraTurn;
}

void Board::collectRemaining() { 
    for (int i = 0; i < 6; ++i) {
        pits[KALAH_0] += pits[i];
        pits[i] = 0;
    }
    for (int i = 7; i < 13; ++i) {
        pits[KALAH_1] += pits[i];
        pits[i] = 0;
    }
}