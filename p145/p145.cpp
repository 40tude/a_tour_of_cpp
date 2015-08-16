#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <thread>
#include <mutex>  
#include <chrono>

using namespace std;

double  gMyDble = 0.0;
mutex   gMyMutex;                                                               // manage access to gMyDble

int     gMyInt1 = 0;
int     gMyInt2 = 100;
mutex   gMutex1;
mutex   gMutex2;

// ----------------------------------------------------------------------------
void f(){                                                                       // take input from v; place result in *res
  unique_lock<mutex> lck{ gMyMutex };                                           // acquire mutex
  gMyDble+=3;                                                                   // manipulate shared data
}                                                                               //release mutex implicitly

// ----------------------------------------------------------------------------
void g(){
  
  unique_lock<mutex> lck1{ gMutex1, defer_lock };                               // defer_lock: don’t yet try to acquire the mutex
  unique_lock<mutex> lck2{ gMutex2, defer_lock };

  lock(lck1, lck2);                                                             //acquire both locks
  gMyInt1++;
  gMyInt2--;
}                                                                               // implicitly release all mutexes

// ----------------------------------------------------------------------------
void Test(void) {

  thread t1{ f };        
  thread t2{ f };

  t1.join();
  t2.join();
  
  cout << "1 value has been manipulated (+3) by 2 threads. Its value is now : " << gMyDble << endl;

  thread t3{ g };
  thread t4{ g };

  t3.join();
  t4.join();

  cout << "2 values have been manipulated (+1 and -1) by 2 threads. Their values are : " << gMyInt1 << " " << gMyInt2 << endl;

  using namespace std::chrono;                                                  // see §11.4 p125
  auto time0 = high_resolution_clock::now();
  this_thread::sleep_for(milliseconds{ 20 });
  auto time1 = high_resolution_clock::now();
  cout << "Current thread was supposed to sleep for 20 ms" << endl;
  cout << duration_cast<nanoseconds>(time1 - time0).count() << " nanoseconds passed\n";
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
