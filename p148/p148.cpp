#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <future>

using namespace std;

// ----------------------------------------------------------------------------
void f(promise<int>& px){                                                       // a task: place the result in px

  try{                                                                          // ... compute a value for res ...
    int res { 1024 };
    px.set_value(res);
  } catch (...) {                                                               // oops: couldn’t compute res
    px.set_exception(current_exception());                                      // pass the exception to the future’s thread. The current_exception() refers to the caught exception.
  }
}

// ----------------------------------------------------------------------------
void g(future<int>& fx){                                                        // a task: get the result from fx

  try{
    int v = fx.get();                                                           // if necessary, wait for the value to get computed
                                                                                // ... use v ...
    cout << "In g(), the future : " << v << endl;
  } catch (...) {                                                               // oops: someone couldn’t compute v
    cout << "Exception in g()" << endl;
  }
}

// ----------------------------------------------------------------------------
void Test(void) {

  promise<int>  myPromise;
  future<int>   myFuture = myPromise.get_future();

  thread t1{f, ref(myPromise)};
  thread t2{g, ref(myFuture)};

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
