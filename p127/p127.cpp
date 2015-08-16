#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

// ----------------------------------------------------------------------------
int Myround(double x) {                                                         // conventional 4/5 rounding
  return static_cast<int>(floor(x + 0.5));
}

// ----------------------------------------------------------------------------
function<int(double)> f;                                                        // f can hold anything that can be called with a double and return an int

enum class Round_style { truncate, round };

struct Round {                                                                  // function object carrying a state
  Round_style s;
  Round(Round_style ss) :s(ss) { }
  int operator()(double x) const { return static_cast<int>((s == Round_style::round) ? (x + 0.5) : x); };
};

// ----------------------------------------------------------------------------
void Test(void) {

  function<int(double)> f;                                                      // f is a function object. See §5.5 p64
  
  f = Myround;                                                                  // Initially Myround was named round. Did not compile under MSVC. Now I use Myround
  cout << f(7.6) << '\n';                                                       // call through f to the function Myround
  
  f = Round(Round_style::truncate);
  cout << f(7.6) << '\n';                                                       // call the function object
  Round_style style = Round_style::round;
  
  f = [style](double x){ return static_cast<int>((style == Round_style::round) ? x + 0.5 : x); };
  cout << f(7.6) << '\n';                                                       // call the lambda
  
  vector<double> v{ 7.6 };
  f = Round(Round_style::round);
  transform(v.begin(), v.end(), v.begin(), f);                                  // pass to algorithm
  cout << v[0] << '\n';                                                         // transformed by the lambda
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
