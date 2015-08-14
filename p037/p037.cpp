#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define _SCL_SECURE_NO_WARNINGS                                                 // Avoid error with copy(...) in the initializer list ctor
#endif // _MSC_VER

#include <algorithm>
#include <iostream> 
#include <limits>

using namespace std;

// ----------------------------------------------------------------------------
class Vector {
private:
  double  *elem;                                                                // elem points to an array of sz doubles
  int     sz;

public:
  Vector() : elem {nullptr}, sz {0} {}                                          // default constructor

  Vector(int s) :elem {new double[s]}, sz {s} {                                 // constructor: acquire resources
    for (int i = 0; i!=s; ++i) {                                                // initialize elements
      elem[i] = 0;
    }
  }

  Vector(Vector& v) :elem {new double[v.sz]}, sz {v.sz} {                       // copy constructor. Used in function read()
    for (int i = 0; i!=sz; ++i) {                                               // initialize elements
      elem[i] = v.elem[i];
    }
  }

  Vector(std::initializer_list<double>);                                        // initialize with a list of doubles
  void push_back(double);                                                       // add element at end, increasing the size by one

  ~Vector() { delete[] elem; sz = 0; }                                          // destructor: release resources
  
  double& operator[](int i) const { return elem[i]; };
  
  int size() const {return sz;};
};

// ----------------------------------------------------------------------------
                                                                                // initialize with a list
Vector::Vector(std::initializer_list<double> lst) :elem {new double[lst.size()]}, sz {static_cast<int>(lst.size())} {

  copy(lst.begin(), lst.end(), elem);                                           // copy from lst into elem (§10.6)
}

// ----------------------------------------------------------------------------
void Vector::push_back(double a) {
  
  if (elem==nullptr) {
    elem = new double[1];
    elem[0] = a;
    sz=1;
  } else {
    double *tmp = new double[sz+1];
    for (int i = 0; i!=sz; ++i) {                                                // initialize elements
      tmp[i] = elem[i];
    }
    tmp[sz] = a;
    delete[] elem;
    elem = tmp;
    sz++;
  }
}

// ----------------------------------------------------------------------------
void fct(int n) {

  Vector v(n);
  
  // ... use v ...
  
  {
    Vector v2(2*n);
    // ... use v and v2 ...
  }                                                                             // v2 is destroyed here
  
  // ... use v ..
}                                                                               // v is destroyed here

// ----------------------------------------------------------------------------
Vector read(istream& is) {
  
  Vector v;
  
  for (double d; is>>d;)                                                        // read floating-point values into d
    v.push_back(d);                                                             // add d to v
  
  cin.clear();
  return v;                                                                     // Make a copy using copy constructor, delete v then return
}

// ----------------------------------------------------------------------------
void Test(void) {
  
  Vector v1 = {1, 2, 3, 4, 5};                                                  // v1 has 5 elements
  Vector v2 = {1.23, 3.45, 6.7, 8};                                             // v2 has 4 elements

  fct(1024);
  
  cout << "Enter double values separated with SPACE. Finish the line with CTRL+Z : ";
  Vector v = read(cin);

  for (int i=0; i != v.size(); ++i)
    cout << v[i] << endl;
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
  
  cout<<"Press ENTER to quit : ";
  cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}
