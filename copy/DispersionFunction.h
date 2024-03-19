#ifndef DISPERSIONFUNCTION_H
#define DISPERSIONFUNCTION_H

#include <iostream>
#include <stdlib.h>

template <class key>
class DispersionFunction {
  public:
    DispersionFunction(unsigned tableSize) {tableSize_ = tableSize;}; 
    virtual unsigned operator()(const key& clave) const = 0;
  protected:
    unsigned tableSize_;
};

template <class key>
class Module_DispersionFunction : public DispersionFunction<key> {
  public:
    unsigned operator()(const key& clave) const {return unsigned(clave) % this -> tableSize_;}; //fd de modulo	
    Module_DispersionFunction(unsigned tableSize): DispersionFunction<key>(tableSize) {};
};

template <class key>
class Sum_DispersionFunction : public DispersionFunction<key> {
  public:
    unsigned operator()(const key& clave) const; 
    Sum_DispersionFunction(unsigned tableSize): DispersionFunction<key>(tableSize) {}; 
};

template <class key>
class Random_DispersionFunction : public DispersionFunction<key> {
  public:
    Random_DispersionFunction(unsigned tableSize): DispersionFunction<key>(tableSize) {};  
    unsigned operator()(const key& clave) const {
      srand(unsigned(clave)); // usammos semilla siempre para obtener el mismo resultado
      return rand() % this -> tableSize_;  // devolvemos resultado pseudoaleatorio
    };   
};

template <class key>
unsigned Sum_DispersionFunction<key>::operator()(const key& clave) const {
  unsigned num = unsigned(clave);
  int suma = 0;
  while (num > 0) { // sumamos los digitos del dni
    suma += num % 10;
    num = num / 10;
  }
  return suma % this -> tableSize_;
}

#endif