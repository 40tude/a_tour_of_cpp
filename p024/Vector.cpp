// Vector.cpp

#include "Vector.h"                                                             // get Vector’s the interface

// ----------------------------------------------------------------------------
Vector::Vector(int s) : elem {new double[s]}, sz {s}                            // initialize members
{
}

// ----------------------------------------------------------------------------
double& Vector::operator[](int i) {
  return elem[i];
}

// ----------------------------------------------------------------------------
int Vector::size() {
  return sz;
}