#ifndef DNI_H
#define DNI_H

#include <iostream>
#include <cstdlib> 

class Dni {
  public:
    unsigned getDni() const {return dni_;};
    Dni() {
      dni_ = 10000000 + (std::rand() % (99999999 - 10000000 + 1));
    }
    bool operator==(const Dni& dni) const {
      return dni_ == dni.getDni();
    }
    operator unsigned int() const {return dni_;};
  private:
    unsigned dni_;
};

#endif