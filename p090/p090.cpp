#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <string>
#include <vector>
#include <iostream> 
#include <sstream>

using namespace std;

struct Entry {
  string  name;
  int     number;
};

// ----------------------------------------------------------------------------
ostream& operator<<(ostream& os, const Entry& e){
  return os << "{\"" << e.name << "\", " << e.number << "}";
}

// ----------------------------------------------------------------------------
istream& operator>>(istream& is, Entry& e){                                     // read { "name" , number } pair. Note: for matted with { " " , and }
  char c, c2;
  if (is >> c && c == '{' && is >> c2 && c2 == '"') {                           // start with a { "
    string name;                                                                // the default value of a string is the empty string: ""
    while (is.get(c) && c != '"')                                               // anything before a " is part of the name
      name += c;
    if (is >> c && c == ',') {
      int number = 0;
      if (is >> number >> c && c == '}') {                                      // read the number and a }
        e = { name, number };                                                   // assign to the entry
        return is;
      }
    }
  }
  is.setstate(ios_base::failbit);                                               // register the failure in the stream
  return is;
}

// ----------------------------------------------------------------------------
void Test(void) {

  vector<Entry> MyInput{
      { "John Marwood Cleese", 123456          },
      { "Michael Edward Palin", 987654 }
  };

  for (auto i:MyInput)                                                          // read from cin into ee
    cout << i << '\n';                                                          // write ee to cout

                                                                                // See 8.6 p 91 about Formating
  cout << 1234 << ',' << hex << 1234 << ',' << oct << 1234 << '\n';             // print 1234,4d2,2322
  
  constexpr double d = 123.456;                                                 // now supported in MSVC 2015    
  cout << d << "; "                                                             // use the default for mat for d
    << scientific << d << "; "                                                  // use 1.123e2 style for mat for d
    << hexfloat << d << "; "                                                    // use hexadecimal notation for d
    << fixed << d << "; "                                                       // use 123.456 style for mat for f
    << defaultfloat << d << '\n';                                               // use the default for mat for d

  cout.precision(8);
  cout << 1234.56789 << ' ' << 1234.56789 << ' ' << 123456 << '\n';
  
  cout.precision(4);
  cout << 1234.56789 << ' ' << 1234.56789 << ' ' << 123456 << '\n';
}

// ----------------------------------------------------------------------------
template<typename Target = string, typename Source = string>                    // see p 93
Target to(Source arg){                                                          // convert Source to Target

  stringstream  interpreter;
  Target        result;
  
  if (!(interpreter << arg)                                                     // write arg into stream
    || !(interpreter >> result)                                                 // read result from stream
    || !(interpreter >> std::ws).eof())                                         // stuff left in stream?
    throw runtime_error{ "to<>() failed" };
  return result;
}

// ----------------------------------------------------------------------------
void Test2(void) {

  auto x1 = to<string, double>(1.2);                                            // very explicit (and verbose)
  auto x2 = to<string>(1.2);                                                    // Source is deduced to double
  auto x3 = to<>(1.2);                                                          // Target is defaulted to string; Source is deduced to double
  auto x4 = to(1.2);                                                            // the <> is redundant;
}

// ----------------------------------------------------------------------------
int main() {

#ifdef _MSC_VER
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _MSC_VER

  Test();
  Test2();

#ifdef _MSC_VER
  //_CrtMemDumpAllObjectsSince(NULL);                                             // Begins the dump from the start of program execution
  _CrtDumpMemoryLeaks();
#endif // _MSC_VER

  cout << "Press ENTER to quit : ";
  cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}
