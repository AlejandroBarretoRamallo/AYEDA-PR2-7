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
    bool search(const key&)const;  //hacer
    bool insert(const key&)const; // hacer
  private:
    unsigned tableSize_;
    DispersionFunction<key>& fd_;
    ExplorationFunction<key>& fe_;
    unsigned blockSize_;
    Container* table_;
};

template <class key>
class HashTable <key> {
  public:
    HashTable(unsigned, DispersionFunction<key>&);
    bool search(const key&)const; //hacer
    bool insert(const key&)const; // hacer
  private:
    dynamicSequence<key>* table_;
    unsigned tableSize_;
    DispersionFunction<key> fd_;
};
// metodos de ambas clases
template <class key, class Container>
HashTable<key, Container>::HashTable(unsigned tableSize,DispersionFunction<key>& fd, ExplorationFunction<key>& fe,
                                    unsigned blockSize) {
  tableSize_ = tableSize;
  blockSize_ = blockSize;
  fd_ = fd;
  fe_ = fe;
  table_ = new staticSequence[tableSize_];
  for (int i = 0; i < tableSize_; ++i) {
    table_[i] = staticSequence(blockSize_);
  }
}

template <class key>
HashTable<key>::HashTable(unsigned tableSize, DispersionFunction<key>& fd) {
  fd_ = fd;
  table_ = new dynamicSequence[tableSize_];
  for (int i = 0; i < tableSize_; ++i) {
    table_[i] = dynamicSequence<key>();
  }
}

template <class key, class Container>
bool HashTable<key, Container>::search(const key& clave)const {
  unsigned pos = fd_(clave);
  if (table_[pos].search(clave)) {
    return true;
  }
  for (int i = 0; i < tableSize_; ++i) {
    unsigned pos2 = fe_(clave, i);
    if (table_[pos2].search(clave)) {
      return true;
    }
    if (!table_[pos2].isFull()) {
      return false;
    }
  }
  return false;
}

template <class key, class Container>
bool HashTable<key, Container>::insert(const key& clave)const {
  for (int i = 0; i < tableSize_; ++i) {
    if (!table_[i].isFull()) {
      return false;
    }
  }
  unsigned pos = fd_(clave);
  if (!table_[pos].isFull) {
    table_[i].insert(clave);
    return true;
  }
  for (int i = 0; i < tableSize_; ++i) {
    unsigned pos2 = fe_(clave, i);
    if (!table_[pos2].isFull()) {
      table_[i].insert(clave);
      return true;
    }
  }
  return false;
}

template <class key>
bool HashTable<key>::insert(const key& clave)const {
  unsigned pos = fd_(clave);
  table_[pos].insert(clave);
  return true;
}

template <class key>
bool HashTable<key>::search(const key& clave)const {
  unsigned pos = fd_(clave);
  if (table_[pos].search(clave)) {
    return true;
  }
  return false;
}
#endif