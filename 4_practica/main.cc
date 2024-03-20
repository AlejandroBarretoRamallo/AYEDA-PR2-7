#include <iostream>
#include <cstdlib>
#include<ctime>

#include "HashTable.h"
#include "ExplorationFunction.h"
#include "DispersionFunction.h"
#include "Sequence.h"
#include "Dni.h"

void help() {
  std::cout << "-ts <tableSize> para indicar el tamaño de la tabla\n";
  std::cout << "-fd <f> para indicar el codigo de la funcion de dispersion\n";
  std::cout << "-fe <f> para indicar el codigo de la funcion de exploracion\n";
  std::cout << "-bs <s> para indicar el tamaño del bloque, solo en dispersion cerrada\n";
  std::cout << "-hash <open|close> para indicar el tipo de secuencia\n";
  std::cout << "COCDIGO DE LAS FUNCIONES DE EXPLORACION:\n";
  std::cout << "1. Lineal\n";
  std::cout << "2. Cuadratica\n";
  std::cout << "3. Dispersion doble\n";
  std::cout << "4. Redispersion\n";
  std::cout << "CODIGO DE LAS FUNCIONES DE DISPERSION:\n";
  std::cout << "1. Modulo\n";
  std::cout << "2. Suma\n";
  std::cout << "3. Pseudoaleatoria\n";
}

int menu() {
  std::cout << "1. Insertar clave\n";
  std::cout << "2. Buscar clave\n";
  std::cout << "3. Mostrar tabla\n";
  std::cout << "4. Salir\n";
  int option;
  std::cin >> option;
  return option;
}

template <class key, class container>
void useHashTable(HashTable<key, container>& hashtable) {
  int option = menu();
  switch (option){
    case 1: {
      std::cout << "Introduce el DNI a insertar\n";
      unsigned dni;
      std::cin >> dni;
      Dni clave(dni);
      if (!hashtable.search(clave)) {
        hashtable.insert(clave);
      }
      else {
        std::cout << "La clave ya existe\n";
      }
    }
    case 2: {
      std::cout << "Introduce el DNI a buscar\n";
      unsigned dni;
      std::cin >> dni;
      Dni clave(dni);
      if (hashtable.search(clave)) {
        std::cout << "La clave existe\n";
      }
      else {
        std::cout << "La clave no existe\n";
      }
    }

  }
}

void createHashTable(unsigned tableSize, unsigned fdCode, unsigned feCode, unsigned blockSize, bool isOpen) {
  if (isOpen) {
    switch(fdCode) {
      case 1: {
        Module_DispersionFunction<Dni> fd(tableSize);
        HashTable<Dni, dynamicSequence<Dni>> tablahash(tableSize, fd);
        useHashTable(tablahash);
        break;
      }
      case 2: {
        Sum_DispersionFunction<Dni> fd(tableSize);
        HashTable<Dni, dynamicSequence<Dni>> tablahash(tableSize, fd);
        useHashTable(tablahash);
        break;
      }
      case 3: {
        Random_DispersionFunction<Dni> fd(tableSize);
        HashTable<Dni, dynamicSequence<Dni>> tablahash(tableSize, fd);
        useHashTable(tablahash);
        break;
      }
      default: {
        std::cout << "Error en el codigo de la funcion de dispersion\n";
        help();
        break;
      }
    }
  }
  else {
    switch(fdCode) {
      case 1: {
        Module_DispersionFunction<Dni> fd(tableSize);
        switch(feCode) {
          case 1: {
            Lineal_ExplorationFunction<Dni> fe(tableSize);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useHashTable(tablahash);
            break;
          }
          case 2: {
            Cuadratic_ExplorationFunction<Dni> fe(tableSize);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useHashTable(tablahash);
            break;
          }
          case 3: {
            bidispersion_ExplorationFunction<Dni> fe(tableSize, fd);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useHashTable(tablahash);
            break;
          }
          case 4: {
            Redispersion_ExplorationFunction<Dni> fe(tableSize, fd);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useHashTable(tablahash);
            break;
          } 
        }
      }
      case 2: {
        Sum_DispersionFunction<Dni> fd(tableSize);
        switch(feCode) {
          case 1: {
            Lineal_ExplorationFunction<Dni> fe(tableSize);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useHashTable(tablahash);
            break;
          }
          case 2: {
            Cuadratic_ExplorationFunction<Dni> fe(tableSize);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useHashTable(tablahash);
            break;
          }
          case 3: {
            bidispersion_ExplorationFunction<Dni> fe(tableSize, fd);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useHashTable(tablahash);
            break;
          }
          case 4: {
            Redispersion_ExplorationFunction<Dni> fe(tableSize, fd);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useHashTable(tablahash);
            break;
          } 
        }
      }
      case 3: {
        Random_DispersionFunction<Dni> fd(tableSize);
        switch(feCode) {
          case 1: {
            Lineal_ExplorationFunction<Dni> fe(tableSize);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useHashTable(tablahash);
            break;
          }
          case 2: {
            Cuadratic_ExplorationFunction<Dni> fe(tableSize);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useHashTable(tablahash);
            break;
          }
          case 3: {
            bidispersion_ExplorationFunction<Dni> fe(tableSize, fd);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useHashTable(tablahash);
            break;
          }
          case 4: {
            Redispersion_ExplorationFunction<Dni> fe(tableSize, fd);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useHashTable(tablahash);
            break;
          } 
        }
      }
      default: {
        std::cout << "Error en el codigo de la funcion de dispersion\n";
        help();
        break;
      }
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc < 5 || argc > 6) {
    std::cout << "Error en los argumentos\n";
    help();
    return 0;
  }
  srand(time(NULL));
  unsigned tableSize, blockSize = 0, fdCode, feCode;
  bool isOpen;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-ts") {
      tableSize = std::stoi(argv[i + 1]);
    } else if (arg == "-fd") {
      fdCode = std::stoi(argv[i + 1]);
    } else if (arg == "-fe") {
      feCode = std::stoi(argv[i + 1]);
    } else if (arg == "-bs") {
      blockSize = std::stoi(argv[i + 1]);
    } else if (arg == "-hash") {
      std::string hash = argv[i + 1];
      if (hash == "open") {
        isOpen = true;
      } else if (hash == "close") {
        isOpen = false;
      }
    }
  }

  return 0;
}