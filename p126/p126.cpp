#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <functional>
#include <string>
#include <vector>
#include <algorithm> // for_each

using namespace std;

// ----------------------------------------------------------------------------
double cube(double x){
  cout << "x is equal to : " << x << endl; 
  return x;
}

// ----------------------------------------------------------------------------
void f(int n, const string& str){
  for (auto i=0; i != n; ++i)
    cout << str << endl;
}

// ----------------------------------------------------------------------------
void Test1(void) {
  
  auto cube2 = bind(cube, 2);
  double bob = cube2();

  using namespace placeholders;
  auto g = bind(f, 2, _1);                                                      // bind f()’s first argument to 2
  cout << "\nUsing f():" << endl;
  f(2, "hello");
  
  cout << "\nUsing g():" << endl;
  g("hello");                                                                   // also calls f(2,"hello");
}


// ----------------------------------------------------------------------------
struct Shape{
  int x;
  int y;
  Shape(int x_in, int y_in) : x{ x_in }, y{ y_in } {};
  void draw() {
    cout << "x : " << x << " y : " << y << endl;
  }
};

// ----------------------------------------------------------------------------
void user(Shape* p){

  p->draw();
  auto draw = mem_fn(&Shape::draw);
  draw(p);
}

// ----------------------------------------------------------------------------
void draw_all1(vector<Shape*>& v){

  cout << "\nUsing mem_fn() : " << endl;
  for_each(v.begin(), v.end(), mem_fn(&Shape::draw));
}

// ----------------------------------------------------------------------------
void draw_all2(vector<Shape*>& v){

  cout << "\nUsing lambda : " << endl;
  for_each(v.begin(), v.end(), [](Shape* p) { p->draw(); });
}

// ----------------------------------------------------------------------------
void Test2(void) {
  
  vector<Shape*> v{ new Shape{ 1, 2 }, new Shape{ 3, 4 } };
  draw_all1(v);
  draw_all2(v);
  
  for (auto &s:v)                                                               // avoid memory leak
    delete(s);
}

// ----------------------------------------------------------------------------
int main() {

  try{
#ifdef _MSC_VER
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _MSC_VER

    Test1();
    Test2();

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