#ifndef ARBOLBINARIO_H
#define ARBOLBINARIO_H

#include <queue>

#include "nodoBinario.h"

template<class key>
class ArbolBinario {
  public:
    virtual bool insertar(const key&) = 0;
    virtual bool buscar(const key&) const = 0; 
    void inorden() const;
    friend std::ostream& operator<<(std::ostream& out, ArbolBinario<key> arbol) {
      std::queue<std::pair<NodoBinario<key>, int>> cola;
      NodoBinario<key> *nodo;
      int nivel, Nivel_actual = 0;
      std::pair<NodoBinario<key>, int> par(arbol.raiz_, 0);
      cola.push(par);
      out << "Nivel 0:  ";
      while (!cola.empty()) {
        std::pair<NodoBinario<key>, int> cola_par = cola.pop();
        nivel = cola_par.second();
        nodo = cola_par.first();
        if(nivel > Nivel_actual) {
          Nivel_actual = nivel;     //Incremento de nivel
          out << "\nNivel " << Nivel_actual << ":  ";
        }
        if(nodo != NULL) {
          out << nodo->getDato();
          cola_par = std::pair<NodoBinario<key>, int> (nodo->getLeft(), nivel + 1);
          cola.push(cola_par);
          cola_par = std::pair<NodoBinario<key>, int> (nodo->getRight(), nivel + 1);
          cola.push(cola_par);
        }
        else {
          out << "[.]";
        }
      }
    }
    ArbolBinario() {raiz_ = nullptr;};
  protected:
    NodoBinario<key> *raiz_;
    void recorrido_inorden(NodoBinario<key>*);
};

template<class key>
class ArbolBinarioBusqueda : public ArbolBinario<key> {
  public:
    bool insertar(const key&);  //hecho
    bool buscar(const key&); // hecho
    ArbolBinarioBusqueda(): ArbolBinario() {};
  private:
    bool añadir_rama(NodoBinario<key>*, key);  //hecho
    bool buscar_rama(NodoBinario<key>*, key);  //hecho
};

template<class key>
class ArbolBinarioEquilibrado : public ArbolBinario<key> {
  public:
    bool insertar(const key&);
    bool buscar(const key&);
    ArbolBinarioEquilibrado(): ArbolBinario() {};
  private:
    bool insertar_rama(NodoBinario<key>*, key);
    bool buscar_rama(NodoBinario<key>*, key);
    int tam_rama(NodoBinario<key>*);
};

template<class key>
bool ArbolBinarioBusqueda<key>::insertar(const key& clave) {
  return añadir_rama(this->raiz_, clave);
}

template<class key>
bool ArbolBinarioBusqueda<key>::añadir_rama(NodoBinario<key>* nodo, key clave) {
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
  return buscar_rama(this->raiz_, clave);
}

template<class key>
bool ArbolBinarioBusqueda<key>::buscar_rama(NodoBinario<key>* nodo, key clave) {
  if (nodo == nullptr) {
    return false;
  }
  else if (nodo->getDato() == clave) {
    return true;
  }
  else if (nodo->getDato() < clave) {
    return buscar_rama(nodo->getLeft(), clave);
  }
  else if (nodo->getDato() > clave) {
    return buscar_rama(nodo->getRight(), clave);
  }
}

template<class key>
bool ArbolBinarioEquilibrado<key>::insertar(const key& clave) {
  return insertar_rama(this->raiz_);
}

template<class key>
bool ArbolBinarioEquilibrado<key>::buscar(const key& clave) {
  return insertar_rama(this->raiz_);
}

template<class key>
bool ArbolBinarioEquilibrado<key>::insertar_rama(NodoBinario<key>* nodo, key clave) {
  if (nodo == nullptr) {
    nodo = new NodoBinario<key> (clave);
    return true;
  }
  else if (tam_rama(nodo->getLeft()) <= tam_rama(nodo->getRight())) {
    return insertar_rama(nodo->getLeft(), clave);
  }
  else if (tam_rama(nodo->getLeft()) > tam_rama(nodo->getRight())) {
    return insertar_rama(nodo->getRight(), clave);
  }
}

template<class key>
bool ArbolBinarioEquilibrado<key>::buscar_rama(NodoBinario<key>* nodo, key clave) {
  if (nodo == nullptr) {
    return false;
  }
  else if (nodo->getDato() == clave) {
    return true;
  }
  else {
    return buscar_rama(nodo->getLeft()) + buscar_rama(nodo->getRight());
  }
}

template<class key>
int ArbolBinarioEquilibrado<key>::tam_rama(NodoBinario<key>* nodo) {
  if (nodo == nullptr) {
    return 0;
  }
  else {
    return 1 + tam_rama(nodo->getLeft()) + tam_rama(nodo->getRight());
  }
}

template<class key>
void ArbolBinario<key>::inorden() const {
  recorrido_inorden(raiz_);
}

template<class key>
void ArbolBinario<key>::recorrido_inorden(NodoBinario<key>* nodo) {
  if (nodo == nullptr) {
    std::cout << "[.]\n";
  }
  else {
    recorrido_inorden(nodo->getLeft());
    std::cout << nodo->getDato() << std::endl;
    recorrido_inorden(nodo->getRight());
  }
}

#endif