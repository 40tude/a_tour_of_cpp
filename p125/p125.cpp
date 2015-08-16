#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <chrono>
#include <stdlib.h>

using namespace std;

// ----------------------------------------------------------------------------
void do_work(){
  for (auto i=0, j=0; i != 10000000; ++i)
    j++;
}

// ----------------------------------------------------------------------------
void Test(void) {
  using namespace std::chrono;                                                  // see §3.3 p26
  
  auto t0 = high_resolution_clock::now();
    do_work();
  auto t1 = high_resolution_clock::now();
  
  cout << duration_cast<milliseconds>(t1 - t0).count() << " msec\n";
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
