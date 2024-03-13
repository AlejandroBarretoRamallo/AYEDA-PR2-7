#include "Sequence.h"

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
  return true;
}

template <class key>

bool staticSequence<key>::search(const key& clave) const {
  for (int i = 0; i < secuencia_.size(); ++i) {
    if (secuencia_[i] == clave) {
      return true;
    }
  }
  return false;
}

template <class key>

bool staticSequence<key>::insert(const key& clave) {
  return true;
}

template <class key>

bool staticSequence<key>::isFull() const {
  for (int i = 0; i < secuencia_.size(); ++i) {
    if (secuencia_[i] == nullptr) {
        return false;
    }
  }
  return true;
}