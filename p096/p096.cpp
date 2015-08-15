#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <vector>
#include <iostream> 
#include <string>

using namespace std;

// ----------------------------------------------------------------------------
struct Entry {
  string name;
  int number;
};

// ----------------------------------------------------------------------------
struct Shape {
  int x;
  int y;
  int z;
};

// ----------------------------------------------------------------------------
ostream& operator<<(ostream& os, const Entry& e){

  return os << "{\"" << e.name << "\", " << e.number << "}";
}

// ----------------------------------------------------------------------------
void print_book(const vector<Entry>& book){
                                                                                // auto x         : when you want to work with copies.
                                                                                // auto &x        : when you want to work with original items and may modify them.
  for (const auto& x : book) cout << x << '\n';                                 // auto const &x  : when you want to work with original items and will not modify them.
}

// ----------------------------------------------------------------------------
void Test(void) {

  vector<Entry> phone_book = {
      { "David Hume", 123456 },
      { "Karl Popper", 234567 },
      { "Bertrand Arthur William Russell", 345678 }
  };

  print_book(phone_book);

  vector<int> v1 = { 1, 2, 3, 4 };                                              // size is 4
  vector<string> v2;                                                            // size is 0
  vector<Shape*> v3(23);                                                        // size is 23; initial element value: nullptr
  vector<double> v4(32, 9.9);                                                   // size is 32; initial element value: 9.9
}

// ----------------------------------------------------------------------------
int main() {

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
