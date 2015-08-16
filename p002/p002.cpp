// On Win : cl /EHsc /nologo /W4 /MT /O2 /GL pXXX.cpp
// On Mac : clang++ -Wall -std=c++0x -stdlib=libc++ pXXX.cpp -o pXXX.cpp

#include <iostream>                                                             // includes ("import") the declarations for the I/O stream library
#include <limits>

// ----------------------------------------------------------------------------
int main(){
	std::cout << "Hello, World!\n";
	std::cout << "Hello, World!" << std::endl;
  
  // Uncomment the 2 lines below if needed
  // std::cout << "Press ENTER to quit : ";
  // std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}
