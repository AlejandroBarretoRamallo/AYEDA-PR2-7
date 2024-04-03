#ifndef SORTMETHOD_H
#define SORTMETHOD_H

#include "sequence.h"
#include <algorithm>

template<class key>
class SortMethod {
  public:
    virtual void sort()  = 0;
    SortMethod( staticSequence<key>& sequence) : sequence_(sequence) {};
    friend std::ostream& operator<<(std::ostream& os, const SortMethod<key>& sortMethod) {
      os << sortMethod.sequence_;
      return os;
    };
  protected:
     staticSequence<key>& sequence_;
};

template<class key>
class Seleccion : public SortMethod<key> {
  public:
    void sort();
    void trace_sort();
    Seleccion( staticSequence<key>& sequence): SortMethod<key>(sequence) {};
};

template <class key>
class QuickSort : public SortMethod<key> {
  public:
    void sort();
    void trace_sort();
    void qSort(unsigned ini, unsigned fin);
    void trace_qSort(unsigned ini, unsigned fin);
    QuickSort( staticSequence<key>& sequence) : SortMethod<key>(sequence) {};
};

template <class key>
class HeapSort: public SortMethod<key> {
  public:
    void sort();
    void trace_sort();
    HeapSort( staticSequence<key>& sequence) : SortMethod<key>(sequence) {};
    void baja(int, int) ;
};

template <class key>
class ShellSort: public SortMethod<key> {
  public:
    void sort();
    void trace_sort();
    void deltaSort(int, int) ;
    ShellSort( staticSequence<key>& sequence): SortMethod<key>(sequence) {};
};

template <class key>
class RadixSort: public SortMethod<key> {
  public:
    void sort();
    void trace_sort();
    RadixSort( staticSequence<key>& sequence): SortMethod<key>(sequence) {};
};

template<class key> 
void Seleccion<key>::sort() {
  unsigned n = this -> sequence_.getSize();
  for (int i = 0; i < n - 1; i++) {
    int min = i ;
    for (int j = i + 1; j < n; j++) {
      if (this -> sequence_[j] < this -> sequence_[min]) {
        min = j;
      }
    }
    if (min != i) {
      std::swap(this -> sequence_[i], this -> sequence_[min]);
    }
  }
}

template<class key> 
void Seleccion<key>::trace_sort() {
  std::cout << this->sequence_ << std::endl;
  unsigned n = this -> sequence_.getSize();
  for (int i = 0; i < n - 1; i++) {
    int min = i ;
    for (int j = i + 1; j < n; j++) {
      if (this -> sequence_[j] < this -> sequence_[min]) {
        min = j;
      }
    }
    if (min != i) {
      std::swap(this -> sequence_[i], this -> sequence_[min]);
      std::cout << this->sequence_ << std::endl;
    }
  }
}

template<class key> 
void QuickSort<key>::sort()  {
  unsigned ini = 0, fin = this ->sequence_.getSize();
  qSort(ini, fin - 1);
}

template<class key>
void QuickSort<key>::trace_sort() {
  std::cout << this->sequence_ << std::endl;
  unsigned ini = 0, fin = this ->sequence_.getSize();
  trace_qSort(ini, fin - 1);
  std::cout << this->sequence_ << std::endl;
}

template <class key>
void QuickSort<key>::qSort(unsigned ini, unsigned fin) {
  unsigned i = ini, f = fin ;
  unsigned p = this -> sequence_[(i+f)/2] ;
  while (i <= f) {
    while (unsigned(this -> sequence_[i]) < p) {
      i++;
    }
    while (unsigned(this -> sequence_[f]) > p) {
      f--;
    }
    if (i <= f) {
      std::swap(this -> sequence_[i],this -> sequence_[f]);
      i++; 
      f--;
    }
  }
  if (ini < f) {
    qSort(ini, f); 
  } 
  if (i < fin) {
    qSort(i, fin); 
  } 
}

template <class key>
void QuickSort<key>::trace_qSort(unsigned ini, unsigned fin) {
  unsigned i = ini, f = fin ;
  unsigned p = this -> sequence_[(i+f)/2] ;
  while (i <= f) {
    while (unsigned(this -> sequence_[i]) < p) {
      i++;
    }
    while (unsigned(this -> sequence_[f]) > p) {
      f--;
    }
    if (i <= f) {
      std::swap(this -> sequence_[i],this -> sequence_[f]);
      std::cout << this->sequence_ << std::endl;
      i++; 
      f--;
    }
  }
  if (ini < f) {
    qSort(ini, f); 
  } 
  if (i < fin) {
    qSort(i, fin); 
  } 
}


template <class key>
void HeapSort<key>::baja(int i, int n) {
  while (2 * i + 1 < n) { 
    int h = 2 * i + 1; 
    int h2 = 2 * i + 2; 
    if (h2 < n && this->sequence_[h] < this->sequence_[h2]) { 
      h = h2;
    }
    if (this->sequence_[i] >= this->sequence_[h]) { 
      break; 
    }
    std::swap(this->sequence_[i], this->sequence_[h]); 
    i = h; 
  }
}

template <class key>
void HeapSort<key>::sort() {
  unsigned n = this->sequence_.getSize();
  for (int i = n / 2 - 1; i >= 0; i--) {
    baja(i, n);
  }
  for (int i = n - 1; i > 0; i--) {
    std::swap(this->sequence_[0], this->sequence_[i]);
    baja(0, i);
  }
}

template <class key>
void ShellSort<key>::deltaSort(int delta, int n) {
  for (int i = delta; i < n; i++) {
    unsigned x = this->sequence_[i];
    unsigned j = i ;
    while ((j >= delta) && (x < this ->sequence_[j - delta])) {
      this->sequence_[j] = this ->sequence_[j - delta];
      j = j - delta;
    }
    this->sequence_[j] = x;
  }
}

template<class key> 
void ShellSort<key>::sort()  {
  int delta = this -> sequence_.getSize();
  unsigned size = delta;
  while (delta > 1) {
   delta = delta / 2 ;
   deltaSort(delta, size);
  }
}

template<class key> 
void RadixSort<key>::sort()  {
  std::vector<std::vector<key>> buckets(10);
  unsigned numOfDigits = 0;
  int num = this -> sequence_[0];
  while (num > 0) {
    num = num / 10;
    numOfDigits++;
  }
  for (int i = 0; i < numOfDigits; i++) {
    for (int j = 0; j < this -> sequence_.getSize(); j++) {
      num = this -> sequence_[j];
      int digito = 0;
      for (int k = 0; k < i + 1; k++) {
        digito = num % 10;
        num /= 10;
      }
      buckets[digito].push_back(this -> sequence_[j]);
    }
    int position = 0;
    for (int j = 0; j < 10; ++j) {
      for (int k = 0; k < buckets[j].size(); ++k) {
        key valor = buckets[j][k];
        this -> sequence_[position] = valor;
        ++position;
      }
    }
    for (int j = 0; j < 10; ++j) {
      buckets[j].clear();
    }
  }
}

#endif