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
  if (borderType_ == "periodica" || borderType_ == "noborder" || borderType_ == "reflectora") {   // si no es abierta no hay que añadir celulas, se crean de la misma forma
    celulas_ = std::vector<std::vector<Cell*>>(N, std::vector<Cell*>(M, nullptr));    // vector de vectores vacio
    std::cout << "Introduzca el numero de celulas que van a estar vivas: ";
    int num_celulas = 0;
    std::cin >> num_celulas;
    for (int i = 0; i < num_celulas; ++i) {     // rellenar manualmente la matriz
      std::cout << "Introduce la coordenada x de la celula: ";
      int x, y;
      std::cin >> x;
      std::cout << "Introduce la coordenada y de la celula: ";
      std::cin >> y;
      celulas_[x][y] = new Cell(Position(x, y), State(1));
    }
    for (int i = 0; i < N; ++i) {   // todas las que no se han creado como vivas se crean con estado 0
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
  else {    // si es abierta debemos añadir celulas alrededor de la matriz
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
    for (int i = 1; i <= N; ++i) {  // rellenar interior de matriz
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
    for(int i = 1; i < rows_ - 1; ++i) {// relllenar los bordes
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

Lattice::Lattice(std::string input, std::string bordertype) { //leer desde fichero
  borderType_ = bordertype;
  std::ifstream fichero(input); // abrir fichero
  fichero >> rows_ >> colums_;
  highCorner_ = Position(0, 0);
  lowCorner_ = Position(rows_ - 1, colums_ - 1);
  if (borderType_ == "periodica" || borderType_ == "noborder" || borderType_ == "reflectora") {    // si no es abierta se crean de la misma forma
    celulas_ = std::vector<std::vector<Cell*>>(rows_, std::vector<Cell*>(colums_, nullptr));    // crear vector de vectores vacio
    char caracter;
    std::string linea;
    std::getline(fichero, linea);   // eliminar retorno de carro que sobra
    for(int i = 0; i < rows_; ++i) {
      std::getline(fichero, linea);
      if (linea.empty()) {    // una linea vacia se interpreta como llena de espacios blancos
        for(int j = 0; j < colums_; ++j) {
          linea += " ";
        }
      }
      for(int j = 0; j < colums_; ++j) {  // leer las celulas y crearlas
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
  else {    // si es caliente debemos añadir celulas en los bordes
    rows_ += 2;
    colums_ += 2;
    celulas_ = std::vector<std::vector<Cell*>>(rows_, std::vector<Cell*>(colums_, nullptr));
    char caracter;
    std::string linea;
    std::getline(fichero, linea);
    for (int i = 1; i < rows_ - 1; ++i) { // rellenar interior de la matriz
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
    for(int i = 1; i < rows_ - 1; ++i) {  // rellenar bordes
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
    return *celulas_[pos_x][pos_y];  // nunca se accedera a una psoicion invalida por haber añadido celulas a los bordes
  }
  else if (borderType_ == "periodica") {  // trata la condicion de forntera como tipo periodica
    // todos los posibles casos de acceso invalido
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
  else  if (borderType_ == "reflectora") {  // trata condicion de frontera como tipo reflectora
    // todos los psoibles casos de accesos invalidos
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
  else {
    // si es no border se ajusta para que tambien devuelva las posiciones negativas si existiesen
    if (pos_x < highCorner_.getPosX() || pos_x > lowCorner_.getPosX() || pos_y < highCorner_.getPosY() || pos_y > lowCorner_.getPosY()) { 
      Cell* celula = new Cell(Position(pos_x, pos_y), State(0));
      return *celula;
    }
    return *celulas_[pos_x -highCorner_.getPosX()][pos_y - highCorner_.getPosY()];
  }
}


void Lattice::nextGeneration() {
  if (borderType_ != "periodica" && borderType_ != "reflectora" && borderType_ != "noborder") { // si es abierta soo interesa actualizar el interior
    for (int i = 1; i < rows_ - 1; ++i) {
      for(int j = 1; j < colums_ - 1; ++j) {
        celulas_[i][j]->setNextState(celulas_[i][j]->NextState(*this));   // calculamos y ponemos el proximo estado
      }
    }
    for (int i = 1; i < rows_ - 1; ++i) {
      for(int j = 1; j < colums_ - 1; ++j) {
        celulas_[i][j]->updateState();    // actualizamos estado
      }
    }
  }
  else  if (borderType_ != "noborder") {  // si es cerraada y distinta de noborder se actualiza toda la matriz
    for(int i = 0; i < rows_; ++i) {
      for (int j = 0; j < colums_; ++j) {
        celulas_[i][j]->setNextState(celulas_[i][j]->NextState(*this));   //calculamos y ponemos el proximo estado
      }
    }
    for(int i = 0; i < rows_; ++i) {
      for (int j = 0; j < colums_; ++j) {
        celulas_[i][j]->updateState();    //actualizamos estado
      }
    }
  }
  else {    // caso nobordder
    int border = 1;
    while (border != 0) { // no termina hasta que no hayan celulas vivas en los bordes
      border = Border();  // calcula en que borde hay celulas vivas
      switch (border) {
        case 0:
          break;
        case 1: // añadir fila por arriba
          insertUpperRow();
          break;
        case 2:  // añadir columna por la izquierda
          insertLeftColum();
          break;
        case 3:   // añadir fila por debajo
          insertDownRow();
          break;
        case 4:    // añadir columna por la derecha
          insertRightColum();
          break;
        case 5:     //añadir fila y columna inicial
          insertLeftColum();
          insertUpperRow();
          break;
        case 6:      //añadir fila inicial y columna final
          insertUpperRow();
          insertRightColum();
          break;    
        case 7:     //añadir fila final y columan inicial
          insertDownRow();
          insertLeftColum();
          break;     
        case 8:     // añadir fila y columna final
          insertDownRow();
          insertRightColum();
          break;
      }
    }
    for(int i = 0; i < rows_; ++i) { 
      for (int j = 0; j < colums_; ++j) {
        celulas_[i][j]->setNextState(celulas_[i][j]->NextState(*this));
      }
    }
    for(int i = 0; i < rows_; ++i) {    // todas se actualizan
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
  for(int i = 0; i < rows_; ++i) {
    for (int j = 0; j < colums_; ++j) {
      delete celulas_[i][j];
    }
  }
}

void Lattice::insertUpperRow() {     
  ++rows_;
  std::vector<Cell*> fila(colums_); // creamos el vector de celulas muertas
  for(int i = 0; i < fila.size(); ++i) {
    fila[i] = new Cell(Position(highCorner_.getPosX() - 1, i + highCorner_.getPosY()), State(0)); // rellenamos el vector con celulas muertas, teniendo en cuenta posiciones negativas
  }
  celulas_.insert(celulas_.begin(), fila);    // insertamos al principio
  highCorner_ = Position(highCorner_.getPosX() - 1, highCorner_.getPosY());   // actualizamos el origen
}

void Lattice::insertDownRow() {   
  ++rows_;
  std::vector<Cell*> fila(colums_); // creamos el vector de celulas muertas
  for(int i = 0; i < fila.size(); ++i) {
    fila[i] = new Cell(Position(lowCorner_.getPosX() + 1, i +highCorner_.getPosY()), State(0)); // rellenamos el vector con celulas muertas, teniendo en cuenta posiciones negativas
  }
  celulas_.insert(celulas_.end(), fila);
  lowCorner_ = Position(lowCorner_.getPosX() + 1, lowCorner_.getPosY()); // actualizamos el final de la matriz (n - 1, n - 1)
}

void Lattice::insertLeftColum() {   
  ++colums_;
  for (int i = 0; i < rows_; ++i) {   // insertamos al principio de cada vector una celula muerta teniendo en cuenta posiciones negativas
    celulas_[i].insert(celulas_[i].begin(), new Cell(Position(i + highCorner_.getPosX(), highCorner_.getPosY() - 1), State(0)));
  }
  highCorner_ = Position(highCorner_.getPosX(), highCorner_.getPosY() - 1);   // actualizamos el origen
}

void Lattice::insertRightColum() {
  ++colums_;
  for (int i = 0; i < rows_; ++i) {   // insertamos al final de cada vector una celula muerta teniendo en cuenta posiciones negativas
    celulas_[i].insert(celulas_[i].end(), new Cell(Position(highCorner_.getPosX() + i, lowCorner_.getPosY() +1), State(0)));
  }
  lowCorner_ = Position(lowCorner_.getPosX(), lowCorner_.getPosY() + 1);  // actualizamos el final de la matriz
}
/**
   * @return Devuelve 0 si no hay niguna celula viva en el borde
   * @return Deveulve 1 si hay una celula viva en la fila 0
   * @return Devuelve 2 si hay una celula viva en la columna 0
   * @return Devuelve 3 si hay una celula viva en la fila n - 1
   * @return Devuelve 4 si hay una celula viva en la columna n-1
   * @return Devuelve 5 si hay una celula viva en la esquina 0,0
   * @return Devuelve 6 si hay una celula viva en la esquina 0, n-1
   * @return Devuelve 7 si hay una celula viva en la esquina n - 1, 0
   * @return Devuelve 8 si hay una celula viva en la esquina n - 1, n - 1
  */
int Lattice::Border() {
  if (celulas_[0][0]->getState().getstate() == 1) {   //esquina arriba izquierda
    return 5;
  }
  if (celulas_[0][colums_ - 1]->getState().getstate() == 1) { // esquina arriba derecha
    return 6;
  }
  if (celulas_[rows_ - 1][0]->getState().getstate() == 1) {   // esquina abajo izquierda
    return 7;
  }
  if (celulas_[rows_ - 1][colums_ - 1]->getState().getstate() == 1) { // esquina abajo derecha
    return 8;
  }
  for (int i = 1; i < rows_ - 1; ++i) {       // columna 0
    if (celulas_[i][0]->getState().getstate() == 1) {
      return 2;
    }
  }
  for (int i = 1; i < colums_ - 1; ++i) {    // fila 0
    if (celulas_[0][i]->getState().getstate() == 1) {
      return 1;
    }
  }
  for (int i = 1; i < rows_ - 1; ++i) {   // columna n - 1
    if (celulas_[i][colums_ - 1]->getState().getstate() == 1) {
      return 4;
    }
  }
  for (int i = 1; i < colums_ - 1; ++i) {   // fila n - 1
    if (celulas_[rows_ -1][i]->getState().getstate() == 1) {
      return 3;
    }
  }
  return 0;
}

std::ostream& operator <<(std::ostream& out, Lattice const& reticulo) {
  for(int i = 0; i < reticulo.getRows(); ++i) { // recorrer toda la matriz
    for(int j = 0; j < reticulo.getColumns(); ++j) {
      out << *reticulo.celulas_[i][j];
    }
    out << "\n";
  }
  return out;
}

std::size_t Lattice::Population() const {
  size_t population = 0;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < colums_; ++j) {
      if (celulas_[i][j]->getState().getstate() == 1) {
        ++population;
      }
    }
  }
  return population;
}