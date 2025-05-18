/* ----------------------------------------------------------------<Header>-
 * Name: cell.h
 * Title: Cell Class Definition
 * Group: TV-41
 * Student: Bilyk Oleksandr
 * Written: 2025-04-25
 * Revised: 2025-04-25
 * Description: Defines a single cell on the game board with properties for
 *             state management including filling, block assignment, and symmetry
 ------------------------------------------------------------------</Header>-*/

#ifndef CELL_H
#define CELL_H

class Cell {
public:
    Cell();
    void setFilled(bool value);
    bool isFilled() const;
    
    // Для числових клітинок та блоків
    void setBlockId(int id);
    int getBlockId() const;
    
    void setValue(int value);   // Для клітинок з літерами (A або S)
    int getValue() const;
    
    void setHasNumber(bool has);
    bool hasNumber() const;
    
    void setIsSymmetry(bool sym); // Для блоків з S
    bool isSymmetry() const;
    
    void setIsAsymmetry(bool asym); // Для блоків з A
    bool isAsymmetry() const;

private:
    bool filled;
    int blockId;
    int value;
    bool hasNum;
    bool symmetry;
    bool asymmetry;
};

#endif // CELL_H