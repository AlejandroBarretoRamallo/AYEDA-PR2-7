#ifndef EXPLORATIONFUNCTION_H
#define EXPLORATIONFUNCTION_H

#include <iostream>
#include "DispersionFunction.h"

template <class key>

class ExplorationFunction {
  public:
    virtual unsigned operator()(const key&, unsigned i) const = 0;
    ExplorationFunction(unsigned tableSize) {tableSize_ = tableSize;};
  protected:
    unsigned tableSize_;
};

template <class key>

class Lineal_ExplorationFunction : public ExplorationFunction<key> {
  public:
    unsigned operator()(const key&, unsigned i) const {return i % this-> tableSize_;};
    Lineal_ExplorationFunction(unsigned tableSize): ExplorationFunction<key>(tableSize) {};
};

template<class key>

class Cuadratic_ExplorationFunction : public ExplorationFunction<key> {
  public:
    unsigned operator()(const key&, unsigned i) const {return (i * i) % this -> tableSize_;};
    Cuadratic_ExplorationFunction(unsigned tableSize): ExplorationFunction<key>(tableSize) {};
};

template <class key>

class bidispersion_ExplorationFunction: public ExplorationFunction<key> {
  public:
    unsigned operator()(const key& clave, unsigned i) const {return (dispersionFunction_(clave) * i) % this -> tableSize_;};
    bidispersion_ExplorationFunction(unsigned tableSize, DispersionFunction<key> dispersionFunction): ExplorationFunction<key>(tableSize) { dispersionFunction_ = dispersionFunction;};
  private:
    DispersionFunction<key> dispersionFunction_;
};

template <class key>

class Redispersion_ExplorationFunction: public ExplorationFunction<key> {
  public:
    unsigned operator()(const key& clave, unsigned i) const {return (dispersionFunction_(dispersionFunction_(clave))) % this -> tableSize_;};
    Redispersion_ExplorationFunction(unsigned tableSize,DispersionFunction<key> dispersionFunction): ExplorationFunction<key>(tableSize) {dispersionFunction_ = dispersionFunction;};
  private:
    DispersionFunction<key> dispersionFunction_;
};

#endif