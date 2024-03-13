#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include "DispersionFunction.h"
#include "ExplorationFunction.h"
#include <vector>

template <class key>

class Sequence {
  public:
    virtual bool search(const key&) const = 0;
    virtual bool insert(const key&) = 0;
};

template <class key>

class dynamicSequence : public Sequence<key> {
  public:
    bool search(const key&) const;
    bool insert(const key&);
  private:
    std::vector<key> secuencia_;
};

template <class key>

class staticSequence : public Sequence<key> {
  public:
    bool search(const key&) const; 
    bool insert(const key&);
    bool isFull() const;
  private:
    key* secuencia_;
};

#endif