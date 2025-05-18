/* ----------------------------------------------------------------<Header>-
 * Name: board.cpp
 * Title: Board Class Implementation
 * Group: TV-41
 * Student: Bilyk Oleksandr
 * Written: 2025-04-30
 * Revised: 2025-04-30
 * Description: Implements the game board functionality for a puzzle solver,
 *             including cell management, rule checking and block operations
 ------------------------------------------------------------------</Header>-*/

#include "board.h"
#include <queue>
#include <set>

/* ---------------------------------------------------------------------[<]-
 * Function: Board::Board
 * Synopsis: Constructor that initializes the game board with given dimensions
 * Parameters: width - board width
 *            height - board height
 ---------------------------------------------------------------------[>]-*/
Board::Board(int width, int height) : width(width), height(height) {
    cells.resize(height, std::vector<Cell>(width));
}

/* ---------------------------------------------------------------------[<]-
 * Function: Board::initialize
 * Synopsis: Initializes the game board, setting all cells to their default state
 ---------------------------------------------------------------------[>]-*/
void Board::initialize() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            cells[y][x].setFilled(false);
            cells[y][x].setBlockId(-1);
            cells[y][x].setHasNumber(false);
            cells[y][x].setIsSymmetry(false);
            cells[y][x].setIsAsymmetry(false);
        }
    }
}

/* ---------------------------------------------------------------------[<]-
 * Function: Board::setCell
 * Synopsis: Sets the filled state of a specific cell on the board
 * Parameters: x - x-coordinate of the cell
 *            y - y-coordinate of the cell
 *            filled - new filled state for the cell
 ---------------------------------------------------------------------[>]-*/
void Board::setCell(int x, int y, bool filled) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        cells[y][x].setFilled(filled);
    }
}

/* ---------------------------------------------------------------------[<]-
 * Function: Board::getCell
 * Synopsis: Gets the filled state of a specific cell on the board
 * Parameters: x - x-coordinate of the cell
 *            y - y-coordinate of the cell
 * Returns: Filled state of the cell
 ---------------------------------------------------------------------[>]-*/
bool Board::getCell(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return cells[y][x].isFilled();
    }
    return false; // Out of bounds
}

/* ---------------------------------------------------------------------[<]-
 * Function: Board::setBlockId
 * Synopsis: Sets the block ID of a specific cell on the board
 * Parameters: x - x-coordinate of the cell
 *            y - y-coordinate of the cell
 *            blockId - new block ID for the cell
 ---------------------------------------------------------------------[>]-*/
void Board::setBlockId(int x, int y, int blockId) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        cells[y][x].setBlockId(blockId);
    }
}

/* ---------------------------------------------------------------------[<]-
 * Function: Board::setCellNumber
 * Synopsis: Sets the number and type (symmetric/asymmetric) of a specific cell
 * Parameters: x - x-coordinate of the cell
 *            y - y-coordinate of the cell
 *            type - type of the cell ('S' for symmetric, 'A' for asymmetric)
 *            value - numeric value to be set to the cell
 ---------------------------------------------------------------------[>]-*/
void Board::setCellNumber(int x, int y, char type, int value) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        cells[y][x].setHasNumber(true);
        cells[y][x].setValue(value);
        
        // Встановлюємо тип блоку (S - симетричний, A - асиметричний)
        if (type == 'S') {
            cells[y][x].setIsSymmetry(true);
        } else if (type == 'A') {
            cells[y][x].setIsAsymmetry(true);
        }
    }
}

/* ---------------------------------------------------------------------[<]-
 * Function: Board::getCellsInBlock
 * Synopsis: Retrieves all cells belonging to a specific block
 * Parameters: blockId - ID of the block
 * Returns: Vector of coordinates representing cells in the block
 ---------------------------------------------------------------------[>]-*/
std::vector<std::pair<int, int>> Board::getCellsInBlock(int blockId) const {
    std::vector<std::pair<int, int>> blockCells;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (cells[y][x].getBlockId() == blockId) {
                blockCells.push_back(std::make_pair(x, y));
            }
        }
    }
    return blockCells;
}

/* ---------------------------------------------------------------------[<]-
 * Function: Board::countFilledCellsInBlock
 * Synopsis: Counts the number of filled cells in a specific block
 * Parameters: blockId - ID of the block
 * Returns: Number of filled cells in the block
 ---------------------------------------------------------------------[>]-*/
int Board::countFilledCellsInBlock(int blockId) const {
    int count = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (cells[y][x].getBlockId() == blockId && cells[y][x].isFilled()) {
                count++;
            }
        }
    }
    return count;
}

/* ---------------------------------------------------------------------[<]-
 * Function: Board::isBlockSymmetric
 * Synopsis: Checks if a specific block is symmetric
 * Parameters: blockId - ID of the block
 * Returns: True if the block is symmetric, false otherwise
 ---------------------------------------------------------------------[>]-*/
bool Board::isBlockSymmetric(int blockId) const {
    auto blockCells = getCellsInBlock(blockId);
    if (blockCells.empty()) return false;
    
    // Найдем центр блока
    int minX = width, minY = height, maxX = 0, maxY = 0;
    for (const auto& cell : blockCells) {
        minX = std::min(minX, cell.first);
        minY = std::min(minY, cell.second);
        maxX = std::max(maxX, cell.first);
        maxY = std::max(maxY, cell.second);
    }
    
    int centerX = (minX + maxX) / 2; (void)centerX;
    int centerY = (minY + maxY) / 2; (void)centerY;
    
    // Проверим симметрию относительно центра
    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            if (cells[y][x].getBlockId() == blockId) {
                // Вычисляем симметричную точку
                int symX = maxX - (x - minX);
                int symY = maxY - (y - minY);
                
                // Проверяем, что она в том же блоке и имеет то же состояние заполнения
                if (symX >= 0 && symX < width && symY >= 0 && symY < height) {
                    if (cells[symY][symX].getBlockId() != blockId || 
                        cells[y][x].isFilled() != cells[symY][symX].isFilled()) {
                        return false;
                    }
                } else {
                    return false;
                }
            }
        }
    }
    return true;
}

/* ---------------------------------------------------------------------[<]-
 * Function: Board::isBlockAsymmetric
 * Synopsis: Checks if a specific block is asymmetric
 * Parameters: blockId - ID of the block
 * Returns: True if the block is asymmetric, false otherwise
 ---------------------------------------------------------------------[>]-*/
bool Board::isBlockAsymmetric(int blockId) const {
    return !isBlockSymmetric(blockId);
}

/* ---------------------------------------------------------------------[<]-
 * Function: Board::checkContinuityRule
 * Synopsis: Checks the continuity rule for the puzzle
 * Returns: True if the rule is satisfied, false otherwise
 ---------------------------------------------------------------------[>]-*/
bool Board::checkContinuityRule() const {
    // Перевірка цілісності незафарбованих клітинок за допомогою BFS
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    
    // Знаходимо першу незафарбовану клітинку
    int startX = -1, startY = -1;
    for (int y = 0; y < height && startX == -1; ++y) {
        for (int x = 0; x < width; ++x) {
            if (!cells[y][x].isFilled()) {
                startX = x;
                startY = y;
                break;
            }
        }
    }
    
    if (startX == -1) return false; // Нет незакрашенных клеток
    
    // BFS
    std::queue<std::pair<int, int>> q;
    q.push({startX, startY});
    visited[startY][startX] = true;
    
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && nx < width && ny >= 0 && ny < height && 
                !cells[ny][nx].isFilled() && !visited[ny][nx]) {
                visited[ny][nx] = true;
                q.push({nx, ny});
            }
        }
    }
    
    // Проверяем, что все незакрашенные клетки были посещены
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (!cells[y][x].isFilled() && !visited[y][x]) {
                return false;
            }
        }
    }
    
    return true;
}

/* ---------------------------------------------------------------------[<]-
 * Function: Board::checkAdjacentRule
 * Synopsis: Checks the adjacent rule for the puzzle
 * Returns: True if the rule is satisfied, false otherwise
 ---------------------------------------------------------------------[>]-*/
bool Board::checkAdjacentRule() const {
    // Проверка, что закрашенные клетки не касаются сторонами
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (cells[y][x].isFilled()) {
                // Проверяем соседей по сторонам
                int dx[] = {0, 0, 1, -1};
                int dy[] = {1, -1, 0, 0};
                
                for (int i = 0; i < 4; ++i) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height && 
                        cells[ny][nx].isFilled()) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

/* ---------------------------------------------------------------------[<]-
 * Function: Board::checkNumbersRule
 * Synopsis: Checks the numbers rule for the puzzle
 * Returns: True if the rule is satisfied, false otherwise
 ---------------------------------------------------------------------[>]-*/
bool Board::checkNumbersRule() const {
    std::set<int> checkedBlocks;
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int blockId = cells[y][x].getBlockId();
            if (blockId != -1 && cells[y][x].hasNumber() && checkedBlocks.find(blockId) == checkedBlocks.end()) {
                int expectedFilled = cells[y][x].getValue();
                int actualFilled = countFilledCellsInBlock(blockId);
                
                if (expectedFilled != actualFilled) {
                    return false;
                }
                
                checkedBlocks.insert(blockId);
            }
        }
    }
    
    return true;
}

/* ---------------------------------------------------------------------[<]-
 * Function: Board::checkCrossingRule
 * Synopsis: Checks the crossing rule for the puzzle
 * Returns: True if the rule is satisfied, false otherwise
 ---------------------------------------------------------------------[>]-*/
bool Board::checkCrossingRule() const {
    // Проверяем каждую строку
    for (int y = 0; y < height; ++y) {
        bool foundFilled = false;  // Нашли закрашенную клетку
        bool foundEmpty = false;   // Нашли пустую клетку после закрашенной
        
        for (int x = 0; x < width; ++x) {
            if (cells[y][x].isFilled()) {
                if (foundEmpty) {
                    // Если нашли закрашенную клетку после пустой,
                    // значит есть разрыв в линии - правило нарушено
                    return false;
                }
                foundFilled = true;
            } else {
                // Незакрашенная клетка
                if (foundFilled) {
                    foundEmpty = true;
                }
            }
        }
    }
    
    // Проверяем каждый столбец
    for (int x = 0; x < width; ++x) {
        bool foundFilled = false;
        bool foundEmpty = false;
        
        for (int y = 0; y < height; ++y) {
            if (cells[y][x].isFilled()) {
                if (foundEmpty) {
                    // Если нашли закрашенную клетку после пустой,
                    // значит есть разрыв в линии - правило нарушено
                    return false;
                }
                foundFilled = true;
            } else {
                // Незакрашенная клетка
                if (foundFilled) {
                    foundEmpty = true;
                }
            }
        }
    }
    
    return true;
}

/* ---------------------------------------------------------------------[<]-
 * Function: Board::getCellNumber
 * Synopsis: Retrieves the numeric value of a specific cell
 * Parameters: x - x-coordinate of the cell
 *            y - y-coordinate of the cell
 * Returns: Numeric value of the cell, 0 if not set
 ---------------------------------------------------------------------[>]-*/
char Board::getCellNumber(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height && cells[y][x].hasNumber()) {
        return static_cast<char>(cells[y][x].getValue());
    }
    return 0;
}

/* ---------------------------------------------------------------------[<]-
 * Function: Board::checkSymmetryRules
 * Synopsis: Checks the symmetry rules for the puzzle
 * Returns: True if the rules are satisfied, false otherwise
 ---------------------------------------------------------------------[>]-*/
bool Board::checkSymmetryRules() const {
    std::set<int> checkedBlocks;
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int blockId = cells[y][x].getBlockId();
            if (blockId != -1 && checkedBlocks.find(blockId) == checkedBlocks.end()) {
                if (cells[y][x].isSymmetry() && !isBlockSymmetric(blockId)) {
                    return false;
                } else if (cells[y][x].isAsymmetry() && isBlockSymmetric(blockId)) {
                    return false;
                }
                
                checkedBlocks.insert(blockId);
            }
        }
    }
    
    return true;
}

/* ---------------------------------------------------------------------[<]-
 * Function: Board::isSolved
 * Synopsis: Checks if the puzzle is solved
 * Returns: True if the puzzle is solved, false otherwise
 ---------------------------------------------------------------------[>]-*/
bool Board::isSolved() const {
    return checkContinuityRule() && 
           checkAdjacentRule() &&
           checkNumbersRule() &&
           checkCrossingRule() &&
           checkSymmetryRules();
}