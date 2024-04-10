#include <iostream>
#include <fstream>

#include "sequence.h"
#include "Dni.h"
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
  std::cout << "2: QuickSort\n";
  std::cout << "3: HeapSort\n";
  std::cout << "4: ShellSort\n";
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
      if (std::string(argv[i + 1]) == "y") {
        trace = true;
      }
      else {
        trace = false;
      }
    }
  }
}

int main(int argc, char* argv[]) {
  Dni* sequence = new Dni[100];    //creamos la secuencia de dni
  Dni* sequence_2 = new Dni[1000];
  Dni* sequence_3 = new Dni[10000];
  Dni* sequence_4 = new Dni[100000];
  for (unsigned i = 0; i < 100; ++i) {
    sequence[i] = Dni();
  }
  for (int i = 0; i < 1000; ++i) {
    sequence_2[i] = Dni();
  }
  for (int i = 0; i < 10000; ++i) {
    sequence_3[i] = Dni();
  }
  for (int i = 0; i < 100000; ++i) {
    sequence_4[i] = Dni();
  }
  staticSequence<Dni> seq_1(100, sequence);
  staticSequence<Dni> seq_2(1000, sequence_2);
  staticSequence<Dni> seq_3(10000, sequence_3);
  staticSequence<Dni> seq_4(100000, sequence_4);
  int asignations = 0;
  std::cout << "Numero de asignaciones\n";
  std::cout << "QuickSort:   100 elementos-";
  QuickSort<Dni> quick_1(seq_1);
  quick_1.sort(asignations);
  std::cout << asignations;
  asignations = 0;
  QuickSort<Dni> quick_2(seq_2);
  quick_2.sort(asignations);
  std::cout << "  1000 elementos-" << asignations;
  asignations = 0;
  QuickSort<Dni> quick_3(seq_3);
  quick_3.sort(asignations);
  std::cout << "10000 elementos-" << asignations;
  QuickSort<Dni> quick_4(seq_4);
  asignations = 0;
  quick_4.sort(asignations);
  std::cout << "100000 elementos-" << asignations << "\n";
  std::cout << "HeapSort:   100 elementos-";
}