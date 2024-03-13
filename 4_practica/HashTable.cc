#include "HashTable.h"

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
    table_[i] = dynamicSequence(tableSize);
  }
}

template <class key, class Container>

bool HashTable<key, Container>::search(const key& clave)const {
  for (int i = 0; i < tableSize_; ++i) {
    if (table_[i].search(clave)) {
      return true;
    }
  }
  return false;
}

template <class key, class Container>

bool HashTable<key, Container>::insert(const key& clave)const {
  return true;
}

template <class key>

bool HashTable<key>::insert(const key& clave)const {
  return true;
}

template <class key, class Container>

bool HashTable<key, Container>::isFull()const {
  for (int i = 0; i < tableSize_; ++i) {
    if (!table_[i].isFull()) {
      return false;
    }
  }
  return true;
}

template<class key>

bool HashTable<key>::isFull()const {
  for (int i = 0; i < tableSize_; ++i) {
    if (!table_[i].isFull()) {
      return false;
    }
  }
  return true;
}

template <class key>

bool HashTable<key>::search(const key& clave)const {
  for (int i = 0; i < tableSize_; ++i) {
    if (table_[i].search(clave)) {
      return true;
    }
  }
  return false;
}