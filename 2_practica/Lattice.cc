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
    highCorner_ = Position(0, 0);
    lowCorner_ = Position(rows_ - 1, colums_ - 1);
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
  highCorner_ = Position(0, 0);
  lowCorner_ = Position(rows_ - 1, colums_ - 1);
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
  int pos_x = position.getPosX();
  int pos_y = position.getPosY();
  if (borderType_ == "caliente" || borderType_ == "fria") {
    return *celulas_[pos_x][pos_y];
  }
  else if (borderType_ == "periodica") {
    if (pos_x == -1 && pos_y == -1) {
      return *celulas_[rows_ - 1][colums_ - 1];
    }
    else if (pos_x == -1 && pos_y == colums_) {
      return *celulas_[rows_ -1][0];
    }
    else if (pos_x == rows_ && pos_y == -1) {
      return *celulas_[0][colums_ - 1];
    }
    else if (pos_x == rows_ && pos_y == colums_) {
      return *celulas_[0][0];
    }
    else if (pos_x == -1) {
      return *celulas_[rows_ - 1][pos_y];
    }
    else if (pos_x == rows_) {
      return *celulas_[0][pos_y];
    }
    else if (pos_y == -1) {
      return *celulas_[pos_x][colums_ - 1];
    }
    else if (pos_y == colums_) {
      return *celulas_[pos_x][0];
    }
    else {
      return *celulas_[pos_x][pos_y];
    }
  }
  else {
    if (pos_x == -1 && pos_y == -1) {
      return *celulas_[0][0];
    }
    else if (pos_x == -1 && pos_y == colums_) {
      return *celulas_[0][pos_y - 1];
    }
    else if (pos_x == rows_ && pos_y == -1) {
      return *celulas_[pos_x - 1][0];
    }
    else if (pos_x == rows_ && pos_y == colums_) {
      return *celulas_[pos_x -1][pos_y - 1];
    }
    else if (pos_x == -1) {
      return *celulas_[0][pos_y];
    }
    else if (pos_x == rows_) {
      return *celulas_[rows_ - 1][pos_y];
    }
    else if (pos_y == -1) {
      return *celulas_[pos_x][0];
    }
    else if (pos_y == colums_) {
      return *celulas_[pos_x][pos_y - 1];
    }
    else {
      return *celulas_[pos_x][pos_y];
    }
  }
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
  else  if (borderType_ != "noborder") {
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
  else {

  }
}

void Lattice::updateN_generation() {
  ++n_generation_;
}

Lattice::~Lattice() {
  for(int i = 0; i < rows_; ++i) {
    for (int j = 0; j < colums_; ++j) {
      delete celulas_[i][j];
    }
  }
}

void Lattice::insertUpperRow() {
  ++rows_;
  std::vector<Cell*> fila(colums_);
  for(int i = 0; i < fila.size(); ++i) {
    fila[i] = new Cell(Position(highCorner_.getPosX() - 1, i), State(0));
  }
  celulas_.insert(celulas_.begin(), fila);
  highCorner_ = Position(highCorner_.getPosX() - 1, highCorner_.getPosY());
}

void Lattice::insertDownRow() {
  ++rows_;
  std::vector<Cell*> fila(colums_);
  for(int i = 0; i < fila.size(); ++i) {
    fila[i] = new Cell(Position(lowCorner_.getPosX() + 1, i), State(0));
  }
  celulas_.insert(celulas_.end(), fila);
  lowCorner_ = Position(lowCorner_.getPosX() + 1, lowCorner_.getPosY());
}

void Lattice::insertLeftColum() {
  ++colums_;
  for (int i = 0; i < rows_; ++i) {
    celulas_[i].insert(celulas_[i].begin(), new Cell(Position(i, highCorner_.getPosY() - 1), State(0)));
  }
  highCorner_ = Position(highCorner_.getPosX(), highCorner_.getPosY() - 1);
}

void Lattice::insertRightColum() {
  ++colums_;
  for (int i = 0; i < rows_; ++i) {
    celulas_[i].insert(celulas_[i].end(), new Cell(Position(lowCorner_.getPosX(), lowCorner_.getPosY() +1), State(0)));
  }
  lowCorner_ = Position(lowCorner_.getPosX(), lowCorner_.getPosY() + 1);
}

/**
   * @return Devuelve 0 si no hay niguna celula viva en el borde
   * @return Deveulve 1 si hay una celula viva en la fila 0
   * @return Devuelve 2 si hay una celula viva en la columna 0
   * @return Devuelve 3 si hay una celula viva en la fila n - 1
   * @return Devuelve 4 si hay una celula viva en la columna n-1
   * @return Devuelve 5 si hay una celula viva en la esquina 0,0
   * @return Devuelve 6 si hay una celula viva EN LA ESQUINA 0, n-1
   * @return Devuelve 7 si hay una celula viva EN LA ESQUINA n - 1, 0
   * @return Devuelve 8 si hay una celula viva EN LA ESQUINA n - 1, n - 1
  */
int Lattice::Border() {
  if (celulas_[0][0]->getState().getstate() == 1) {
    return 5;
  }
  if (celulas_[0][colums_ - 1]->getState().getstate() == 1) {
    return 6;
  }
  if (celulas_[rows_ - 1][0]->getState().getstate() == 1) {
    return 7;
  }
  if (celulas_[rows_ - 1][colums_ - 1]->getState().getstate() == 1) {
    return 8;
  }
  for (int i = 1; i < rows_ - 1; ++i) {
    if (celulas_[i][0]->getState().getstate() == 1) {
      return 2;
    }
  }
  for (int i = 1; i < colums_ - 1; ++i) {
    if (celulas_[0][i]->getState().getstate() == 1) {
      return 1;
    }
  }
  for (int i = 1; i < rows_ - 1; ++i) {
    if (celulas_[i][colums_ - 1]->getState().getstate() == 1) {
      return 4;
    }
  }
  for (int i = 1; i < colums_ - 1; ++i) {
    if (celulas_[rows_ -1][i]->getState().getstate() == 1) {
      return 4;
    }
  }
  return 0;
}