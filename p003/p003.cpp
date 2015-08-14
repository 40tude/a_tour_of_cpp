#include <iostream>                                                             
#include <limits>

using namespace std;                                                            // make names from std visible without std:: (§3.3)

// ----------------------------------------------------------------------------
double square(double x){                                                        // square a double precision floating-point number
  return x*x;
}

// ----------------------------------------------------------------------------
void print_square(double x){
  cout << "The square of " << x << " is " << square(x) << "\n";
}

// ----------------------------------------------------------------------------
int main(){
  print_square(1.234);                                                          // print: the square of 1.234 is 1.52276

  cout << "Press ENTER to quit : ";
  cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}
	