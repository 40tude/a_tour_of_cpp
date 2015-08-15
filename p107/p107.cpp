#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

struct Entry{
  string  name;
  int     number;
};

// ----------------------------------------------------------------------------
bool operator<(const Entry& x, const Entry& y){                                 // less than operator. Returns true when satisfied and false otherwise
  return x.name < y.name;                                                       // order Entrys by their names
}

// ----------------------------------------------------------------------------
bool operator==(const Entry& x, const Entry& y){                                // equality
  return x.name == y.name;                                                      // test Entrys by their names
}

// ----------------------------------------------------------------------------
void f_p107(vector<Entry>& vec, list<Entry>& lst){

  sort(vec.begin(), vec.end());                                                  // use < for order
  unique_copy(vec.begin(), vec.end(), lst.begin());                              // don’t copy adjacent equal elements
}

// ----------------------------------------------------------------------------
list<Entry> f_p108(vector<Entry>& vec){
  
  list<Entry> res;

  sort(vec.begin(), vec.end());
  unique_copy(vec.begin(), vec.end(), back_inserter(res));                      // append to res
  return res;                                                                   // list have a move constructor so this is OK
}

// ----------------------------------------------------------------------------
void Test(void) {

  vector<Entry> phone_book = {
      { "David Hume", 123456 },
      { "Karl Popper", 234567 },
      { "Bertrand Arthur William Russell", 345678 },
      { "Karl Popper", 234567 },
      { "David Hume", 123456 },
      { "Karl Popper", 234567 },
      { "David Hume", 123456 },
      { "Bertrand Arthur William Russell", 345678 },
      { "Karl Popper", 234567 },
      { "Bertrand Arthur William Russell", 345678 },
      { "David Hume", 123456 },
      { "Karl Popper", 234567 }
  };

  list<Entry> MyList{ 10 };
  f_p107(phone_book, MyList);                                                       // MyList must exist and be large enough
  for (const auto x : MyList)
    cout << x.name << endl;

  list<Entry> MyOtherList = f_p108(phone_book);                                     // MyOtherList is built
  for (const auto x : MyOtherList)
    cout << x.name << endl;
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
