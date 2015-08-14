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
bool has_c1(const string& s, char c){                                           // does s contain the character c?

  auto p = find(s.begin(), s.end(), c);
  if (p != s.end())
    return true;
  else
    return false;
}

// ----------------------------------------------------------------------------
bool has_c2(const string& s, char c){                                           // does s contain the character c?
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
    cout << "There is at least one a in Alibaba" << endl;
  else
    cout << "There is a bug in has_c1()" << endl;
  cout << "\n";

  Bob = has_c2("alibaba", 'a');
  if (Bob)
    cout << "There is at least one a in Alibaba" << endl;
  else
    cout << "There is a bug in has_c2()" << endl;
  cout << "\n";

  vector<string::iterator> Places = Find_All(string("Alibaba"), 'a');
  int count = 1;
  for (const auto &x : Places)
    cout << "Occurence # : " << count++ << endl;
  cout << "\n";

  // Now it use the template version
  string m{ "Mary had a little lamb" };
  for (auto p : find_all(m, 'a')) // p is a str ing::iterator
    if (*p != 'a')
      cerr << "string bug!\n";
  
  list<double> ld{ 1.1, 2.2, 3.3, 1.1 };
  for (auto p : find_all(ld, 1.1))
    if (*p != 1.1)
      cerr << "list bug!\n";
  
  vector<string> vs{ "red", "blue", "green", "green", "orange", "green" };
  for (auto p : find_all(vs, "red"))
    if (*p != "red")
      cerr << "vector bug!\n";
  
  for (auto p : find_all(vs, "green"))
    *p = "vert";

  for (const auto &p : vs)
    cout << p << endl;
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
