#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _MSC_VER

#include <iostream> 
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// ----------------------------------------------------------------------------
int DoSomeFileIO(){

  // fill input.txt file with some words
  string FileNameIn{ "input.txt" };
  ofstream MyFile(FileNameIn);
  string DefaultContent{ "Lorem ipsum dolor sit amet, iriure disputationi ut vel, ullum velit congue cu his.\nCu nam utinam appellantur, tibique incorrupte constituam qui cu." };
  MyFile << DefaultContent << endl;
  MyFile.close();

  ifstream InputStream{ FileNameIn };                                           // input stream for file "FileNameIn"
  istream_iterator<string> InputIterator{ InputStream };                        // input iterator for stream
  istream_iterator<string> eos{};                                               // input sentinel
  
  string FileNameOut{ "output.txt" };
  ofstream OutputStream{ FileNameOut };                                         // output stream for file "output.txt"
  ostream_iterator<string> OutputIterator{ OutputStream, "\n" };                // output iterator for stream. '\n' will delimit outpu values

  vector<string> Buffer { InputIterator, eos };                                 // Construct Buffer using 2 iterators
  sort(Buffer.begin(), Buffer.end());                                           // sort the Buffer
  unique_copy(Buffer.begin(), Buffer.end(), OutputIterator);                    // copy Buffer in FileNameOut discarding replicated values

  return !InputStream.eof() || !OutputStream;                                   // return error state (§1.3, §8.4)
}

// ----------------------------------------------------------------------------
int DoSomeFileIO2(){

  // fill input.txt file with some words
  string FileNameIn{ "input2.txt" };
  ofstream MyFile(FileNameIn);
  string DefaultContent{ "Lorem ipsum dolor sit amet, iriure disputationi ut vel, ullum velit congue cu his.\nCu nam utinam appellantur, tibique incorrupte constituam qui cu." };
  MyFile << DefaultContent << endl;
  MyFile.close();

  // TODO : Add more comment and/or rename variables
  ifstream InputStream{ FileNameIn };                                           // input stream for file "FileNameIn"
  istream_iterator<string> InputIterator{ InputStream };                        // input iterator for stream
  istream_iterator<string> eos{};                                               // input sentinel

  string FileNameOut{ "output2.txt" };
  ofstream OutputStream{ FileNameOut };                                         // output stream for file "output2.txt"

  set<string> Buffer { istream_iterator<string>{InputStream}, istream_iterator<string>{} }; // read input
  copy(Buffer.begin(), Buffer.end(), ostream_iterator<string>{OutputStream, "\n"});         // copy FileNameOut output

  return !InputStream.eof() || !OutputStream;                                   // return error state (§1.3, §8.4)
}

// ----------------------------------------------------------------------------
void Test(void) {

  ostream_iterator<string> OutputIterator{ cout };                              // write strings to cout  
  *OutputIterator = "Hello, ";                                                  // meaning cout<<"Hello, "
  ++OutputIterator;
  ++OutputIterator;
  ++OutputIterator;
  ++OutputIterator;
  *OutputIterator = "world!\n";                                                 // meaning cout<<"world!\n"

  DoSomeFileIO();
  DoSomeFileIO2();
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