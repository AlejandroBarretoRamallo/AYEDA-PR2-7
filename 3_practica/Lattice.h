#ifndef LATTICE_H
#define LATTICE_H

#include <iostream>
#include <vector>
#include <iostream>
#include <vector>
#include "Cell.h"  
#include "Position.h"
#include "FactoryCell.h"  
#include <fstream>

class Cell;

class FactoryCell;

class Lattice {
  public:
    virtual ~Lattice();
    virtual Cell& operator[](const Position&) const = 0;
    virtual void nextGeneration() = 0;
    virtual std::size_t Population() const = 0;
    virtual std::ostream& display(std::ostream&) = 0;
    friend std::ostream& operator<<(std::ostream&, Lattice& ); 
    virtual int getRows() const = 0;
    virtual int getColumns() const = 0;
    virtual int getSize() const = 0;
    int getN_generation() const {return n_generation_;};
    void updateN_generation() {++n_generation_;};
  protected:
    int n_generation_;
};

class Lattice1D: public Lattice {
  public:
    ~Lattice1D();
    virtual Cell& operator[](const Position&) const = 0;
    void nextGeneration();  
    std::size_t Population() const; 
    std::ostream& display(std::ostream&); 
    Lattice1D(int, FactoryCell&); 
    Lattice1D(std::string, FactoryCell&);
    int getSize() const {return size_;};
    int getRows() const {return size_;};
    int getColumns() const {return 0;};
    protected:
      std::vector<Cell*> celulas_;
      int size_;
      FactoryCell &tipoCelula_;
};

class Lattice1D_open: public Lattice1D {
  public:
    Lattice1D_open(int size, FactoryCell& celula, int border): Lattice1D(size, celula) {border_ = border;};
    Lattice1D_open(std::string fichero, FactoryCell& celula, int border): Lattice1D(fichero, celula) { border_ = border;};
    Cell& operator[](const Position&) const;
  private:
  int border_;
};

class Lattice1D_periodic: public Lattice1D {
  public:
    Lattice1D_periodic(int size, FactoryCell& celula): Lattice1D(size, celula) {}; 
    Lattice1D_periodic(std::string fichero, FactoryCell& celula): Lattice1D(fichero, celula) {};
    Cell& operator[](const Position&) const;
};

class Lattice2D: public Lattice {
  public:
    ~Lattice2D(); 
    virtual Cell& operator[](const Position&) const = 0;
    virtual void nextGeneration() = 0;
    std::size_t Population() const;
    std::ostream& display(std::ostream&); 
    Lattice2D(int, int, FactoryCell&);
    Lattice2D(std::string, FactoryCell&); 
    int getSize() const {return rows_*columns_;};
    int getRows() const {return rows_;};
    int getColumns() const {return columns_;};
    protected:
      std::vector<std::vector<Cell*>> celulas_;
      PositionDim<2> origen_;
      PositionDim<2> fin_;
      int rows_;
      int columns_;
      FactoryCell &tipoCelula_;
};

class Lattice2D_reflective: public Lattice2D {
  public:
    Lattice2D_reflective(int x, int y, FactoryCell& celula): Lattice2D(x, y, celula) {};
    Lattice2D_reflective(std::string fichero, FactoryCell&celula): Lattice2D(fichero, celula) {}; 
    Cell& operator[](const Position&) const; 
    void nextGeneration(); 
};

class Lattice2D_noborder: public Lattice2D {
  public:
    Lattice2D_noborder(int x, int y, FactoryCell& celula): Lattice2D(x, y, celula) {};
    Lattice2D_noborder(std::string fichero, FactoryCell&celula): Lattice2D(fichero, celula) {}; 
    Cell& operator[](const Position&) const; 
    void nextGeneration(); 
    void insertUpperRow();
    void insertLowerRow();
    void insertLeftColumn();
    void insertRightColumn();
    int Border();
};  

#endif