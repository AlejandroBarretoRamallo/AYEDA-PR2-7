#ifndef POSITION_H
#define POSITION_H

#include <iostream>

class Position {
  public:
    const int getPosition() const {return posicion_;};
    Position(int posicion);
    Position();
  private:
    int posicion_;
};

#endif