
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

bool gRun = true;

struct Message {                                                                // object to be communicated
  int Index;
};

queue<Message>      gQueue;                                                     // the queue of messages
condition_variable  gCond;                                                      // the variable communicating events
mutex               gLockQueue;                                                 // the locking mechanism
mutex               gLockPrint;
bool                gNotified;

// ----------------------------------------------------------------------------
void producer() {

  static int count = 0;

  while (gRun) {
    Message m;
    m.Index = ++count;
    {
      unique_lock<mutex> locker(gLockPrint);
      cout << "producer() - " << m.Index << endl;
    }

    unique_lock<mutex> lock{ gLockQueue };                                      // protect operations
    
    gQueue.push(m);
    gNotified = true;
    gCond.notify_one();                                                         // notify
  }                                                                             // release lock (at end of scope)
}

// ----------------------------------------------------------------------------
void consumer() {

  while (gRun) {
    unique_lock<mutex> lock{ gLockQueue };                                      // acquire gLockQueue
    
    while (!gNotified) {                                                        // used to avoid spurious wakeups 
      gCond.wait(lock);                                                         // suspends the thread until the condition variable is signaled. When that happens the thread is awaken and the lock is re-acquired.
    }

    while (!gQueue.empty()) {                                                    // get one or more messages
      auto m = gQueue.front();
      gQueue.pop();                                                             // Removes an element from the front of the queue
      {
        unique_lock<mutex> locker(gLockPrint);
        cout << "consumer() - " << m.Index << endl;
      }
      
    }
    //lock.unlock();                                                              // release lock
    gNotified = false;
  }
  
}

// ----------------------------------------------------------------------------
void Test(void) {

  thread t1{ producer };
  thread t2{ consumer };

  this_thread::sleep_for(seconds{1});
  {
    unique_lock<mutex> locker(gLockPrint);
    cout << "\nTest() function waking up\n" << endl;
  }
  gRun = false;

  t1.join();                                                                    // wait threads completion  
  t2.join();

  cout << "\n";                                                                 // display values which may be still in the queue
  while (!gQueue.empty()) {                                                    
    auto m = gQueue.front();
    gQueue.pop();
    cout << m.Index << " remains in the queue." << endl;
  }
  cout << "\n";
}

// ----------------------------------------------------------------------------
int main() {

  try {
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


/*
// Works with no memory leak

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <condition_variable>
#include <mutex>
#include <thread>

using namespace std;
using namespace std::chrono;                                                    // see §11.4

struct Message {                                                                // object to be communicated
  int Index;
};

condition_variable  gCond;                                                      // the variable communicating events
mutex               gLockQueue;                                                     // the locking mechanism
Message             gMessage;
bool                gRun = true;

// ----------------------------------------------------------------------------
void producer() {

  static int count = 0;

  while (gRun) {
    unique_lock<mutex> lock{ gLockQueue };                                          // protect operations
    gMessage.Index = ++count;
    cout << "producer() - " << gMessage.Index << endl;
    gCond.notify_one();                                                         // notify
  }                                                                             // release lock (at end of scope)
}

// ----------------------------------------------------------------------------
void consumer() {

  while (gRun) {
    unique_lock<mutex> lock{ gLockQueue };                                          // acquire gLockQueue
    gCond.wait(lock);

    cout << "consumer() - " << gMessage.Index << endl;
    lock.unlock();                                                              // release lock
  }
}

// ----------------------------------------------------------------------------
void Test(void) {

  
  thread t2{ consumer };
  thread t1{ producer };


  this_thread::sleep_for(seconds{2});
  cout << "\nTest() function waking up\n" << endl;
  gRun = false;

  t1.join();
  t2.join();
}

// ----------------------------------------------------------------------------
int main() {

  try {
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
*/


/*
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <queue>
#include <random>

std::mutex              g_lockprint;
std::mutex              g_lockqueue;
std::condition_variable g_queuecheck;
std::queue<int>         g_codes;
bool                    g_done;
bool                    g_notified;

void workerfunc(int id, std::mt19937& generator)
{
// print a starting message
{
std::unique_lock<std::mutex> locker(g_lockprint);
std::cout << "[worker " << id << "]\trunning..." << std::endl;
}

// simulate work
std::this_thread::sleep_for(std::chrono::seconds(1 + generator() % 5));

// simulate error
int errorcode = id * 100 + 1;
{
std::unique_lock<std::mutex> locker(g_lockprint);
std::cout << "[worker " << id << "]\tan error occurred: " << errorcode << std::endl;
}

// notify error to be logged
{
std::unique_lock<std::mutex> locker(g_lockqueue);
g_codes.push(errorcode);
g_notified = true;
g_queuecheck.notify_one();
}
}

void loggerfunc()
{
// print a starting message
{
std::unique_lock<std::mutex> locker(g_lockprint);
std::cout << "[logger]\trunning..." << std::endl;
}

// loop until end is signaled
while (!g_done)
{
std::unique_lock<std::mutex> locker(g_lockqueue);

while (!g_notified) // used to avoid spurious wakeups
{
g_queuecheck.wait(locker);
}

// if there are error codes in the queue process them
while (!g_codes.empty())
{
std::unique_lock<std::mutex> locker(g_lockprint);
std::cout << "[logger]\tprocessing error:  " << g_codes.front() << std::endl;
g_codes.pop();
}

g_notified = false;
}
}

int main()
{

#ifdef _MSC_VER
_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _MSC_VER



// initialize a random generator
std::mt19937 generator((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());

// start the logger
std::thread loggerthread(loggerfunc);

// start the working threads
std::vector<std::thread> threads;
for (int i = 0; i < 5; ++i)
{
threads.push_back(std::thread(workerfunc, i + 1, std::ref(generator)));
}

// work for the workers to finish
for (auto& t : threads)
t.join();

// notify the logger to finish and wait for it
g_done = true;
loggerthread.join();

#ifdef _MSC_VER
//_CrtMemDumpAllObjectsSince(NULL);                                         // Begins the dump FileNameIn the start of program execution
_CrtDumpMemoryLeaks();
#endif // _MSC_VER

return 0;
}
*/
