#ifndef FACTORYCELL_H
#define FACTORYCELL_H

#include "Cell.h"

class Cell;

class FactoryCell {
  public:
    // Método creador de células
    virtual Cell* createCell(Position*, const State&) const = 0;
};

class FactoryCellACE110: public FactoryCell {
  public:
    Cell* createCell(Position*, const State&) const;
};

class FactoryCellACE30: public FactoryCell {
  public:
    Cell* createCell(Position*, const State&) const;
};

class FactoryCellLife23_3: public FactoryCell {   
  public:
    Cell* createCell(Position*, const State&) const;
};

class FactoryCellLife51_346: public FactoryCell {
  public: 
    Cell* createCell(Position*, const State&) const;
};


#endif