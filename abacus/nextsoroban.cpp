/*
 *  2022.2.20
 *  nextsoroban.cpp
 *  ver 0.1
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <iostream>

int kekka(int b, int a, int *c)
{
	int bu, bd, au, ad, count(0);

	bu = b / 4; bd = b % 4;
	au = a / 4; ad = a % 4;

	if(a ^ b)
	{
		if(a > b)
		{
			if(ad > bd)
			{
				if(au - bu) c[count++] = 4 + au;
				c[count++] = ad;
			}
			else
			{
				if(au - bu) c[count++] = 4 + au;
				if(ad - bd) c[count++] = ad;
			}
		}
		else
		{
			if(ad > bd)
			{
				if(au - bu) c[count++] = 4 + au;
				c[count++] = ad;
			}
			else
			{
				if(au - bu) c[count++] = 4 + au;
				if(ad - bd) c[count++] = ad;
			}
			c[count++] = 80;
		}
	}
	c[count] = -1;

	return a-b < 0 ? 16 + a-b : a-b;
}

char i2c(int n)
{
	std::string str = "QRSTUVWXYZABCDEF";
	return str[n];
}

int bao() /*Bets are off*/
{
//	int i;
//	for(i=0; i<MAX7KETA; i++) ss[i] = ZERO;
//	keta = 0;
	return(0);
}

int main(int argc, char **argv)
{
	int i, j, k;
	int a[10];

	/* chk_arg */
//	if(argv[1] == NULL) a = '0'; else a = *argv[1];


	for(i=0; i<16; i++)
	{
		for(j=0; j<16; j++)
		{
			std::cout << i2c(kekka(i, j, a)) << " : " << i2c(i) << " -> " << i2c(j) << " ( ";
			for(k=0; !(a[k]<0); k++) std::cout << a[k] << " ";
			std::cout << ")" << std::endl;
		}
	}
	return 0;
}
