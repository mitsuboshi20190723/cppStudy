/*
 *  2026.1.19
 *  sorobanlib.cpp
 *  ver.0.3
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <string>
#include <iostream>
#include "soroban.hpp"
#include "sorobanframe.hpp"


divans division_answer(int a, int b)
{
	divans c; /*    a / b = c    */

	c.q = a / b;
	c.r = a % b;

	return c;
}

bool number4soroban(std::string number)
{
	if(number == "exit" || number == "quit") return 0;
	else return 1;
}

op_num get_operator(std::string on)
{
	op_num s;

	std::string bao[] = {"O", "bao", "BAO", "Bets are off", "bets are off"};
	std::string op = "+-*/";

	for(std::string each: bao) if(on == each) { s.op = bao[1][0]; s.num = 0; return s; }

	s.op = 'n';
	for(int i=0; i<op.size(); i++) if(on[0] == op[i]) { s.op = op[i]; break; }
//	s.num = s.op == 'n' ? std::stod(&on[0]) : std::stod(&on[1]);

	if(number4soroban(&on[s.op!='n'])) { s.num = std::stod(&on[s.op!='n']); return s; }
	else { s.op = 'q'; s.num = 0; return s; }
}