#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <thread>
#include <vector>
#include <functional>                                                           // ref()

using namespace std;

// ----------------------------------------------------------------------------
void f(vector<double>& v){}                                                      // function do something with v

// ----------------------------------------------------------------------------
struct F {                                                                      // function object: do something with v
  vector<double>& v;

  F(vector<double>& vv) :v{ vv } { }                                            // saves a reference to the argument vector
  void operator()(){};                                                          // application operator ; §5.5
};

// ----------------------------------------------------------------------------
void Test(void) {

  vector<double> some_vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  thread t1{ f, ref(some_vec) };                                                // thread variadic template constructor. 
                                                                                // ref() tell the variadic template to treat some_vec as a reference
                                                                                // f(some_vec) executes in a separate thread
  vector<double> vec2{ 10, 11, 12, 13, 14 };
  thread t2{ F{ vec2 } };                                                       // F(vec2)() executes in a separate thread
  
  t1.join();
  t2.join();
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
