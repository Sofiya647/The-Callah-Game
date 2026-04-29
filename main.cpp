#include "Board.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include <iostream>
#include <fstream>
#include <windows.h> 

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    if (argc != 3) {
        std::cerr << "Использование: " << argv[0] << " <входной_файл> <выходной_файл>\n";
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile(argv[2]);

    if (!inputFile || !outputFile) {
        std::cerr << "Ошибка открытия файлов.\n";
        return 1;
    }

    // Игра начинается с 4 камнями в каждой малой лунке
    Board board;

    HumanPlayer human(0, "Человек", std::cin);
    AIPlayer ai(1, "Компьютер", 6); // Указываем глубину поиска

    Player* currentPlayer = &human;
    Player* otherPlayer = &ai;

    

    int turnCount = 1;

    while (!board.isGameOver()) {
        outputFile << "Ход " << turnCount++ << ":\n";
        board.printBoard(outputFile);
        board.printBoard(std::cout);

        int move = currentPlayer->chooseMove(board);
        bool extraTurn = board.makeMove(currentPlayer->getId(), move);

        if (!extraTurn) {
            std::swap(currentPlayer, otherPlayer);
        }
    }

    board.collectRemaining();
    outputFile << "Игра окончена.\n";
    board.printBoard(outputFile);
    board.printBoard(std::cout);

    int score0 = board.getPlayerScore(0);
    int score1 = board.getPlayerScore(1);
    outputFile << "Итоговый счёт: Человек " << score0 << " — " << score1 << " Компьютер\n";
    std::cout << "Итоговый счёт: Человек " << score0 << " — " << score1 << " Компьютер\n";

    if (score0 > score1)
        std::cout << "Победил Человек!\n";
    else if (score1 > score0)
        std::cout << "Победил Компьютер!\n";
    else
        std::cout << "Ничья!\n";

    return 0;
}