#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <cmath>
#include <numeric>
#include <list>

using namespace std;

// ----------------------------------------------------------------------------
void Test(void) {
  errno = 0;                                                                    // clear old error state
  
  sqrt(-1);
  if (errno == EDOM)
    cerr << "sqrt() not defined for negative argument" << endl;;
  
  errno = 0;                                                                    // clear old error state
  pow(numeric_limits<double>::max(), 2);
  if (errno == ERANGE)
    cerr << "result of pow() too large to represent as a double" << endl;

  list<double> lst{ 1, 2, 3, 4, 5, 9999.99999 };
  auto s = accumulate(lst.begin(), lst.end(), 0.0);                             // calculate the sum
  cout.precision(10);                                                           // otherwise print 10015
  cout << s << '\n';                                                            // print 10014.9999
}

// ----------------------------------------------------------------------------
int main() {

  try{
#ifdef _MSC_VER
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _MSC_VER

    Test();

#ifdef _MSC_VER
    //_CrtMemDumpAllObjectsSince(NULL);                                         // Begins the dump since the start of program execution
    _CrtDumpMemoryLeaks();
#endif // _MSC_VER

    cout << "Press ENTER to quit : ";
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
  }
  catch (...) {
    cout << "Unknowns Exception Thrown" << endl;
  }
}
