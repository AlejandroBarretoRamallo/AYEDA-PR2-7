#ifndef CELL_H
#define CELL_H

#include <iostream>

#include "State.h"
#include "Position.h"
#include "Lattice.h"

class Lattice;

class Cell {
  public:
    Cell(const Position&, const  State&); 
    Cell();           
    State getState() const;
    void updateState(); 
    void setNextState(const int&);
    int NextState(Lattice&) const;  // falta no border
    bool IsBorder(Lattice&) const; 
    State getNextState() { return next_state_;};
  private:
    State state_;
    Position position_;
    State next_state_;
};

std::ostream& operator<<(std::ostream&, const Cell&); 

#endif