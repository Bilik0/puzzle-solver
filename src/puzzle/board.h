#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include <vector>
#include <string>

class Board {
public:
    Board(int width, int height);
    void initialize();
    void setCell(int x, int y, bool filled);
    bool getCell(int x, int y) const;
    bool isSolved() const;
    
    // Методы для работы с блоками и правилами
    void setBlockId(int x, int y, int blockId);
    void setCellNumber(int x, int y, char type, int value = 0);
    bool isBlockSymmetric(int blockId) const;
    bool isBlockAsymmetric(int blockId) const;
    std::vector<std::pair<int, int>> getCellsInBlock(int blockId) const;
    int countFilledCellsInBlock(int blockId) const;
    bool checkAllRules() const;

private:
    int width;
    int height;
    std::vector<std::vector<Cell>> cells;
    
    bool checkContinuityRule() const;  // Правило целостности незакрашенных клеток
    bool checkNumbersRule() const;     // Правило соответствия чисел в блоках
    bool checkAdjacentRule() const;    // Правило о неприкосновении закрашенных клеток
    bool checkCrossingRule() const;    // Правило о непрерывных линиях
    bool checkSymmetryRules() const;   // Правила симметрии/асимметрии
};

#endif // BOARD_H