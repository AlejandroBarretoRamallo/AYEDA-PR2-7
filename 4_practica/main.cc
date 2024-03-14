#include <iostream>

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

void createHashTable(unsigned tableSize, unsigned fdCode, unsigned feCode, unsigned blockSize, bool isOpen) {
  if (isOpen) {
    switch(fdCode) {
      case 1: {
        Module_DispersionFunction<Dni> fd(tableSize);
        HashTable<Dni, dynamicSequence<Dni>> tablahash(tableSize, fd);
        break;
      }
      case 2: {
        Sum_DispersionFunction<Dni> fd(tableSize);
        HashTable<Dni, dynamicSequence<Dni>> tablahash(tableSize, fd);
        break;
      }
      case 3: {
        Random_DispersionFunction<Dni> fd(tableSize);
        HashTable<Dni, dynamicSequence<Dni>> tablahash(tableSize, fd);
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
      case 1:
        switch(feCode) {
          case 1: {
            Module_DispersionFunction<Dni> fd(tableSize);
            Lineal_ExplorationFunction<Dni> fe(tableSize);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            break;
          }
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