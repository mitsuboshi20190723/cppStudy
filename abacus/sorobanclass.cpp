/*
 *  2022.3.19
 *  sorobanclass.cpp
 *  ver 0.2
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <string>
#include <iostream>
#include "soroban.hpp"



std::string place::str[3] = {"0123456789ABCDEF", "QRSTUVWXYZABCDEF", "qrstuvwxyzabcdef"};
int place::type = -1;

std::string place::set_chartype(char type)
{
	switch(type)
	{
	case '0':
		this->type = 0;
		return this->str[0];
	case 'Q':
		this->type = 1;
		return this->str[1];
	case 'q':
		this->type = 2;
		return this->str[2];
	}
	return nullptr;
}

int place::set_num(int n)
{
	if(n<0 || n>0xF) return -1;

//	this->old = this->n;
	this->n = n;
	this->c = this->str[this->type][n];

	return this->n;

}

int place::get_num(char *c)
{
	int i;

	for(i=0; i<16; i++) if(*c == this->str[1][i]) return i;
	for(i=0; i<16; i++) if(*c == this->str[2][i]) return i;
	for(i=0; i<10; i++)
	{
		if(*c == '1')
		{
			for(int j=0; j<6; j++) if(*(c+1) == this->str[0][j]) return 10+j;
			return 1;
		}
		else if(*c == this->str[0][i]) return i;
	}
	return -1;
}



int beads::to_beads(long long int n)
{
	int i, k(0);

	int h[sizeof(long long int)];
	do
	{
		h[k] = (int)(n % 16);
		n /= 16;
		k++;
	}
	while(n);

	this->p.clear();
	this->p.resize(k);
	
	for(i=0; i<k; i++)
	{
		this->p[i].i = k-1-i;
		this->p[i].set_num(h[k-1-i]);
	}

	return k;
}

int beads::to_beads(double n)
{
	union {double d; uint64_t u;} u;
	u.d = n;

	int sign = (int)((u.u >> (64-1)) & 1);
	int exponent = (int)((u.u >> (64-1-11)) & 0x7FF);
	uint64_t fraction = u.u & 0xFFFFFFFFFFFFF;

	if(sign < 0) std::cout << "num error" << std::endl; //////////////////

	int k = this->to_beads((long long int)fraction);
	for(int i=0; i<k; i++) this->p[i].i = this->p[i].i + exponent;

	return k;
}

int beads::zero()
{
	int count(0), a(0)/*add*/, d(0)/*del*/;
	place z;

	z.set_num(0);

	count = this->p.size();
	if(!count){this->to_beads((double)0); return 1;}
	for(int i=1; i<count; i++)
	{
		if(this->p[i-1].i - 1 != this->p[i].i)
		{
			int s = this->p[i-1].i;
			int e = this->p[i].i;
			for(int j=0; j<s-e; j++)
			{
				z.i = s-i;
				this->p.insert(this->p.begin() + i + j, z);
			}
		}
	}

	if(this->p[0].i > 0)
	{
		for(int i=0; i<this->p[0].i; i++)
		{
			if(i < this->p.size()) if(this->p[i].n == 0) d++;
			else a = this->p[0].i - this->p.size();
		}
		for(int i=0; i<d; i++) this->p.erase(this->p.begin());
		count = this->p.end()[0].i;
		for(int i=0; i<a; i++)
		{
			z.i = count - i;
			this->p.push_back(z);
		}
	}
	else
	{
		a -= this->p[0].i;
		for(int i=0; i<this->p.size(); i++)
		{
			if(this->p[i].n == 0) d++;
			else d = 0;
		}
		for(int i=0; i<d; i++) this->p.erase(this->p.end() - 1);
		for(int i=0; i<a; i++)
		{
			z.i = -i;
			this->p.insert(this->p.begin(), z);
		}
	}

	for(count=1; count<this->p.size(); count++)
	{
		if(this->p[count-1].i-1 != this->p[count].i) break;
	}
	if(count != this->p.size()) std::cout << "ZERO ERROR !" << std::endl; ///////////////

	return count;
}