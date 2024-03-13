#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include "Sequence.h"
#include "DispersionFunction.h"
#include "ExplorationFunction.h"

template <class key, class Container = staticSequence<key> >

class HashTable {
  public:
    HashTable(unsigned,DispersionFunction<key>&, ExplorationFunction<key>&,unsigned);
  private:
    unsigned tableSize_;
    DispersionFunction<key>& fd_;
    ExplorationFunction<key>& fe_;
    unsigned blockSize_;
    Container* table_;
};

template <class key, class Container>

class HashTable <key, dynamicSequence<key>> {
  public:
    HashTable(unsigned, DispersionFunction<key>&);
  private:
    Container* table_;
    unsigned tableSize_;
};

#endif