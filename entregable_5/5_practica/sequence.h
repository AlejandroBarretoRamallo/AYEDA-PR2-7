#ifndef SEQUENCE_H
#define SEQUENCE_H

template <class key>
class Sequence {
  public:
    virtual key operator[](const int&) const = 0;
    Sequence() {};
};

template <class key>
class staticSequence {
  public:
    key& operator[](const int& i) const {
      if (i < 0 || i >= size_) {
        throw "Index out of bounds";
      }
      return secuencia_[i];
    };
    staticSequence(unsigned size, key* secuencia): size_(size), secuencia_(secuencia) {};
    unsigned getSize()const {return size_;};
    friend std::ostream& operator<<(std::ostream& os, const staticSequence<key>& sequence) {
      for (int i = 0; i < sequence.size_; i++) {
        os << sequence[i] << " ";
      }
      return os;
    };
  private:
    key* secuencia_;
    unsigned size_;
};

#endif