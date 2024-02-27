#ifndef POSITION_H
#define POSITION_H

#include <cstdarg>
#include <stdexcept>
#include <iostream>

typedef int Coor_t;

class Position {
  public:
    virtual Coor_t operator[](unsigned int) const = 0;
};

template <int Dim = 2, class Coordinate_t = int>

class PositionDim: public Position {
  private:
    Coor_t Coordinates[Dim];
  public:
    // Constructor con lista variable de parámetros
    PositionDim(int sz, ...) {
      va_list vl;
      va_start(vl, sz);
      for(int d = 0; d < Dim; d++) {
        Coordinates[d] = va_arg(vl, Coordinate_t);
      }
      va_end(vl);
    }
    //operador para obtener posiciones
    Coor_t operator[](unsigned int i) const {
      try {
        return Coordinates[i];
      }
      catch(const std::exception& out_of_range) {
        std::cerr << "Error: " << out_of_range.what() << std::endl;
      }
    }
};

#endif