#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <thread>

using namespace std;

// ----------------------------------------------------------------------------
void f(){                                                                       // function
  cout << "Hello ";                                                             // cout access is not protected!
}

// ----------------------------------------------------------------------------
struct F {                                                                      // function object
  void operator()(){ cout << "Parallel World!\n"; }                             // F’s call operator (§5.5). cout access is not protected!
};

// ----------------------------------------------------------------------------
void Test(void) {

  thread t1{ f };                                                               // f() executes in separate thread
  thread t2{ F() };                                                             // F()() executes in separate thread
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
