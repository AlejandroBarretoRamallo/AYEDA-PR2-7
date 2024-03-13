#include "DispersionFunction.h"

template <class key>

DispersionFunction<key>::DispersionFunction(unsigned tableSize) {
  tableSize_ = tableSize;
}

template<class key>

unsigned Module_DispersionFunction<key>::operator()(const key& clave) const {
  return clave % tableSize_;
}

template <class key>

unsigned Sum_DispersionFunction<key>::operator()(const key& clave) const {
  unsigned sum = 0;
  while(clave > 0) {
    sum += clave % 10;
    clave /= 10;
  }
  return clave % tableSize_;
}

template <class key>

unsigned Random_DispersionFunction<key>::operator()(const key& clave) const {
  return rand(srand(clave)) % tableSize_;
}