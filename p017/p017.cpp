#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <limits>
#include <vector>

using namespace std;

class Vector {
private:
  double  *elem;                                                                // pointer to the elements
  int     sz;                                                                   // the number of elements

public:
  Vector(int s) : elem {new double[s]}, sz {s} {}                               // construct a Vector
  double& operator[](int i) { return elem[i]; }                                 // element access: subscripting
  int size() { return sz; }
};

// ----------------------------------------------------------------------------
double read_and_sum(int s) {
  Vector v(s);                                                                  // make a vector of s elements

  cout << "Enter " << s << " integers separated with spaces : ";
  for (int i = 0; i!=v.size(); ++i)
    cin>>v[i];                                                                  // read into elements

  double sum = 0;
  for (int i = 0; i!=v.size(); ++i)
    sum += v[i];                                                                // take the sum of the elements
  return sum;
}

// ----------------------------------------------------------------------------
int main() {

#ifdef _MSC_VER
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
#endif // _MSC_VER

  cout<<"Sum of 3 is : "<<read_and_sum(3)<<endl;
  cin.sync();

#ifdef _MSC_VER
  //_CrtMemDumpAllObjectsSince(NULL);                                             // Begins the dump from the start of program execution
  _CrtDumpMemoryLeaks();
#endif // _MSC_VER

  cout<<"Press ENTER to quit : ";
  cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}
