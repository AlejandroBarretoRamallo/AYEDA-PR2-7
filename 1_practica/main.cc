#include <iostream>
#include <fstream>

#include "Cell.h"
#include "Lattice.h"
#include "Position.h"
#include "State.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Numero de parametros incorrecto\n";
    return 0;
  }
  if (argv[1] == "-h") {
    std::cout << "Se debe introducir el tamaño del reticulo, y despues el tipo de frontera(caliente, fria o periodica\n";
    std::cout << "Si se desea, se puede obtener la ristra inicial desde un fichero indicando su nombre\n";
    return 0;
  }
  std::string arg1 = argv[1];
  int size = std::stoi(arg1);
  std::string border = argv[2];
  std::string ristra = "";
  if (argc > 3) {
    std::string nombre_fichero = argv[3];
    std::ifstream input(nombre_fichero);
    input >> ristra;
  }
  else {
    for (int i = 0; i < size; ++i) {
      if (i == size / 2) {
        ristra += '1';
      }
      else {
        ristra += '0';
      }
    }
  }
  Lattice reticulo(ristra, border);
  std::cout << "Para detener las generaciones introduzca la letra 's'\n";
  std::cout << reticulo;
  reticulo.updateN_generation();
  while (true) {
    reticulo.nextGeneration();
    std::cout << reticulo;
    reticulo.updateN_generation();
    if (std::cin.get() == 's') {
      break;
    }
  }
  return 0;
}
