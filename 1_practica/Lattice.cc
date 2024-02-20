#include "Lattice.h"

Lattice::Lattice() {
  celulas_ = new Cell[1];
  size_ = 1;
  Position posicion;
  State state;
  celulas_[0] = Cell(posicion, state);
  std::string borderType_ = "caliente";
  n_generation_ = 1;
}


Lattice::Lattice(const std::string& configuracion, const std::string& frontera) {
  n_generation_ = 1;
  const int tamaño_reticulo = configuracion.size() + 2;
  if (frontera != "periodica") {
    size_ = tamaño_reticulo;
    celulas_ = new Cell[tamaño_reticulo];
    Position position(0), position2(tamaño_reticulo - 1);
    State state;
    if (frontera == "caliente") {  
      state.setState(1);
    }
    else {
      state.setState(0);
    }
    celulas_[0] = Cell(position, state); 
    celulas_[tamaño_reticulo - 1] = Cell(position2, state);
    for (int i = 0; i < configuracion.size(); ++i) {
      Position position(i + 1);
      int estado = configuracion[i] - '0';
      State state(estado);
      celulas_[i + 1] = Cell(position, state);
    }
  }
  else {
    size_ = configuracion.size();
    celulas_ = new Cell[size_];
    for (int i = 0; i < size_; ++i) {
      Position position(i);
      int estado = configuracion[i] - '0';
      State state(estado);
      celulas_[i] = Cell(position, state);
    }
  }
  borderType_ = frontera;
}

const Cell& Lattice::getCell(const Position& position) const {
  if (borderType_ == "periodica") {
    if (position.getPosition() == -1) {
      return celulas_[size_ - 1];
    }
    else if (position.getPosition() == size_) {
      return celulas_[0];
    }
    else {
      return celulas_[position.getPosition()];
    }
  }
  else {
    return celulas_[position.getPosition()];
  }
}

Cell* Lattice::getCelulas() {
  return celulas_;
}

int Lattice::getSize() const {
  return size_;
}

std::ostream& operator <<(std::ostream& out, Lattice const& reticulo) {
  for (int i = 0; i < reticulo.getSize(); ++i) {
    Position posicion(i);
    std::cout << reticulo.getCell(posicion);
  }
  std::cout << "  (" << reticulo.getN_generation() << ")\n";
  return out;
}

void Lattice::nextGeneration() {
  if (borderType_ != "periodica") {
    for (int i = 1; i < size_ - 1; ++i) {
      celulas_[i].setNextState(celulas_[i].NextState(*this));
    }
    for (int i = 1; i < size_ - 1; ++i) {
      celulas_[i].updateState();
    }
  }
  else {
    for (int i = 0; i < size_; ++i) {
      celulas_[i].setNextState(celulas_[i].NextState(*this));
    }
    for (int i = 0; i < size_; ++i) {
      celulas_[i].updateState();
    }
  }
  
}

void Lattice::updateN_generation() {
  ++n_generation_;
}

Lattice::~Lattice() {
  delete[] celulas_;
}