#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <queue>
#include <condition_variable>
#include <mutex>
#include <thread>

using namespace std;
using namespace std::chrono;                                                    // see §11.4

bool gRun       = true;

struct Message {                                                                // object to be communicated
  int Index;
};

queue<Message>      gQueue;                                                     // the queue of messages
condition_variable  gCond;                                                      // the variable communicating events
mutex               gMutex;                                                     // the locking mechanism

// ----------------------------------------------------------------------------
void producer(){

  static int count = 0;

  while (gRun) {
    //this_thread::sleep_for(seconds{ 1 });                                     // may be used to generate a message every second

    Message m;
    m.Index = ++count;
    cout << "producing index : " << m.Index << endl;                            
    
    unique_lock<mutex> lock{ gMutex };                                          // protect operations
    gQueue.push(m);                                                             
    gCond.notify_one();                                                         // notify
  }                                                                             // release lock (at end of scope)
}

// ----------------------------------------------------------------------------
void consumer(){

  while (gRun) {
    unique_lock<mutex> lock{ gMutex };                                          // acquire gMutex
    gCond.wait(lock);                                                           // re-acquire lock upon wakeup
                                                                                
    while (!gQueue.empty()){                                                    // get one or more messages
      auto m = gQueue.front();                                                   
      cout << "consuming index : " << m.Index << endl;                          
      gQueue.pop();                                                             // Removes an element from the front of the queue
    }
    lock.unlock();                                                              // release lock
  }
}

// ----------------------------------------------------------------------------
void Test(void) {

  thread t1{ producer };
  thread t2{ consumer };
  
  this_thread::sleep_for(seconds{ 10 });
  cout << "Test finished to wait" << endl;
  gRun = false;

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
