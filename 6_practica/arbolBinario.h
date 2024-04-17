#ifndef ARBOLBINARIO_H
#define ARBOLBINARIO_H

#include "nodoBinario.h"

template<class key>
class arbolBinario {
  public:
    virtual bool insertar(const key&);
    virtual bool buscar(const key& k) const; 
    void inorden( ) const;
  protected:
    nodoBinario<key> *nodo;
};

#endif