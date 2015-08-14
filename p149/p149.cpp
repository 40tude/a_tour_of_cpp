// TODO : generate exception on http://ideone.com/ and http://webcompiler.cloudapp.net/

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <vector>
#include <numeric>
#include <thread>
#include <future>

using namespace std;

// ----------------------------------------------------------------------------
double accum(double* beg, double* end, double init){
  return accumulate(beg, end, init);                                            // compute the sum of [beg:end) starting with the initial value init
}

// ----------------------------------------------------------------------------
double comp2(vector<double>& v){
  using Task_type = double(double*, double*, double);                           // type of task
  
  packaged_task<Task_type> pt0{ accum };                                        // package the task (i.e., accum)
  packaged_task<Task_type> pt1{ accum };
  
  future<double> f0{ pt0.get_future() };                                        // get hold of pt0’s future
  future<double> f1{ pt1.get_future() };                                        // get hold of pt1’s future
  
  double* first = &v[0];
  thread t1{ move(pt0), first, first + v.size() / 2, 0 };                       // start a thread for pt0
  thread t2{ move(pt1), first + v.size() / 2, first + v.size(), 0 };            // start a thread for pt1
  
  t1.join();                                                                    // mandatory otherwise the code hangs
  t2.join();

  return f0.get() + f1.get();                                                   // get the results
}

// ----------------------------------------------------------------------------
void Test(void) {

  vector<double> v{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
  auto result = comp2(v);
  cout << result << endl;

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
