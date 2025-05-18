/* ----------------------------------------------------------------<Header>-
 * Name: board.h
 * Title: Board Class Definition
 * Group: TV-41
 * Student: Bilyk Oleksandr
 * Written: 2025-04-29
 * Revised: 2025-04-29
* Description: Defines the game board and its properties, including cell
 ------------------------------------------------------------------</Header>-*/

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
    /* ---------------------------------------------------------------------[<]-
     * Function: getCellNumber
     * Synopsis: Gets the letter (A or S) assigned to the cell at given coordinates
     * Parameters: x - x coordinate of the cell
     *            y - y coordinate of the cell
     * Returns: Character ('A' or 'S') if cell has a letter, space character otherwise
     ---------------------------------------------------------------------[>]-*/
    char getCellNumber(int x, int y) const;
    bool isBlockSymmetric(int blockId) const;
    bool isBlockAsymmetric(int blockId) const;
    std::vector<std::pair<int, int>> getCellsInBlock(int blockId) const;
    int countFilledCellsInBlock(int blockId) const;
    bool checkAllRules() const;


    bool checkContinuityRule() const;  // Правило целостности незакрашенных клеток
    bool checkNumbersRule() const;     // Правило соответствия чисел в блоках
    bool checkAdjacentRule() const;    // Правило о неприкосновении закрашенных клеток
    bool checkCrossingRule() const;    // Правило о непрерывных линиях
    bool checkSymmetryRules() const;   // Правила симметрии/асимметрии

private:
    int width;
    int height;
    std::vector<std::vector<Cell>> cells;     
};

#endif // BOARD_H