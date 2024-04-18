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
    ArbolBinario();
  protected:
    NodoBinario<key> *nodo;
};

template<class key>
class ArbolBinarioBusqueda : public ArbolBinario<key> {
  public:
    bool insertar(const key&);
    bool buscar(const key&);
};

template<class key>
class ArbolBinarioEquilibrado : public ArbolBinario<key> {
  public:
    bool insertar(const key&);
    bool buscar(const key&);
};

#endif