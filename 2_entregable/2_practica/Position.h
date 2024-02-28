#ifndef POSITION_H
#define POSITION_H

#include <iostream>

class Position {
  public:
    const int getPosX() const{return pos_x_;};
    const int getPosY() const {return pos_y_;};
    Position(int pos_x, int pos_y);
    Position();
  private:
    int pos_x_;
    int pos_y_;
};

#endif