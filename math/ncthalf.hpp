/*
 *  2022.3.20
 *  ncthalf.hpp
 *  ver 2.0
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

/*
 *  long double                                                1 + 15 + 112 = 128bits
 *  double                                                     1 + 11 + 52  = 64bits
 *  float        +###/####/#___/____/____/____/____/____       1 + 8  + 23  = 32bits
 *  half         +###/##__/____/____                           1 + 5  + 10  = 16bits
 *  quarter      +###/____                                     1 + 3  + 4   = 8bits(1byte)
 */

#include <iostream>
#include <cstdint>


class half
{
private:

	uint16_t _;

	half f2h(float n)
	{
		half h;
		uint32_t *u;
		u = (uint32_t *)&n;

		if(n == 0) h._ = (uint16_t)(*u >> 16);
		else
		{
			uint16_t     sign((*u >> 16) & 0x8000);
			uint16_t exponent((((*u >> 23) - 127 + 15) & 0x1f) << 10);
			uint16_t fraction((*u >> (23 - 10)) & 0x3ff);
			h._ = sign | exponent | fraction;
		}

		return h;
	}

	float h2f(half h)
	{
		float *n;
		uint32_t f;

		if(h._ == 0 || h._ == 0x8000) f = h._ << 16;
		else
		{
			uint32_t     sign((h._ & 0x8000) << 16);
			uint32_t exponent(((((h._ >> 10) & 0x1f) - 15 + 127) & 0xff) << 23);
			uint32_t fraction((h._ & 0x3ff) << (23 - 10));
			f = sign | exponent | fraction;
		}

		n = (float *)&f;
		return *n;
	}

public:
	half(){}
	half(float n){*this = f2h(n);}
	half(double n){*this = f2h((float)n);}
	half(int n){*this = f2h((float)n);}

	operator float(){return h2f(*this);}

	half operator =(half rhs){this->_ = rhs._; return *this;}
	half operator -(){return half(-h2f(*this));}

	half operator +=(half rhs){*this = f2h(h2f(*this) + h2f(rhs)); return *this;}
	half operator -=(half rhs){*this = f2h(h2f(*this) - h2f(rhs)); return *this;}
	half operator *=(half rhs){*this = f2h(h2f(*this) * h2f(rhs)); return *this;}
	half operator /=(half rhs){*this = f2h(h2f(*this) / h2f(rhs)); return *this;}
	half operator +(half rhs){half h(h2f(*this) + h2f(rhs)); return h;}
	half operator -(half rhs){half h(h2f(*this) - h2f(rhs)); return h;}
	half operator *(half rhs){half h(h2f(*this) * h2f(rhs)); return h;}
	half operator /(half rhs){half h(h2f(*this) / h2f(rhs)); return h;}

	bool operator ==(half rhs){return this->_ == rhs._;}
	bool operator ==(double rhs){half h(rhs); return this->_ == h._;}
	bool operator ==(int rhs){half h(rhs); return this->_ == h._;}
	bool operator !=(half rhs){return !(*this == rhs);}

	float operator !(){return (float)(*this);}
};

class quarter
{
private:

	uint8_t _;

	quarter f2q(float n)
	{
		quarter q;
		uint32_t *u;
		u = (uint32_t *)&n;

		if(n == 0) q._ = (uint8_t)(*u >> 24);
		else
		{
			uint8_t     sign((*u >> 24) & 0x80);
			uint8_t exponent((((*u >> 23) - 127 + 3) & 0x7) << 4);
			uint8_t fraction((*u >> (23 - 4)) & 0xf);
			q._ = sign | exponent | fraction;
		}

		return q;
	}

	float q2f(quarter q)
	{
		float *n;
		uint32_t f;

		if(q._ == 0 || q._ == 0x80) f = q._ << 24;
		else
		{
			uint32_t     sign((q._ & 0x80) << 24);
			uint32_t exponent(((((q._ >> 4) & 0x7) - 3 + 127) & 0xff) << 23);
			uint32_t fraction((q._ & 0xf) << (23 - 4));
			f = sign | exponent | fraction;
		}

		n = (float *)&f;
		return *n;
	}

public:
	quarter(){}
	quarter(float n){*this = f2q(n);}
	quarter(double n){*this = f2q((float)n);}
	quarter(int n){*this = f2q((float)n);}

	operator float(){return q2f(*this);}

	quarter operator =(quarter rhs){this->_ = rhs._; return *this;}
	quarter operator -(){return quarter(-q2f(*this));}

	quarter operator +=(quarter rhs){*this = f2q(q2f(*this) + q2f(rhs)); return *this;}
	quarter operator -=(quarter rhs){*this = f2q(q2f(*this) - q2f(rhs)); return *this;}
	quarter operator *=(quarter rhs){*this = f2q(q2f(*this) * q2f(rhs)); return *this;}
	quarter operator /=(quarter rhs){*this = f2q(q2f(*this) / q2f(rhs)); return *this;}
	quarter operator +(quarter rhs){quarter q(q2f(*this) + q2f(rhs)); return q;}
	quarter operator -(quarter rhs){quarter q(q2f(*this) - q2f(rhs)); return q;}
	quarter operator *(quarter rhs){quarter q(q2f(*this) * q2f(rhs)); return q;}
	quarter operator /(quarter rhs){quarter q(q2f(*this) / q2f(rhs)); return q;}

	bool operator ==(quarter rhs){return this->_ == rhs._;}
	bool operator ==(double rhs){quarter q(rhs); return this->_ == q._;}
	bool operator ==(int rhs){quarter q(rhs); return this->_ == q._;}
	bool operator !=(quarter rhs){return !(*this == rhs);}

	float operator !(){return (float)(*this);}
};


void com(double n, int ln, int le, std::string str)
{
	std::cout << str << n << " : ";
	for(int i=0; i<ln; i++) std::cout << ((uint64_t)n >> ln-1-i)%2 << (i==0 || i==le ? "/" : " ");
	std::cout << std::endl;
}

void show(double n, std::string str="In function"){com((double)n, 64, 11, str);}
void show(float n, std::string str="In function"){com((double)n, 32, 8, str);}
void show(half n, std::string str="In function"){com((double)n, 16, 5, str);}
void show(quarter n, std::string str="In function"){com((double)n, 8, 3, str);}

