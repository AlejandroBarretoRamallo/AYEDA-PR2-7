#ifndef ARBOLBINARIO_H
#define ARBOLBINARIO_H

#include "nodoBinario.h"

template<class key>
class ArbolBinario {
  public:
    virtual bool insertar(const key&) = 0;
    virtual bool buscar(const key&) const = 0; 
    void inorden() const;
    friend std::ostream& operator<<(std::ostream& out, ArbolBinario<key> arbol) {
      return out;
    }
    ArbolBinario() {raiz_ = nullptr;};
  protected:
    NodoBinario<key> *raiz_;
};

template<class key>
class ArbolBinarioBusqueda : public ArbolBinario<key> {
  public:
    bool insertar(const key&);  //hecho
    bool buscar(const key&);
  private:
    bool añadir_rama(NodoBinario<key>*, key);
    bool buscar_rama(NodoBinario<key>*, key);
};

template<class key>
class ArbolBinarioEquilibrado : public ArbolBinario<key> {
  public:
    bool insertar(const key&);
    bool buscar(const key&);
};

template<class key>
bool ArbolBinarioBusqueda<key>::insertar(const key& clave) {
  return añadir_rama(raiz_, clave);
}

template<class key>
bool ArbolBinarioBusqueda<key>::añadir_rama(NodoBinario<key>* nodo, key) {
  if (nodo == nullptr) {
    nodo == new NodoBinario<key>(clave);
    return true;
  }
  else if (nodo->getDato() < clave) {
    return añadir_rama(nodo->getLeft(), clave);
  }
  else if (nodo->getDato() > clave) {
    return añadir_rama(nodo->getRight(), clave);
  }
}

template<class key>
bool ArbolBinarioBusqueda<key>::buscar(const key& clave) {

}

#endif