/*
 *  2022.2.22
 *  hw.cpp
 *  ver.2.2
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <iostream>


using namespace std;

int main(int argc, char **argv)
{
	cout << "Hello world!" << endl;

	/* "echo | gcc -dM -E -" or "gcc -dM -E hw.cpp" */
	cout << "defined macro __GNUC__ is " << __GNUC__ << endl;

	return 0;
}
