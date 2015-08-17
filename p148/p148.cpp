#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <future>

using namespace std;

// ----------------------------------------------------------------------------
void Producer(promise<int>& px){                                                // a task: place the result in px

  try{                                                                          // ... compute a value for res ...
    int MyValue { 42 };
    px.set_value(MyValue);                                                      // put the value MyValue into the promise
  } catch (...) {                                                               // oops: couldn’t compute res
    px.set_exception(current_exception());                                      // pass the exception to the future’s thread. The current_exception() refers to the caught exception.
  }
}

// ----------------------------------------------------------------------------
void Consumer(future<int>& fx){                                                 // a task: get the result from fx

  try{
    int v = fx.get();                                                           // If the value isn’t there yet, the thread is blocked until it arrives
                                                                                // If the value couldn’t be computed, get() might throw an exception 
                                                                                // From the system or transmitted from the task from which we were trying to get() the value

                                                                                // ... use v ...
    cout << "In Consumer(), the value is : " << v << endl;
  } catch (...) {                                                               // oops: someone couldn’t compute v
    cout << "Exception in Consumer()" << endl;
  }
}

// ----------------------------------------------------------------------------
void Test(void) {

  promise<int>  myPromise;
  future<int>   myFuture = myPromise.get_future();

  thread t1{Producer, ref(myPromise)};
  thread t2{Consumer, ref(myFuture)};

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
