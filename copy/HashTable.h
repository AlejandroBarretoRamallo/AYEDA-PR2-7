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
    ~HashTable();
    bool search(const key&)const;  //hacer
    bool insert(const key&); // hacer
    void print();
  private:
    unsigned tableSize_;
    DispersionFunction<key>& fd_;
    ExplorationFunction<key>& fe_;
    unsigned blockSize_;
    Container** table_;
};

template <class key>
class HashTable <key, dynamicSequence<key>> {
  public:
    HashTable(unsigned, DispersionFunction<key>&);
    bool search(const key&)const;
    bool insert(const key&); 
    void print();
    ~HashTable();
  private:
    std::vector<dynamicSequence<key>> table_;
    unsigned tableSize_;
    DispersionFunction<key>& fd_;
};

template <class key, class container>
HashTable<key,container>::HashTable(unsigned tableSize, DispersionFunction<key>& fd, ExplorationFunction<key>& fe, unsigned blockSize)
                                   : tableSize_(tableSize), fd_(fd), fe_(fe), blockSize_(blockSize), table_(new container*[tableSize_]) {
    for (int i = 0; i < tableSize_; i++) {
      table_[i] = new container(blockSize_);
    }
}

template <class key, class container>   // buscar en hastable con secuencia estatica
bool HashTable<key, container>::search(const key& clave) const {
  unsigned pos = fd_(clave);
  if (table_[pos]->search(clave)) {
    return true;
  }
  unsigned pos_;
  for (int i = 0; i < tableSize_; ++i) {
    pos_ = (pos + fe_(clave, i)) % tableSize_;
    if (table_[pos_]-> search(clave)) {
      return true;
    }
    if (!table_[pos_]-> isFull()) {
      return false;
    }
  }
  return false;
}

template <class key, class container>   // insertar en hastable con secuencia estatica
bool HashTable<key, container>::insert(const key& clave) {
  bool full = true;
  for (int i = 0; i < tableSize_; ++i) {
    if (!table_[i]-> isFull()) {
      full = false;
    }
  }
  if (full) {
    return false;
  }
  unsigned pos = fd_(clave);
  if (!table_[pos] -> search(clave)) {
    if (!table_[pos] -> isFull()) {
      table_[pos] -> insert(clave);
      return true;
    }
    else {
      unsigned pos_;
      for (int i = 0; i < tableSize_; ++i) {
        pos_ = (pos + fe_(clave, i)) % tableSize_;
        if (!table_[pos_]-> search(clave)) {
          if (!table_[pos_]-> isFull()) {
            table_[pos_]-> insert(clave);
            return true;
          }
        }
        else {
          std::cout << "Ya existe: " << "\n";
          return false;
        }
      }
    }
  }
  else {
    std::cout << "Ya existe: " << "\n";
    return false;
  }
  return false;
}

template <class key>   // constructor de hastable con secuencia dinamica
HashTable<key, dynamicSequence<key>>::HashTable(unsigned tableSize, DispersionFunction<key>& fd): fd_(fd) {
  tableSize_ = tableSize;
  table_ = std::vector<dynamicSequence<key>>(tableSize_);
}

template <class key>   // buscar en hastable con secuencia dinamica
bool HashTable<key, dynamicSequence<key>>::search(const key& clave) const {
  unsigned pos = fd_(clave);
  if (table_[pos].search(clave)) {
    return true;
  }
  return false;
}

template <class key>   // insertar en hastable con secuencia dinamica
bool HashTable<key, dynamicSequence<key>>::insert(const key& clave) {
  unsigned pos = fd_(clave);
  if (table_[pos].search(clave)) {
    std::cout << "Ya existe: " << std::endl;
    return false;
  }
  if (table_[pos].insert(clave)) {
    return true;
  }
  return false;
}

template <class key>   // imprimir hastable con secuencia dinamica
void HashTable<key, dynamicSequence<key>>::print() {
  for (int i = 0; i < tableSize_; i++) {
    std::cout << "Posicion " << i << ":\n";
    for (int j = 0; j < table_[i].getSecuencia().size(); j++) {
      std::cout << unsigned(table_[i][j]) << "\n";
    }
    std::cout << "\n";
  }
}

template <class key, class container>   // imprimir hastable con secuencia estatica
void HashTable<key, container>::print() {
  for (int i = 0; i < tableSize_; i++) {
    std::cout << "Posicion " << i << ":\n";
    for (int j = 0; j < blockSize_; j++) {
      if (((*table_[i])[j]) != nullptr) {
        std::cout << unsigned(*(*table_[i])[j]) << "\n";
      }
    }
    std::cout << "\n";
  }
}

template <class key, class Container>
HashTable<key, Container>::~HashTable() {
  for (int i = 0; i < tableSize_; i++) {
    if (table_[i] != nullptr) {
      delete table_[i];
    }
  }
  delete[] table_;
}

template <class key>
HashTable<key, dynamicSequence<key>>::~HashTable() {
  table_.clear();
}
#endif