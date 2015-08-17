#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <vector>
#include <forward_list>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

// ----------------------------------------------------------------------------
template<typename Ran>                                                          // for random-access iterators
void sort_helper(Ran beg, Ran end, random_access_iterator_tag){                 // we can subscript into [beg:end)

  sort(beg, end);                                                               // just sort it
}

// ----------------------------------------------------------------------------
template<typename C>
using Value_type = typename C::value_type;                                      // C’s value type

// ----------------------------------------------------------------------------
template<typename For>                                                          // for forward iterators
void sort_helper(For beg, For end, forward_iterator_tag){                       // we can traverse [beg:end)

  vector<Value_type<For>> v{ beg, end };                                        // initialize a vector from [beg:end)
  sort(v.begin(), v.end());
  copy(v.begin(), v.end(), beg);                                                // copy the elements back
}

// ----------------------------------------------------------------------------
template<typename C>
using Iterator_type = typename C::iterator;                                     // C’s iterator type

// ----------------------------------------------------------------------------
template<typename Iter>
using Iterator_category = typename iterator_traits<Iter>::iterator_category;    // Iter’s category

// ----------------------------------------------------------------------------
template<typename C>
void sort(C& c){

  using Iter = Iterator_type<C>;
  sort_helper(c.begin(), c.end(), Iterator_category<Iter>{});                   // Iterator_category<Iter>{} constructs a "tag" value inidicating the kind of iterator provided
                                                                                // Here it will return either std::random_access_iterator_tag or std::forward_iterator_tag
}

// ----------------------------------------------------------------------------
void RealTest(vector<string>& v, forward_list<int>& lst){
  sort(v);                                                                      // sort the vector
  sort(lst);                                                                    // sort the singly-linked list
}

// ----------------------------------------------------------------------------
void Test(void) {

  vector<string>    myvector  { "riri", "fifi", "loulou" };
  forward_list<int> mylist    { 3, 2, 1 };

  cout << "Before RealTest() :" << endl;
  for (const auto& s : myvector)
    cout << s << endl;

  for (const auto& n : mylist)
    cout << n << endl;

  RealTest(myvector, mylist);

  cout << "\nAfter RealTest() :" << endl;
  for (const auto& s : myvector)
    cout << s << endl;

  for (const auto& n : mylist)
    cout << n << endl;
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
