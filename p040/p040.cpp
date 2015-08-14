#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define _SCL_SECURE_NO_WARNINGS                                                 // Avoid error with copy(...) in the initializer list ctor
#endif // _MSC_VER

#include <algorithm>
#include <vector>
#include <list>
#include <iostream> 

using namespace std;

// ----------------------------------------------------------------------------
class Container {
public:
  virtual double& operator[](int) = 0;                                          // pure virtual function
  virtual int size() const = 0;                                                 // const member function (§4.2.1)
  virtual ~Container() {}                                                       // destructor (§4.2.2)
};

// ----------------------------------------------------------------------------
class Vector {
private:
  double  *elem;                                                                // elem points to an array of sz doubles
  int     sz;

public:
  Vector(std::initializer_list<double>);                                        // initialize with a list of doubles
  ~Vector() { delete[] elem; sz = 0; }                                          // destructor: release resources
  double& operator[](int i) const { return elem[i]; };
  int size() const {return sz;};
};

// ----------------------------------------------------------------------------
// Initialize Vector with a list
Vector::Vector(std::initializer_list<double> lst) :elem {new double[lst.size()]}, sz {static_cast<int>(lst.size())} {

  copy(lst.begin(), lst.end(), elem);                                           // copy from lst into elem (§10.6)
}

// ----------------------------------------------------------------------------
class Vector_container: public Container {                                      // Vector_container implements Container
private :
  Vector v;

public:
  Vector_container(std::initializer_list<double>);                              // initialize with a list of doubles
  ~Vector_container() {}
  double& operator[](int i) { return v[i]; }
  int size() const { return v.size(); }
};

// ----------------------------------------------------------------------------
// initialize with a list
//Vector_container::Vector_container(initializer_list<double> lst) : v {lst}{   // No way to use list initialization inside member initializer list
Vector_container::Vector_container(initializer_list<double> lst) :v(lst) {}     // v Default constructor must be defined

// ----------------------------------------------------------------------------
class List_container: public Container {                                        // List_container implements Container
private:
  list<double> ld;                                                              // (standard-library) list of doubles (§9.3)

public:
  List_container(initializer_list<double> il)  {
    ld = {il};
  }

  ~List_container() {}
  double& operator[](int i);
  int size() const { return ld.size(); }
};

// ----------------------------------------------------------------------------
double& List_container::operator[](int i) {
  
  for (auto& x:ld) {
    if (i==0) return x;
    --i;
  }
  throw out_of_range("List container");
}

// ----------------------------------------------------------------------------
void use(Container& c) {
  const int sz = c.size();
  for (int i = 0; i!=sz; ++i)
    cout<<c[i]<<'\n';
}

// ----------------------------------------------------------------------------
void Test(void) {
  
  Vector_container vc {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  cout<<"Content of Vector_Container"<<endl;
  use(vc);

  List_container lc = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  cout<<"Content of List_Container"<<endl;
  use(lc);
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
