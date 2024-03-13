#include "ExplorationFunction.h"

template<class key>

ExplorationFunction<key>::ExplorationFunction(unsigned tableSize) {
  tableSize_ = tableSize;
}

template<class key>

unsigned Lineal_ExplorationFunction<key>::operator()(const key& clave, unsigned i) const {
  return i % this-> tableSize_;
}

template <class key>

unsigned Cuadratic_ExplorationFunction<key>::operator()(const key& clave, unsigned i) const {
  return (i * i) % this -> tableSize_;
}

template <class key>

unsigned bidispersion_ExplorationFunction<key>::operator()(const key& clave, unsigned i) const {
  return (dispersionFunction_(clave) * i) % this -> tableSize_;
}

template <class key>

unsigned Redispersion_ExplorationFunction<key>::operator()(const key& clave, unsigned i) const {
  return (dispersionFunction_(dispersionFunction_(clave))) % this -> tableSize_;
}