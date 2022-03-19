/*
 *  2022.3.18
 *  sorobanframe.hpp
 *  ver 1.0
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef SOROBANFRAME_HPP
#define SOROBANFRAME_HPP

#include "soroban.hpp"

#define KETA_M 15
#define KETA_W 4

class waku
{
private:
	static std::string tama[4];

	char waku[8+4][KETA_M*KETA_W+2];
	int keta = KETA_M;

public:
	int make_waku();
	int print_waku();
	int set_keta(int k);
	int set_place(place p);
	int set_beads(beads b);
};

#endif /* SOROBANFRAME_HPP */