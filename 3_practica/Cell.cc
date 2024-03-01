#include "Cell.h"

State Cell::getState() const {
  return state_;
}

Cell::Cell(Position* position, const  State& state): position_(position) {
  state_ = state;
  State next_state(0);        // el estado siguiente por defecto es 0
  next_state_ = next_state;
}

void Cell::setState(State state) {
  state_ = state;
}

void Cell::setNextState(const State& state) {
  next_state_ = state;
}

std::ostream& operator<<(std::ostream& out, const Cell& cell) {
  return cell.display(out);
}

void CellACE110::updateState() {
  state_ = next_state_;
}
void CellACE30::updateState() {
  state_ = next_state_;
}

void CellLife23_3::updateState() {
  state_ = next_state_;
}

void CellLife51_346::updateState() {
  state_ = next_state_;
}

std::ostream& CellACE110::display(std::ostream& out) const {
  if (state_.getstate() == 0) {
    out << " ";
  } else {
    out << "*";
  }
  return out;
}

std::ostream& CellACE30::display(std::ostream& out) const {
  if (state_.getstate() == 0) {
    out << " ";
  } else {
    out << "X";
  }
  return out;
}

std::ostream& CellLife23_3::display(std::ostream& out) const{
  if (state_.getstate() == 0) {
    out << " ";
  }
  else {
    out << "+";
  }
  return out;
}

std::ostream& CellLife51_346::display(std::ostream& out) const {
  if (state_.getstate() == 0) {
    out << " ";
  }
  else {
    out << "O";
  }
  return out;
}

int CellACE110::nextState(Lattice& lattice) {
  int nueva_position = (*position_)[0] - 1;
  PositionDim<1> position(1, nueva_position);
  int left = lattice[position].getState().getstate();
  int middle = lattice[*position_].getState().getstate(); 
  nueva_position = (*position_)[0] + 1;
  PositionDim<1> pos(1, nueva_position);
  int right = lattice[pos].getState().getstate();
  return (middle + right + middle * right + left * right * middle) % 2; 
}

int CellACE30::nextState(Lattice& lattice) {
  int nueva_position = (*position_)[0] - 1;
  PositionDim<1> position(1, nueva_position);
  int left = lattice[position].getState().getstate();
  int middle = lattice[*position_].getState().getstate(); 
  nueva_position = (*position_)[0] + 1;
  PositionDim<1> pos(1, nueva_position);
  int right = lattice[pos].getState().getstate();
  return (left + middle + right + (middle * right)) % 2; 
}

int CellLife23_3::nextState(Lattice& lattice) {
  int nueva_positionx = (*position_)[0] - 1;
  int nueva_positiony = (*position_)[1] - 1;
  PositionDim<2> pos_1(2, nueva_positionx, nueva_positiony);
  nueva_positionx = (*position_)[0] - 1;
  nueva_positiony = (*position_)[1];
  PositionDim<2> pos_2(2, nueva_positionx, nueva_positiony);
  nueva_positionx = (*position_)[0] - 1;
  nueva_positiony = (*position_)[1] + 1;
  PositionDim<2> pos_3(2, nueva_positionx, nueva_positiony);
  nueva_positionx = (*position_)[0];
  nueva_positiony = (*position_)[1] - 1;
  PositionDim<2> pos_4(2, nueva_positionx, nueva_positiony);
  nueva_positionx = (*position_)[0];
  nueva_positiony = (*position_)[1] + 1;
  PositionDim<2> pos_5(2, nueva_positionx, nueva_positiony);
  nueva_positionx = (*position_)[0] + 1;
  nueva_positiony = (*position_)[1] - 1;
  PositionDim<2> pos_6(2, nueva_positionx, nueva_positiony);
  nueva_positionx = (*position_)[0] + 1;
  nueva_positiony = (*position_)[1];
  PositionDim<2> pos_7(2, nueva_positionx, nueva_positiony);
  nueva_positionx = (*position_)[0] + 1;
  nueva_positiony = (*position_)[1] + 1;
  PositionDim<2> pos_8(2, nueva_positionx, nueva_positiony);
  int celulas_vivas = 0;
  celulas_vivas += lattice[pos_1].getState().getstate();
  celulas_vivas += lattice[pos_2].getState().getstate();
  celulas_vivas += lattice[pos_3].getState().getstate();
  celulas_vivas += lattice[pos_4].getState().getstate();
  celulas_vivas += lattice[pos_5].getState().getstate();
  celulas_vivas += lattice[pos_6].getState().getstate();
  celulas_vivas += lattice[pos_7].getState().getstate();
  celulas_vivas += lattice[pos_8].getState().getstate();
  if (state_.getstate() == 1) {
    if (celulas_vivas == 2 || celulas_vivas == 3) {
      return 1;
    }
    else {
      return 0;
    }
  }
  else {
    if (celulas_vivas == 3) {
      return 1;
    }
    else {
      return 0;
    }
  }
}

int CellLife51_346::nextState(Lattice& lattice) {
  int nueva_positionx = (*position_)[0] - 1;
  int nueva_positiony = (*position_)[1] - 1;
  PositionDim<2> pos_1(2, nueva_positionx, nueva_positiony);
  nueva_positionx = (*position_)[0] - 1;
  nueva_positiony = (*position_)[1];
  PositionDim<2> pos_2(2, nueva_positionx, nueva_positiony);
  nueva_positionx = (*position_)[0] - 1;
  nueva_positiony = (*position_)[1] + 1;
  PositionDim<2> pos_3(2, nueva_positionx, nueva_positiony);
  nueva_positionx = (*position_)[0];
  nueva_positiony = (*position_)[1] - 1;
  PositionDim<2> pos_4(2, nueva_positionx, nueva_positiony);
  nueva_positionx = (*position_)[0];
  nueva_positiony = (*position_)[1] + 1;
  PositionDim<2> pos_5(2, nueva_positionx, nueva_positiony);
  nueva_positionx = (*position_)[0] + 1;
  nueva_positiony = (*position_)[1] - 1;
  PositionDim<2> pos_6(2, nueva_positionx, nueva_positiony);
  nueva_positionx = (*position_)[0] + 1;
  nueva_positiony = (*position_)[1];
  PositionDim<2> pos_7(2, nueva_positionx, nueva_positiony);
  nueva_positionx = (*position_)[0] + 1;
  nueva_positiony = (*position_)[1] + 1;
  PositionDim<2> pos_8(2, nueva_positionx, nueva_positiony);
  int celulas_vivas = 0;
  celulas_vivas += lattice[pos_1].getState().getstate();
  celulas_vivas += lattice[pos_2].getState().getstate();
  celulas_vivas += lattice[pos_3].getState().getstate();
  celulas_vivas += lattice[pos_4].getState().getstate();
  celulas_vivas += lattice[pos_5].getState().getstate();
  celulas_vivas += lattice[pos_6].getState().getstate();
  celulas_vivas += lattice[pos_7].getState().getstate();
  celulas_vivas += lattice[pos_8].getState().getstate();
  if (state_.getstate() == 1) {
    if (celulas_vivas == 5 || celulas_vivas == 1) {
      return 1;
    }
    else {
      return 0;
    }
  }
  else {
    if (celulas_vivas == 3 || celulas_vivas == 4 || celulas_vivas == 6) {
      return 1;
    }
    else {
      return 0;
    }
  }
}

Cell::~Cell() {
  delete position_;
}