#ifndef EXPLORATIONFUNCTION_H
#define EXPLORATIONFUNCTION_H

#include <iostream>
#include "DispersionFunction.h"

template <class key>

class ExplorationFunction {
  public:
    virtual unsigned operator()(const key&, unsigned) const = 0;
    ExplorationFunction(unsigned);
  protected:
    unsigned tableSize_;
};

template <class key>

class Lineal_ExplorationFunction : public ExplorationFunction<key> {
  public:
    unsigned operator()(const key&, unsigned) const;
    Lineal_ExplorationFunction(unsigned tableSize): ExplorationFunction<key>(tableSize) {};
};

template<class key>

class Cuadratic_ExplorationFunction : public ExplorationFunction<key> {
  public:
    unsigned operator()(const key&, unsigned) const;
    Cuadratic_ExplorationFunction(unsigned tableSize): ExplorationFunction<key>(tableSize) {};
};

template <class key>

class bidispersion_ExplorationFunction: public ExplorationFunction<key> {
  public:
    unsigned operator()(const key&, unsigned) const;
    bidispersion_ExplorationFunction(unsigned tableSize, DispersionFunction<key> dispersionFunction): ExplorationFunction<key>(tableSize) { dispersionFunction_ = dispersionFunction;};
  private:
    DispersionFunction<key> dispersionFunction_;
};

template <class key>

class Redispersion_ExplorationFunction: public ExplorationFunction<key> {
  public:
    unsigned operator()(const key&, unsigned) const;
    Redispersion_ExplorationFunction(unsigned tableSize,DispersionFunction<key> dispersionFunction): ExplorationFunction<key>(tableSize) {dispersionFunction_ = dispersionFunction;};
  private:
    DispersionFunction<key> dispersionFunction_;
};

#endif