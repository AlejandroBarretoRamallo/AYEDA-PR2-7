#ifndef DNI_H
#define DNI_H

#include <iostream>
#include <cstdlib> 

class Dni {
  public:
    unsigned getDni() const {return dni_;};
    Dni() {
      dni_ = 0;
    }
    Dni(unsigned dni) {
      dni_ = dni;
    }
    bool operator==(const Dni& dni) const {
      return dni_ == dni.getDni();
    }
    operator unsigned int() const {return dni_;};
  private:
    unsigned dni_;
};

#endif