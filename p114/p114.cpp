#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// ----------------------------------------------------------------------------
struct Greater_than {
  
  int val;
  
  Greater_than(int v) : val{ v } { }
  bool operator()(const pair<string, int>& r) { return r.second>val; }
};

// ----------------------------------------------------------------------------
void f(map<string, int>& m){

  auto p = find_if(m.begin(), m.end(), Greater_than{ 40 });
  cout << p->first << " : " << p->second << endl;
  // ...
}

// ----------------------------------------------------------------------------
void g(map<string, int>& m){                                                    // use a lambda
  
  auto p = find_if(m.begin(), m.end(), [](const pair<string, int>& r) { return r.second>20; });     
  cout << p->first << " : " << p->second << endl;
  // ...
}

// ----------------------------------------------------------------------------
void Test(void) {
 
  map<string, int> MyValues{ { "riri", 10 }, { "fifi", 30 }, { "loulou", 50 }, };
  
  f(MyValues);
  g(MyValues);
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