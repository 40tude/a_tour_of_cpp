#include <iostream> 
#include <limits>

using namespace std;

// ----------------------------------------------------------------------------
int count_x1(char* p, char x){                                                  // count the number of occurrences of x in p[]
                                                                                // p is assumed to point to a zero-terminated array of char (or to nothing)
	if (p == nullptr) return 0;
  
  int count = 0;
  //for (; p != nullptr; ++p)                                                   // In the Sept 2013 printing, the for statement did'nt work for me : for (; p != nullptr; ++p) 
  for (; *p != 0; ++p)                                                          // Corrected in the Sept 2014 prinitng
    if (*p == x) ++count;
	
	return count;
}

// ----------------------------------------------------------------------------
int count_x2(char* p, char x){                                                  // count the number of occurrences of x in p[]
                                                                                // p is assumed to point to a zero terminated array of char (or to nothing)
  if (p == nullptr) return 0;
  
  int count = 0;
  while (*p) {                                                                  // There was a typo in the Sept 2013 printing. It was writtent while (p) instead of while (*p). Correction made in Sept 2014 printing
		if (*p == x) ++count;
		++p;
	}
	return count;
}

// ----------------------------------------------------------------------------
int main(){
	
  auto n1 = count_x1("alibaba", 'a');
  cout << "Number of 'a' : " << n1 << endl;
	
  auto n2 = count_x2("alibaba", 'a');
  cout << "Number of 'a' : " << n1 << endl;

	cout << "Press ENTER to quit : ";
	cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}
