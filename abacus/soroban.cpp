/*
 *  2026.1.18
 *  soroban.cpp
 *  ver.0.6
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <string>
#include <iostream>
#include <vector>
#include "soroban.hpp"
#include "sorobanframe.hpp"

char EG[] = "./hexsoroban -Q -d -k 15";


void chk_arg(int c, char **v, waku *w)
{
	int k;
	place p;

	p.set_chartype('Q');
	w->set_keta(KETA_M);

	for(int i=1; i<c; i++)
	{
		if(v[i][0] == '-')
		{
			if(v[i][1] == '0' || v[i][1] == 'Q' || v[i][1] == 'q') p.set_chartype(v[i][1]);
			else if(v[i][1] == 'k')
			{
				i++;
				k = std::stoi(v[i]);
				std::cout << k << std::endl;
				if(k>0 && k<16) w->set_keta(k);
				else { std::cout << "-k overflow. Please input 1-15." << std::endl; exit(0); }
			}
			else
			{
				std::cout << "-" << v[i][1] << " : unknown option." << std::endl;
				std::cout << std::endl << "For example > " << EG << std::endl << std::endl;
				exit(0);
			}
		}
	}
	w->make_waku();
}


int main(int argc, char **argv)
{
	std::string s;
	beads b;
	waku w;
	op_num on;


	chk_arg(argc, argv, &w);

	for(;;)
	{
		std::cout << "Input > ";
		std::cin >> s;
		on = get_operator(s);

		b.to_beads((long long int)on.num);
	//	b.to_beads(on.num);
		w.set_beads(b);

		w.print_waku();
	} 

	return 0;
}