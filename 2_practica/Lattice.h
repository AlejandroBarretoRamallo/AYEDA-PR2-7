#ifndef LATTICE_H
#define LATTICE_H

#include <iostream>
#include <vector>
#include <fstream>
#include "Cell.h"
#include "Position.h"


class Cell;

class Lattice {
  public:
    ~Lattice(); 
    Lattice();
    Lattice(int N, int M, std::string frontera); 
    Lattice(std::string fichero, std::string frontera); // leer desde fichero
    const Cell& getCell(const Position&) const; 
    void nextGeneration(); 
    int getRows() const {return rows_;};
    int getColumns() const {return colums_;};
    std::string getBorderType() {return borderType_;};
    int getN_generation() const {return n_generation_;};
    void updateN_generation();
    std::size_t Population() const;
    friend std::ostream& operator<<(std::ostream&, const Lattice&); 
  private:
    std::vector<std::vector<Cell*>> celulas_;
    int rows_;
    int colums_;
    std::string borderType_;
    int n_generation_;
    void insertDownRow();
    void insertLeftColum();
    void insertUpperRow();
    void insertRightColum();
    //atributos para saber si se han añadido filas o columnas, guarda el orgien y el final de la matriz
    Position highCorner_;
    Position lowCorner_;
    int Border();  // comprueba si hay que añadir filas o columnas segun donde se encuentren las células muertas
};



#endif