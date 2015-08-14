// On Win : cl /EHsc /nologo /W4 /MT /O2 /GL pXXX.cpp
// On Mac : clang++ -Wall -std=c++0x -stdlib=libc++ pXXX.cpp -o pXXX.cpp

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif  // _MSC_VER

#include <iostream> 
#include <limits>
#include <stdexecpt>

using namespace std;

// ----------------------------------------------------------------------------
void Test(void) {

}

// ----------------------------------------------------------------------------
int main() {

  try{                                                                          // try-catch show one way to intercept exception if any
#ifdef _MSC_VER
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _MSC_VER

    Test();

#ifdef _MSC_VER
    // _CrtMemDumpAllObjectsSince(NULL);                                        // Begins the dump from the start of program execution
    _CrtDumpMemoryLeaks();
#endif // _MSC_VER

    cout << "Press ENTER to quit : ";
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');                      // wait for a new line

  } catch (out_of_range){                                                       // Shows how to catch one exception
    cout << "Range Error somewhere..." << endl;
  } catch (...){
    cout << "Unknowns Exception Thrown" << endl;
  }
}
