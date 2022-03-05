// CMakeProject1.cpp : Defines the entry point for the application.
//

#include "CMakeProject1.h"
#include "..\..\CMakeProject1\lib\parameter.h"

using namespace std;

int main()
{
	auto y = lib::ret(1.0);
	cout << "Hello CMake." << endl;
	return 0;
}
