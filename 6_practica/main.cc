#include <iostream>

#include "arbolBinario.h"
#include "nodoBinario.h"

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
  
}