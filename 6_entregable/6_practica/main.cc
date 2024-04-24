#include <iostream>
#include <fstream>

#include "arbolBinario.h"
#include "nodoBinario.h"
#include "Dni.h"

void help() {
  std::cout << "-ab <abe|abb>, para indicar el tipo de árbol con el que se va a trabajar.\n";
  std::cout << "-init <i> [s][f], indica la forma de introducir los datos de la secuencia\n";
  std::cout << "i=manual\n";
  std::cout << "i=random [s], s es el número de elementos a generar\n";
  std::cout << "i=file [s][f], s es el número de elementos a generar, f es nombre del fichero de entrada\n";
}

void readArgs(std::string& arbolType, std::string& introduceData, std::string& file, int& numElements, int argc, char* argv[]) {
  for (int i = 0; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-ab") {
      arbolType = argv[i + 1];
    }
    else if (arg == "-init") {
      introduceData = argv[i + 1];
      if (introduceData == "random") {
        numElements = std::stoi(argv[i + 2]);
      }
      else if (introduceData == "file") {
        numElements = std::stoi(argv[i + 2]);
        file = argv[i + 3];
      }
    }
  }
}

template<class key>
void useTree(ArbolBinario<key>& tree, std::string introduceData, int numElements, std::string file) {
  if (introduceData == "manual") {
    for (int i = 0; i < numElements; ++i) {
      std::cout << "Introduce un elemento: ";
      int elemento;
      bool correct = false;
      std::cin >> elemento;
      if (elemento >= 10000000 && elemento <= 99999999) {
        correct = true;
      }
      while (!correct) {
        std::cout << "El dni debe de tener 8 cifras\n";
        std::cout << "Introduce un elemento: ";
        std::cin >> elemento;
        if (elemento >= 10000000 && elemento <= 99999999) {
          correct = true;
        }
      }
      Dni dni(elemento);
      tree.insertar(dni);
    }
  }
  else if (introduceData == "random") {
    for (int i = 0; i < numElements; ++i) {
      tree.insertar(Dni());
    }
  }
  else if (introduceData == "file") {
    std::ifstream input(file);
    for (int i = 0; i < numElements; ++i) {
      int elemento;
      input >> elemento;
      Dni dni(elemento);
      tree.insertar(dni);
    }
  }
  std::string option = "1";
  while (option != "0") {
    std::cout << "\n0 Salir\n";
    std::cout << "1 Insertar\n";
    std::cout << "2 Buscar\n";
    std::cout << "3 Mostrar arbol inorden\n";
    std::cout << "Elige una opcion: \n";
    std::cin >> option;
    while(option != "0" && option != "1" && option != "2" && option != "3") {
      std::cout << "Opción no válida\n";
      std::cout << "0 Salir\n";
      std::cout << "1 Insertar\n";
      std::cout << "2 Buscar\n";
      std::cout << "3 Mostrar arbol inorden\n";
      std::cout << "Elige una opcion: \n";
      std::cin >> option;
    }
    if (option == "1") {
      std::cout << "Introduce elemento\n";
      int elemento;
      std::cin >> elemento;
      while (elemento < 10000000 || elemento > 99999999) {
        std::cout << "El dni debe de tener 8 cifras\n";
        std::cout << "Introduce un elemento: ";
        std::cin >> elemento;
      }
      if (tree.buscar(Dni(elemento))) {
        std::cout << "Elemento ya existe\n";
        continue;
      }
      tree.insertar(Dni(elemento));
      std::cout << tree;
    }
    else if (option == "2") {
      std::cout << "Introduce elemento\n";
      int elemento;
      std::cin >> elemento;
      while (elemento < 10000000 || elemento > 99999999) {
        std::cout << "El dni debe de tener 8 cifras\n";
        std::cout << "Introduce un elemento: ";
        std::cin >> elemento;
      }
      if (tree.buscar(Dni(elemento))) {
        std::cout << "Elemento encontrado\n";
      }
      else {
        std::cout << "Elemento no encontrado\n";
      }
    }
    else if (option == "3") {
      tree.inorden();
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    help();
    return 0;
  }
  std::string arg1 = argv[1];
  if (argc < 2 || argc > 7 || arg1 == "-h") {
    help();
    return 0;
  }
  std::string arbolType = "", introduceData = "", file = "";
  int numElements = 0;
  readArgs(arbolType, introduceData, file, numElements, argc, argv);
  if (arbolType == "abe") {
    ArbolBinarioEquilibrado<Dni> tree;
    useTree(tree, introduceData, numElements, file);
  }
  else if (arbolType == "abb") {
    ArbolBinarioBusqueda<Dni> tree;
    useTree(tree, introduceData, numElements, file);
  }
  else {
    std::cout << "Tipo de árbol no válido.\n";
    return 0;
  }
}