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
  if (argc < 9 || argc > 10) {
    help();
    return 0;
  }
  unsigned size = 0, orderType = 0;
  std::string fichero = "", init = "";
  bool trace = false;
  readArgs(size, orderType, fichero, init, trace, argc, argv);
  Dni* sequence = new Dni[size];
  if (init == "manual") {
    for (unsigned i = 0; i < size; ++i) {
      unsigned dni;
      std::cin >> dni;
      while (dni < 10000000 || dni > 99999999) {
        std::cout << "Introduce un DNI válido\n";
        std::cin >> dni;
      }
      sequence[i] = Dni(dni);
    }
  }
  else if (init == "random") {
    for (unsigned i = 0; i < size; ++i) {
      sequence[i] = Dni();
    }
  }
  else if (init == "fichero") {
    std::ifstream input(fichero);
    for (unsigned i = 0; i < size; ++i) {
      unsigned dni;
      while (input >> dni) {
        sequence[i] = Dni(dni);
      }
    }
  }
  staticSequence<Dni> seq(size, sequence);
  switch(orderType) {
    case 1: {
      Seleccion seleccion(seq);
      if (trace) {
        seleccion.trace_sort();
      }
      else {
        seleccion.sort();
        std::cout << seleccion;
      }
      break;
    }
    case 2: {
      QuickSort<Dni> quickSort(seq);
      if (trace) {
        quickSort.trace_sort();
      }
      else {
        quickSort.sort();
        std::cout << quickSort;
      }
      break;
    }
    case 3: {
      HeapSort<Dni> heapSort(seq);
      if (trace) {
        heapSort.trace_sort();
      }
      else {
        heapSort.sort();
        std::cout << heapSort;
      }
      break;
    }
    case 4: {
      ShellSort<Dni> shellSort(seq);
      if (trace) {
        shellSort.trace_sort();
      }
      else {
        shellSort.sort();
        std::cout << shellSort;
      }
      break;
    }
    case 5: {
      RadixSort<Dni> radixSort(seq);
      if (trace) {
        radixSort.trace_sort();
      }
      else {
        radixSort.sort();
        std::cout << radixSort;
      }
      break;
    }
  }
}