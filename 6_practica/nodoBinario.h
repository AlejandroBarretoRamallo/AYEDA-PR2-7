#ifndef NODOBINARIO_H
#define NODOBINARIO_H

#include <iostream>

template<class key>
class nodoBinario {
  public:
    nodoBinario(key);
    void addLeft(nodoBinario*);
    void addRight(nodoBinario*);
    friend std::ostream& operator<<(std::ostream& cout, const nodoBinario<key>& nodo) {
      cout << nodo.dato_;
      return cout;
    }
  protected:
    key dato_;
    nodoBinario *left_;
    nodoBinario *right_;
};

template<class key>
nodoBinario<key>::nodoBinario(key dato) {
  dato_ = dato;
  left_ = nullptr;
  right_ = nullptr;
}

template<class key>
void nodoBinario<key>::addLeft(nodoBinario* izq) {
  left_ = izq;
}

template<class key>
void nodoBinario<key>::addRight(nodoBinario* der) {
  right_ = der;
}

#endif