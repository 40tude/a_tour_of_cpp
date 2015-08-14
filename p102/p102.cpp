#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

// ----------------------------------------------------------------------------
map<string, int> phone_book{
  { "David Hume", 123456 },
  { "Karl Popper", 234567 },
  { "Bertrand Arthur William Russell", 345678 }
};

unordered_map<string, int> phone_bookU{
  { "David Hume", 123456 },
  { "Karl Popper", 234567 },
  { "Ber trand Ar thur William Russell", 345678 }
};

// ----------------------------------------------------------------------------
int get_number(const string& s){
  return phone_book[s];
}

// ----------------------------------------------------------------------------
int get_numberU(const string& s){
  return phone_bookU[s];
}
// ----------------------------------------------------------------------------
void Test(void) {

  if (auto Num = get_number("Karl Popper"))
    cout << "Karl Popper phone number is : " << Num << endl;
  else
    cout << "Karl Popper is NOT in the directory" << endl;

  if (auto Num = get_numberU("David Hume"))
    cout << "David Hume phone number is : " << Num << endl;
  else
    cout << "David Hume is NOT in the directory" << endl;
}

// ----------------------------------------------------------------------------
int main() {

  try{
#ifdef _MSC_VER
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _MSC_VER

    Test();

#ifdef _MSC_VER
    //_CrtMemDumpAllObjectsSince(NULL);                                             // Begins the dump from the start of program execution
    _CrtDumpMemoryLeaks();
#endif // _MSC_VER

    cout << "Press ENTER to quit : ";
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
  }
  catch (...) {
    cout << "Unknowns Exception Thrown" << endl;
  }
}
