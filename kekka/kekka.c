#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SUBJECT_MAX 20
#define NUM 185

struct subject {
	char name[50];
	int tokuten;
	double mean;
	double deviation;
	double order_d;
	int order_i;
};

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
	FILE *fin, *fout;
	char *infname = "kekka.csv", *outfname = "kekka.out.csv";
	char tokuten_c[5], mean_c[5];
	int i, s_num, end_of_file;
	struct subject ss[SUBJECT_MAX+1], *ss_total;

	fin = fopen(infname, "r");

	s_num = 0;
    end_of_file = 0;

	while ( 1 ) {
        end_of_file = fscanf(fin, "%[^,],%[^,],%s", ss[s_num].name, tokuten_c, mean_c);
        if (end_of_file != 3) break;
		ss[s_num].tokuten = atoi(tokuten_c);
		ss[s_num].mean = (double)atof(mean_c);
		printf("%d:%d, %f, %d\n", s_num, ss[s_num].tokuten, ss[s_num].mean, end_of_file);
		s_num++;
	}

    fclose(fin);


	for (i=0; i<s_num; i++) {
		ss[i].deviation = deviation_v((double)ss[i].tokuten, ss[i].mean);
		ss[i].order_d = inormdistc(ss[i].deviation, 50, 10);
		ss[i].order_i = (int)(ss[i].order_d * NUM);
        if (ss[i].order_i == 0) ss[i].order_i = 1;
	}

    ss_total = &ss[s_num];
    strcpy(ss_total->name, "TOTAL");
    ss_total->tokuten = ss_total->mean = 0;
	for (i=0; i<s_num; i++) { ss_total->tokuten += ss[i].tokuten; ss_total->mean += ss[i].mean; }
	ss_total->deviation = deviation_v(((double)ss_total->tokuten) / s_num, ss_total->mean / s_num);
	ss_total->order_d = inormdistc(ss_total->deviation, 50, 10);
	ss_total->order_i = (int)(ss_total->order_d * NUM);
    if (ss_total->order_i == 0) ss_total->order_i = 1;


	fout = fopen(outfname, "w");

	for (i=0; i<s_num+1; i++) {
        if (i == s_num) fprintf(fout, "\n\n");
		fprintf(fout, "%s,", ss[i].name);
		fprintf(fout, "%d,", ss[i].tokuten);
		fprintf(fout, "%.1f,", ss[i].mean);
		fprintf(fout, "%.2f,", ss[i].deviation);
		fprintf(fout, "%.1f,", ss[i].order_d * 100);
		fprintf(fout, "%d", ss[i].order_i);
	}
/*
	fprintf(fout, "\n---gauss---mean=50--sigma=10---\n");
	for (i=0; i<100; i++) { fprintf(fout, "%2d, %f, %f\n", i, normdist((double)i,50,10), inormdistc((double)i,50,10)); }
*/
	fclose(fout);


	return(0);
}
