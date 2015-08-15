#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <vector>
#include <string>
#include <list>

using namespace std;

// ----------------------------------------------------------------------------
bool has_c1(const string& s, char c){                                           // does string s contain the character c?

  auto p = find(s.begin(), s.end(), c);
  if (p != s.end())
    return true;
  else
    return false;
}

// ----------------------------------------------------------------------------
bool has_c2(const string& s, char c){                                           // does string s contain the character c?
  return find(s.begin(), s.end(), c) != s.end();
}

// ----------------------------------------------------------------------------
vector<string::iterator> Find_All(string& s, char c){                           // find all occurrences of c in s

  vector<string::iterator> res;

  for (auto p = s.begin(); p != s.end(); ++p)
    if (*p == c)
      res.push_back(p);
  
  return res;
}

// ----------------------------------------------------------------------------
template<typename T>
using Iterator = typename T::iterator;                                          // T’s iterator

template<typename C, typename V>
vector<Iterator<C>> find_all(C& c, V v){                                        // find all occurrences of v in c

  vector<Iterator<C>> res;
  for (auto p = c.begin(); p != c.end(); ++p)
    if (*p == v)
      res.push_back(p);
  return res;
}

// ----------------------------------------------------------------------------
void Test(void) {
  
  auto Bob = has_c1("alibaba", 'a');
  if (Bob)
    cout << "There is at least one 'a' in 'Alibaba'" << endl;
  else
    cout << "There is a bug in has_c1()" << endl;

  Bob = has_c2("alibaba", 'a');
  if (Bob)
    cout << "There is at least one 'a' in 'Alibaba'" << endl;
  else
    cout << "There is a bug in has_c2()" << endl;
  cout << endl;

  string m1 { "Mary had a little lamb" };                                       // Use the "genuine" version
  auto count1 = 0;
  for (auto p : Find_All(m1, 'a'))
    if (*p != 'a')
      cerr << "A bug!\n";
    else
      ++count1;
  cout << "There are " << count1 << " 'a' in 'Mary had a little lamb'" << endl;

  
  string m2 { "Mary had a little lamb" };                                       // Now it use the templated version
  auto count2 = 0;
  for (auto p : find_all(m2, 'a'))                                              // p is a string::iterator
    if (*p != 'a')
      cerr << "string bug!\n";
    else
      ++count2;
  cout << "There are " << count2 << " 'a' in 'Mary had a little lamb'" << endl;
  cout << endl;

  list<double> ld{ 1.1, 2.2, 3.3, 1.1 };
  auto count3 = 0;
  for (auto p : find_all(ld, 1.1))
    if (*p != 1.1)
      cerr << "list bug!\n";
    else
      ++count3;
  cout << "There are " << count3 << " values equal to 1.1 in the list" << endl;

  vector<string> vs{ "red", "blue", "green", "green", "orange", "green" };
  cout << "\nInitial list :" << endl;
  for (const auto &p : vs) cout << p << endl;
  cout << endl;

  auto count4 = 0;
  for (auto p : find_all(vs, "red"))
    if (*p != "red")
      cerr << "vector bug!\n";
    else
      ++count4;
  cout << "There are " << count4 << " red in the vector" << endl;
  cout << endl;
  
  for (auto p : find_all(vs, "green"))
    *p = "vert";

  cout << "After replacing 'green' by 'vert' in the list :" << endl;

  for (const auto &p : vs) cout << p << endl;
  cout << "\n";
}

// ----------------------------------------------------------------------------
int main() {

  try{
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
  catch (...) {
    cout << "Unknowns Exception Thrown" << endl;
  }
}
