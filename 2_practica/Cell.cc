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
  int celulas_vivas = 0;
  int pos_x = position_.getPosX();
  int pos_y = position_.getPosY();
  int n_filas = reticulo.getRows();
  int n_colums = reticulo.getColumns();
  std::string borderType = reticulo.getBorderType();
  if (borderType != "periodica" && borderType != "reflectora" && borderType != "noborder") {
    celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y - 1)).getState().getstate();   // n -1 ,m -1
    celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y)).getState().getstate();       //n -1 ,m
    celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y + 1)).getState().getstate();   //n - 1, m + 1
    celulas_vivas += reticulo.getCell(Position(pos_x, pos_y - 1)).getState().getstate();       //n, m - 1
    celulas_vivas += reticulo.getCell(Position(pos_x, pos_y + 1)).getState().getstate();       //n, m + 1
    celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y - 1)).getState().getstate();    //n +1, m - 1
    celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y)).getState().getstate();        // n + 1, m
    celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y + 1)).getState().getstate();    //n + 1, m + 1
  }
  else if (borderType == "periodica") {
    if (!IsBorder(reticulo)) {
      celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y - 1)).getState().getstate();   // n -1 ,m -1
      celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y)).getState().getstate();       //n -1 ,m
      celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y + 1)).getState().getstate();   //n - 1, m + 1
      celulas_vivas += reticulo.getCell(Position(pos_x, pos_y - 1)).getState().getstate();       //n, m - 1
      celulas_vivas += reticulo.getCell(Position(pos_x, pos_y + 1)).getState().getstate();       //n, m + 1
      celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y - 1)).getState().getstate();    //n +1, m - 1
      celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y)).getState().getstate();        // n + 1, m
      celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y + 1)).getState().getstate();  // n+ 1, m + 1
    }
    else {
      if (pos_x == 0 && pos_y == 0) {             
        celulas_vivas += reticulo.getCell(Position(n_filas - 1, n_colums - 1)).getState().getstate();  // n -1 ,m -1
        celulas_vivas += reticulo.getCell(Position(n_filas - 1, 0)).getState().getstate(); // n - 1, m
        celulas_vivas += reticulo.getCell(Position(n_filas - 1, 1)).getState().getstate();  //n - 1. m + 1
        celulas_vivas += reticulo.getCell(Position(0, n_colums - 1)).getState().getstate(); // n, m - 1
        celulas_vivas += reticulo.getCell(Position(0, 1)).getState().getstate();            //n, m + 1
        celulas_vivas += reticulo.getCell(Position(1, n_colums - 1)).getState().getstate(); // n + 1, m - 1
        celulas_vivas += reticulo.getCell(Position(1, 0)).getState().getstate();            // n + 1, m
        celulas_vivas += reticulo.getCell(Position(1, 1)).getState().getstate();            // n + 1. m + 1
      }
      else if (pos_x == n_filas - 1 && pos_y == n_colums - 1) {    
        celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y - 1)).getState().getstate();  // n- 1, m - 1
        celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y)).getState().getstate();    // n - 1, m
        celulas_vivas += reticulo.getCell(Position(pos_x -1, 0)).getState().getstate(); // n - 1, m + 1
        celulas_vivas += reticulo.getCell(Position(pos_x, pos_y - 1)).getState().getstate();   // n, m - 1
        celulas_vivas += reticulo.getCell(Position(pos_x, 0)).getState().getstate();          // n , m + 1
        celulas_vivas += reticulo.getCell(Position(0, pos_y - 1)).getState().getstate();  //n + 1. m - 1
        celulas_vivas += reticulo.getCell(Position(0, pos_y)).getState().getstate();       // n + 1, m
        celulas_vivas += reticulo.getCell(Position(0, 0)).getState().getstate();            //n + 1, m + 1
      }
      else if (pos_x == 0 && pos_y == n_colums - 1) {
        celulas_vivas += reticulo.getCell(Position(n_filas - 1, pos_y - 1)).getState().getstate();  // n- 1, m - 1
        celulas_vivas += reticulo.getCell(Position(n_filas - 1, pos_y)).getState().getstate();    // n - 1, m
        celulas_vivas += reticulo.getCell(Position(n_filas - 1, n_colums - 1)).getState().getstate(); // n - 1, m + 1
        celulas_vivas += reticulo.getCell(Position(pos_x, pos_y- 1)).getState().getstate();   // n, m - 1
        celulas_vivas += reticulo.getCell(Position(pos_x, 0)).getState().getstate();          // n , m + 1
        celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y - 1)).getState().getstate();  //n + 1. m - 1
        celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y)).getState().getstate();       // n + 1, m
        celulas_vivas += reticulo.getCell(Position(pos_x + 1, 0)).getState().getstate();            //n + 1, m + 1
      }
      else if (pos_x == n_filas - 1 && pos_y == 0) {
        celulas_vivas += reticulo.getCell(Position(pos_x - 1,  n_colums - 1)).getState().getstate();  // n- 1, m - 1
        celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y)).getState().getstate();    // n - 1, m
        celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y + 1)).getState().getstate(); // n - 1, m + 1
        celulas_vivas += reticulo.getCell(Position(pos_x, n_colums - 1)).getState().getstate();   // n, m - 1
        celulas_vivas += reticulo.getCell(Position(pos_x, pos_y + 1)).getState().getstate();          // n , m + 1
        celulas_vivas += reticulo.getCell(Position(0, n_colums - 1)).getState().getstate();  //n + 1. m - 1
        celulas_vivas += reticulo.getCell(Position(0, 0)).getState().getstate();       // n + 1, m
        celulas_vivas += reticulo.getCell(Position(0, pos_y + 1)).getState().getstate();            //n + 1, m + 1
      }
      else if (pos_x == 0) {
        celulas_vivas += reticulo.getCell(Position(n_filas - 1, pos_y - 1)).getState().getstate();  // n- 1, m - 1
        celulas_vivas += reticulo.getCell(Position(n_filas - 1, pos_y)).getState().getstate();    // n - 1, m
        celulas_vivas += reticulo.getCell(Position(n_filas - 1, pos_y + 1)).getState().getstate(); // n - 1, m + 1
        celulas_vivas += reticulo.getCell(Position(pos_x, pos_y - 1)).getState().getstate();   // n, m - 1
        celulas_vivas += reticulo.getCell(Position(pos_x, pos_y + 1)).getState().getstate();          // n , m + 1
        celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y - 1)).getState().getstate();  //n + 1. m - 1
        celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y)).getState().getstate();       // n + 1, m
        celulas_vivas += reticulo.getCell(Position(pos_x+ 1, pos_y + 1)).getState().getstate();            //n + 1, m + 1
      }
      else if (pos_y == 0) {
        celulas_vivas += reticulo.getCell(Position(pos_x - 1, n_colums - 1)).getState().getstate();  // n- 1, m - 1
        celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y)).getState().getstate();    // n - 1, m
        celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y + 1)).getState().getstate(); // n - 1, m + 1
        celulas_vivas += reticulo.getCell(Position(pos_x, n_colums - 1)).getState().getstate();   // n, m - 1
        celulas_vivas += reticulo.getCell(Position(pos_x, pos_y + 1)).getState().getstate();          // n , m + 1
        celulas_vivas += reticulo.getCell(Position(pos_x + 1, n_colums - 1)).getState().getstate();  //n + 1. m - 1
        celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y)).getState().getstate();       // n + 1, m
        celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y + 1)).getState().getstate();            //n + 1, m + 1
      }
      else if (pos_x == n_filas - 1) {
        celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y - 1)).getState().getstate();  // n- 1, m - 1
        celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y)).getState().getstate();    // n - 1, m
        celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y + 1)).getState().getstate(); // n - 1, m + 1
        celulas_vivas += reticulo.getCell(Position(pos_x, pos_y - 1)).getState().getstate();   // n, m - 1
        celulas_vivas += reticulo.getCell(Position(pos_x, pos_y + 1)).getState().getstate();          // n , m + 1
        celulas_vivas += reticulo.getCell(Position(0, pos_y - 1)).getState().getstate();  //n + 1. m - 1
        celulas_vivas += reticulo.getCell(Position(0, pos_y)).getState().getstate();       // n + 1, m
        celulas_vivas += reticulo.getCell(Position(0, pos_y + 1)).getState().getstate();            //n + 1, m + 1
      }
      else if (pos_y == n_colums - 1) {
        celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y - 1)).getState().getstate();  // n- 1, m - 1
        celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y)).getState().getstate();    // n - 1, m
        celulas_vivas += reticulo.getCell(Position(pos_x - 1, 0)).getState().getstate(); // n - 1, m + 1
        celulas_vivas += reticulo.getCell(Position(pos_x, pos_y - 1)).getState().getstate();   // n, m - 1
        celulas_vivas += reticulo.getCell(Position(pos_x, 0)).getState().getstate();          // n , m + 1
        celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y - 1)).getState().getstate();  //n + 1. m - 1
        celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y)).getState().getstate();       // n + 1, m
        celulas_vivas += reticulo.getCell(Position(pos_x + 1, 0)).getState().getstate();            //n + 1, m + 1
      }
    }
  }
  else if (borderType == "reflectora") {
    if (!IsBorder(reticulo)) {
      celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y - 1)).getState().getstate();   // n -1 ,m -1
      celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y)).getState().getstate();       //n -1 ,m
      celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y + 1)).getState().getstate();   //n - 1, m + 1
      celulas_vivas += reticulo.getCell(Position(pos_x, pos_y - 1)).getState().getstate();       //n, m - 1
      celulas_vivas += reticulo.getCell(Position(pos_x, pos_y + 1)).getState().getstate();       //n, m + 1
      celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y - 1)).getState().getstate();    //n +1, m - 1
      celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y)).getState().getstate();        // n + 1, m
      celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y + 1)).getState().getstate();  // n+ 1, m + 1
    }
    else if (pos_x == 0 && pos_y == 0) {
      celulas_vivas += state_.getstate() * 3;
      celulas_vivas += reticulo.getCell(Position(0, pos_y + 1)).getState().getstate() * 2;
      celulas_vivas += reticulo.getCell(Position(1, pos_y)).getState().getstate() * 2;
      celulas_vivas += reticulo.getCell(Position(1, 1)).getState().getstate();
    }
    else if (pos_x == 0 && pos_y == n_colums - 1) {
      celulas_vivas += reticulo.getCell(Position(0, pos_y - 1)).getState().getstate() * 2;
      celulas_vivas += state_.getstate() * 3;
      celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y)).getState().getstate() * 2;
      celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y - 1)).getState().getstate();
    }
    else if (pos_x == n_filas - 1 && pos_y == 0) {
      celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y)).getState().getstate() * 2;
      celulas_vivas += state_.getstate() * 3;
      celulas_vivas += reticulo.getCell(Position(pos_x, pos_y + 1)).getState().getstate() * 2;
      celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y + 1)).getState().getstate();
    }
    else if (pos_x == n_filas - 1 && pos_y == n_colums - 1) {
      celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y)).getState().getstate() * 2;
      celulas_vivas += state_.getstate() * 3;
      celulas_vivas += reticulo.getCell(Position(pos_x, pos_y - 1)).getState().getstate() * 2;
      celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y - 1)).getState().getstate();
    }
    else if (pos_x == 0) {
      celulas_vivas += reticulo.getCell(Position(pos_x, pos_y - 1)).getState().getstate() * 2;
      celulas_vivas += state_.getstate();
      celulas_vivas += reticulo.getCell(Position(pos_x, pos_y + 1)).getState().getstate() * 2;
      celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y - 1)).getState().getstate();    //n +1, m - 1
      celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y)).getState().getstate();        // n + 1, m
      celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y + 1)).getState().getstate();  // n+ 1, m + 1
    }
    else if (pos_y == 0) {
      celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y + 1)).getState().getstate();
      celulas_vivas += reticulo.getCell(Position(pos_x, pos_y + 1)).getState().getstate();
      celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y + 1)).getState().getstate();
      celulas_vivas += reticulo.getCell(Position(pos_x -1, pos_y)).getState().getstate() * 2;
      celulas_vivas += state_.getstate();
      celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y)).getState().getstate() * 2;
    }
    else if (pos_x == n_filas - 1) {
      celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y - 1)).getState().getstate();   // n -1 ,m -1
      celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y)).getState().getstate();       //n -1 ,m
      celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y + 1)).getState().getstate();
      celulas_vivas += reticulo.getCell(Position(pos_x, pos_y - 1)).getState().getstate() * 2;
      celulas_vivas += state_.getstate();
      celulas_vivas += reticulo.getCell(Position(pos_x, pos_y + 1)).getState().getstate() * 2;
    }
    else {
      celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y)).getState().getstate() * 2;
      celulas_vivas += state_.getstate();
      celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y)).getState().getstate() * 2;
      celulas_vivas += reticulo.getCell(Position(pos_x - 1, pos_y - 1)).getState().getstate();
      celulas_vivas += reticulo.getCell(Position(pos_x, pos_y - 1)).getState().getstate();
      celulas_vivas += reticulo.getCell(Position(pos_x + 1, pos_y - 1)).getState().getstate();
    }
  }
  else {      // no border
    
  }
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