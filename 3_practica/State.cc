

#include "State.h"

State::State(int state) {
  state_ = state;
}

State::State() {
  state_ = 0;
}

void State::setState(int state) {
  state_ = state;
}
