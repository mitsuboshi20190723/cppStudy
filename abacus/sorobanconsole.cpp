/*
 *  2026.1.24
 *  sorobanconsole.cpp
 *  ver.1.1
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <string>
#include <iostream>
#include <thread> // for sleep
#include "sorobanframe.hpp"


std::string waku::tama[4] = {"  |  <-> <-> <->", " <->  |  <-> <->", " <-> <->  |  <->", " <-> <-> <->  | "};
// std::string waku::tama[4] = {"  |  <|> <|> <|>", " <|>  |  <|> <|>", " <|> <|>  |  <|>", " <|> <|> <|>  | "};

int waku::make_waku()
{
	int i, j;
	
	for(i=0; i<KETA_W*this->keta+1; i++) this->waku[0][i] = '-'; this->waku[0][i] = '\n';
	for(i=0; i<this->keta; i++) for(j=0; j<KETA_W; j++) this->waku[1][i*KETA_W+j] = this->tama[3][j]; this->waku[1][KETA_W*this->keta] = ' '; this->waku[1][KETA_W*this->keta+1] = '\n';
	for(i=0; i<this->keta; i++) for(j=0; j<KETA_W; j++) this->waku[2][i*KETA_W+j] = this->tama[3][j+4]; this->waku[2][KETA_W*this->keta] = ' '; this->waku[2][KETA_W*this->keta+1] = '\n';
	for(i=0; i<this->keta; i++) for(j=0; j<KETA_W; j++) this->waku[3][i*KETA_W+j] = this->tama[3][j+8]; this->waku[3][KETA_W*this->keta] = ' '; this->waku[3][KETA_W*this->keta+1] = '\n';
	for(i=0; i<this->keta; i++) for(j=0; j<KETA_W; j++) this->waku[4][i*KETA_W+j] = this->tama[3][j+12]; this->waku[4][KETA_W*this->keta] = ' '; this->waku[4][KETA_W*this->keta+1] = '\n';
	for(i=0; i<KETA_W*this->keta/2; i++) this->waku[5][i] = '-'; this->waku[5][i] = '.'; for(j=i+1; j<KETA_W*this->keta+1; j++) this->waku[5][j] = '-'; this->waku[5][j] = '\n';
	for(i=0; i<this->keta; i++) for(j=0; j<KETA_W; j++) this->waku[6][i*KETA_W+j] = this->tama[0][j]; this->waku[6][KETA_W*this->keta] = ' '; this->waku[6][KETA_W*this->keta+1] = '\n';
	for(i=0; i<this->keta; i++) for(j=0; j<KETA_W; j++) this->waku[7][i*KETA_W+j] = this->tama[0][j+4]; this->waku[7][KETA_W*this->keta] = ' '; this->waku[7][KETA_W*this->keta+1] = '\n';
	for(i=0; i<this->keta; i++) for(j=0; j<KETA_W; j++) this->waku[8][i*KETA_W+j] = this->tama[0][j+8]; this->waku[8][KETA_W*this->keta] = ' '; this->waku[8][KETA_W*this->keta+1] = '\n';
	for(i=0; i<this->keta; i++) for(j=0; j<KETA_W; j++) this->waku[9][i*KETA_W+j] = this->tama[0][j+12]; this->waku[9][KETA_W*this->keta] = ' '; this->waku[9][KETA_W*this->keta+1] = '\n';
	for(i=0; i<KETA_W*this->keta+1; i++) this->waku[10][i] = '-'; this->waku[10][i] = '\n';
	for(i=0; i<KETA_W*this->keta+1; i++) this->waku[11][i] = ' '; this->waku[11][i] = '\n';

	return i+1;
}

int waku::print_waku()
{
	std::cout << "\033[2J";
	for(int i=0; i<12; i++) for(int j=0; j<KETA_W*this->keta+2; j++) std::cout << this->waku[i][j];

	return 0;
}

int waku::set_keta(int k)
{
	if(k<0 || k>KETA_M) return -1;
	this->keta = k=0 ? KETA_M : k+(k%2==0);
	return this->keta;
}

int waku::set_place(place p)
{
	int i, j, k;

	k = this->keta/2 - p.i;
	for(i=0; i<4; i++) for(j=0; j<KETA_W; j++) this->waku[4-i][j+k*KETA_W] = this->tama[p.n/4][i*KETA_W+j];
	for(i=0; i<4; i++) for(j=0; j<KETA_W; j++) this->waku[i+6][j+k*KETA_W] = this->tama[p.n%4][i*KETA_W+j];
	this->waku[11][k*KETA_W+2] = p.c;

	return p.n;
}

int waku::set_beads(beads b)
{
	for(int i=0; i<b.p.size(); i++) set_place(b.p[i]);
	return b.p.size();
}