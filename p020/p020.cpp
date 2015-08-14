#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <limits>

using namespace std;

enum class Traffic_light { green, yellow, red };

// ----------------------------------------------------------------------------
Traffic_light& operator++(Traffic_light& t){                                    // prefix increment: ++

  switch (t) {
    case Traffic_light::green:  return t = Traffic_light::yellow;
    case Traffic_light::yellow: return t = Traffic_light::red;
    case Traffic_light::red:    return t = Traffic_light::green;
  }
}

// ----------------------------------------------------------------------------
void Test(void){
  
  enum class Color { red, blue, green };

  Color col = Color::red;
  Traffic_light light = Traffic_light::red;

  Traffic_light next = ++light;                                                 // next becomes Traffic_light::green
}

// ----------------------------------------------------------------------------
int main(){

#ifdef _MSC_VER
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _MSC_VER

  Test();

#ifdef _MSC_VER
  //_CrtMemDumpAllObjectsSince(NULL);                                           // Begins the dump from the start of program execution
  _CrtDumpMemoryLeaks();
#endif // _MSC_VER

  cout << "Press ENTER to quit : ";
  cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}