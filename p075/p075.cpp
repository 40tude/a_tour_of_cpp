#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <string>
#include <iostream> 

using namespace std;

// ----------------------------------------------------------------------------
void m3(){

  string name = "Niels Stroustrup";

  string s = name.substr(6, 10);                                                // s = "Stroustrup"
  name.replace(0, 5, "nicholas");                                               // name becomes "nicholas Stroustrup"
                                                                                // the replacement string need not be the same size as the substring that it is replacing
  name[0] = toupper(name[0]);                                                   // name becomes "Nicholas Stroustrup"
  cout << name << endl;
}

// ----------------------------------------------------------------------------
void m2(string& s1, string& s2){

  s1 = s1 + '\n';                                                               // append newline
  cout << s1;
  s2 += '\n';                                                                   // append newline
  cout << s2;
}

// ----------------------------------------------------------------------------
string compose(const string& name, const string& domain){
  return name + '@' + domain;
}

// ----------------------------------------------------------------------------
void print(const string& s){
  printf("For people who like printf: %s\n", s.c_str());
  cout << "For people who like streams: " << s << '\n';
}

// ----------------------------------------------------------------------------
void Test(void) {

  auto addr = compose("dmr", "bell-labs.com");
  cout << addr << endl;

  m2(string("Niels"), string("Stroustrup"));

  m3();

  print("Niels Stroustrup");
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
