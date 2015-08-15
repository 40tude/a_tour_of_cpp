#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <regex>
#include <iostream> 

using namespace std;

// ----------------------------------------------------------------------------
void use_p78(){
  regex pat(R"(\w{2}\s*\d{5}(-\d{4})?)");                                       // US postal code pattern: XXddddd-dddd and variants

  vector<string> source{ "US postal code pattern: XXddddd-dddd and variants", "TX 77845", "TX       77845", "TX       77845-12345678", "TX77845-1234", "DC 20500-0001" };

  int lineno = 0;
  //for (string line; getline(cin, line);) {                                    // read into line buffer
  for (auto line : source){
    ++lineno;
    smatch matches;                                                             // matched strings go here
    if (regex_search(line, matches, pat))                                       // search for pat in line
      cout << lineno << ": " << matches[0] << '\n';
  }
}

// ----------------------------------------------------------------------------
void use_p79() {

  vector<string> source{ "US postal code pattern: XXddddd-dddd and variants", "TX 77845", "TX       77845", "TX       77845-12345678", "TX77845-1234", "DC 20500-0001" };

  regex pat{ R"(\w{2}\s*\d{5}(-\d{4})?)" };                                     // U.S. postal code pattern

  int lineno = 0;
  //for (string line; getline(in, line);) {
  for (auto line : source) {
    ++lineno;
    smatch matches;                                                             // matched strings go here
    if (regex_search(line, matches, pat)) {
      cout << lineno << ": The complete match  : " << matches[0] << '\n';
      if (1<matches.size() && matches[1].matched)
        cout << " : Subpattern : " << matches[1] << '\n';
    }
  }
}

// ----------------------------------------------------------------------------
bool is_identifier(const string& s){                                            // see p 82
  regex pat{ R"([_[:alpha:]]\w*)" };                                            // underscore or letter
                                                                                // followed by zero or more underscore, letters or digits
  return regex_match(s, pat);
}

// ----------------------------------------------------------------------------
void Test(void) {
  cout << "Using use_p78()" << endl;
  use_p78();

  cout << "\nUsing use_p79()" << endl;
  use_p79();

  cout << "\nCheck valid identifier" << endl;
  if (is_identifier(string("MyFunctionCall")))
    cout << "MyFunctionCall is a valid identifier" << endl;
  else
    cout << "MyFunctionCall is not a valid identifier" << endl;

  cout << "\nOutput white space separated words   : " << endl;                  // see p83
  string input1 = "aa as; asd ++eˆasdf asdfg";
  regex pat1{ R"(\s+(\w+))" };                                                  // output white space separated words

  for (sregex_iterator p(input1.begin(), input1.end(), pat1); p != sregex_iterator{}; ++p)
    cout << (*p)[1] << '\n';

  cout << "\nOutput white space separated words 2 : " << endl;
  regex pat2{ R"((\w+))" };                                                     // do not forget the very first "aa"
  for (sregex_iterator p(input1.begin(), input1.end(), pat2); p != sregex_iterator{}; ++p)
    cout << (*p)[1] << '\n';
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
