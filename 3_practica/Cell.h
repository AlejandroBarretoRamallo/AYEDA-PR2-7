#ifndef CELL_H
#define CELL_H

#include <iostream>

#include "State.h"
#include "Position.h"
//#include "Lattice.h"

//class Lattice;

class Cell {
  public:
    Cell(Position&, const  State&); 
    State getState() const;   
    void setState(State);    
    virtual int nextState() = 0; 
    virtual void updateState() = 0;
    friend std::ostream& operator<<(std::ostream&, const Cell&);
  protected:
    virtual std::ostream& display(std::ostream&) const = 0;
    State state_;
    Position& position_;
    State next_state_;
};

class CellACE: public Cell {
  public:
    virtual int nextState() = 0;  
    void updateState();
    virtual std::ostream& display(std::ostream&) const = 0;
    CellACE(Position& position, const State& state): Cell(position, state) {};
};

class CellLife: public Cell {
  public:
    virtual int nextState() = 0;  
    void updateState();
    virtual std::ostream& display(std::ostream&) const = 0;
    CellLife(Position& position, const State& state): Cell(position, state) {};
};

class CellACE110: public CellACE {
  public:
    int nextState();  // falta implementar
    std::ostream& display(std::ostream&) const;
    CellACE110(Position& position, const State& state): CellACE(position, state) {};
};

class CellACE30: public CellACE {
  public:
    int nextState();  // falta implementar
    std::ostream& display(std::ostream&) const;
    CellACE30(Position& position, const State& state): CellACE(position, state) {};
};

class CellLife23_3: public CellLife {
  public:
    int nextState(); // falta implementar
    std::ostream& display(std::ostream&) const;
    CellLife23_3(Position& positionn, const State& state): CellLife(positionn, state) {};
};

class CellLife51_346: public CellLife {
  public:
    int nextState(); // falta implementar
    std::ostream& display(std::ostream&) const;
    CellLife51_346(Position& positionn, const State& state): CellLife(positionn, state) {};
};


#endif
