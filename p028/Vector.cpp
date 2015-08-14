// Vector.cpp

#include "Vector.h"                                                             // get Vector’s the interface
#include <stdexcept>

// ----------------------------------------------------------------------------
Vector::Vector(int s) : elem {new double[s]}, sz {s} {                          // initialize members
}

// ----------------------------------------------------------------------------
double& Vector::operator[](int i) {
  if (i < 0 || size() <= i) throw std::out_of_range("Vector::operator[]");
  return elem[i];
}

// ----------------------------------------------------------------------------
int Vector::size() {
  return sz;
}