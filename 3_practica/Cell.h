#ifndef CELL_H
#define CELL_H

#include <iostream>

#include <iostream>
#include "State.h"
#include "Position.h"  
#include "Lattice.h"

class Lattice;

class Cell {
  public:
    ~Cell();
    Cell(Position*, const  State&); 
    State getState() const;   
    void setState(State);    
    virtual int nextState(Lattice&) = 0; 
    virtual void updateState() = 0;
    void setNextState(const State&);
    friend std::ostream& operator<<(std::ostream&, const Cell&);
  protected:
    virtual std::ostream& display(std::ostream&) const = 0;
    State state_;
    Position* position_;
    State next_state_;
};

class CellACE: public Cell {
  public:
    virtual int nextState(Lattice&) = 0;  
    virtual void updateState() = 0;
    virtual std::ostream& display(std::ostream&) const = 0;
    CellACE(Position* position, const State& state): Cell(position, state) {};
};

class CellLife: public Cell {
  public:
    virtual int nextState(Lattice&) = 0;  
    virtual void updateState() = 0;
    virtual std::ostream& display(std::ostream&) const = 0;
    CellLife(Position* position, const State& state): Cell(position, state) {};
};

class CellACE110: public CellACE {
  public:
    void updateState();
    int nextState(Lattice&);  
    std::ostream& display(std::ostream&) const;
    CellACE110(Position* position, const State& state): CellACE(position, state) {};
};

class CellACE30: public CellACE {
  public:
    void updateState();
    int nextState(Lattice&);  
    std::ostream& display(std::ostream&) const;
    CellACE30(Position* position, const State& state): CellACE(position, state) {};
};

class CellLife23_3: public CellLife {
  public:
    void updateState();
    int nextState(Lattice&);
    std::ostream& display(std::ostream&) const;
    CellLife23_3(Position* position, const State& state): CellLife(position, state) {};
};

class CellLife51_346: public CellLife {
  public:
    void updateState();
    int nextState(Lattice&);
    std::ostream& display(std::ostream&) const;
    CellLife51_346(Position* position, const State& state): CellLife(position, state) {};
};


#endif
