#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <thread>
#include <vector>
#include <functional>                                                           // cref()
#include <numeric>                                                              //accumulate

using namespace std;

// ----------------------------------------------------------------------------
void f(const vector<double>& v, double* res){                                   // take input from v; place result in *res
  *res = accumulate(v.begin(), v.end(), 0);
}

// ----------------------------------------------------------------------------
class F {
public:
  F(const vector<double>& vv, double* p) :v{ vv }, res{ p } { }
  void operator()(){                                                            // place result in *res
    *res = accumulate(v.begin(), v.end(), 0);
  }
private:
  const vector<double>& v;                                                      // source of input
  double*res;                                                                   //target for output
};

// ----------------------------------------------------------------------------
void Test(void) {

  vector<double> some_vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  vector<double> vec2{ 10, 20, 30, 40, 50, 60, 70, 80, 90 };
  // ...
  double res1;
  double res2;
  thread t1{ f, cref(some_vec), &res1 };                                        // cref onstructs a const reference_wrapper from an argument.
  thread t2{ F{ vec2, &res2 } };                                                // 
  t1.join();
  t2.join();
  cout << res1 << ' ' << res2 << '\n';
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
