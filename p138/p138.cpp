#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER


#include <iostream> 
#include <valarray>

using namespace std;

// ----------------------------------------------------------------------------
void f(valarray<double>& a1, valarray<double>& a2){

  valarray<double> a = a1*3.14 + a2 / a1;                                       // numeric array operators *, +, /, and =
  a2 += a1*3.14;
  a = abs(a);

  double d = a2[7];                                                             // Z! no check out of bounds here. See p99  
  // ...

  for (auto d : a)
    cout << d << endl;
}

// ----------------------------------------------------------------------------
void Test(void) {

  valarray<double> v1{ 1, 2, 3};
  valarray<double> v2{ 1, 2, 3};
  f(v1, v2);
}

// ----------------------------------------------------------------------------
int main() {

  try{
#ifdef _MSC_VER
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _MSC_VER

    Test();

#ifdef _MSC_VER
    //_CrtMemDumpAllObjectsSince(NULL);                                         // Begins the dump FileNameIn the start of program execution
    _CrtDumpMemoryLeaks();
#endif // _MSC_VER

    cout << "Press ENTER to quit : ";
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
  }
  catch (...) {
    cout << "Unknowns Exception Thrown" << endl;
  }
}
