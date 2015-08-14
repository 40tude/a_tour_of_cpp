#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <vector>
#include <list>
#include <string>
#include <iostream> 

using namespace std;

// ----------------------------------------------------------------------------
template<typename T>
class Less_than {
private:
  const T val;                                                                  // value to compare against

public:
  Less_than(const T& v) :val(v) { }
  bool operator()(const T& x) const { return x<val; }                           // call operator
};

// ----------------------------------------------------------------------------
template<typename C, typename P>
int count(const C& c, P pred){

  int cnt = 0;
  for (const auto& x : c)
    if (pred(x))
      ++cnt;
  return cnt;
}

// ----------------------------------------------------------------------------
void f(const vector<int>& vec, const list<string>& lst, int x, const string& s){

  cout << "number of values less than " << x
    << ": " << count(vec, Less_than<int>{x})
    << '\n';
  cout << "number of values less than " << s
    << ": " << count(lst, Less_than<string>{s})
    << '\n';
}

// ----------------------------------------------------------------------------
void g(const vector<int>& vec, const list<string>& lst, int x, const string& s){

  cout << "number of values less than " << x
    << ": " << count(vec, [&](int a){ return a<x; })
    << '\n';
  cout << "number of values less than " << s
    << ": " << count(lst, [&](const string& a){ return a<s; })
    << '\n';
}

// ----------------------------------------------------------------------------
template<typename T, typename ... Tail>
void h(T head, Tail... tail){
  i(head);                                                                      // do something to head
  h(tail...);                                                                   // try again with tail
}

// ----------------------------------------------------------------------------
void h() { }                                                                    // Handle cases where h() get called. Do nothing

// ----------------------------------------------------------------------------
template<typename T>
void i(T x){

  cout << x << " ";
}

// ----------------------------------------------------------------------------
void Test(void) {
  Less_than<int> lti{ 42 };                                                     // lti(i) will compare i to 42 using < (i<42)
  Less_than<string> lts{ "Backus" };                                            // lts(s) will compare s to "Backus" using < (s<"Backus")

  auto n=24;
  bool b1 = lti(n);                                                             // true if n<42

  auto s= "Blabla";
  bool b2 = lts(s);                                                             // true if s<"Backus"
  // ...

  vector<int> MyVec { 100, 200, 300, 400 };
  list<string> MyList{ "aaaa", "bbbb", "ccc", "zzzz" };
  cout << "Using f() : " << endl;
  f(MyVec, MyList, 250, "ddd");

  cout << "\nUsing g() : " << endl;
  g(MyVec, MyList, 250, "ddd");


  // Variadic templates
  cout << "\n\nFirst  : ";
  h(1, 2.2, "hello");

  cout << "\nSecond : ";
  h(0.2, 'c', "yuck!", 0, 1, 2);
  cout << "\n";
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
