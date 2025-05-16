#include "puzzle/board.h"
#include <iostream>
#include <vector>
#include <string>

// Глобальные переменные для задания головоломки
const int BOARD_SIZE = 10;

void setPuzzle(Board &board) {
    // Инициализация базовой доски
    board.initialize();
    
    // Установка блоков (указываем границы блоков)
    // Блок 0 - верхний левый угол
    board.setBlockId(0, 0, 0);
    board.setBlockId(1, 0, 0);
    board.setBlockId(2, 0, 0);
    board.setBlockId(0, 1, 0);
    board.setBlockId(1, 1, 0);
    board.setBlockId(2, 1, 0);
    board.setBlockId(0, 2, 0);
    board.setBlockId(1, 2, 0);
    board.setBlockId(2, 2, 0);
    
    // И так далее для всех блоков...
    
    // Устанавливаем цифры и типы блоков
    board.setCellNumber(3, 2, 'A'); // A в позиции (3,2)
    board.setCellNumber(5, 3, 'A'); // A в позиции (5,3)
    board.setCellNumber(0, 6, 'S'); // S в позиции (0,6)
    // И так далее для всех меток на доске
}

bool solveBacktracking(Board &board, int x, int y) {
    // Если мы достигли конца доски, проверяем решение
    if (y >= BOARD_SIZE) {
        return board.isSolved();
    }
    
    // Вычисляем следующую клетку
    int nextX = (x + 1) % BOARD_SIZE;
    int nextY = y + (x + 1) / BOARD_SIZE;
    
    // Пробуем оставить клетку незакрашенной
    board.setCell(x, y, false);
    if (solveBacktracking(board, nextX, nextY)) {
        return true;
    }
    
    // Пробуем закрасить клетку
    board.setCell(x, y, true);
    
    // Проверяем основные правила, которые можно проверить для текущей частичной доски
    // Если правила нарушены, то нет смысла продолжать решение с этой клеткой закрашенной
    
    if (solveBacktracking(board, nextX, nextY)) {
        return true;
    }
    
    // Возвращаем клетку в незакрашенное состояние (бэктрек)
    board.setCell(x, y, false);
    
    return false;
}

void printBoard(const Board &board) {
    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            if (board.getCell(x, y)) {
                std::cout << "◼ ";
            } else {
                std::cout << "□ ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    Board board(BOARD_SIZE, BOARD_SIZE);
    setPuzzle(board);
    
    std::cout << "Решаем головоломку..." << std::endl;
    
    if (solveBacktracking(board, 0, 0)) {
        std::cout << "Решение найдено!" << std::endl;
        printBoard(board);
    } else {
        std::cout << "Решения не существует!" << std::endl;
    }
    
    return 0;
}