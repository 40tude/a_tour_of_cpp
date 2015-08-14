#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <vector>
#include <iostream> 
#include <stdexcept>                                                            // out_of_range
#include <limits>                                                               // numeric_limits

using namespace std;

// ----------------------------------------------------------------------------
struct Entry {
  string name;
  int number;
};

// ----------------------------------------------------------------------------
template<typename T>
class Vec : public std::vector<T> {

public:
  // TO DO : I d not understand the next statement (commented : using vector<T>::vector;)
  // See http://www.stroustrup.com/what-is-2009.pdf
  // This means "import" vector() (constructors) from std::vector
  // Inheriting constructors
  // see http://ideone.com/NpAXgJ
  // There is a bug with MSVC (works fine on ideone)
  // using vector<T>::vector;
  using vector<T>::vector<T>;                                                   // use the constructors from vector (under the name Vec). There is a typo in the book
  T& operator[](int i)                                                          // range check
  {
    return vector<T>::at(i);
  }

  const T& operator[](int i) const // range check const objects; §4.2.1
  {
    return vector<T>::at(i);
  }
};


// ----------------------------------------------------------------------------
void checked(Vec<Entry>& book){

  try {
    book[book.size()] = { "Joe", 999999 };                                      // will throw an exception
    // ...
  }
  catch (out_of_range) {
    cout << "Range error\n";
  }
}

// ----------------------------------------------------------------------------
void Test(void) {

  Vec<Entry> MyBook;
  checked(MyBook);
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
  catch (out_of_range){
    cout << "Range Error somewhere..." << endl;
  }
  catch(...){
    cout << "Unknowns Exception Thrown" << endl;
  }
}
