/*
 *  2022.2.18
 *  gauss.c
 *  ver 1.0
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <stdio.h>
#include <math.h>


double deviation_v(double t, double m)
{
	return( 50 + (t - m) / 2 );
}

double normdist(double dv, double m, double s)
{
	double i, y;

	i = -pow((dv - m), 2) / (2 * pow(s, 2));
	y = exp(i) / sqrt(2 * M_PI * pow(s, 2));

	return(y);
}

double inormdistc(double dv, double m, double s)
{
	double i, y;

	i = (dv - m) / sqrt(2 * pow(s, 2));
	y = 1 - (1 + erf(i)) / 2;

	return(y);
}


int main()
{
	FILE *fout;
	char *outfname = "gauss-order.csv";
	int i;
	double n, in;

	fout = fopen(outfname, "w");

	fprintf(fout, "\n---gauss---mean=50--sigma=10---\n");
	for (i=0; i<100; i++)
	{
		n = normdist((double)i,50,10);
		in = inormdistc((double)i,50,10);
		fprintf(fout, "%2d, %f, %f\n", i, n, in);
	}

	fclose(fout);

	return(0);
}
