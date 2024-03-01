#include <iostream>

#include "Lattice.h"

void help() {
  std::cout << "Usage: \n",
  std::cout << "-dim [d] para indicar si es 1 dimesion o 2 dimensiones\n",
  std::cout << "-size [N] si solo hay 1 dimension, -size[N][M] si hay 2 dimensiones\n",
  std::cout << "-init [file] si se quiere leer desde un archivo, en cuyo caso no hace falta -size\n",
  std::cout << "-cell <t> para indicar el tipo de celula\n";
  std::cout << "-border [b] para indicar el tipo de frontera\n";
}

void generations(Lattice& lattice, int dim) {
  std::cout << lattice;
  //std::cout << "-------------------------------------------\n";
  //std::cout << "Generacion: " << lattice.getN_generation() << "\n";
  //std::cout << "-------------------------------------------\n";
  lattice.updateN_generation();
  bool population = false;
  char opcion;
  while(true) {
    if (population) {
      std::cout << "Poblacion: " << lattice.Population() << "\n";
      lattice.nextGeneration();
      lattice.updateN_generation();
    }
    else {
      lattice.nextGeneration();
      std::cout << lattice;
      //std::cout << "-------------------------------------------\n";
      //std::cout << "Generacion: " << lattice.getN_generation() << "\n";
      //std::cout << "-------------------------------------------\n";
      lattice.updateN_generation();
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
          std::cout << "Poblacion: " << lattice.Population() << "\n";
          lattice.nextGeneration();
          lattice.updateN_generation();
        }
      }
      for (int i = 0; i < 4; ++i) {
        lattice.nextGeneration();
        std::cout << lattice;
        std::cout << "-------------------------------------------\n";
        std::cout << "Generacion: " << lattice.getN_generation() << "\n";
        std::cout << "-------------------------------------------\n";
        lattice.updateN_generation();
      }
    }
    else if (opcion == 's') { // se guarda en un fichero el tablero
      std::cout << "Introduce el nombre del fichero\n";
      std::string fichero;
      std::cin >> fichero;
      std::ofstream output(fichero);
      if (dim == 1) {
        output << lattice.getSize() << "\n";
      }
      else {
        output << lattice.getRows() << "\n" << lattice.getColumns() << "\n";
      }
      output << lattice;
      std::cout << "\n";
    }
    else if (opcion == 'c'){
      population = !population;
    }
  }
  return;
}

void createLattice(int dim, int dim_x, int dim_y, std::string cellType, std::string borderType, std::string fichero)  {
  if (fichero == "") {
    if (dim == 1) {
      if (borderType == "caliente") {
        if (cellType == "Ace110") {
          FactoryCellACE110 factory;
          Lattice1D_open lattice(dim_x, factory, 1);
          generations(lattice, dim);
        }
        else if (cellType == "Ace30") {
          FactoryCellACE30 factory;
          Lattice1D_open lattice(dim_x, factory, 1);
          generations(lattice, dim);
        }
      }
      else if (borderType == "fria") {
        if (cellType == "Ace110") {
          FactoryCellACE110 factory;
          Lattice1D_open lattice(dim_x, factory, 0);
          generations(lattice, dim);
        }
        else if (cellType == "Ace30") {
          FactoryCellACE30 factory;
          Lattice1D_open lattice(dim_x, factory, 0);
          generations(lattice, dim);
        }
      }
      else if (borderType == "periodica") {
        if (cellType == "Ace110") {
          FactoryCellACE110 factory;
          Lattice1D_periodic lattice(dim_x, factory);
          generations(lattice, dim);
        }
        else if (cellType == "Ace30") {
          FactoryCellACE30 factory;
          Lattice1D_periodic lattice(dim_x, factory);
          generations(lattice, dim);
        }
      }
    }
    else {
      if (borderType == "reflectora") {
        if (cellType == "Life23_3") {
          FactoryCellLife23_3 factory;
          Lattice2D_reflective lattice(dim_x, dim_y, factory);
          generations(lattice, dim);
        }
        else {
          FactoryCellLife51_346 factory;
          Lattice2D_reflective lattice(dim_x, dim_y, factory);
          generations(lattice, dim);
        }
      }
      else {
        if (cellType == "Life23_3") {
          FactoryCellLife23_3 factory;
          Lattice2D_noborder lattice(dim_x, dim_y, factory);
          generations(lattice, dim);
        }
        else {
          FactoryCellLife51_346 factory;
          Lattice2D_noborder lattice(dim_x, dim_y, factory);
          generations(lattice, dim);
        }
      }
    }
  }
  else {
    if (dim == 1) {
      if (borderType == "caliente") {
        if (cellType == "Ace110") {
          FactoryCellACE110 factory;
          Lattice1D_open lattice(fichero, factory, 1);
          generations(lattice, dim);
        }
        else if (cellType == "Ace30") {
          FactoryCellACE30 factory;
          Lattice1D_open lattice(fichero, factory, 1);
          generations(lattice, dim);
        }
      }
      else if (borderType == "fria") {
        if (cellType == "Ace110") {
          FactoryCellACE110 factory;
          Lattice1D_open lattice(fichero, factory, 0);
          generations(lattice, dim);
        }
        else if (cellType == "Ace30") {
          FactoryCellACE30 factory;
          Lattice1D_open lattice(fichero, factory, 0);
          generations(lattice, dim);
        }
      }
      else {
        if (cellType == "Ace110") {
          FactoryCellACE110 factory;
          Lattice1D_periodic lattice(fichero, factory);
          generations(lattice, dim);
        }
        else if (cellType == "Ace30") {
          FactoryCellACE30 factory;
          Lattice1D_periodic lattice(fichero, factory);
          generations(lattice, dim);
        }
      }
    }
    else {
      if (borderType == "reflectora") {
        if (cellType == "Life23_3") {
          FactoryCellLife23_3 factory;
          Lattice2D_reflective lattice(fichero, factory);
          generations(lattice, dim);
        }
        else {
          FactoryCellLife51_346 factory;
          Lattice2D_reflective lattice(fichero, factory);
          generations(lattice, dim);
        }
      }
      else {
        if (cellType == "Life23_3") {
          FactoryCellLife23_3 factory;
          Lattice2D_noborder lattice(fichero, factory);
          generations(lattice, dim);
        }
        else {
          FactoryCellLife51_346 factory;
          Lattice2D_noborder lattice(fichero, factory);
          generations(lattice, dim);
        }
      }
    }
  }
}
  
int main(int argc, char* argv[]) {
  std::string arg1  = argv[1];
  if (argc == 1 || arg1 == "-h") {
    help();
    return 0;
  }
  std::string borderType = "";
  std::string fichero = "";
  int dim_x = 0, dim_y = 0;
  int dim = 0;
  std::string cellType = "";
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-dim") {
      dim = std::stoi(argv[i + 1]);
    }
    if (arg == "-cell") {
      cellType = argv[i + 1];
    }
    if (arg == "-border") {
      borderType = argv[i + 1];
    }
    if (arg == "-init") {
      fichero = argv[i + 1];
    }
    if (arg == "-size") {
      std::string size = argv[i + 1];
      dim_x = std::stoi(size);
      if (argc == 10) {
        dim_y = std::stoi(argv[i + 2]);
      }
    }
  }
  createLattice(dim, dim_x, dim_y, cellType, borderType, fichero);
}
