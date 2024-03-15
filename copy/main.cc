#include <iostream>

#include "DispersionFunction.h"
#include "ExplorationFunction.h"
#include "Sequence.h"
#include "HashTable.h"
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

void readArgs(int argc, char* argv[], unsigned& tableSize, unsigned& blockSize, unsigned& fd, unsigned& fe, bool& isOpen) {
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-ts") {
      tableSize = std::stoi(argv[i + 1]);
    } else if (arg == "-bs") {
      blockSize = std::stoi(argv[i + 1]);
    } else if (arg == "-fd") {
      fd = std::stoi(argv[i + 1]);
    } else if (arg == "-fe") {
      fe = std::stoi(argv[i + 1]);
    } else if (arg == "-hash") {
      isOpen = (std::string(argv[i + 1]) == "open" ? true : false);
    }
  }
}

int menu() {
  std::cout << "1. Insertar\n";
  std::cout << "2. Buscar\n";
  std::cout << "3. Imprimir\n";
  std::cout << "4. Salir\n";
  std::cout << "Opcion: ";
  int option;
  std::cin >> option;
  return option;
}

template <class key, class container>
void useTable(HashTable<key, container> hashtable) {
  int opcion = menu();
  while (opcion != 4) {
    switch (opcion) {
      case 1: {
        bool valid = false;
        unsigned int clave;
        while(!valid) {
          std::cout << "Insertar: ";
          std::cin >> clave;
          if (clave >= 10000000 && clave <= 99999999) {
            valid = true;
          } else {
            std::cout << "Clave invalida, se necesitan 8 digitos\n";
          }
        }
        Dni dni(clave);
        if (hashtable.insert(clave)) {
          std::cout << "Insertado\n";
        } else {
          std::cout << "No se pudo insertar\n";
        }
        break;
      }
      case 2: {
        std::cout << "Buscar: ";
        unsigned int clave;
        std::cin >> clave;
        Dni dni(clave);
        if (hashtable.search(clave)) {
          std::cout << "Encontrado" << std::endl;
        } else {
          std::cout << "No se encontro" << std::endl;
        }
        break;
      }
      case 3: {
        hashtable.print();
        break;
      } 
      case 4: {
        break;
      }
    }
    opcion = menu();
  }
}

int main(int argc, char* argv[]) {
  if ((argc < 9 || argc > 11) && argc != 2) {
    std::cout << "Error en los argumentos\n";
    help();
    return 0;
  }
  std::string arg = argv[1];
  if (arg == "-h") {
    help();
    return 0;
  }
  unsigned tableSize = 0, blockSize = 0, fd = 0, fe = 0;
  bool isOpen = false;
  readArgs(argc, argv, tableSize, blockSize, fd, fe, isOpen);
  if (isOpen) {
    switch (fd) {
      case 1: {
        Module_DispersionFunction<Dni> fd(tableSize);
        HashTable<Dni, dynamicSequence<Dni>> tablahash(tableSize, fd);
        useTable(tablahash);
        break;
      }
      case 2: {
        Sum_DispersionFunction<Dni> fd(tableSize);
        HashTable<Dni, dynamicSequence<Dni>> tablahash(tableSize, fd);
        useTable(tablahash);
        break;
      }
      case 3: {
        Random_DispersionFunction<Dni> fd(tableSize);
        HashTable<Dni, dynamicSequence<Dni>> tablahash(tableSize, fd);
        useTable(tablahash);
        break;
      }
      default: {
        std::cout << "Error en el codigo de la funcion de dispersion\n";
        help();
        return 0;
      }
    }
  }
  else {
    switch(fd) {
      case 1: {
        Module_DispersionFunction<Dni> fd(tableSize);
        DispersionFunction<Dni>* dispersionFunction = new Module_DispersionFunction<Dni>(tableSize);
        switch (fe) {
          case 1: {
            Lineal_ExplorationFunction<Dni> fe(tableSize);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useTable(tablahash);
            break;
          }
          case 2: {
            Cuadratic_ExplorationFunction<Dni> fe(tableSize);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useTable(tablahash);
            break;
          }
          case 3: {
            bidispersion_ExplorationFunction<Dni> fe(tableSize, dispersionFunction);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useTable(tablahash);
            break;
          }
          case 4: {
            Redispersion_ExplorationFunction<Dni> fe(tableSize, dispersionFunction);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useTable(tablahash);
            break;
          }
          default: {
            std::cout << "Error en el codigo de la funcion de exploracion\n";
            help();
            return 0;
          }
        }
        delete dispersionFunction;
        break;
      }
      case 2: {
        Sum_DispersionFunction<Dni> fd(tableSize);
        DispersionFunction<Dni>* dispersionFunction = new Sum_DispersionFunction<Dni>(tableSize);
        switch (fe) {
          case 1: {
            Lineal_ExplorationFunction<Dni> fe(tableSize);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useTable(tablahash);
            break;
          }
          case 2: {
            Cuadratic_ExplorationFunction<Dni> fe(tableSize);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useTable(tablahash);
            break;
          }
          case 3: {
            bidispersion_ExplorationFunction<Dni> fe(tableSize, dispersionFunction);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useTable(tablahash);
            break;
          }
          case 4: {
            Redispersion_ExplorationFunction<Dni> fe(tableSize, dispersionFunction);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useTable(tablahash);
            break;
          }
          default: {
            std::cout << "Error en el codigo de la funcion de exploracion\n";
            help();
            return 0;
          }
        }
        delete dispersionFunction;
        break;
      }
      case 3: {
        Random_DispersionFunction<Dni> fd(tableSize);
        DispersionFunction<Dni>* dispersionFunction = new Random_DispersionFunction<Dni>(tableSize);
        switch (fe) {
          case 1: {
            Lineal_ExplorationFunction<Dni> fe(tableSize);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useTable(tablahash);
            break;
          }
          case 2: {
            Cuadratic_ExplorationFunction<Dni> fe(tableSize);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useTable(tablahash);
            break;
          }
          case 3: {
            bidispersion_ExplorationFunction<Dni> fe(tableSize, dispersionFunction);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useTable(tablahash);
            break;
          }
          case 4: {
            Redispersion_ExplorationFunction<Dni> fe(tableSize, dispersionFunction);
            HashTable<Dni, staticSequence<Dni>> tablahash(tableSize, fd, fe, blockSize);
            useTable(tablahash);
            break;
          }
          default: {
            std::cout << "Error en el codigo de la funcion de exploracion\n";
            help();
            return 0;
          }
        }
        delete dispersionFunction;
        break;
      }
    }
  }
}