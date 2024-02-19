#include "Lattice.h"

Lattice::Lattice() {
  celulas_ = std::vector<std::vector<Cell*>>(0, std::vector<Cell*>(0, nullptr));
  rows_ = 0;
  colums_ = 0;
  Position posicion;
  State state;
  std::string borderType_ = "caliente";
  n_generation_ = 1;
  rows_ = 1;
  colums_ = 1;
}

Lattice::Lattice(int N, int M, std::string borderType) {
  borderType_ = borderType;
  if (borderType_ == "periodica" || borderType_ == "noborder" || borderType_ == "reflectora") {
    celulas_ = std::vector<std::vector<Cell*>>(N, std::vector<Cell*>(M, nullptr));
    std::cout << "Introduzca el numero de celulas que van a estar vivas: ";
    int num_celulas = 0;
    std::cin >> num_celulas;
    for (int i = 0; i < num_celulas; ++i) {
      std::cout << "Introduce la coordenada x de la celula: ";
      int x, y;
      std::cin >> x;
      std::cout << "Introduce la coordenada y de la celula: ";
      std::cin >> y;
      celulas_[x][y] = new Cell(Position(x, y), State(1));
    }
    for (int i = 0; i < N; ++i) {
      for(int j = 0; j < M; ++j) {
        if (celulas_[i][j] == nullptr) {
          celulas_[i][j] = new Cell(Position(i, j), State(0));
        }
      }
    }
    rows_ = N;
    colums_ = M;
  }
  else {
    rows_ = N + 2;
    colums_ = M + 2;
    celulas_ = std::vector<std::vector<Cell*>>(rows_, std::vector<Cell*>(colums_, nullptr));
    std::cout << "Introduzca el numero de celulas que van a estar vivas: ";
    int num_celulas = 0;
    std::cin >> num_celulas;
    for (int i = 0; i < num_celulas; ++i) {  // crear el interior de la matriz
      std::cout << "Introduce la coordenada x de la celula: ";
      int x, y;
      std::cin >> x;
      std::cout << "Introduce la coordenada y de la celula: ";
      std::cin >> y;
      celulas_[x + 1][y + 1] = new Cell(Position(x + 1, y + 1), State(1));
    }
    for (int i = 1; i <= N; ++i) {
      for(int j = 1; j <= M; ++j) {
        if (celulas_[i][j] == nullptr) {
          celulas_[i][j] = new Cell(Position(i, j), State(0));
        }
      }
    }
    for (int i = 0; i < colums_; ++i) {  // rellenar los bordes 
      if (borderType_ == "caliente") {
        celulas_[0][i] = new Cell(Position(0, i), State(1));
        celulas_[rows_ - 1][i] = new Cell(Position(rows_ - 1, i), State(1));
      }
      else {
        celulas_[0][i] = new Cell(Position(0, i), State(0));
        celulas_[rows_ - 1][i] = new Cell(Position(rows_ - 1, i), State(0));
      }
    }
    for(int i = 1; i < rows_ - 1; ++i) {
      if (borderType_ == "caliente") {
        celulas_[i][0] = new Cell(Position(i, 0), State(1));
        celulas_[i][colums_ - 1] = new Cell(Position(i, colums_ - 1), State(1));
      }
      else if (borderType_ == "fria") {
        celulas_[i][0] = new Cell(Position(i, 0), State(0));
        celulas_[i][colums_ - 1] = new Cell(Position(i, colums_ - 1), State(0));
      }
    }
  }
  n_generation_ = 1;
}

Lattice::Lattice(std::string input, std::string bordertype) {
  borderType_ = bordertype;
  std::ifstream fichero(input);
  fichero >> rows_ >> colums_;
  if (borderType_ == "periodica" || borderType_ == "noborder" || borderType_ == "reflectora") {
    celulas_ = std::vector<std::vector<Cell*>>(rows_, std::vector<Cell*>(colums_, nullptr));
    char caracter;
    std::string linea;
    std::getline(fichero, linea);
    for(int i = 0; i < rows_; ++i) {
      std::getline(fichero, linea);
      if (linea.empty()) {
        for(int j = 0; j < colums_; ++j) {
          linea += " ";
        }
      }
      for(int j = 0; j < colums_; ++j) {
        caracter = linea[j];
        if (caracter == 'x') {
          celulas_[i][j] = new Cell(Position(i, j), State(1));
        }
        else {
          celulas_[i][j] = new Cell(Position(i, j), State(0));
        }
      }
    }
  }
  else {
    rows_ += 2;
    colums_ += 2;
    celulas_ = std::vector<std::vector<Cell*>>(rows_, std::vector<Cell*>(colums_, nullptr));
    char caracter;
    std::string linea;
    std::getline(fichero, linea);
    for (int i = 1; i < rows_ - 1; ++i) {
      std::getline(fichero, linea);
      if (linea.empty()) {
        for(int j = 0; j < colums_; ++j) {
          linea += " ";
        }
      }
      for (int j = 1; j < colums_ - 1; ++j) {
        caracter = linea[j - 1];
        if (caracter == 'x') {
          celulas_[i][j] = new Cell(Position(i, j), State(1));
        }
        else {
          celulas_[i][j] = new Cell(Position(i, j), State(0));
        }
      }
    }
    for (int i = 0; i < colums_; ++i) {  // rellenar los bordes 
      if (borderType_ == "caliente") {
        celulas_[0][i] = new Cell(Position(0, i), State(1));
        celulas_[rows_ - 1][i] = new Cell(Position(rows_ - 1, i), State(1));
      }
      else {
        celulas_[0][i] = new Cell(Position(0, i), State(0));
        celulas_[rows_ - 1][i] = new Cell(Position(rows_ - 1, i), State(0));
      }
    }
    for(int i = 1; i < rows_ - 1; ++i) {
      if (borderType_ == "caliente") {
        celulas_[i][0] = new Cell(Position(i, 0), State(1));
        celulas_[i][colums_ - 1] = new Cell(Position(i, colums_ - 1), State(1));
      }
      else {
        celulas_[i][0] = new Cell(Position(i, 0), State(0));
        celulas_[i][colums_ - 1] = new Cell(Position(i, colums_ - 1), State(0));
      } 
    }
  }
  n_generation_ = 1;
}

const Cell& Lattice::getCell(const Position& position) const {
  return *celulas_[position.getPosX()][position.getPosY()];
}

std::ostream& operator <<(std::ostream& out, Lattice const& reticulo) {
  for(int i = 0; i < reticulo.getRows(); ++i) {
    for(int j = 0; j < reticulo.getColumns(); ++j) {
      std::cout << reticulo.getCell(Position(i, j));
    }
    std::cout << "\n";
  }
  return out;
}

void Lattice::nextGeneration() {
  if (borderType_ != "periodica" && borderType_ != "reflectora" && borderType_ != "noborder") {
    for (int i = 1; i < rows_ - 1; ++i) {
      for(int j = 1; j < colums_ - 1; ++j) {
        celulas_[i][j]->setNextState(celulas_[i][j]->NextState(*this));
      }
    }
    for (int i = 1; i < rows_ - 1; ++i) {
      for(int j = 1; j < colums_ - 1; ++j) {
        celulas_[i][j]->updateState();
      }
    }
  }
  else {
    for(int i = 0; i < rows_; ++i) {
      for (int j = 0; j < colums_; ++j) {
        celulas_[i][j]->setNextState(celulas_[i][j]->NextState(*this));
      }
    }
    for(int i = 0; i < rows_; ++i) {
      for (int j = 0; j < colums_; ++j) {
        celulas_[i][j]->updateState();
      }
    }
  }
}

void Lattice::updateN_generation() {
  ++n_generation_;
}

Lattice::~Lattice() {
  //hacer
}