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
    Sequence() {};
};

template <class key>
class dynamicSequence : public Sequence<key> {
  public:
    bool search(const key&) const; 
    bool insert(const key&);
    dynamicSequence(): Sequence<key>() {secuencia_ = std::vector<key>(0);};
    key operator[](int i) const {return secuencia_[i];};
    std::vector<key> getSecuencia() const {return secuencia_;};
  private:
    std::vector<key> secuencia_;
};

template <class key>
class staticSequence : public Sequence<key> {
  public:
    bool search(const key&) const;
    bool insert(const key&);
    bool isFull() const;
    key* operator[](int i) const {return secuencia_[i];};
    staticSequence(unsigned blockSize): Sequence<key>() {
      secuencia_ = new key*[blockSize];
      for (int i = 0; i < blockSize; i++) {
        secuencia_[i] = nullptr;
      }
      size_ = blockSize;
    };
  private:
    key** secuencia_;
    unsigned size_;
};

template <class key>
bool staticSequence<key>::search(const key& clave) const {
  for (int i = 0; i < size_; i++) {
    if (secuencia_[i] == nullptr) {
      continue;
    }
    if (*secuencia_[i] == clave) {
      return true;
    }
  }
  return false;
}

template <class key>
bool staticSequence<key>::insert(const key& clave) {
  if (isFull()) {
    return false;
  }
  for (int i = 0; i < size_; i++) {
    if (secuencia_[i] == nullptr) {
      secuencia_[i] = new key(clave);
      return true;
    }
  }
  return false;
}

template <class key>
bool staticSequence<key>::isFull() const {
  for (int i = 0; i < size_; ++i) {
    if (secuencia_[i] == nullptr) {
      return false;
    }
  }
  return true;
}

template <class key>
bool dynamicSequence<key>::search(const key& clave) const {
  for (int i = 0; i < secuencia_.size(); i++) {
    if (secuencia_[i] == clave) {
      return true;
    }
  }
  return false;
}

template <class key>
bool dynamicSequence<key>::insert(const key& clave) {
  for (int i = 0; i < secuencia_.size(); i++) {
    if (secuencia_[i] == clave) {
      return false;
    }
  }
  secuencia_.push_back(clave);
  return true;
}
#endif