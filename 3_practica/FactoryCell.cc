#include "FactoryCell.h"

Cell* FactoryCellACE110::createCell(Position* position, const State& state) const{
  return new CellACE110(position, state);
}

Cell* FactoryCellACE30::createCell(Position* position, const State& state) const{
  return new CellACE30(position, state);
}

Cell* FactoryCellLife23_3::createCell(Position* position, const State& state) const{
  return new CellLife23_3(position, state);
}

Cell* FactoryCellLife51_346::createCell(Position* position, const State& state) const{
  return new CellLife51_346(position, state);
}