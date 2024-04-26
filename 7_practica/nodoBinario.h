#ifndef NODOBINARIO_H
#define NODOBINARIO_H

#include <iostream>

template<class key>
class NodoBinario {
  public:
    NodoBinario(const key&);
    void addLeft(NodoBinario*);
    void addRight(NodoBinario*);
    key getDato() {return dato_;};
    NodoBinario*& getRight() {return right_;};
    NodoBinario*& getLeft() {return left_;};
    void setDato(key dato) {dato_ = dato;};
    void setRight(NodoBinario* right) {right_ = right;};
    void setLeft(NodoBinario* left) {left_ = left;};
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
class nodoAVL : public NodoBinario<key> {
  public:
    nodoAVL(const key& dato): NodoBinario<key>(dato) {
      balance_ = 0;
    }
    int getBalance() {return balance_;};
    void setBalance(int balance) {balance_ = balance;};
  private:
    int balance_;
};

template<class key>
NodoBinario<key>::NodoBinario(const key& dato): left_(nullptr), right_(nullptr) {
  dato_ = dato;
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