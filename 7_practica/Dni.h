#ifndef DNI_H
#define DNI_H

#include <iostream>
#include <cstdlib> 

class Dni {
  public:
    unsigned getDni() const {return dni_;};
    Dni() {   // generador de dni aleatorio
    int min = 10000000;
    int max = 99999999;
    dni_ = rand() % (max - min + 1) + min; // nos aseguramos de que tenga 8 digitos
    }
    Dni(unsigned dni) {
      dni_ = dni;
    }
    bool operator==(const Dni& dni) const {   // sobrecarga del operador ==
      return dni_ == dni.getDni();
    }
    operator unsigned int() const {return dni_;}; // sobrecarga del operador de conversion a unsigned int
    bool operator<(const Dni& dni) const {  // sobrecarga del operador <
      return dni_ < dni.getDni();
    }
    bool operator>(const Dni& dni) const {  // sobrecarga del operador >
      return dni_ > dni.getDni();
    }
    bool operator<=(const Dni& dni) const {  // sobrecarga del operador <=
      return dni_ <= dni.getDni();
    }
    bool operator>=(const Dni& dni) const {  // sobrecarga del operador >=
      return dni_ >= dni.getDni();
    }
  private:
    unsigned dni_;
};

#endif