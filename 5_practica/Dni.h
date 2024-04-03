#ifndef DNI_H
#define DNI_H

#include <iostream>
#include <cstdlib> 

class Dni {
  public:
    unsigned getDni() const {return dni_;};
    Dni() {
      dni_ = rand() % 99999999 + 10000000;
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