#include "HumanPlayer.h"
#include "Board.h"
#include <iostream>

int HumanPlayer::chooseMove(const Board& board) {
    int pit;
    while (true) {
        std::cout << name << ", выберите лунку (1-6): ";
        input >> pit;
        if (pit >= 1 && pit <= 6) {
            int idx = pit - 1;
            if ((id == 0 && board.pits[idx] > 0) ||
                (id == 1 && board.pits[idx + 7] > 0)) {
                return pit - 1;
            }
        }
        std::cout << "Неверный ход. Лунка пуста или не существует.\n";
    }
}
