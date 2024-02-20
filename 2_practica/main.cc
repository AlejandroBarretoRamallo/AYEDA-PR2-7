#include <iostream>
#include <fstream>

#include "Cell.h"
#include "Lattice.h"
#include "Position.h"
#include "State.h"

void generations(Lattice& reticulo) {
  std::cout << reticulo;
  std::cout << "-------------------------------------------\n";
  std::cout << "Generacion: " << reticulo.getN_generation() << "\n";
  std::cout << "-------------------------------------------\n";
  reticulo.updateN_generation();
  while(true) {
    reticulo.nextGeneration();
    std::cout << reticulo;
    std::cout << "-------------------------------------------\n";
    std::cout << "Generacion: " << reticulo.getN_generation() << "\n";
    std::cout << "-------------------------------------------\n";
    reticulo.updateN_generation();
    if (std::cin.get() == 's') {
      break;
    }
  }
  return;
}

void help() {
  std::cout << "los parametros deben introducirse en el sigueinte orden: tamaño(numero de filas y numero de columnas) y tipo de frontera(periodica, caliente, fria, reflectora o noborder)\n";
  std::cout << "Si desea dar una configuracion inicial de algun fichero, introduce el nombre del fichero\n y no introduzcas el tamaño\n";
  return;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Numero de parametros incorrecto\n";
    return 0;
  }
  std::string arg1 = argv[1];
  if (arg1 == "-h") {
    help();
    return 0;
  }
  if (argc == 3) {
    std::string borderType = argv[2];
    std::string fichero = argv[1];
    Lattice reticulo(fichero, borderType);
    generations(reticulo);
  }
  else {
    std::string arg2 = argv[1];
    std::string arg3 = argv[2];
    std::string borderType = argv[3];
    const int rows = std::stoi(arg2);
    const int colums = std::stoi(arg3);
    Lattice reticulo(rows, colums, borderType);
    generations(reticulo);
  }
  return 0;
}

