/*
 *  2022.3.6
 *  perceptron.cpp
 *  ver 1.0
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <iostream>

typedef float IEEE754;
typedef IEEE754 ieee754;
typedef ieee754 fpn;


IEEE754 dot(IEEE754 *v1, IEEE754 *v2, int len)
{
	IEEE754 sum = 0.0;
	for(int i=0; i<len; i++) sum += v1[i] * v2[i];
	return sum;
}

ieee754 step(ieee754 v)
{
	return v>0 ? 1 : 0;
}

fpn forward(fpn *x, fpn *w, int len)
{
	fpn u = dot(x, w, len);
	return step(u);
}

void train(fpn *w, fpn *x, fpn t, fpn e, int len)
{
	fpn z = forward(x, w, len);
	for(int i=0; i<len; i++) w[i] += (t-z) * x[i] * e;
}


#define D_NUM 4
#define W_NUM 3

int main()
{
	fpn e=0.1;
	fpn w[D_NUM] = {0, 0, 0};

	IEEE754 x[D_NUM][W_NUM] = {{1,0,0}, {1,0,1}, {1,0,1}, {1,1,1}};

//	ieee754 t[D_NUM] = {0, 0, 0, 1}; /* AND */
//	ieee754 t[D_NUM] = {0, 1, 1, 1}; /* OR */
	ieee754 t[D_NUM] = {0, 1, 1, 0}; /* XOR */

	int epoch = 10;
	for(int i=0; i<epoch; i++)
	{
		std::cout << "epoch : " << i << " ";
		for(int j=0; j<D_NUM; j++) train(w, x[j], t[j], e, W_NUM);
		for(int j=0; j<W_NUM; j++) std::cout << "w" << j << ":" << w[j] << " ";
		std::cout << std::endl;
	}
	for(int i=0; i<D_NUM; i++) std::cout << forward(x[i], w, W_NUM) << " ";
	std::cout << std::endl;

	return 0;
}

/*                     future work
 *  20201206 ver 1.0 : normal version
 *           ver 2.0 : class version
 *           ver 2.2 : vector is tensor1 version
 *           ver 3.0 : multi fpn build
 *           ver 3.4 : adapting to half and quarter
 *           ver 4.0 : 
 */