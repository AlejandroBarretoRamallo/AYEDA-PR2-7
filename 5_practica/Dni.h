#ifndef DNI_H
#define DNI_H

#include <iostream>
#include <cstdlib> 

class Dni {
  public:
    unsigned getDni() const {return dni_;};
    Dni() {
    int min = 10000000;
    int max = 99999999;
    dni_ = rand() % (max - min + 1) + min;
    }
    Dni(unsigned dni) {
      dni_ = dni;
    }
    bool operator==(const Dni& dni) const {
      return dni_ == dni.getDni();
    }
    operator unsigned int() const {return dni_;};
    bool operator<(const Dni& dni) const {
      return dni_ < dni.getDni();
    }
    bool operator>(const Dni& dni) const {
      return dni_ > dni.getDni();
    }
    bool operator<=(const Dni& dni) const {
      return dni_ <= dni.getDni();
    }
    bool operator>=(const Dni& dni) const {
      return dni_ >= dni.getDni();
    }
  private:
    unsigned dni_;
};

#endif