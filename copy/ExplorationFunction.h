#ifndef EXPLORATIONFUNCTION_H
#define EXPLORATIONFUNCTION_H

#include <iostream>
#include <cmath>

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
    unsigned operator()(const key& clave, unsigned i) const {return 1 + i % (this->tableSize_ - 1);};
    Lineal_ExplorationFunction(unsigned tableSize): ExplorationFunction<key>(tableSize) {};
};

template<class key>

class Cuadratic_ExplorationFunction : public ExplorationFunction<key> {
  public:
    unsigned operator()(const key& clave, unsigned i) const { return (((i + 1) * (i + 1)) - 1) % (this->tableSize_ - 1) + 1;}; 
    Cuadratic_ExplorationFunction(unsigned tableSize): ExplorationFunction<key>(tableSize){};
};

template <class key>

class bidispersion_ExplorationFunction: public ExplorationFunction<key> {
  public:
    unsigned operator()(const key& clave, unsigned i) const {
      return ((dispersionFunction_->operator()(clave) * (i + 1) - 1) % (this->tableSize_ - 1)) + 1;
    }
    bidispersion_ExplorationFunction(unsigned tableSize, DispersionFunction<key>* dispersionFunction): ExplorationFunction<key>(tableSize), dispersionFunction_(dispersionFunction) {};
  private:
    DispersionFunction<key>* dispersionFunction_;
};

template <class key>

class Redispersion_ExplorationFunction: public ExplorationFunction<key> {
  public:
    unsigned operator()(const key& clave, unsigned i) const {
      unsigned dispersionResult = dispersionFunction_->operator()(clave);
      return ((unsigned(pow(dispersionResult, i + 1))) % this->tableSize_ - 1) + 1;
    }
    Redispersion_ExplorationFunction(unsigned tableSize,DispersionFunction<key>* dispersionFunction): ExplorationFunction<key>(tableSize), dispersionFunction_(dispersionFunction) {};
  private:
    DispersionFunction<key>* dispersionFunction_;
};

#endif