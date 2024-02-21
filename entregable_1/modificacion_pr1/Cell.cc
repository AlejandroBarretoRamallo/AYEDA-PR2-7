#include "Cell.h"

Cell::Cell(const Position& position, const  State& state) {
  state_ = state;
  position_ = position;
  State next_state(0);
  next_state_ = next_state;
}

Cell::Cell() {
  position_ = Position();
  state_ = State();
  next_state_ = State(0);
}

State Cell::getState() const {
  return state_;
}

void Cell::updateState() {               
  state_ = next_state_;
}

std::ostream& operator<<(std::ostream& out, const Cell& cell) {
  if(cell.getState().getstate()) {
    std::cout << "X";
  }
  else {
    std::cout << " ";
  }
  return out;
}

int Cell::NextState(Lattice& reticulo) const{
  int vecindad = 0;
  Position position(position_.getPosition() -2);
  int numero = reticulo.getCell(position).getState().getstate();
  vecindad += numero * 100;  // obtenemos el estado de la celula anterior
  numero = state_.getstate();
  vecindad += numero * 10;      // obtenemos el estado de la celula actual
  Position posicion(position_.getPosition() + 2);           // obtenemos el estado de la celula siguiente
  vecindad += reticulo.getCell(posicion).getState().getstate();
  switch(vecindad) {    // calculamos el estado dependiendo de la vecindad
    case 0:
      return 0;
      break;
    case 1:
      return 1;
      break;
    case 10:
      return 1;
      break;
    case 11:
      return 1;
      break;
    case 100:
      return 0;
      break;
    case 101:
      return 1;
      break;
    case 110:
      return 1;
      break;
    case 111:
      return 0; 
      break;
    default:
      return 0;
  }
}

bool Cell::IsBorder(Lattice& reticulo) const {
  if (position_.getPosition() == 0 || position_.getPosition() == reticulo.getSize() - 1) {
    return true;
  }
  return false;
}

std::ostream& operator<<(std::ostream& out, Cell& celula) {
  if (celula.getState().getstate() == 1) {
    std::cout << "X";
  }
  else {
    std::cout << " ";
  }
  return out;
}

void Cell::setNextState(const int& state) {
  next_state_ = State(state);
}