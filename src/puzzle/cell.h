/* ----------------------------------------------------------------<Header>-
 * Name: cell.h
 * Title: Cell Class Definition
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
    
    // Для числовых клеток и блоков
    void setBlockId(int id);
    int getBlockId() const;
    
    void setValue(int value);   // Для клеток с числами (A или S)
    int getValue() const;
    
    void setHasNumber(bool has);
    bool hasNumber() const;
    
    void setIsSymmetry(bool sym); // Для блоков с S
    bool isSymmetry() const;
    
    void setIsAsymmetry(bool asym); // Для блоков с A
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