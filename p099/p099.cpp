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
class Vec : public std::vector<T> {                                             // the class Vec publicly inherit from std::vector

                                                                                // TODO : I d not understand the next statement (using vector<T>::vector;)
                                                                                // See http://www.stroustrup.com/what-is-2009.pdf p10-11
                                                                                // This means "import" vector() (constructors) from std::vector
                                                                                // Inheriting constructors
                                                                                // see http://ideone.com/NpAXgJ
public:
  using vector<T>::vector;                                                      // was not working in MSVC 2103. Now work in MSVC 2015
                                                                                // use the constructors from vector (under the name Vec)
  
  T& operator[](int i){                                                         // range check
    return vector<T>::at(i);
  }

  const T& operator[](int i) const {                                            // range check const objects; §4.2.1
    return vector<T>::at(i);
  }
};


// ----------------------------------------------------------------------------
void checked(Vec<Entry>& book){

  try {
    book[book.size()] = { "Joe", 999999 };                                      // will throw an exception
    // ...
  } catch (out_of_range) {
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
    //_CrtMemDumpAllObjectsSince(NULL);                                         // Begins the dump from the start of program execution
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
