#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <string>
#include <list>
#include <iostream> 

using namespace std;

// ----------------------------------------------------------------------------
template<typename T>
class Vector {
private:
  T*  elem;                                                                     // elem points to an array of sz elements of type T
  int sz;

public:
  explicit Vector(int s);                                                       // constructor: establish invariant, acquire resources
  ~Vector() { delete[] elem; }                                                  // destructor: release resources
  // ... copy and move operations ...
  T& operator[](int i) { return elem[i]; }
  const T& operator[](int i) const;                                             // read only operator since retruned value is const
  int size() const { return sz; }
};

// ----------------------------------------------------------------------------
template<typename T>
Vector<T>::Vector(int s){
  if (s<0)
    throw out_of_range{ "Vector constructor" };
  elem = new T[s];
  sz = s;
}

// ----------------------------------------------------------------------------
template<typename T>
const T& Vector<T>::operator[](int i) const
{
  if (i<0 || size() <= i)
    throw out_of_range{ "Vector::operator[]" };
  return elem[i];
}

// ----------------------------------------------------------------------------
template<typename T>
T* begin(Vector<T>& x){
  return x.size() ? &x[0] : nullptr;                                            // pointer to first element or nullptr
}

// ----------------------------------------------------------------------------
template<typename T>
T* end(Vector<T>& x){
  return begin(x) + x.size();                                                   // pointer to one-past-last element
}

// ----------------------------------------------------------------------------
void func(Vector<string>& vs){                                                  // Vector of some strings
  auto i = 0;
  for (auto& s : vs){
    cout << "String #" << i << " :" << s << '\n';
    i++;
  }
}

// ----------------------------------------------------------------------------
void Test(void) {

  Vector<char>      vc(200);                                                    // vector of 200 characters
  Vector<string>    vs(17);                                                     // vector of 17 strings
  Vector<list<int>> vli(45);                                                    // vector of 45 lists of integers

  Vector<string>    MyVec(3);
  func(MyVec);

  try{
    string bob = MyVec[100];
  } catch(...){
    cout << "Oh oh I just catched an exception." << endl;
  }
}

// ----------------------------------------------------------------------------
int main() {

#ifdef _MSC_VER
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _MSC_VER

  Test();

#ifdef _MSC_VER
  //_CrtMemDumpAllObjectsSince(NULL);                                           // Begins the dump from the start of program execution
  _CrtDumpMemoryLeaks();
#endif // _MSC_VER

  cout << "Press ENTER to quit : ";
  cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}
