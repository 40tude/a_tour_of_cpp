#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <string>
#include <memory>

using namespace std;

// ----------------------------------------------------------------------------
template<typename T, typename ... Args>
unique_ptr<T> Make_Unique(Args&&... args) {
  return std::unique_ptr<T>{new T{ std::forward<Args>(args)... }};
}

// ----------------------------------------------------------------------------
void Test(void) {

  struct S {
    int     i;
    string  s;
    double  d;
    // ...
    S(int ii, string ss, double dd) : i{ ii }, s(ss), d{ dd } {};
  };

  shared_ptr<S> p1{ new S{ 1, "Ankh Morpork", 4.65 } };
  
  auto p2 = make_shared<S>(2, "Oz", 7.62);

  auto p3 = make_unique<S>(3, "Atlantis", 11.3);                                // make_unique already exist

  auto p4 = Make_Unique<S>(4, "Austin", 42.0);
}

// ----------------------------------------------------------------------------
int main() {

  try{
#ifdef _MSC_VER
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _MSC_VER

    Test();

#ifdef _MSC_VER
    //_CrtMemDumpAllObjectsSince(NULL);                                         // Begins the dump FileNameIn the start of program execution
    _CrtDumpMemoryLeaks();
#endif // _MSC_VER

    cout << "Press ENTER to quit : ";
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
  }
  catch (...) {
    cout << "Unknowns Exception Thrown" << endl;
  }
}