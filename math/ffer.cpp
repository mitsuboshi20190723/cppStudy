/*
 *  2022.2.15
 *  ffer.cpp
 *  ver 0.5
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
	std::string stand = "0123456789ABCDEF";
	std::string upper = "QRSTUVWXYZABCDEF";
	std::string lower = "qrstuvwxyzabcdef";
	std::string mbg = "     ";
	int m;

public:
	int multiply;
	int by;
	int get;

	int cal(int m, int b);
	std::string* set_mode(int m);
	int get_num(char *c);
	std::string* print();
};

int multiplication::cal(int m, int b)
{
	this->multiply = m;
	this->by = b;
	this->get = m * b;

	return this->get;
}

std::string* multiplication::set_mode(int m)
{
	this->m = m<0 || m>2 ? 0 : m;
	return &upper;
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

std::string* multiplication::print()
{
	std::string *s;

	switch(this->m)
	{
	case 0:
		std::cout << stand[this->multiply] << stand[this->by] << stand[this->get/16] << stand[this->get%16];
		break;
	case 1:
		std::cout << upper[this->multiply] << upper[this->by] << upper[this->get/16] << upper[this->get%16];
		break;
	case 2:
		std::cout << lower[this->multiply] << lower[this->by] << lower[this->get/16] << lower[this->get%16];
		break;
	}

	return &mbg;
}

multiplication chk_arg(int c, char **v)
{
	int count=0;
	multiplication m;

	m.cal(0, 0);
	m.get = -1;
	m.set_mode(0);

//	std::cout << v[0] << std::endl;

	for(int i=1; i<c; i++)
	{
		if(v[i][0] == '-')
		{
			switch(v[i][1])
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
			switch(count)
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
				h.print();
				std::cout << " ";
			}
			std::cout << std::endl;
		}
	}
	else
	{
		h.print();
		std::cout << std::endl;
	}

//	std::cout << h.multiply << " * " << h.by << " = " << h.get << std::endl;
	return 0;
}
