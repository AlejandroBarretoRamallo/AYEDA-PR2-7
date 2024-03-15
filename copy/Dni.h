#ifndef DNI_H
#define DNI_H

#include <iostream>
#include <cstdlib> 

class Dni {
  public:
    unsigned getDni() const {return dni_;};
    Dni(unsigned dni) {
      dni_ = dni;
    }
    Dni() {dni_ = 0;};
    bool operator==(const Dni& dni) const {
      return dni_ == dni.getDni();
    }
    operator unsigned() const {return dni_;};
  private:
    unsigned dni_;
};

#endif