#include <iostream> 
#include <limits>

using namespace std;

// ----------------------------------------------------------------------------
void copy_fct(){

	int v1[10] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int v2[10];                                                                   // to become a copy of v1

	for (auto x : v1)                                                             // for each x in v
		cout << x << '\n';
	cout << endl;
	
	for (auto i = 0; i != 10; ++i)                                                // copy elements
		v2[i] = v1[i];
		
	for (auto x : v2) 
		cout << x << '\n';
	cout << endl;
}

// ----------------------------------------------------------------------------
void print(){

	int v[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	for (auto x : v) 
		cout << x << '\n';
	cout <<endl;

	for (auto x : {10, 21, 32, 43, 54, 65})
		cout << x << '\n';
	cout << endl;
}

// ----------------------------------------------------------------------------
void increment(){

	int v[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	for (auto x : v) 
		cout << x << '\n';
	cout << endl;

	for (auto& x : v)                                                             // x is a reference to an object whose type is automatically deduced
		++x;
	
	for (const auto& x : v)                                                       // x is a read only reference to an object whose type is automatically deduced
		cout << x << '\n';
	cout << endl;
}

// ----------------------------------------------------------------------------
int main(){

	copy_fct();
	print();
	increment();

	cout << "Press ENTER to quit : ";
	cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}