#include "Cell.h"

State Cell::getState() const {
  return state_;
}

Cell::Cell(Position& position, const  State& state): position_(position) {
  state_ = state;
  State next_state(0);        // el estado siguiente por defecto es 0
  next_state_ = next_state;
}

void Cell::setState(State state) {
  state_ = state;
}

std::ostream& operator<<(std::ostream& out, const Cell& cell) {
  return cell.display(out);
}

void CellACE::updateState() {
  state_ = next_state_;
}

void CellLife::updateState() {
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

int CellACE110::nextState() {
  return 0;
}

int CellACE30::nextState() {
  return 0;
}

int CellLife23_3::nextState() {
  return 0;
}

int CellLife51_346::nextState() {
  return 0;
}