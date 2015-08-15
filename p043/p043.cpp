                                                                                // TODO : immplement read_shape() using unique_ptr. see p 48
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define _SCL_SECURE_NO_WARNINGS                                                 // Avoid error with copy(...) in the initializer list ctor
#endif // _MSC_VER

#include <iostream> 
#include <vector>
#include <limits>

using namespace std;

class Point {
  double x;
  double y;
};

class Shape {
public:
  virtual Point center() const = 0;                                             // pure virtual
  virtual void move(Point to) = 0;
  virtual void draw() const = 0;                                                // draw on current "Canvas"
  virtual void rotate(int angle) = 0;
  virtual ~Shape() {}                                                           // destructor
  // ...
};

class Circle: public Shape {
public:
  Circle(Point p, int rr) :x {p}, r {rr} {}                                     // constructor
  Point center() const { return x; }
  void move(Point to) { x = to; }
  void draw() const {};
  void rotate(int) {}                                                           // nice simple algorithm
private:
  Point x;                                                                      // center
  int r;                                                                        // radius
};

class Smiley: public Circle {                                                   // use the circle as the base for a face
public:
  Smiley(Point p, int r) : Circle {p, r}, mouth {nullptr} {}
  ~Smiley() {
    delete mouth;
    for (auto p:eyes)
      delete p;
  }
  void move(Point to) override;                                                 // Explicit overriding
  void draw() const override;
  void rotate(int) override;

  void add_eye(Shape* s) { eyes.push_back(s); }
  void set_mouth(Shape *s);
  virtual void wink(int i);                                                     // wink eye number i
  // ...
private:
  vector<Shape*> eyes;                                                          // usually two eyes
  Shape* mouth;
};

void Smiley::draw() const {
  
  Circle::draw();
  for (auto p:eyes) p->draw();
  mouth->draw();
}

void Smiley::move(Point to){
  cout << "Move" << endl;
}

void Smiley::rotate(int i){
  cout << "Rotate" << endl;
}

void Smiley::wink(int i){
  cout << "wink eye N° " << i << endl;
}

void rotate_all(vector<Shape*>& v, int angle){                                  // rotate v's elements by angle degrees
  for (auto p:v) p->rotate(angle);
}

// ----------------------------------------------------------------------------
void Test(void) {

  Smiley MySmiley {Point(), 5};
  Shape* ps = &MySmiley;                                                        // see p 47

  if (Smiley* p = dynamic_cast<Smiley*>(ps)) {
    cout<<"This is a smiley"<<endl;                                             // ... is the Smiley pointer to by p ...
  }  else {
    cout<<"This is NOT a smiley"<<endl;                                         // ... not a Smiley, try something else ...
  }
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
