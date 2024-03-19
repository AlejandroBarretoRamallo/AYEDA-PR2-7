#ifndef DNI_H
#define DNI_H

#include <iostream>
#include <cstdlib> 

class Dni {
  public:
    unsigned getDni() const {return dni_;}; //getter
    Dni(unsigned dni) {
      dni_ = dni;
    }
    Dni() {
      dni_ = 10000000 + rand() % 90000000;  // dni aleatorio de 8 digitos
    };
    bool operator==(const Dni& dni) const {
      return dni_ == dni.getDni();
    }
    operator unsigned() const {return dni_;};
  private:
    unsigned dni_;
};

#endif