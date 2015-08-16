#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream>
#include <vector>
#include <future>
#include <numeric>

using namespace std;

// ----------------------------------------------------------------------------
double accum(double* beg, double* end, double init){
  return accumulate(beg, end, init);                                            // compute the sum of [beg:end) starting with the initial value init
}

// ----------------------------------------------------------------------------
double comp4(vector<double>& v){                                                // spawn many tasks if v is large enough
  
  if (v.size()<10000)                                                           // is it worth using concurrency?
    return accumulate(v.begin(), v.end(), 0.0);
  
  auto v0 = &v[0];
  auto sz = v.size();
  auto f0 = async(accum, v0, v0 + sz / 4, 0.0);                                 // first quarter
  auto f1 = async(accum, v0 + sz / 4, v0 + sz / 2, 0.0);                        // second quarter
  auto f2 = async(accum, v0 + sz / 2, v0 + sz * 3 / 4, 0.0);                    // third quarter
  auto f3 = async(accum, v0 + sz * 3 / 4, v0 + sz, 0.0);                        // fourth quarter
  
  return f0.get() + f1.get() + f2.get() + f3.get();                             // collect and combine the results
}

// ----------------------------------------------------------------------------
void Test(void) {

  vector<double> v(20000);
  iota(v.begin(), v.end(), 0.0);
  auto result = comp4(v);
  
  cout << "Sum of " << v.size() << " elements equals : " << fixed << result << endl;
}

// ----------------------------------------------------------------------------
int main() {

  try{
#ifdef _MSC_VER
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _MSC_VER

    Test();

#ifdef _MSC_VER
    //_CrtMemDumpAllObjectsSince(NULL);                                         // Begins the dump since the start of program execution
    _CrtDumpMemoryLeaks();
#endif // _MSC_VER

    cout << "Press ENTER to quit : ";
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
  }
  catch (...) {
    cout << "Unknowns Exception Thrown" << endl;
  }
}
