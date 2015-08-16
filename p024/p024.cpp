// p024.cpp

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <limits>
#include "Vector.h"

double sqrt_sum(Vector& v);

using namespace std;

// ----------------------------------------------------------------------------
int main() {

#ifdef _MSC_VER
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _MSC_VER


  Vector v(5);                                                                  // make a vector of 5 elements
  for (auto i = 0; i<5; ++i)
    v[i] = i;

  cout<<"Sum of the vector's square rooted components is : "<<sqrt_sum(v)<<endl;

#ifdef _MSC_VER
  _CrtMemDumpAllObjectsSince(NULL);                                             // Begins the dump from the start of program execution
  _CrtDumpMemoryLeaks();
#endif // _MSC_VER

  cout<<"Press ENTER to quit : ";
  cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}
