#include "puzzle/board.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>

// Глобальные переменные для задания головоломки
const int BOARD_SIZE = 10;

// Определение всех блоков головоломки
const std::vector<std::vector<std::pair<int, int>>> BLOCKS = {
    // Блок 0 - верхний левый квадрат 3x3
    {{0,0}, {1,0}, {2,0}, {0,1}, {1,1}, {2,1}, {0,2}, {1,2}, {2,2}},
    
    // Блок 1 - верхний правый повернутый квадрат с буквой A
    {{6,0}, {7,0}, {8,0}, {9,0}, {6,1}, {7,1}, {8,1}, {9,1}, {7,2}, {8,2}, {9,2}},
    
    // Блок 2 - средний верхний блок с буквами A
    {{3,1}, {4,1}, {5,1}, {3,2}, {4,2}, {5,2}, {3,3}, {4,3}, {5,3}},
    
    // Блок 3 - квадрат в правой средней части с AA и S
    {{7,3}, {8,3}, {9,3}, {7,4}, {8,4}, {9,4}, {7,5}, {8,5}, {9,5}},
    
    // Блок 4 - нижний левый повернутый квадрат с A и S
    {{0,5}, {1,5}, {2,5}, {0,6}, {1,6}, {2,6}, {0,7}, {1,7}, {2,7}, {0,8}},
    
    // Блок 5 - нижний правый квадрат 3x3
    {{7,7}, {8,7}, {9,7}, {7,8}, {8,8}, {9,8}, {7,9}, {8,9}, {9,9}},
    
    // Блок 6 - средний нижний блок с A
    {{4,6}, {5,6}, {6,6}, {4,7}, {5,7}, {6,7}, {4,8}, {5,8}, {6,8}},
    
    // Блок 7 - правый блок с S внизу
    {{6,8}, {6,9}, {5,9}, {4,9}, {3,9}, {3,8}}
};

void setPuzzle(Board &board) {
    // Инициализация базовой доски
    board.initialize();
    
    // Блок 0 - верхний левый квадрат 3x3
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            board.setBlockId(x, y, 0);
        }
    }
    
    // Блок 1 - верхний правый повернутый квадрат с буквой A
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
    
    // Блок 2 - средний верхний блок с буквами A
    board.setBlockId(3, 1, 2);
    board.setBlockId(4, 1, 2);
    board.setBlockId(5, 1, 2);
    board.setBlockId(3, 2, 2);
    board.setBlockId(4, 2, 2);
    board.setBlockId(5, 2, 2);
    board.setBlockId(3, 3, 2);
    board.setBlockId(4, 3, 2);
    board.setBlockId(5, 3, 2);
    
    // Блок 3 - квадрат в правой средней части с AA и S
    board.setBlockId(7, 3, 3);
    board.setBlockId(8, 3, 3);
    board.setBlockId(9, 3, 3);
    board.setBlockId(7, 4, 3);
    board.setBlockId(8, 4, 3);
    board.setBlockId(9, 4, 3);
    board.setBlockId(7, 5, 3);
    board.setBlockId(8, 5, 3);
    board.setBlockId(9, 5, 3);
    
    // Блок 4 - нижний левый повернутый квадрат с A и S
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
    
    // Блок 5 - нижний правый квадрат 3x3
    for (int y = 7; y < 10; y++) {
        for (int x = 7; x < 10; x++) {
            board.setBlockId(x, y, 5);
        }
    }
    
    // Блок 6 - средний нижний блок с A
    board.setBlockId(4, 6, 6);
    board.setBlockId(5, 6, 6);
    board.setBlockId(6, 6, 6);
    board.setBlockId(4, 7, 6);
    board.setBlockId(5, 7, 6);
    board.setBlockId(6, 7, 6);
    board.setBlockId(4, 8, 6);
    board.setBlockId(5, 8, 6);
    board.setBlockId(6, 8, 6);
    
    // Блок 7 - правый блок с S внизу
    board.setBlockId(6, 8, 7);
    board.setBlockId(6, 9, 7);
    board.setBlockId(5, 9, 7);
    board.setBlockId(4, 9, 7);
    board.setBlockId(3, 9, 7);
    board.setBlockId(3, 8, 7);
    
    // Устанавливаем буквы A и S для соответствующих блоков
    std::cout << "Установка букв..." << std::endl;
    board.setCellNumber(3, 1, 'A'); // A в блоке 2
    std::cout << "После установки A в (3,1), getCellNumber возвращает: " 
              << (int)board.getCellNumber(3, 1) << std::endl;
    board.setCellNumber(4, 2, 'A'); // A в блоке 2
    board.setCellNumber(9, 1, 'A'); // A в блоке 1
    board.setCellNumber(7, 3, 'A'); // A в блоке 3
    board.setCellNumber(8, 3, 'A'); // A в блоке 3
    board.setCellNumber(1, 6, 'A'); // A в блоке 4
    board.setCellNumber(5, 7, 'A'); // A в блоке 6
    board.setCellNumber(0, 8, 'A'); // A в блоке 4

    board.setCellNumber(0, 5, 'S'); // S в блоке 4
    board.setCellNumber(9, 4, 'S'); // S в блоке 3
    board.setCellNumber(2, 6, 'S'); // S в блоке 4
    board.setCellNumber(6, 8, 'S'); // S в блоке 7
}

// Теперь попробуем более простой подход, напрямую закрашивая клетки A
// и проверяя корректность без опоры на getCellNumber
void setUpInitialState(Board &board) {
    // Закрашиваем клетки с буквами A
    std::vector<std::pair<int, int>> aPositions = {
        {3, 1}, {4, 2}, {9, 1}, {7, 3}, {8, 3}, {1, 6}, {5, 7}, {0, 8}
    };
    
    // Добавляем соединения между буквами A
    std::vector<std::pair<int, int>> additionalFilledCells = {
        {4, 1}, // соединяем A в блоке 2
        {8, 2}, // соединяем A в блоке 1 с блоком 3
        {7, 4}, // дополнительное соединение в блоке 3
        {1, 7}, // соединяем A в блоке 4
        {5, 8}  // соединяем A в блоке 6
    };
    
    // Устанавливаем все A и их соединения
    for (auto& pos : aPositions) {
        board.setCell(pos.first, pos.second, true);
    }
    
    // Добавляем соединительные клетки
    for (auto& pos : additionalFilledCells) {
        board.setCell(pos.first, pos.second, true);
    }
    
    // Устанавливаем S клетки как незакрашенные
    std::vector<std::pair<int, int>> sPositions = {
        {0, 5}, {9, 4}, {2, 6}, {6, 8}
    };
    
    for (auto& pos : sPositions) {
        board.setCell(pos.first, pos.second, false);
    }
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
    // Выполняем базовые проверки правил перед рекурсией
    if (board.checkAdjacentRule() && board.checkContinuityRule()) {
        if (solveBacktracking(board, nextX, nextY)) {
            return true;
        }
    }
    
    // Пробуем закрасить клетку
    board.setCell(x, y, true);
    // Выполняем базовые проверки правил перед рекурсией
    if (board.checkAdjacentRule() && !board.checkCrossingRule()) {
        // ИСПРАВЛЕНИЕ: Если правила НЕ нарушены, продолжаем решение
        if (solveBacktracking(board, nextX, nextY)) {
            return true;
        }
    }
    
    // Возвращаем клетку в незакрашенное состояние (бэктрек)
    board.setCell(x, y, false);
    
    return false;
}

// Правила для букв A и S
bool checkLetterRules(const Board &board, int x, int y) {
    char letter = board.getCellNumber(x, y);
    bool isMarked = board.getCell(x, y);
    
    if (letter == 'A') {
        // Для буквы A: клетка должна быть закрашена
        return isMarked;
    } else if (letter == 'S') {
        // Для буквы S: клетка не должна быть закрашена
        return !isMarked;
    }
    
    return true; // Нет ограничений для клеток без букв
}

// Добавляем прототип функции перед её использованием
bool solveWithCells(Board &board, const std::vector<std::pair<int, int>>& cells, int index);
// Добавляем прототип улучшенной функции
bool solveWithCellsImproved(Board &board, const std::vector<std::pair<int, int>>& cells, int index);
// Добавляем прототип функции вывода доски
void printBoard(const Board &board);

bool customCheckCrossingRule(const Board &board) {
    // В пустой доске нет пересечений
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
    
    if (!anyFilled) return true; // пустая доска всегда корректна
    
    // Проверяем стандартным методом
    return !board.checkCrossingRule();
}

bool solveOptimizedBacktracking(Board &board) {
    // Создаем вектор всех клеток, которые нужно заполнить
    std::vector<std::pair<int, int>> cells;
    
    // Сначала помечаем все клетки как незакрашенные (пустая доска)
    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            board.setCell(x, y, false);
        }
    }
    
    // Устанавливаем начальные A и S без использования getCellNumber
    setUpInitialState(board);
    
    // Проверка правил после ручной установки букв
    std::cout << "Состояние доски после установки A:" << std::endl;
    printBoard(board);
    
    std::cout << "Проверка правил после ручной установки:" << std::endl;
    std::cout << "Правило соседства: " << (board.checkAdjacentRule() ? "OK" : "нарушено") << std::endl;
    std::cout << "Правило непрерывности: " << (board.checkContinuityRule() ? "OK" : "нарушено") << std::endl;
    std::cout << "Правило пересечений: " << (customCheckCrossingRule(board) ? "OK" : "нарушено") << std::endl;
    
    // Если правила нарушены после установки букв, решения нет
    if (!board.checkAdjacentRule() || !board.checkContinuityRule() || board.checkCrossingRule()) {
        std::cout << "Невозможно решить: правила нарушены после установки A" << std::endl;
        return false;
    }
    
    // Создаем список всех клеток, которые нужно проверить
    // Исключаем клетки, которые мы уже установили (A и S)
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
    
    std::cout << "Начинаем решение с " << cells.size() << " клетками для заполнения" << std::endl;
    return solveWithCellsImproved(board, cells, 0);
}

// Добавляем новую функцию проверки правила несоприкосновения закрашенных клеток
bool checkNoAdjacentFilled(const Board &board) {
    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            if (board.getCell(x, y)) { // Если клетка закрашена
                // Проверяем только горизонтальных и вертикальных соседей
                if ((x > 0 && board.getCell(x-1, y)) ||            // слева
                    (x < BOARD_SIZE-1 && board.getCell(x+1, y)) || // справа
                    (y > 0 && board.getCell(x, y-1)) ||            // сверху
                    (y < BOARD_SIZE-1 && board.getCell(x, y+1))) {  // снизу
                    return false; // Нашли соприкасающиеся закрашенные клетки
                }
                // Диагональные соседи разрешены, их не проверяем
            }
        }
    }
    return true;
}

// Проверка связности незакрашенных клеток
bool checkEmptyCellsContinuity(const Board &board) {
    // Находим первую незакрашенную клетку
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
    
    if (startX == -1) return true; // Все клетки закрашены, правило выполнено тривиально
    
    // Выполняем поиск в ширину из найденной незакрашенной клетки
    std::vector<std::vector<bool>> visited(BOARD_SIZE, std::vector<bool>(BOARD_SIZE, false));
    std::vector<std::pair<int, int>> queue;
    
    queue.push_back({startX, startY});
    visited[startY][startX] = true;
    
    while (!queue.empty()) {
        int x = queue.front().first;
        int y = queue.front().second;
        queue.erase(queue.begin());
        
        // Проверяем соседей
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
    
    // Проверяем, что все незакрашенные клетки посещены
    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            if (!board.getCell(x, y) && !visited[y][x]) {
                return false; // Нашли непосещенную незакрашенную клетку
            }
        }
    }
    
    return true;
}

// Структура для хранения информации о блоках
struct BlockInfo {
    std::vector<std::pair<int, int>> cells;
    std::vector<bool> states;
};

// Проверка симметрии блока
bool checkBlockSymmetry(const Board &board, const std::vector<std::pair<int, int>>& blockCells) {
    if (blockCells.empty()) return true;
    
    // Находим центр блока
    int minX = BOARD_SIZE, maxX = 0, minY = BOARD_SIZE, maxY = 0;
    for (auto& cell : blockCells) {
        minX = std::min(minX, cell.first);
        maxX = std::max(maxX, cell.first);
        minY = std::min(minY, cell.second);
        maxY = std::max(maxY, cell.second);
    }
    
    // Проверяем горизонтальную симметрию
    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            int mirrorX = maxX - (x - minX);
            bool hasOriginal = false, hasMirror = false;
            bool originalState = false, mirrorState = false;
            
            // Ищем оригинальную клетку
            for (auto& cell : blockCells) {
                if (cell.first == x && cell.second == y) {
                    hasOriginal = true;
                    originalState = board.getCell(x, y);
                    break;
                }
            }
            
            // Ищем зеркальную клетку
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

// Функция проверки симметрии блока при повороте на 180 градусов
bool checkBlock180Symmetry(const Board &board, const std::vector<std::pair<int, int>>& blockCells) {
    if (blockCells.empty()) return true;
    
    // Находим границы блока
    int minX = BOARD_SIZE, maxX = 0, minY = BOARD_SIZE, maxY = 0;
    for (auto& cell : blockCells) {
        minX = std::min(minX, cell.first);
        maxX = std::max(maxX, cell.first);
        minY = std::min(minY, cell.second);
        maxY = std::max(maxY, cell.second);
    }
    
    // Проверяем симметрию при повороте на 180 градусов
    for (auto& cell : blockCells) {
        int x = cell.first;
        int y = cell.second;
        
        // Находим координаты симметричной клетки при повороте на 180°
        int rotX = maxX - (x - minX);
        int rotY = maxY - (y - minY);
        
        // Проверяем, есть ли клетка в блоке
        bool hasRotated = false;
        for (auto& rotCell : blockCells) {
            if (rotCell.first == rotX && rotCell.second == rotY) {
                hasRotated = true;
                // Проверяем совпадение состояний
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

// Функция определения типа блока (с буквой A или S)
char getBlockType(const Board &board, const std::vector<std::pair<int, int>>& blockCells) {
    for (auto& cell : blockCells) {
        char letter = board.getCellNumber(cell.first, cell.second);
        if (letter == 'A' || letter == 'S') {
            return letter;
        }
    }
    return ' ';
}

// Обновленная функция проверки блоков
bool checkBlockRules(const Board &board, const std::vector<std::pair<int, int>>& blockCells) {
    char blockType = getBlockType(board, blockCells);
    bool isSymmetric = checkBlock180Symmetry(board, blockCells);
    
    if (blockType == 'S') {
        // Блоки с S должны быть симметричны
        return isSymmetric;
    } else if (blockType == 'A') {
        // Блоки с A не должны быть симметричны
        return !isSymmetric;
    }
    
    return true; // Для блоков без букв нет ограничений
}

// Обновляем функцию проверки всех блоков
bool checkAllBlocksSymmetry(const Board &board) {
    for (const auto& block : BLOCKS) {
        if (!checkBlockRules(board, block)) {
            return false;
        }
    }
    return true;
}

// Модифицируем solveWithCellsImproved для проверки симметрии
bool solveWithCellsImproved(Board &board, const std::vector<std::pair<int, int>>& cells, int index) {
    // Выход из рекурсии - все клетки заполнены
    if (index >= static_cast<int>(cells.size())) {
        // Проверяем все правила вместе
        bool noAdjacentFilledOk = checkNoAdjacentFilled(board);
        bool emptyContinuityOk = checkEmptyCellsContinuity(board);
        bool symmetryOk = checkAllBlocksSymmetry(board);
        
        if (!noAdjacentFilledOk || !emptyContinuityOk || !symmetryOk) {
            std::cout << "Доска заполнена, но решение не найдено. Дополнительная проверка:" << std::endl;
            std::cout << "Правило несоприкосновения закрашенных клеток: " << (noAdjacentFilledOk ? "OK" : "нарушено") << std::endl;
            std::cout << "Правило связности незакрашенных клеток: " << (emptyContinuityOk ? "OK" : "нарушено") << std::endl;
            return false;
        }
        
        return true; // Все правила выполнены, решение найдено
    }
    
    static int steps = 0;
    if (++steps % 10000 == 0) {
        std::cout << "Проверено вариантов: " << steps << ", текущий индекс: " << index << "/" << cells.size() << std::endl;
        if (steps % 100000 == 0) {
            std::cout << "Текущее состояние доски:" << std::endl;
            printBoard(board);
        }
    }
    
    int x = cells[index].first;
    int y = cells[index].second;
    
    // Проверяем, можно ли закрасить текущую клетку
    bool canFill = true;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            if (abs(dx) + abs(dy) != 1) continue; // Проверяем только соседей по сторонам
            
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && board.getCell(nx, ny)) {
                canFill = false;
                break;
            }
        }
        if (!canFill) break;
    }
    
    // Пробуем сначала НЕ закрашивать клетку
    board.setCell(x, y, false);
    if (checkEmptyCellsContinuity(board)) {
        if (solveWithCellsImproved(board, cells, index + 1)) {
            return true;
        }
    }
    
    // Затем пробуем закрасить клетку, если это не нарушает правило соприкосновения
    if (canFill) {
        board.setCell(x, y, true);
        if (checkEmptyCellsContinuity(board)) {
            if (solveWithCellsImproved(board, cells, index + 1)) {
                return true;
            }
        }
    }
    
    // Если не нашли решение, восстанавливаем незакрашенное состояние
    board.setCell(x, y, false);
    return false;
}

// Все константы и структуры для букв
const std::vector<std::pair<int, int>> LETTER_A_POSITIONS = {
    {3, 1}, {4, 2}, {9, 1}, {7, 3}, {8, 3}, {1, 6}, {5, 7}, {0, 8}
};

const std::vector<std::pair<int, int>> LETTER_S_POSITIONS = {
    {0, 5}, {9, 4}, {2, 6}, {6, 8}
};

// Упрощенная функция установки букв
void setupLetters(Board &board) {
    for (auto& pos : LETTER_A_POSITIONS) {
        board.setCellNumber(pos.first, pos.second, 'A');
    }
    
    for (auto& pos : LETTER_S_POSITIONS) {
        board.setCellNumber(pos.first, pos.second, 'S');
    }
}

// Упрощенная функция проверки букв
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
        std::cout << "Переустановка букв..." << std::endl;
        setupLetters(board);
    }
    
    std::cout << "Решаем головоломку..." << std::endl;
    
    if (solveOptimizedBacktracking(board)) {
        std::cout << "Решение найдено!" << std::endl;
        printBoard(board);
    } else {
        std::cout << "Решения не существует!" << std::endl;
        std::cout << "Состояние доски в конце алгоритма:" << std::endl;
        printBoard(board);
    }
    
    return 0;
}