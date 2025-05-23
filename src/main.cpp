/* ----------------------------------------------------------------<Header>-
 * Name: main.cpp
 * Title: Puzzle Solver with A and S letters
 * Group: TV-41
 * Student: Bilyk Oleksandr
 * Written: 2025-04-22
 * Revised: 2025-04-22
 * Description: Program solves a 10x10 board puzzle where you need to
 * place filled cells according to the following rules:
 * - Cells with letter A must be filled
 * - Cells with letter S must be empty
 * - Filled cells cannot share sides
 * - All empty cells must be connected
 * - Blocks with letter S must be symmetric when rotated 180°
 * - Blocks with letter A must not be symmetric when rotated 180°
 ------------------------------------------------------------------</Header>-*/

#include "puzzle/board.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>

// Глобальні змінні для завдання головоломки
const int BOARD_SIZE = 10;

// Визначення всіх блоків головоломки
const std::vector<std::vector<std::pair<int, int>>> BLOCKS = {
    // Блок 0 - верхній лівий квадрат 3x3
    {{0,0}, {1,0}, {2,0}, {0,1}, {1,1}, {2,1}, {0,2}, {1,2}, {2,2}},
    
    // Блок 1 - верхній правий повернутий квадрат з літерою A
    {{6,0}, {7,0}, {8,0}, {9,0}, {6,1}, {7,1}, {8,1}, {9,1}, {7,2}, {8,2}, {9,2}},
    
    // Блок 2 - середній верхній блок з буквами A
    {{3,1}, {4,1}, {5,1}, {3,2}, {4,2}, {5,2}, {3,3}, {4,3}, {5,3}},
    
    // Блок 3 - квадрат в правій середній частині з AA і S
    {{7,3}, {8,3}, {9,3}, {7,4}, {8,4}, {9,4}, {7,5}, {8,5}, {9,5}},
    
    // Блок 4 - нижній лівий повернутий квадрат з A і S
    {{0,5}, {1,5}, {2,5}, {0,6}, {1,6}, {2,6}, {0,7}, {1,7}, {2,7}, {0,8}},
    
    // Блок 5 - нижній правий квадрат 3x3
    {{7,7}, {8,7}, {9,7}, {7,8}, {8,8}, {9,8}, {7,9}, {8,9}, {9,9}},
    
    // Блок 6 - середній нижній блок з A
    {{4,6}, {5,6}, {6,6}, {4,7}, {5,7}, {6,7}, {4,8}, {5,8}, {6,8}},
    
    // Блок 7 - правий блок з S внизу
    {{6,8}, {6,9}, {5,9}, {4,9}, {3,9}, {3,8}}
};

void setPuzzle(Board &board) {
    /* ---------------------------------------------------------------------[<]-
     * Function: setPuzzle
     * Synopsis: Initializes the initial state of the board by setting blocks
     *           and the letters A and S in their respective positions
     * Parameters: board - board object reference
     * Returns: void
     ---------------------------------------------------------------------[>]-*/
    // Ініціалізація базової дошки
    board.initialize();
    
    // Блок 0 - верхній лівий квадрат 3x3
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            board.setBlockId(x, y, 0);
        }
    }
    
    // Блок 1 - верхній правий повернутий квадрат з літерою A
    board.setBlockId(6, 0, 1);
    board.setBlockId(7, 0, 1);
    board.setBlockId(8, 0, 1);
    board.setBlockId(9, 0, 1);
    board.setBlockId(6, 1, 1);
    board.setBlockId(7, 1, 1);
    board.setBlockId(8, 1, 1);
    board.setBlockId(9, 1, 1);
    board.setBlockId(7, 2, 1);
    board.setBlockId(8, 2, 1);
    board.setBlockId(9, 2, 1);
    
    // Блок 2 - середній верхній блок з буквами A
    board.setBlockId(3, 1, 2);
    board.setBlockId(4, 1, 2);
    board.setBlockId(5, 1, 2);
    board.setBlockId(3, 2, 2);
    board.setBlockId(4, 2, 2);
    board.setBlockId(5, 2, 2);
    board.setBlockId(3, 3, 2);
    board.setBlockId(4, 3, 2);
    board.setBlockId(5, 3, 2);
    
    // Блок 3 - квадрат в правій середній частині з AA і S
    board.setBlockId(7, 3, 3);
    board.setBlockId(8, 3, 3);
    board.setBlockId(9, 3, 3);
    board.setBlockId(7, 4, 3);
    board.setBlockId(8, 4, 3);
    board.setBlockId(9, 4, 3);
    board.setBlockId(7, 5, 3);
    board.setBlockId(8, 5, 3);
    board.setBlockId(9, 5, 3);
    
    // Блок 4 - нижній лівий повернутий квадрат з A і S
    board.setBlockId(0, 5, 4);
    board.setBlockId(1, 5, 4);
    board.setBlockId(2, 5, 4);
    board.setBlockId(0, 6, 4);
    board.setBlockId(1, 6, 4);
    board.setBlockId(2, 6, 4);
    board.setBlockId(0, 7, 4);
    board.setBlockId(1, 7, 4);
    board.setBlockId(2, 7, 4);
    board.setBlockId(0, 8, 4);
    
    // Блок 5 - нижній правий квадрат 3x3
    for (int y = 7; y < 10; y++) {
        for (int x = 7; x < 10; x++) {
            board.setBlockId(x, y, 5);
        }
    }
    
    // Блок 6 - середній нижній блок з A
    board.setBlockId(4, 6, 6);
    board.setBlockId(5, 6, 6);
    board.setBlockId(6, 6, 6);
    board.setBlockId(4, 7, 6);
    board.setBlockId(5, 7, 6);
    board.setBlockId(6, 7, 6);
    board.setBlockId(4, 8, 6);
    board.setBlockId(5, 8, 6);
    board.setBlockId(6, 8, 6);
    
    // Блок 7 - правий блок з S внизу
    board.setBlockId(6, 8, 7);
    board.setBlockId(6, 9, 7);
    board.setBlockId(5, 9, 7);
    board.setBlockId(4, 9, 7);
    board.setBlockId(3, 9, 7);
    board.setBlockId(3, 8, 7);
    
    // Встановлюємо літери A і S для відповідних блоків
    std::cout << "Встановлення літер..." << std::endl;
    board.setCellNumber(3, 1, 'A'); // A в блоці 2
    std::cout << "Після встановлення A в (3,1), getCellNumber повертає: " 
              << (int)board.getCellNumber(3, 1) << std::endl;
    board.setCellNumber(4, 2, 'A'); // A в блоці 2
    board.setCellNumber(9, 1, 'A'); // A в блоці 1
    board.setCellNumber(7, 3, 'A'); // A в блоці 3
    board.setCellNumber(8, 3, 'A'); // A в блоці 3
    board.setCellNumber(1, 6, 'A'); // A в блоці 4
    board.setCellNumber(5, 7, 'A'); // A в блоці 6
    board.setCellNumber(0, 8, 'A'); // A в блоці 4

    board.setCellNumber(0, 5, 'S'); // S в блоці 4
    board.setCellNumber(9, 4, 'S'); // S в блоці 3
    board.setCellNumber(2, 6, 'S'); // S в блоці 4
    board.setCellNumber(6, 8, 'S'); // S в блоці 7
}

// Спробуємо простіший підхід, безпосередньо зафарбовуючи клітинки A
// та перевіряючи коректність без опори на getCellNumber
void setUpInitialState(Board &board) {
    /* ---------------------------------------------------------------------[<]-
     * Function: setUpInitialState
     * Synopsis: Sets the initial state of the board by coloring the cells
     * with the letters A and adding connecting squares.
     * Parameters: board - reference to the board object
     * Returns: void
     ---------------------------------------------------------------------[>]-*/
    // Спочатку встановлюємо всі клітинки як незафарбовані
    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            board.setCell(x, y, false);
        }
    }

    // Зафарбовуємо клітинки з літерами A - змінюємо позиції для уникнення стикання
    std::vector<std::pair<int, int>> aPositions = {
        {3, 1}, {4, 2}, {9, 1}, {7, 3}, {8, 3}, {1, 6}, {5, 7}, {0, 8}
    };
    
    // Додаємо з'єднувальні клітинки з урахуванням правила несоприкосновения
    std::vector<std::pair<int, int>> additionalFilledCells = {
        {8, 2},  // з'єднує блок 1 з блоком 3
        {6, 4},  // з'єднання в блоці 3 (змінено з {7,4})
        {0, 7},  // з'єднання в блоці 4 (змінено з {1,7})
        {4, 6}   // з'єднання для блока 6 (змінено з {5,6})
    };

    // Спочатку встановлюємо букви A
    for (auto& pos : aPositions) {
        board.setCell(pos.first, pos.second, true);
    }
    
    // Потім додаємо з'єднувальні клітини
    for (auto& pos : additionalFilledCells) {
        board.setCell(pos.first, pos.second, true);
    }
    
    // Встановлюємо S клітини як незафарбовані
    std::vector<std::pair<int, int>> sPositions = {
        {0, 5}, {9, 4}, {2, 6}, {6, 8}
    };
    
    for (auto& pos : sPositions) {
        board.setCell(pos.first, pos.second, false);
    }
}

bool solveBacktracking(Board &board, int x, int y) {
    // Якщо ми досягли кінця дошки, перевіряємо рішення
    if (y >= BOARD_SIZE) {
        return board.isSolved();
    }

    // Обчислюємо наступну клітинку
    int nextX = (x + 1) % BOARD_SIZE;
    int nextY = y + (x + 1) / BOARD_SIZE;
    
    // Пробуємо залишити клітинку незафарбованою
    board.setCell(x, y, false);
    // Виконуємо базові перевірки правил перед рекурсією
    if (board.checkAdjacentRule() && board.checkContinuityRule()) {
        if (solveBacktracking(board, nextX, nextY)) {
            return true;
        }
    }
    
    // Пробуємо зафарбувати клітинку
    board.setCell(x, y, true);
    // Виконуємо базові перевірки правил перед рекурсією
    if (board.checkAdjacentRule() && !board.checkCrossingRule()) {
        // ІСПРАВЛЕННЯ: Якщо правила НЕ порушені, продовжуємо рішення
        if (solveBacktracking(board, nextX, nextY)) {
            return true;
        }
    }
    
    // Повертаємо клітинку в незафарбоване стан (бэктрек)
    board.setCell(x, y, false);
    
    return false;
}

// Правила для літер A і S
bool checkLetterRules(const Board &board, int x, int y) {
    char letter = board.getCellNumber(x, y);
    bool isMarked = board.getCell(x, y);
    
    if (letter == 'A') {
        // Для літери A: клітинка має бути зафарбована
        return isMarked;
    } else if (letter == 'S') {
        // Для літери S: клітинка не має бути зафарбована
        return !isMarked;
    }
    
    return true; // Немає обмежень для клітинок без літер
}

// Додаємо прототип функції перед її використанням
bool solveWithCells(Board &board, const std::vector<std::pair<int, int>>& cells, int index);
// Додаємо прототип поліпшеної функції
bool solveWithCellsImproved(Board &board, const std::vector<std::pair<int, int>>& cells, int index);
// Додаємо прототип функції виведення дошки
void printBoard(const Board &board);

bool customCheckCrossingRule(const Board &board) {
    // У порожній дошці немає перетинів
    bool anyFilled = false;
    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            if (board.getCell(x, y)) {
                anyFilled = true;
                break;
            }
        }
        if (anyFilled) break;
    }
    
    if (!anyFilled) return true; // порожня дошка завжди коректна
    
    // Перевіряємо стандартним методом
    return !board.checkCrossingRule();
}

bool solveOptimizedBacktracking(Board &board) {
    // Створюємо вектор усіх клітин, які потрібно заповнити
    std::vector<std::pair<int, int>> cells;
    
    // Спочатку позначаємо всі клітинки як незафарбовані (порожня дошка)
    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            board.setCell(x, y, false);
        }
    }
    
    // Встановлюємо початкові A і S без використання getCellNumber
    setUpInitialState(board);
    
    // Створюємо список усіх клітин, які потрібно перевірити
    // Виключаємо клітини, які ми вже встановили (A і S)
    std::vector<std::pair<int, int>> aPositions = {
        {3, 1}, {4, 2}, {9, 1}, {7, 3}, {8, 3}, {1, 6}, {5, 7}, {0, 8}
    };
    std::vector<std::pair<int, int>> sPositions = {
        {0, 5}, {9, 4}, {2, 6}, {6, 8}
    };
    
    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            bool isA = false, isS = false;
            
            for (auto& pos : aPositions) {
                if (pos.first == x && pos.second == y) {
                    isA = true;
                    break;
                }
            }
            
            for (auto& pos : sPositions) {
                if (pos.first == x && pos.second == y) {
                    isS = true;
                    break;
                }
            }
            
            if (!isA && !isS) {
                cells.push_back({x, y});
            }
        }
    }
    
    return solveWithCellsImproved(board, cells, 0);
}

// Додаємо нову функцію перевірки правила недотику зафарбованих клітин
bool checkNoAdjacentFilled(const Board &board) {
    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            if (board.getCell(x, y)) { // Якщо клітина зафарбована
                // Перевіряємо тільки горизонтальних і вертикальних сусідів
                if ((x > 0 && board.getCell(x-1, y)) ||            // зліва
                    (x < BOARD_SIZE-1 && board.getCell(x+1, y)) || // справа
                    (y > 0 && board.getCell(x, y-1)) ||            // зверху
                    (y < BOARD_SIZE-1 && board.getCell(x, y+1))) {  // знизу
                    return false; // Знайшли дотичні зафарбовані клітини, що стикаються
                }
                // Діагональні сусіди дозволені, їх не перевіряємо
            }
        }
    }
    return true;
}

// Перевірка зв'язності незафарбованих клітин
bool checkEmptyCellsContinuity(const Board &board) {
    // Знаходимо першу незафарбовану клітинку
    int startX = -1, startY = -1;
    for (int y = 0; y < BOARD_SIZE && startX == -1; ++y) {
        for (int x = 0; x < BOARD_SIZE && startX == -1; ++x) {
            if (!board.getCell(x, y)) {
                startX = x;
                startY = y;
                break;
            }
        }
    }
    
    if (startX == -1) return true; // Усі клітини зафарбовані, правило виконано тривіально
    
    // Виконуємо пошук завширшки зі знайденої незафарбованої клітинки
    std::vector<std::vector<bool>> visited(BOARD_SIZE, std::vector<bool>(BOARD_SIZE, false));
    std::vector<std::pair<int, int>> queue;
    
    queue.push_back({startX, startY});
    visited[startY][startX] = true;
    
    while (!queue.empty()) {
        int x = queue.front().first;
        int y = queue.front().second;
        queue.erase(queue.begin());
        
        // Перевіряємо сусідів
        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};
        
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && 
                !board.getCell(nx, ny) && !visited[ny][nx]) {
                visited[ny][nx] = true;
                queue.push_back({nx, ny});
            }
        }
    }
    
    // Перевіряємо, що всі незафарбовані клітини відвідані
    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            if (!board.getCell(x, y) && !visited[y][x]) {
                return false; // Знайшли невідвідувану незафарбовану клітку
            }
        }
    }
    
    return true;
}

// Структура для зберігання інформації про блоки
struct BlockInfo {
    std::vector<std::pair<int, int>> cells;
    std::vector<bool> states;
};

// Перевірка симетрії блока
bool checkBlockSymmetry(const Board &board, const std::vector<std::pair<int, int>>& blockCells) {
    /* ---------------------------------------------------------------------[<]-
     * Function: checkBlockSymmetry
     * Synopsis: Checks block symmetry with respect to the vertical axis
     * Parameters: board - reference to the board object
     * blockCells - vector of cells that make up the block
     * Returns: true if the block is symmetric, false otherwise.
     ---------------------------------------------------------------------[>]-*/
    if (blockCells.empty()) return true;
    
    // Знаходимо центр блоку
    int minX = BOARD_SIZE, maxX = 0, minY = BOARD_SIZE, maxY = 0;
    for (auto& cell : blockCells) {
        minX = std::min(minX, cell.first);
        maxX = std::max(maxX, cell.first);
        minY = std::min(minY, cell.second);
        maxY = std::max(maxY, cell.second);
    }
    
    // Перевіряємо горизонтальну симетрію
    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            int mirrorX = maxX - (x - minX);
            bool hasOriginal = false, hasMirror = false;
            bool originalState = false, mirrorState = false;
            
            // Шукаємо оригінальну клітку
            for (auto& cell : blockCells) {
                if (cell.first == x && cell.second == y) {
                    hasOriginal = true;
                    originalState = board.getCell(x, y);
                    break;
                }
            }
            
            // Шукаємо дзеркальну клітку
            for (auto& cell : blockCells) {
                if (cell.first == mirrorX && cell.second == y) {
                    hasMirror = true;
                    mirrorState = board.getCell(mirrorX, y);
                    break;
                }
            }
            
            if (hasOriginal != hasMirror || (hasOriginal && originalState != mirrorState)) {
                return false;
            }
        }
    }
    
    return true;
}

// Функція перевірки симетрії блока при повороті на 180 градусів
bool checkBlock180Symmetry(const Board &board, const std::vector<std::pair<int, int>>& blockCells) {
    /* ---------------------------------------------------------------------[<]-
     * Function: checkBlock180Symmetry
     * Synopsis: Checks block symmetry when rotated by 180 degrees
     * Parameters: board - reference to the board object
     * blockCells - vector of cells that make up the block
     * Returns: true if the block is symmetric when rotated by 180°, false otherwise.
     ---------------------------------------------------------------------[>]-*/
    if (blockCells.empty()) return true;
    
    // Знаходимо межі блоку
    int minX = BOARD_SIZE, maxX = 0, minY = BOARD_SIZE, maxY = 0;
    for (auto& cell : blockCells) {
        minX = std::min(minX, cell.first);
        maxX = std::max(maxX, cell.first);
        minY = std::min(minY, cell.second);
        maxY = std::max(maxY, cell.second);
    }
    
    // Перевіряємо симетрію при повороті на 180 градусів
    for (auto& cell : blockCells) {
        int x = cell.first;
        int y = cell.second;
        
        // Знаходимо координати симетричної клітинки при повороті на 180°
        int rotX = maxX - (x - minX);
        int rotY = maxY - (y - minY);
        
        // Перевіряємо, чи є клітина в блоці
        bool hasRotated = false;
        for (auto& rotCell : blockCells) {
            if (rotCell.first == rotX && rotCell.second == rotY) {
                hasRotated = true;
                // Перевіряємо збіг станів
                if (board.getCell(x, y) != board.getCell(rotX, rotY)) {
                    return false;
                }
                break;
            }
        }
        if (!hasRotated) return false;
    }
    return true;
}

// Функція визначення типу блока (з літерою A або S)
char getBlockType(const Board &board, const std::vector<std::pair<int, int>>& blockCells) {
    for (auto& cell : blockCells) {
        char letter = board.getCellNumber(cell.first, cell.second);
        if (letter == 'A' || letter == 'S') {
            return letter;
        }
    }
    return ' ';
}

// Оновлена функція перевірки блоків
bool checkBlockRules(const Board &board, const std::vector<std::pair<int, int>>& blockCells) {
    char blockType = getBlockType(board, blockCells);
    bool isSymmetric = checkBlock180Symmetry(board, blockCells);
    
    if (blockType == 'S') {
        // Блоки з S повинні бути симетричні
        return isSymmetric;
    } else if (blockType == 'A') {
        // Блоки з A не повинні бути симетричні
        return !isSymmetric;
    }
    
    return true; // Для блоків без букв немає обмежень
}

// Оновлюємо функцію перевірки всіх блоків
bool checkAllBlocksSymmetry(const Board &board) {
    for (const auto& block : BLOCKS) {
        if (!checkBlockRules(board, block)) {
            return false;
        }
    }
    return true;
}

// Модифікуємо solveWithCellsImproved для перевірки симетрії
bool solveWithCellsImproved(Board &board, const std::vector<std::pair<int, int>>& cells, int index) {
    if (!checkNoAdjacentFilled(board) || !checkEmptyCellsContinuity(board)) {
        return false;
    }

    // Швидка перевірка поточного блоку
    if (index > 0) {
        for (const auto& block : BLOCKS) {
            if (std::find(block.begin(), block.end(), cells[index-1]) != block.end()) {
                char type = getBlockType(board, block);
                if (type != ' ' && !checkBlockRules(board, block)) {
                    return false;
                }
                break;
            }
        }
    }

    if (index >= static_cast<int>(cells.size())) {
        return checkAllBlocksSymmetry(board);
    }

    int x = cells[index].first;
    int y = cells[index].second;

    // Спробуємо спочатку НЕ зафарбовувати
    board.setCell(x, y, false);
    if (solveWithCellsImproved(board, cells, index + 1)) {
        return true;
    }

    // Перевіряємо можливість зафарбувати
    for (int d = 0; d < 4; d++) {
        int nx = x + (d == 0 ? -1 : d == 1 ? 1 : 0);
        int ny = y + (d == 2 ? -1 : d == 3 ? 1 : 0);
        if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && 
            board.getCell(nx, ny)) {
            board.setCell(x, y, false);
            return false;
        }
    }

    board.setCell(x, y, true);
    if (solveWithCellsImproved(board, cells, index + 1)) {
        return true;
    }

    board.setCell(x, y, false);
    return false;
}

// Всі константи та структури для літер
const std::vector<std::pair<int, int>> LETTER_A_POSITIONS = {
    {3, 1}, {4, 2}, {9, 1}, {7, 3}, {8, 3}, {1, 6}, {5, 7}, {0, 8}
};

const std::vector<std::pair<int, int>> LETTER_S_POSITIONS = {
    {0, 5}, {9, 4}, {2, 6}, {6, 8}
};

// Спрощена функція встановлення літер
void setupLetters(Board &board) {
    for (auto& pos : LETTER_A_POSITIONS) {
        board.setCellNumber(pos.first, pos.second, 'A');
    }
    
    for (auto& pos : LETTER_S_POSITIONS) {
        board.setCellNumber(pos.first, pos.second, 'S');
    }
}

// Спрощена функція перевірки літер
bool verifyLetters(const Board &board) {
    for (auto& pos : LETTER_A_POSITIONS) {
        if (board.getCellNumber(pos.first, pos.second) != 'A') return false;
    }
    
    for (auto& pos : LETTER_S_POSITIONS) {
        if (board.getCellNumber(pos.first, pos.second) != 'S') return false;
    }
    
    return true;
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
    
    if (!verifyLetters(board)) {
        std::cout << "Перевстановлення літер..." << std::endl;
        setupLetters(board);
    }
    
    std::cout << "Розв'язуємо головоломку..." << std::endl;
    
    if (solveOptimizedBacktracking(board)) {
        std::cout << "Рішення знайдено!" << std::endl;
        printBoard(board);
    } else {
        std::cout << "Рішення не існує!" << std::endl;
        std::cout << "Стан дошки в кінці алгоритму:" << std::endl;
        printBoard(board);
    }
    
    return 0;
}