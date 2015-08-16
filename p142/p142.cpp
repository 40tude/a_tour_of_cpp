#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <thread>

using namespace std;

// ----------------------------------------------------------------------------
void f(){                                                                       // A task can be a function
  cout << "Hello ";                                                             // Error! Access to cout object is not synchronized!
}

// ----------------------------------------------------------------------------
struct F {                                                                      // A task can be a function object
  void operator()(){ cout << "Parallel World!\n"; }                             // F’s call operator (see §5.5 p64). Please note access to cout object is not synchronized
};

// ----------------------------------------------------------------------------
void Test(void) {

  thread t1{ f };                                                               // The task f() is launched by constructing a thread with the task as argument
  thread t2{ F() };                                                             // The task f() executes in one thread and the task F() in an other thread
  t1.join();                                                                    // wait for t1
  t2.join();                                                                    // wait for t2
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
