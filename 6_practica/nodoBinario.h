#ifndef NODOBINARIO_H
#define NODOBINARIO_H

#include <iostream>

template<class key>
class NodoBinario {
  public:
    NodoBinario(const key&);
    void addLeft(NodoBinario*);
    void addRight(NodoBinario*);
    key getDato() const {return dato_;};
    NodoBinario* getRight() const {return right_;};
    NodoBinario* getLeft() const {return left_;};
    void setDato(const key dato) {dato_ = dato;};
    void setRight(const NodoBinario* right) {right_ = right;};
    void setLeft(const NodoBinario* left) {left_ = left;};
    friend std::ostream& operator<<(std::ostream& cout, const NodoBinario<key>& nodo) {
      cout << nodo.dato_;
      return cout;
    }
  protected:
    key dato_;
    NodoBinario *left_;
    NodoBinario *right_;
};

template<class key>
NodoBinario<key>::NodoBinario(const key& dato) {
  dato_ = dato;
  left_ = nullptr;
  right_ = nullptr;
}

template<class key>
void NodoBinario<key>::addLeft(NodoBinario* izq) {
  left_ = izq;
}

template<class key>
void NodoBinario<key>::addRight(NodoBinario* der) {
  right_ = der;
}

#endif