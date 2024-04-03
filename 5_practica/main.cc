#include <iostream>

#include "sequence.h"
#include "sortMethod.h"

void help() {
  std::cout << "-size <s>, s es el tamaño de la secuencia\n";
  std::cout << "-ord <m>, m es el código que identifica un método de ordenación.\n";
  std::cout << "-init <i> [f], indica la forma de introducir los datos de la secuencia.\n";
  std::cout << "i = manual | aleatorio | fichero\n";
  std::cout << "f = nombre del fichero\n";
  std::cout << "-trace <y|n>, indica si se muestra o no la traza durante la ejecución.\n";
  std::cout << "CODIGO DE ORDENACIÓN\n";
  std::cout << "1: Selección\n";
  std::cout << "2: Burbuja\n";
  std::cout << "3: HeapSort\n";
  std::cout << "4: QuickSort\n";
  std::cout << "5: RadixSort\n";
  return;
}

void readArgs(unsigned& size, unsigned& orderType, std::string& fichero, std::string& init, bool& trace, int& argc, char* argv[]) {
  std::string arg = "";
  for (int i = 0; i < argc; ++i) {
    arg = argv[i];
    if (arg == "-size") {
      size = std::stoi(argv[i + 1]);
    }
    else if (arg == "-ord") {
      orderType = std::stoi(argv[i + 1]);
    }
    else if (arg == "-init") {
      init = argv[i + 1];
      if (init == "fichero") {
        fichero = argv[i + 2];
      }
    }
    else if (arg == "-trace") {
      if (argv[i + 1] == "y") {
        trace = true;
      }
      else {
        trace = false;
      }
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc < 9 || argc > 10) {
    help();
    return 0;
  }
  unsigned size = 0, orderType = 0;
  std::string fichero = "", init = "";
  bool trace = false;
}