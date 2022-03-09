/*
 *  2022.3.8
 *  perceptron.cpp
 *  ver 2.0
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <iostream>
#include <vector>

typedef float IEEE754;
typedef IEEE754 ieee754;
typedef ieee754 fpn; // multi precision floating point number

fpn dot(int n, std::vector<fpn> a, std::vector<fpn> b)
{
	return n ? dot(n-1, a, b) + a[n] * b[n] : 0.0;
}


class perceptron
{
private:
	IEEE754 step(IEEE754 x);
	IEEE754 output(IEEE754 x);

public:

	std::vector<fpn> e;
	std::vector<fpn> w;
	std::vector<fpn> in;
	fpn out;

	std::vector<perceptron *> previous;
	fpn (perceptron::*activation)(fpn);
	std::vector<perceptron *> next;

	perceptron(){}
	perceptron(fpn out){this->out = out;}

	void init(fpn e, fpn w, std::vector<perceptron> &x, std::string function);
	void set_function(std::string function);
	fpn forward();
	void train(perceptron t);
};


IEEE754 perceptron::step(IEEE754 x)
{
	double y = (double)x > 0.0 ? 1.0 : 0.0;
	return (IEEE754)y;
}

IEEE754 perceptron::output(IEEE754 x)
{
	return x;
}

void perceptron::init(fpn e, fpn w, std::vector<perceptron> &x, std::string function)
{
	int n = x.size();

	this->e.resize(n); for(int i=0; i<n; i++) this->e[i] = e;
	this->w.resize(n); for(int i=0; i<n; i++) this->w[i] = w;
	this->in.resize(n); for(int i=0; i<n; i++) this->in[i] = 0.0;

	this->previous.resize(n); for(int i=0; i<n; i++) this->previous[i] = &x[i];
	this->set_function(function);
}

void perceptron::set_function(std::string function)
{
	if(function == "STEP")
	{
		std::cout << "step" << std::endl;
		this->activation = &perceptron::step;
	}
	else if(function == "INPUT")
	{
		this->activation = nullptr;
	}
	else if(function == "OUTPUT")
	{
		this->activation = &perceptron::output;
	}
}

fpn perceptron::forward()
{
	for(int i=0; i<this->in.size(); i++) this->in[i] = this->previous[i]->out;
	this->out = (this->*activation)(dot(this->w.size(), this->in, this->w));

	return this->out;
}

void perceptron::train(perceptron t)
{
	this->forward();
	for(int i=0; i<this->w.size(); i++) this->w[i] += (t.out - this->out) * this->previous[i]->out * this->e[i];
}


#define D_NUM 4
#define W_NUM 3



int main()
{
	std::vector<std::vector<perceptron>> x{{1,0,0}, {1,0,1}, {1,0,1}, {1,1,1}};
	std::vector<std::vector<perceptron>> t{{0,0,0,1}/* AND */, {0,1,1,1}/* OR */, {0,1,1,0}/* XOR */};



	std::vector<perceptron> inlayer(W_NUM);

	perceptron nn;
	nn.init(0.1, 0.0, inlayer, "STEP");



	int tt(2), epoch(10);

	for(int i=0; i<epoch; i++)
	{
		std::cout << "epoch " << i << " : ";
		for(int j=0; j<D_NUM; j++) {for(int k=0; k<W_NUM; k++) inlayer[k].out = x[j][k].out; nn.train(t[tt][j]);}
		for(int j=0; j<W_NUM; j++) std::cout << "w" << j << "=" << nn.w[j] << ",   "; std::cout << std::endl;
	}
	for(int i=0; i<D_NUM; i++) {for(int j=0; j<W_NUM; j++) inlayer[j].out = x[i][j].out; std::cout << nn.forward() << " ";} std::cout << std::endl;

	return 0;
}

/*                     future work
 *  20201206 ver 1.0 : normal version
 *  20220308 ver 2.0 : class version
 *           ver 2.2 : vector is tensor1 version, lambda
 *           ver 3.0 : multi fpn build
 *           ver 3.4 : adapting to half and quarter
 *           ver 4.0 : 
 */