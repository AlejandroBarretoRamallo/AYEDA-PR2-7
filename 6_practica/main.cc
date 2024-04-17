#include <iostream>

#include "arbolBinario.h"
#include "nodoBinario.h"

int main(int argc, char* argv[]) {
  nodoBinario<int> nodo(4);
  std::cout << nodo;
}