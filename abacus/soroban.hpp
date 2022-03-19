/*
 *  2022.3.19
 *  soroban.hpp
 *  ver 0.5
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef SOROBAN_HPP
#define SOROBAN_HPP
/*
#include <string>
#include <iostream>
#include <vector>
#include <thread> // for sleep
*/

#include <vector>

class place
{
private:
	static int type;
	static std::string str[3];

//	int old;

public:
	int n; /* number */
	int i; /* index */
	char c; /* char */

	std::string set_chartype(char type);
	int set_num(int n);
	int get_num(char *c);
};


class beads
{
private:

public:
	std::vector<place> p;

	int to_beads(long long int n);
	int to_beads(double n);
	int zero();
	int add(beads b);
	int del(beads b);
};


/* for sorobanlib */

typedef struct quotient_remainder{int q; int r;} divans;
struct op_num{char op; double num;};

divans division_answer(int a, int b); /* a waru b */
op_num get_operator(std::string str);

void simple_print(beads b);

#endif /* SOROBAN_HPP */