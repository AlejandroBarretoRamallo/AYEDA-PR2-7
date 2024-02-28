#include "Cell.h"

Cell::Cell(const Position& position, const  State& state) {  
  state_ = state;
  position_ = position;
  State next_state(0);        // el estado siguiente por defecto es 0
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



int Cell::NextState(Lattice& reticulo) const{
  int celulas_vivas = 0;
  int pos_x = position_.getPosX();
  int pos_y = position_.getPosY();
  int n_filas = reticulo.getRows();
  int n_colums = reticulo.getColumns();
  celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y - 1)).getState().getstate();   // n -1 ,m -1
  celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y)).getState().getstate();       //n -1 ,m
  celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y + 1)).getState().getstate();   //n - 1, m + 1
  celulas_vivas += reticulo.getCell(Position(pos_x, pos_y - 1)).getState().getstate();       //n, m - 1
  celulas_vivas += reticulo.getCell(Position(pos_x, pos_y + 1)).getState().getstate();       //n, m + 1
  celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y - 1)).getState().getstate();    //n +1, m - 1
  celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y)).getState().getstate();        // n + 1, m
  celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y + 1)).getState().getstate();    //n + 1, m + 1
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

bool Cell::IsBorder(Lattice& reticulo) const {
  if (position_.getPosX() == 0 || position_.getPosY() == 0) {
    return true;
  }
  if (position_.getPosX() == reticulo.getRows() - 1 || position_.getPosY() == reticulo.getColumns() - 1) {
    return true;
  }
  return false;
}

std::ostream& operator<<(std::ostream& out, const Cell& cell) {
  if(cell.getState().getstate()) {
    out << "X";
  }
  else {
    out << " ";
  }
  return out;
}
void Cell::setNextState(const int& state) {
  next_state_ = State(state);
}