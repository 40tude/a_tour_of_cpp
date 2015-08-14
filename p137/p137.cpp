#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <random>
#include <functional>                                                           // bind

using namespace std;

// ----------------------------------------------------------------------------
class Rand_int {
public:
  Rand_int(int low, int high) :dist{ low, high } { }
  int operator()() { return dist(re); }                                         // draw an int

private:
  default_random_engine       re;
  uniform_int_distribution<>  dist;
};

// ----------------------------------------------------------------------------
void Test(void) {

  using my_engine = default_random_engine;                                      // type of engine
  using my_distribution = uniform_int_distribution<>;                           // type of distribution

  my_engine re{};                                                               // the default engine
  my_distribution one_to_six{ 1, 6 };                                           // distribution that maps to the ints 1..6
  auto die = bind(one_to_six, re);                                              // make a generator
  int x = die();                                                                // roll the die: x becomes a value in [1:6]

  auto die2 = bind(uniform_int_distribution<>{1, 60}, default_random_engine{});
  int y = die2();
  
  const int max = 8;                                                            // constexpr int max = 8;
  Rand_int rnd{ 0, max };                                                       // make a uniform random number generator
  vector<int> histogram(max + 1);                                               // make a vector of appropriate size
  
  for (int i = 0; i != 200; ++i)
    ++histogram[rnd()];                                                         // fill histogram with the frequencies of numbers [0:max]
  
  for (int i = 0; i != histogram.size(); ++i) {                                 // write out a bar graph
    cout << i << '\t';
    for (int j = 0; j != histogram[i]; ++j) cout << '*';
    cout << endl;
  }
  cout << endl;
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