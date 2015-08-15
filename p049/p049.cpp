#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 

using namespace std;

// ----------------------------------------------------------------------------
class Vector {
private:
  double* elem;                                                                 // elem points to an array of sz doubles
  int sz;

public:
  Vector() : elem{ nullptr }, sz{ 0 } {}
  explicit Vector(int s) :elem{ new double[s] }, sz{ s } {                      // constructor: establish invariant, acquire resources
                                                                                // explicit => no implicit conversion from int to Vector. Avoid Vector v2 = 7; allow Vector v2(7);
                                                                                // advise : use explicit for constructors that take a single argument unless there is a good reason not to
    for (int i = 0; i != s; ++i) {												                      // initialize elements (see p 54)
      elem[i] = 0;
    }
  }

  ~Vector() { delete[] elem; }                                                  // destructor: release resources
  Vector(const Vector& a);                                                      // copy constructor
  Vector& operator=(const Vector& a);                                           // copy assignment
  Vector(Vector&& a);                                                           // move constructor
  Vector& operator=(Vector&& a);                                                // move assignment

  //const double& operator[](int i) const { return elem[i]; };                  // read only operator since returned value is const
  double& operator[](int i) const { return elem[i]; };
  int size() const {return sz;};
};

// ----------------------------------------------------------------------------
// copy constructor
Vector::Vector(const Vector& a) : elem{ new double[a.sz] }, sz{ a.sz } {          // allocate space for elements 

  for (int i = 0; i != sz; ++i)                                                   // copy elements
    elem[i] = a.elem[i];
}

// ----------------------------------------------------------------------------
// copy assignment
Vector& Vector::operator=(const Vector& a) {

  double* p = new double[a.sz];
  for (int i = 0; i != a.sz; ++i)
    p[i] = a.elem[i];
  delete[] elem;                                                                // delete old elements
  elem = p;
  sz = a.sz;
  return *this;
}

// ----------------------------------------------------------------------------
// A move constructor does not take a const argument
Vector::Vector(Vector&& a) : elem{ a.elem }, sz{ a.sz } {                       // "grab the elements" from a

  a.elem = nullptr;                                                             // now a has no elements
  a.sz = 0;
}

// ----------------------------------------------------------------------------
// move assignement
Vector& Vector::operator=(Vector&& a) {

  if (this != &a) {
    delete[] elem;
    sz = 0;
    elem = a.elem;
    sz = a.sz;
    a.elem = nullptr;                                                           // now a has no elements
    a.sz = 0;
  }
  return *this;
}

// ----------------------------------------------------------------------------
Vector operator+(const Vector& a, const Vector& b) {
  if (a.size() != b.size())
    throw out_of_range("operator+");                                            // throw Vector_size_mismatch {};
  
  Vector res(a.size());
  for (int i = 0; i != a.size(); ++i)
    res[i] = a[i] + b[i];
  return res;
}

// ----------------------------------------------------------------------------
void g(const Vector& x, const Vector& y, const Vector& z) {

  Vector r;
  // ...
  r = x + y + z;
  // ...
}

// ----------------------------------------------------------------------------
Vector f() {
  Vector x(1000);
  Vector y(1000);
  Vector z(1000);

  z = x;                                                                        // we get a copy
  y = std::move(x);                                                             // we get a move
  return z;                                                                     // we get a move
};

// ----------------------------------------------------------------------------
void Test(void) {

  Vector myV = f();

  Vector x(1000);
  Vector y(1000);
  Vector z(1000);
  g(x, y, z);

}

// ----------------------------------------------------------------------------
int main() {

#ifdef _MSC_VER
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _MSC_VER

  Test();

#ifdef _MSC_VER
  //_CrtMemDumpAllObjectsSince(NULL);                                             // Begins the dump from the start of program execution
  _CrtDumpMemoryLeaks();
#endif // _MSC_VER

  cout << "Press ENTER to quit : ";
  cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}
