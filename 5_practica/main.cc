#include <iostream>

#include "sequence.h"
#include "sortMethod.h"

int main(int argc, char* argv[]) {
  int* secuencia = new int[10];
  secuencia[0] = 101;
  secuencia[1] = 100;
  secuencia[2] = 999;
  secuencia[3] = 286;
  secuencia[4] = 938;
  secuencia[5] = 639;
  secuencia[6] = 123;
  secuencia[7] = 456;
  secuencia[8] = 789;
  secuencia[9] = 321;
  staticSequence<int> sequence(10, secuencia);
  RadixSort<int> rs(sequence);
  rs.sort();
  std::cout << sequence << std::endl;
}