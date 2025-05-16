#include "cell.h"

Cell::Cell() : filled(false), blockId(-1), value(0), hasNum(false), symmetry(false), asymmetry(false) {
}

void Cell::setFilled(bool value) {
    filled = value;
}

bool Cell::isFilled() const {
    return filled;
}

void Cell::setBlockId(int id) {
    blockId = id;
}

int Cell::getBlockId() const {
    return blockId;
}

void Cell::setValue(int val) {
    value = val;
}

int Cell::getValue() const {
    return value;
}

void Cell::setHasNumber(bool has) {
    hasNum = has;
}

bool Cell::hasNumber() const {
    return hasNum;
}

void Cell::setIsSymmetry(bool sym) {
    symmetry = sym;
    if (sym) asymmetry = false;
}

bool Cell::isSymmetry() const {
    return symmetry;
}

void Cell::setIsAsymmetry(bool asym) {
    asymmetry = asym;
    if (asym) symmetry = false;
}

bool Cell::isAsymmetry() const {
    return asymmetry;
}