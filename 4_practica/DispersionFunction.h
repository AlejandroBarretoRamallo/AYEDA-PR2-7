#ifndef DISPERSIONFUNCTION_H
#define DISPERSIONFUNCTION_H

#include <iostream>
#include <stdlib.h>

template <class key>

class DispersionFunction {
  public:
    DispersionFunction(unsigned); 
    virtual unsigned operator()(const key&) const = 0;
  protected:
    unsigned tableSize_;
};

template <class key>

class Module_DispersionFunction : public DispersionFunction<key> {
  public:
    unsigned operator()(const key&) const;
    Module_DispersionFunction(unsigned tableSize): DispersionFunction<key>(tableSize) {};
};

template <class key>

class Sum_DispersionFunction : public DispersionFunction<key> {
  public:
    unsigned operator()(const key&) const;
    Sum_DispersionFunction(unsigned tableSize): DispersionFunction<key>(tableSize) {};
};

template <class key>

class Random_DispersionFunction : public DispersionFunction<key> {
  public:
    Random_DispersionFunction(unsigned tableSize): DispersionFunction<key>(tableSize) {};  
    unsigned operator()(const key&) const; 
};

#endif