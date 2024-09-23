#include <iostream>
#include <string>
#include <sstream>


using namespace std;

int main(int argc, char* argv[])
{
	string green = "\033[92m";
	string yellow = "\033[93m";
	string coloroff = "\033[0m";
	
	cout << green << "Green" << " " << yellow << "Yellow" << coloroff << endl;
	cout << "Normal" << endl;
	cout << green << "Diff" << yellow << "eren" << green << "t" << coloroff << endl;
	
}