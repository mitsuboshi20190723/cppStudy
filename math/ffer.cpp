/*
 *  2022.2.20
 *  ffer.cpp
 *  ver 1.0
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

// g++ -o ffer ffer.cpp
// ffer -Q

#include <iostream>
#include <string>

class multiplication
{
private:
	static int mode;
	static std::string stand;
	static std::string upper;
	static std::string lower;
	static std::string *sp[3];

public:
	int multiply;
	int by;
	int get;
	std::string mbg = "     "; /* mbg("     ")  or  mbg(5, ' ') */

	int cal(int m, int b);
	std::string print();
	std::string set_mode(int m);
	int get_num(char *c);
};

int multiplication::mode = 0;
std::string multiplication::stand = "0123456789ABCDEF"; /* mode==0 */
std::string multiplication::upper = "QRSTUVWXYZABCDEF"; /* mode==1 */
std::string multiplication::lower = "qrstuvwxyzabcdef"; /* mode==2 */
std::string *multiplication::sp[3] = {&stand, &upper, &lower};

int multiplication::cal(int m, int b)
{
	this->multiply = m;
	this->by = b;
	this->get = m * b;

	return this->get;
}

std::string multiplication::print()
{
	std::string str(*this->sp[this->mode]);

	this->mbg[0] = str[this->multiply];
	this->mbg[1] = str[this->by];
	this->mbg[2] = str[this->get/16];
	this->mbg[3] = str[this->get%16];
	this->mbg[4] = '\0';

	return this->mbg;
}

std::string multiplication::set_mode(int m)
{
	this->mode = m<0 || m>2 ? 0 : m;

	return *this->sp[this->mode];
}

int multiplication::get_num(char *c)
{
	for(int i=0; i<16; i++) if(*c == upper[i]) return i;
	for(int i=0; i<16; i++) if(*c == lower[i]) return i;
	for(int i=0; i<10; i++)
	{
		if(*c == '1')
		{
			for(int j=0; j<6; j++) if(*(c+1) == stand[j]) return 10+j;
			return 1;
		}
		else if(*c == stand[i]) return i;
	}
	return -1;
}


multiplication chk_arg(int c, char **v)
{
	int count = 0;
	multiplication m;

	m.cal(0, 0);
	m.get = -1;

//	std::cout << v[0] << std::endl;

	for(int i=1; i<c; i++)
	{
		if(v[i][0] == '-')
		{
			switch( v[i][1] )
			{
			case '0':
				m.set_mode(0);
				break;
			case 'Q':
				m.set_mode(1);
				break;
			case 'q':
				m.set_mode(2);
				break;
			default:
				std::cout << "-" << v[i][1] << " : unknown option." << std::endl;
				exit(0);
			}
		}
		else
		{
			m.get = m.get_num(v[i]);
			if(m.get < 0){std::cout << "Not number found." << std::endl; exit(0);}
			switch( count )
			{
			case 0:
				m.multiply = m.get;
				break;
			case 1:
				m.by = m.get;
				m.cal(m.multiply, m.by);
				break;
			}
			count++;
		}
	}
	if(count==1 || count>2){std::cout << count << "Need 2 numbers." << std::endl; exit(0);};

	return m;
}


int main(int argc, char **argv)
{
	multiplication h;
	int m, b;

	h = chk_arg(argc, argv);

	if(h.get < 0)
	{
		for(m=1; m<16; m++)
		{
			for(b=1; b<16; b++)
			{
				h.cal(m, b);
				std::cout << h.print() << " ";
			}
			std::cout << std::endl;
		}
	}
	else
	{
		std::cout << h.print() << std::endl;
	}

	return 0;
}
