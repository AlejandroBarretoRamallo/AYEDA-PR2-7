#include "Lattice.h"


Lattice1D::Lattice1D(int size, FactoryCell& celula): tipoCelula_(celula){
  n_generation_ = 0;
  size_ = size;
  celulas_ = std::vector<Cell*> (size_);
  std::cout << "Numero de celulas vivas: \n";
  int numero_vivas = 0;
  std::cin >> numero_vivas;
  for (int i = 0; i < numero_vivas; ++i) {  // metemos celula vivas en las posiciones indicadas
    int position;
    std::cout << "Posicion de la celula viva: \n";
    std::cin >> position;
    PositionDim<1>* posicion = new PositionDim<1> (1, position);   // creamos la posicion
    celulas_[position] = celula.createCell(posicion, State(1));   // creamos la celula
  }
  for (int i = 0; i < size_; ++i) { // creamos las celulas muertas
    if (celulas_[i] == nullptr) {
      PositionDim<1>* posicion = new PositionDim<1>(1, i);
      celulas_[i] = celula.createCell(posicion, State(0));  // las celulas que falten por crear estaran muertas
    }
  }
}

Lattice1D_open::Lattice1D_open(int size, FactoryCell& celula, int border): Lattice1D(size, celula) {
  border_ = border;
  PositionDim<1>* pos = new PositionDim<1>(1, -1);
  celulas_.insert(celulas_.begin(), celula.createCell(pos, State(border)));  // insertamos la celula de frontera al principio
  pos = new PositionDim<1>(1, size);
  celulas_.insert(celulas_.end(), celula.createCell(pos, State(border)));  // insertamos la celula de frontera al final
  size_ += 2;  // aumentamos el tamaño
}

Lattice1D_open::Lattice1D_open(std::string fichero, FactoryCell& celula, int border): Lattice1D(fichero, celula) {
  border_ = border;
  PositionDim<1>* pos = new PositionDim<1>(1, -1);
  celulas_.insert(celulas_.begin(), celula.createCell(pos, State(border)));  // insertamos la celula de frontera al principio
  pos = new PositionDim<1>(1, size_);
  celulas_.insert(celulas_.end(), celula.createCell(pos, State(border)));  // insertamos la celula de frontera al final
  size_ += 2;  // aumentamos el tamaño
}

Lattice1D::Lattice1D(std::string fichero, FactoryCell& celula): tipoCelula_(celula) {
  n_generation_ = 0;
  std::ifstream input(fichero);     // abrimos el fichero
  std::string ristra;
  input >> ristra;    // obtenemos las celulas vvias o muertas  
  celulas_ = std::vector<Cell*> (ristra.size());
  size_ = ristra.size();  // asignamos al tamañoe l tamaño de la ristra
  for (int i = 0; i < ristra.size(); ++i) {   // creamos las celulas segun los valores de la ristra
    PositionDim<1>* posicion = new PositionDim<1>(1, i);
    if (ristra[i] == '1') {
      celulas_[i] = celula.createCell(posicion, State(1));
    }
    else {
      celulas_[i] = celula.createCell(posicion, State(0));
    }
  }
}

Lattice2D::Lattice2D(int rows, int columns, FactoryCell& celula): origen_(2, 0, 0), fin_(2, rows - 1, columns - 1), tipoCelula_(celula){
  n_generation_ = 0;
  celulas_ = std::vector<std::vector<Cell*>>(rows, std::vector<Cell*>(columns_, nullptr));    // vector de vectores vacio
  std::cout << "Introduzca el numero de celulas que van a estar vivas: ";
  int num_celulas = 0;
  std::cin >> num_celulas;
  for (int i = 0; i < num_celulas; ++i) {     // rellenar manualmente la matriz
    std::cout << "Introduce la coordenada x de la celula: ";
    int x, y;
    std::cin >> x;
    std::cout << "Introduce la coordenada y de la celula: ";
    std::cin >> y;
    PositionDim<2>* posicion = new PositionDim<2>(2, x, y);
    celulas_[x][y] = celula.createCell(posicion, State(1));
  }
  for (int i = 0; i < rows; ++i) {   // todas las que no se han creado como vivas se crean con estado 0
    for(int j = 0; j < columns; ++j) {
      PositionDim<2>* posicion = new PositionDim<2>(2, i , j);
      if (celulas_[i][j] == nullptr) {
        celulas_[i][j] = celula.createCell(posicion, State(0));
      }
    }
  }
  rows_ = rows;
  columns_ = columns;
}

Lattice2D::Lattice2D(std::string fichero, FactoryCell& celula): origen_(2, 0, 0), fin_(2, 0, 0), tipoCelula_(celula) {
  n_generation_ = 0;
  std::ifstream input(fichero); // abrir fichero
  input >> rows_ >> columns_;
  fin_ = PositionDim<2>(2, rows_ -1, columns_ - 1);
  celulas_ = std::vector<std::vector<Cell*>>(rows_, std::vector<Cell*>(columns_, nullptr));    // crear vector de vectores vacio
  char caracter;
  std::string linea;
  std::getline(input, linea);   // eliminar retorno de carro que sobra
  for(int i = 0; i < rows_; ++i) {
    std::getline(input, linea);
    if (linea.empty()) {    // una linea vacia se interpreta como llena de espacios blancos
       for(int j = 0; j < columns_; ++j) {
        linea += " ";
      }
    }
    for(int j = 0; j < columns_; ++j) {  // leer las celulas y crearlas
      caracter = linea[j];
      PositionDim<2>* position = new PositionDim<2>(2, i, j);
      if (caracter == 'x') {
        celulas_[i][j] = celula.createCell(position, State(1));
      }
      else {
        celulas_[i][j] =celula.createCell(position, State(0));
      }
    }
  }
}

Lattice1D::~Lattice1D() {
  for (int i = 0; i < size_; ++i) {
    delete celulas_[i];
  }
}

Lattice2D::~Lattice2D() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      delete celulas_[i][j];
    }
  }
}

std::size_t Lattice1D::Population() const {
  std::size_t population = 0;
  for (int i = 0; i < size_; ++i) {
    if (celulas_[i]->getState().getstate() == 1) {
      ++population;
    }
  }
  return population;
}

std::size_t Lattice2D::Population() const {
  std::size_t population = 0;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      if (celulas_[i][j]->getState().getstate() == 1) {
        ++population;
      }
    }
  }
  return population;
}

std::ostream& operator<<(std::ostream& out,Lattice& reticulo) {
  return reticulo.display(out);
}

std::ostream& Lattice1D::display(std::ostream& out) {
  for (int i = 0; i < size_; ++i) {
    out << *celulas_[i];
  }
  out << "\n";
  return out;
}

std::ostream& Lattice2D::display(std::ostream& out) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      out << *celulas_[i][j];
    }
    out << "\n";
  }
  return out;
}

Cell& Lattice1D_open::operator[](const Position& position) const {
  return *celulas_[position[0] + 1];
}

Cell& Lattice1D_periodic::operator[](const Position& position) const {
  if (position[0] < 0) {
    return *celulas_[size_ - 1];
  }
  else if (position[0] >= size_) {
    return *celulas_[0];
  }
  else {
    return *celulas_[position[0]];
  }
}

Cell& Lattice2D_reflective::operator[](const Position& position) const {
  int pos_x = position[0];
  int pos_y = position[1];
  if (pos_x == -1 && pos_y == -1) {
    return *celulas_[0][0];
  }
  else if (pos_x == -1 && pos_y == columns_) {
    return *celulas_[0][pos_y - 1];
  }
  else if (pos_x == rows_ && pos_y == -1) {
    return *celulas_[pos_x - 1][0];
  }
  else if (pos_x == rows_ && pos_y == columns_) {
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
  else if (pos_y == columns_) {
    return *celulas_[pos_x][pos_y - 1];
  }
  else {
    return *celulas_[pos_x][pos_y];
  }
}

Cell& Lattice2D_noborder::operator[](const Position& position) const {
  int pos_x = position[0];
  int pos_y = position[1];
  if (pos_x < origen_[0] || pos_x > fin_[0] || pos_y < origen_[0] || pos_y > fin_[1]) {
    State state(0);
    PositionDim<2>* posicion = new PositionDim<2>(2, pos_x, pos_y);
    return *tipoCelula_.createCell(posicion, state);
  }
  else {
    return *celulas_[pos_x - origen_[0]][pos_y - origen_[1]];
  }
}

void Lattice1D_open::nextGeneration() {
  for (int i = 1; i < size_ - 1; ++i) {
    celulas_[i]->setNextState(State(celulas_[i]->nextState(*this)));
  }
  for (int i = 1; i < size_ - 1; ++i) {
    celulas_[i]->updateState();
  }
}

void Lattice1D_periodic::nextGeneration() {
  for (int i = 0; i < size_; ++i) {
    celulas_[i]->setNextState(State(celulas_[i]->nextState(*this)));
  }
  for (int i = 0; i < size_; ++i) {
    celulas_[i]->updateState();
  }
}

void Lattice2D_reflective::nextGeneration() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      celulas_[i][j]->setNextState(State(celulas_[i][j]->nextState(*this)));
    }
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      celulas_[i][j] ->updateState();
    }
  }
}

void Lattice2D_noborder::nextGeneration() {
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
        insertLeftColumn();
        break;
      case 3:   // añadir fila por debajo
        insertLowerRow();
        break;
      case 4:    // añadir columna por la derecha
        insertRightColumn();
        break;
      case 5:     //añadir fila y columna inicial
        insertLeftColumn();
        insertUpperRow();
        break;
      case 6:      //añadir fila inicial y columna final
        insertUpperRow();
        insertRightColumn();
        break;    
      case 7:     //añadir fila final y columan inicial
        insertLowerRow();
        insertLeftColumn();
        break;     
      case 8:     // añadir fila y columna final
        insertLowerRow();
        insertRightColumn();
        break;
    }
  }
  for(int i = 0; i < rows_; ++i) { 
    for (int j = 0; j < columns_; ++j) {
      celulas_[i][j]->setNextState(State(celulas_[i][j]->nextState(*this)));
    }
  }
  for(int i = 0; i < rows_; ++i) {    // todas se actualizan
    for (int j = 0; j < columns_; ++j) {
      celulas_[i][j]->updateState();
    }
  }
  border = 1;
  while (border != 0) {
    border = Border();  // calcula en que borde hay celulas vivas
    switch (border) {
      case 0:
        break;
      case 1: // añadir fila por arriba
        insertUpperRow();
        break;
      case 2:  // añadir columna por la izquierda
        insertLeftColumn();
        break;
      case 3:   // añadir fila por debajo
        insertLowerRow();
        break;
      case 4:    // añadir columna por la derecha
        insertRightColumn();
        break;
      case 5:     //añadir fila y columna inicial
        insertLeftColumn();
        insertUpperRow();
        break;
      case 6:      //añadir fila inicial y columna final
        insertUpperRow();
        insertRightColumn();
        break;    
      case 7:     //añadir fila final y columan inicial
        insertLowerRow();
        insertLeftColumn();
        break;     
      case 8:     // añadir fila y columna final
        insertLowerRow();
        insertRightColumn();
        break;
    }
  } 
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
int Lattice2D_noborder::Border() {
  if (celulas_[0][0]->getState().getstate() == 1) {   //esquina arriba izquierda
    return 5;
  }
  if (celulas_[0][columns_ - 1]->getState().getstate() == 1) { // esquina arriba derecha
    return 6;
  }
  if (celulas_[rows_ - 1][0]->getState().getstate() == 1) {   // esquina abajo izquierda
    return 7;
  }
  if (celulas_[rows_ - 1][columns_ - 1]->getState().getstate() == 1) { // esquina abajo derecha
    return 8;
  }
  for (int i = 1; i < rows_ - 1; ++i) {       // columna 0
    if (celulas_[i][0]->getState().getstate() == 1) {
      return 2;
    }
  }
  for (int i = 1; i < columns_ - 1; ++i) {    // fila 0
    if (celulas_[0][i]->getState().getstate() == 1) {
      return 1;
    }
  }
  for (int i = 1; i < rows_ - 1; ++i) {   // columna n - 1
    if (celulas_[i][columns_ - 1]->getState().getstate() == 1) {
      return 4;
    }
  }
  for (int i = 1; i < columns_ - 1; ++i) {   // fila n - 1
    if (celulas_[rows_ -1][i]->getState().getstate() == 1) {
      return 3;
    }
  }
  return 0;
}

void Lattice2D_noborder::insertUpperRow() {
  ++rows_;
  std::vector<Cell*> fila(columns_); // creamos el vector de celulas muertas
  for(int i = 0; i < fila.size(); ++i) {
    PositionDim<2>* posicion = new PositionDim<2>(2, origen_[0] - 1, i + origen_[1]);
    fila[i] = tipoCelula_.createCell(posicion, State(0)); // rellenamos el vector con celulas muertas, teniendo en cuenta posiciones negativas
  }
  celulas_.insert(celulas_.begin(), fila);    // insertamos al principio
  PositionDim<2> origen(2, origen_[0] - 1, origen_[1]);  // actualizamos el origen
  origen_ = origen;
}

void Lattice2D_noborder::insertLowerRow() {
  ++rows_;
  std::vector<Cell*> fila(columns_); // creamos el vector de celulas muertas
  for(int i = 0; i < fila.size(); ++i) {
    PositionDim<2>* posicion = new PositionDim<2>(2, fin_[0] + 1, i + origen_[1]);
    fila[i] = tipoCelula_.createCell(posicion, State(0)); // rellenamos el vector con celulas muertas, teniendo en cuenta posiciones negativas
  }
  celulas_.insert(celulas_.end(), fila);
  PositionDim<2> fin(2, fin_[0] + 1, fin_[1]);  // actualizamos el final
  fin_ = fin; // actualizamos el final de la matriz (n - 1, n - 1)
}

void Lattice2D_noborder::insertLeftColumn() {
  ++columns_;
  for (int i = 0; i < rows_; ++i) {   // insertamos al principio de cada vector una celula muerta teniendo en cuenta posiciones negativas
    PositionDim<2>* posicion = new PositionDim<2>(2,i + origen_[0], origen_[1] - 1);
    celulas_[i].insert(celulas_[i].begin(), tipoCelula_.createCell(posicion, State(0)));
  }
  PositionDim<2> origen(2, origen_[0], origen_[1] - 1);
  origen_ = origen;   // actualizamos el origen
}

void Lattice2D_noborder::insertRightColumn() {
  ++columns_;
  for (int i = 0; i < rows_; ++i) {   // insertamos al final de cada vector una celula muerta teniendo en cuenta posiciones negativas
    PositionDim<2>* posicion = new PositionDim<2>(2, origen_[0] + i, fin_[1] + 1);
    celulas_[i].insert(celulas_[i].end(), tipoCelula_.createCell(posicion, State(0)));
  }
  PositionDim<2> fin(2, fin_[0], fin_[1] + 1);
  fin_ = fin;  // actualizamos el final de la matriz
}

Lattice::~Lattice() {}