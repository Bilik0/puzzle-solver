#include "board.h"
#include <queue>
#include <set>

Board::Board(int width, int height) : width(width), height(height) {
    cells.resize(height, std::vector<Cell>(width));
}

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

void Board::setCell(int x, int y, bool filled) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        cells[y][x].setFilled(filled);
    }
}

bool Board::getCell(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return cells[y][x].isFilled();
    }
    return false; // Out of bounds
}

void Board::setBlockId(int x, int y, int blockId) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        cells[y][x].setBlockId(blockId);
    }
}

void Board::setCellNumber(int x, int y, char type, int value) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        cells[y][x].setHasNumber(true);
        cells[y][x].setValue(value);
        
        // Устанавливаем тип блока (S - симметричный, A - асимметричный)
        if (type == 'S') {
            cells[y][x].setIsSymmetry(true);
        } else if (type == 'A') {
            cells[y][x].setIsAsymmetry(true);
        }
    }
}

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

bool Board::isBlockAsymmetric(int blockId) const {
    return !isBlockSymmetric(blockId);
}

bool Board::checkContinuityRule() const {
    // Проверка целостности незакрашенных клеток с помощью BFS
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    
    // Найдем первую незакрашенную клетку
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


char Board::getCellNumber(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height && cells[y][x].hasNumber()) {
        return static_cast<char>(cells[y][x].getValue());
    }
    return 0;
}

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

bool Board::isSolved() const {
    return checkContinuityRule() && 
           checkAdjacentRule() &&
           checkNumbersRule() &&
           checkCrossingRule() &&
           checkSymmetryRules();
}