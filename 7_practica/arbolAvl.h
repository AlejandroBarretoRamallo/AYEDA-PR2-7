#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include "arbolBinario.h"
#include "nodoBinario.h"


template<class key>
class ArbolBinarioAVL : public ArbolBinarioBusqueda<key> {
  public:
    bool insertar(const key&);
    nodoAVL<key>* isBalanced();
    ArbolBinarioAVL(bool trace): ArbolBinarioBusqueda<key>() {
      trace_ = trace;
      this->raiz_ = nodo_raiz_;
    };
  private:
    nodoAVL<key>* checkBalance(nodoAVL<key>*&);
    bool insertar_rama(nodoAVL<key>*&, key);
    void actualizar_balance(nodoAVL<key>*&);
    bool trace_;
    int tam_rama(NodoBinario<key>*&);
    void rotate(nodoAVL<key>*&);
    void rotate_II(nodoAVL<key>*&);
    void rotate_ID(nodoAVL<key>*&);
    void rotate_DI(nodoAVL<key>*&);
    void rotate_DD(nodoAVL<key>*&);
    nodoAVL<key>* nodo_raiz_;
};

template<class key>
nodoAVL<key>* ArbolBinarioAVL<key>::isBalanced() {
  return checkBalance(nodo_raiz_);
}

template<class key>
nodoAVL<key>* ArbolBinarioAVL<key>::checkBalance(nodoAVL<key>*& nodo) {
  if (nodo == nullptr) {
    return nullptr;
  }
  else {
    if (nodo->getBalance() > 1 || nodo->getBalance() < -1) {
      return nodo;
    }
    else {
      NodoBinario<key>* nodo_ = checkBalance(nodo->getLeft());
      if (nodo_ != nullptr) {
        return nodo_;
      }
      else {
        return checkBalance(nodo->getRight());
      }
    }
  }
}

template<class key>
bool ArbolBinarioAVL<key>::insertar(const key& clave) {
  if (this->buscar(clave)) {
    std::cout << "El elemento ya existe\n";
    return false;
  }
  bool exito = insertar_rama(nodo_raiz_, clave);
  if (exito) {
    actualizar_balance(nodo_raiz_);
    nodoAVL<key>* nodo = isBalanced();
    if (nodo != nullptr) {
      rotate(nodo);
    }
  }
  return exito;
}

template<class key>
bool ArbolBinarioAVL<key>::insertar_rama(nodoAVL<key>*& nodo, key clave) {
  if (nodo == nullptr) {
    nodo = new nodoAVL<key>(clave);
    return true;
  }
  else if (nodo->getDato() > clave) {
    return insertar_rama(nodo->getLeft(), clave);
  }
  else {
    return insertar_rama(nodo->getRight(), clave);
  }
  return false;
}

template<class key>
void ArbolBinarioAVL<key>::rotate(nodoAVL<key>*& nodo) {
  if (trace_) {
    std::cout << this;
  }
  if (nodo->getBalance() < -1) {
    nodoAVL<key>* sub_rama = nodo->getRight();
    if (sub_rama->getBalance() < 0) {
      if (trace_) {
        std::cout << "rotate_DD\n";
      }
      rotate_DD(nodo);
    }
    else if (sub_rama->getBalance() > 0) {
      if (trace_) {
        std::cout << "rotate_DI\n";
      }
      rotate_DI(nodo);
    }
  }
  else if (nodo->getBalance() > 1) {
    NodoBinario<key>* sub_rama = nodo->getLeft();
    if (sub_rama->getBalance() < 0) {
      if (trace_) {
        std::cout << "rotate_ID\n";
      }
      rotate_ID(nodo);
    }
    else if (sub_rama->getBalance() > 0) {
      if (trace_) {
        std::cout << "rotate_II\n";
      }
      rotate_II(nodo);
    }
  }
  if (trace_) {
    std::cout << this;
  }
}

template<class key>
void ArbolBinarioAVL<key>::actualizar_balance(nodoAVL<key>*& nodo) {
  if (nodo != nullptr) {
    nodo->setBalance(tam_rama(nodo->getRight()) - tam_rama(nodo->getLeft()));
    actualizar_balance(nodo->getLeft());
    actualizar_balance(nodo->getRight());
  }
}

template<class key>
int ArbolBinarioAVL<key>::tam_rama(NodoBinario<key>*& nodo) {
  if (nodo == nullptr) {
    return 0;
  }
  else {
    return 1 + tam_rama(nodo->getLeft()) + tam_rama(nodo->getRight());
  }
}

template<class key>
void ArbolBinarioAVL<key>::rotate_II(nodoAVL<key>*& nodo) {
  NodoBinario<key>* nodo1 = nodo->getLeft();
  nodo->setLeft(nodo1->getLeft());
  nodo1->setRight(nodo);
  if (nodo1->getBalance() == 1) {
     nodo->setBalance(0);
     nodo1->setBalance(0);
  }
  else { // nodo1->bal == 0
    nodo->setBalance(1);
    nodo1->setBalance(1);
  }
  nodo = nodo1;
}

template<class key>
void ArbolBinarioAVL<key>::rotate_ID (nodoAVL<key>* &nodo) {
  NodoBinario<key>* nodo1 = nodo->getLeft();
  NodoBinario<key>* nodo2 = nodo1->getRight();
  nodo->setLeft(nodo2->getRight());
  nodo2->setRight(nodo);
  nodo1->setRight(nodo2->getLeft());
  nodo2->setLeft(nodo1);
  if (nodo2->getBalance() == -1) {
    nodo1->setBalance(1);
  } 
  else  {
    nodo1->setBalance(0);
  }
  if (nodo2->getBalance() == 1) {
    nodo->setBalance(-1);
  }
  else  {
    nodo->setBalance(0); 
  }
  nodo2->setBalance(0);
  nodo = nodo2;
}

template<class key>
void ArbolBinarioAVL<key>::rotate_DI(nodoAVL<key>* &nodo) {
  NodoBinario<key>* nodo1 = nodo->getRight();
  NodoBinario<key>* nodo2 = nodo1->getLeft();
  nodo->setRight(nodo2->getLeft());
  nodo2->setLeft(nodo);
  nodo1->setLeft(nodo2->getRight());
  nodo2->setRight(nodo1);
  if (nodo2->getBalance() == 1) {
    nodo1->setBalance(-1);
  } 
  else  {
    nodo1->setBalance(0);
  }
  if (nodo2->getBalance() == -1) {
    nodo->setBalance(1); 
  }
  else  {
    nodo->setBalance(0);
  }
  nodo2->setBalance(0);
  nodo = nodo2;
}

template<class key>
void ArbolBinarioAVL<key>::rotate_DD (nodoAVL<key>* &nodo) {
  NodoBinario<key>* nodo1 = nodo->getRight();
  nodo->setRight(nodo1->getLeft());
  nodo1->setLeft(nodo);
  if (nodo1->getBalance() == -1) {
     nodo->setBalance(0);
     nodo1->setBalance(0);
  }
  else { // nodo1->bal == 0
    nodo->setBalance(-1);
    nodo1->setBalance(1);
  }
  nodo = nodo1; 
}




#endif