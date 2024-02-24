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
  bool population = false;
  char opcion;
  while(true) {
    if (population) {
      std::cout << "Poblacion: " << reticulo.Population() << "\n";
      reticulo.nextGeneration();
      reticulo.updateN_generation();
    }
    else {
      reticulo.nextGeneration();
      std::cout << reticulo;
      std::cout << "-------------------------------------------\n";
      std::cout << "Generacion: " << reticulo.getN_generation() << "\n";
      std::cout << "-------------------------------------------\n";
      reticulo.updateN_generation();
    }
    std::cin >> opcion;
    while (opcion != 'n' && opcion != 'x' && opcion != 'L' && opcion != 's' && opcion != 'c') {
      std::cout << "Introduce una opcion valida\n";
      std::cin >> opcion;
    }
    if (opcion == 'x') {  // si se introduce x se sale del bucle
      break;
    }
    else if (opcion == 'n') {  // si se introduce n se salta a la siguiente generacion
      continue;
    }
    else if (opcion == 'L') { //si se introduce L se hacen 5 generaciones
      if (population) {
        for (int i = 0; i < 4; ++i) {
          std::cout << "Poblacion: " << reticulo.Population() << "\n";
          reticulo.nextGeneration();
          reticulo.updateN_generation();
        }
      }
      for (int i = 0; i < 4; ++i) {
        reticulo.nextGeneration();
        std::cout << reticulo;
        std::cout << "-------------------------------------------\n";
        std::cout << "Generacion: " << reticulo.getN_generation() << "\n";
        std::cout << "-------------------------------------------\n";
        reticulo.updateN_generation();
      }
    }
    else if (opcion == 's') { // se guarda en un fichero el tablero
      std::cout << "Introduce el nombre del fichero\n";
      std::string fichero;
      std::cin >> fichero;
      std::ofstream output(fichero);
      output << reticulo.getRows() << "\n" << reticulo.getColumns() << "\n";
      output << reticulo;
      std::cout << "\n";
    }
    else if (opcion == 'c'){
      population = !population;
    }
  }
  return;
}

void help() {
  std::cout << "los parametros deben introducirse en el sigueinte orden: tamaño(numero de filas y numero de columnas) y tipo de frontera(periodica, caliente, fria, reflectora o noborder)\n";
  std::cout << "Si desea dar una configuracion inicial de algun fichero, introduce el nombre del fichero\n y no introduzcas el tamaño\n";
  return;
}

void options() {
  std::cout << "Las opciones son:\n";
  std::cout << "n: siguiente generacion\n";
  std::cout << "x: salir\n";
  std::cout << "L: 5 generaciones\n";
  std::cout << "s: guardar en un fichero\n";
  std::cout << "c: cambiar entre mostrar poblacion o no\n\n";
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
  options();
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

