#ifndef STATE_H
#define STATE_H

#include <iostream>

class State {
  public:
    int getstate() const { return state_;};
    State(int state);
    State();
    void setState(int);
  private:
    int state_;
};

#endif