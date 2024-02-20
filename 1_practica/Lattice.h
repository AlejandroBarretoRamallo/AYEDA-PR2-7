#ifndef LATTICE_H
#define LATTICE_H

#include <iostream>
#include <vector>
#include "Cell.h"
#include "Position.h"

class Cell;

class Lattice {
  public:
    ~Lattice();
    Lattice();
    Lattice(const std::string&, const std::string&);
    const Cell& getCell(const Position&) const;
    void nextGeneration();
    int getSize() const;
    Cell* getCelulas();
    std::string getBorderType() {return borderType_;};
    int getN_generation() const {return n_generation_;};
    void updateN_generation();
  private:
    Cell *celulas_;
    int size_;
    std::string borderType_;
    int n_generation_;
};

std::ostream& operator<<(std::ostream&, const Lattice&);

#endif