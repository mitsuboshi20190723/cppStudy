/*
 *  2022.3.19
 *  sorobanlib.cpp
 *  ver 0.2
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <string>
#include <iostream>
#include "soroban.hpp"
#include "sorobanframe.hpp"


/*
std::string set_chartype(char type)
{
	place p;

	switch(type)
	{
	case '0':
		p.type = 0;
		return p.str[0];
	case 'Q':
		p.type = 1;
		return p.str[1];
	case 'q':
		p.type = 2;
		return p.str[2];
	}
	return nullptr;
}

int get_num(char *c)
{
	int i;
	place p;

	for(i=0; i<16; i++) if(*c == p.str[1][i]) return i;
	for(i=0; i<16; i++) if(*c == p.str[2][i]) return i;
	for(i=0; i<10; i++)
	{
		if(*c == '1')
		{
			for(int j=0; j<6; j++) if(*(c+1) == p.str[0][j]) return 10+j;
			return 1;
		}
		else if(*c == p.str[0][i]) return i;
	}
	return -1;
}
*/

divans division_answer(int a, int b)
{
	divans c; /*    a / b = c    */

	c.q = a / b;
	c.r = a % b;

	return c;
}

op_num get_operator(std::string str)
{
	op_num s;
	std::string op = "+-*/";

	s.op = 'n';
	for(int i=0; i<op.size(); i++) if(str[0] == op[i]) {s.op = op[i]; break;}

	s.num = s.op == 'n' ? std::stod(&str[0]) : std::stod(&str[1]);

	return s;
}