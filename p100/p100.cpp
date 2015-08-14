#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <list>
#include <string>

using namespace std;

struct Entry{
  string  name;
  int     number;
};

// ----------------------------------------------------------------------------
list<Entry> phone_book = {
    { "David Hume", 123456 },
    { "Karl Popper", 234567 },
    { "Bertrand Arthur William Russell", 345678 }
};

// ----------------------------------------------------------------------------
int get_number(const string& s){

  for (const auto& x : phone_book)
    if (x.name == s)
      return x.number;
  return 0;                                                                     // use 0 to represent "number not found"
}

// ----------------------------------------------------------------------------
int get_numberV2(const string& s){

  for (auto p = phone_book.begin(); p != phone_book.end(); ++p)
    if (p->name == s)
      return p->number;
  return 0;                                                                     // use 0 to represent "number not found"
}

// ----------------------------------------------------------------------------
list<Entry>::iterator ReturnIeratorTo(const Entry& ee){
  for (auto p = phone_book.begin(); p != phone_book.end(); ++p)
    if (p->name == ee.name && p->number == ee.number)
      return p;
  return phone_book.end();
}

// ----------------------------------------------------------------------------
void f(const Entry& ee, list<Entry>::iterator p, list<Entry>::iterator q){

  phone_book.insert(p, ee); // add ee before the element referred to by p
  phone_book.erase(q); // remove the element referred to by q
}

// ----------------------------------------------------------------------------
void Test(void) {
  
  if (auto Num = get_number("Karl Popper"))
    cout << "Karl Popper phone number is : " << Num << endl;
  else
    cout << "Karl Popper is NOT in the directory" << endl;

  if (auto Num = get_numberV2("Karl Popper"))
    cout << "Karl Popper phone number is : " << Num << endl;
  else
    cout << "Karl Popper is NOT in the directory" << endl;

  list<Entry>::iterator p = ReturnIeratorTo({ "Karl Popper", 234567 });
  list<Entry>::iterator q=p;

  f({ "Me", 148944 }, p, q);
  cout << "\nListing of the Phone Book" << endl;
  for (const auto & x : phone_book)
    cout << x.name << " : " << x.number << endl;
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
  }  catch (...) {
    cout << "Unknowns Exception Thrown" << endl;
  }
}
