// Read : http://en.wikibooks.org/wiki/C%2B%2B_Programming/Operators/Operator_Overloading

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <limits>

using namespace std;

// ----------------------------------------------------------------------------
class complex {                                                                   
private:
  double re;                                                                    // representation: two doubles
  double im;

public:
  complex(double r, double i) :re {r}, im {i} {}                                // construct complex from two scalars
  complex(double r) :re {r}, im {0} {}                                          // construct complex from one scalar
  complex() :re {0}, im {0} {}                                                  // default complex: {0,0}
  
  double real() const { return re; }
  void real(double d) { re = d; }
  double imag() const { return im; }
  void imag(double d) { im = d; }
  
                                                                                // Operators are generally overloaded as members when they:
                                                                                //    1 - change the left-hand operand, or
                                                                                //    2 - require direct access to the non-public parts of an object.

                                                                                // When an operator is defined as a member, the number of explicit parameters 
                                                                                // is reduced by one, as the calling object is implicitly supplied as an operand
  
                                                                                // Compound assignment operators
                                                                                // Compound assignment operators should be overloaded as member functions, as 
                                                                                // they change the left-hand operand

  complex& operator+= (complex z) { re += z.re, im += z.im; return *this; }     // add to re and im and return the result
  complex& operator-= (complex z) { re -= z.re, im -= z.im; return *this; }
  complex& operator*= (complex rhs);                                            // defined out-of-class somewhere
  complex& operator/= (complex);                                                // defined out-of-class somewhere
};

                                                                                // Don't need access to private data and don't change the lhs so there are defined as non member functions
                                                                                // argument passed by value, so one can modify an argument without affecting the caller’s copy
complex operator+(complex a, complex b) { return a += b; }
complex operator-(complex a, complex b) { return a -= b; }
complex operator-(complex a) { return {-a.real(), -a.imag()}; }                 // unary minus
complex operator*(complex a, complex b) { return a *= b; }
complex operator/(complex a, complex b) { return a /= b; }

// ----------------------------------------------------------------------------
bool operator== (complex a, complex b){                                         // equal
  return a.real()==b.real() && a.imag()==b.imag();
}

// ----------------------------------------------------------------------------
bool operator!= (complex a, complex b){                                         // not equal
  return !(a==b);
}

// ----------------------------------------------------------------------------
complex& complex::operator*=(complex rhs) {

  double tmp_re = this->re * rhs.re - this->im * rhs.im;
  double tmp_im = this->re * rhs.im + this->im * rhs.re;
  
  this->re = tmp_re;
  this->im = tmp_im;
  return *this;
}

// ----------------------------------------------------------------------------
complex& complex::operator/=(complex rhs) {

  double tmp_re = this->re * rhs.re + this->im * rhs.im;
  double tmp_im = this->im * rhs.re - this->re * rhs.im;
  double tmp = rhs.re * rhs.re + rhs.im * rhs.im;

  this->re = tmp_re/tmp;
  this->im = tmp_im/tmp;

  return *this;
}

// ----------------------------------------------------------------------------
void Test(void) {

  complex a {1.4, 0.4};                                                         // set a breakpoint here and trace inside the code step by step
  complex b {1/a};
  complex c {0.8, 0.8};
  complex d = a/c;
  complex e {a+b*complex {1, 2.3}};
  
  if (c!=b)
    c = -(b/a)+2*b;
}

// ----------------------------------------------------------------------------
int main() {

#ifdef _MSC_VER
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _MSC_VER

  Test();

#ifdef _MSC_VER
  _CrtMemDumpAllObjectsSince(NULL);                                             // Begins the dump from the start of program execution
  _CrtDumpMemoryLeaks();
#endif // _MSC_VER

  cout<<"Press ENTER to quit : ";
  cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}
