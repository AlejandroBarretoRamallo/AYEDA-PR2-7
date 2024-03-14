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
    unsigned operator()(const key& clave) const {return unsigned(clave) % this -> tableSize_;};
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
    unsigned operator()(const key& clave) const {return rand() % this -> tableSize_;}; 
};

template <class key>
unsigned Sum_DispersionFunction<key>::operator()(const key& clave)const {
  unsigned sum = 0;
    unsigned clave_ = unsigned(clave);
    while(clave_ > 0) {
      sum += clave_ % 10;
      clave_ /= 10;
    }
  return clave_ % this -> tableSize_;
}

#endif