/*
 *  2022.3.12
 *  perceptron.cpp
 *  ver 2.2
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <iostream>
#include <vector>
#include <cmath>

typedef float IEEE754;
typedef IEEE754 ieee754;
typedef ieee754 fpn; // multi precision floating point number


fpn recursive_dot(int n, std::vector<fpn> a, std::vector<fpn> b)
{
	return n ? recursive_dot(n-1, a, b) + a[n] * b[n] : 0.0;
}

auto lambda_dot = [](int n, std::vector<fpn> a, std::vector<fpn> b)
{
	fpn sum = 0.0;
	for(int i=0; i<n; i++) sum += a[i] * b[i];
	return sum;
};

class perceptron
{
private:
	IEEE754 step(IEEE754 x){double y = (double)(x > 0.0 ? 1.0 : 0.0); return (IEEE754)y;}
	IEEE754 relu(IEEE754 x){double y = (double)(x > 0.0 ? x : 0.0); return (IEEE754)y;}
	IEEE754 sigmoid(IEEE754 x){return (IEEE754)(1 / (1 + exp((double)x)) );}
	IEEE754 tan_h(IEEE754 x){return (IEEE754)tanh((double)x);}
	IEEE754 input(IEEE754 x){return (IEEE754)1.0;}
	IEEE754 output(IEEE754 x){return x;}

public:
	std::vector<fpn> lr;
	std::vector<fpn> w;
	std::vector<fpn> in;
	fpn out;

	std::vector<perceptron *> previous;
	fpn (perceptron::*activation)(fpn);
	std::vector<perceptron *> next;

	perceptron(){}
	perceptron(fpn out){this->out = out;}

	void init(fpn lr, fpn w, std::vector<perceptron> &x, std::vector<perceptron> &t, std::string fn);
	void set_function(std::string fn);
	void forward();
	void train();
};


void perceptron::init(fpn lr, fpn w, std::vector<perceptron> &x, std::vector<perceptron> &t, std::string fn)
{
	this->lr.resize(x.size()); for(int i=0; i<x.size(); i++) this->lr[i] = lr;
	this->w.resize(x.size()); for(int i=0; i<x.size(); i++) this->w[i] = w;
	this->in.resize(x.size()); for(int i=0; i<x.size(); i++) this->in[i] = 0.0;

	this->previous.resize(x.size()); for(int i=0; i<x.size(); i++) this->previous[i] = &x[i];
	this->set_function(fn);
	this->next.resize(t.size()); for(int i=0; i<t.size(); i++) this->next[i] = &t[i];
}

void perceptron::set_function(std::string fn)
{
	     if(fn == "STEP") this->activation = &perceptron::step;
	else if(fn == "RELU") this->activation = &perceptron::relu;
	else if(fn == "SIGMOID") this->activation = &perceptron::sigmoid;
	else if(fn == "TANH") this->activation = &perceptron::tan_h;
	else if(fn == "INPUT") this->activation = &perceptron::input;
	else if(fn == "OUTPUT") this->activation = &perceptron::output;
	else this->activation = nullptr;
}

void perceptron::forward()
{
	for(int i=0; i<this->in.size(); i++) this->in[i] = this->previous[i]->out;
	this->out = (this->*activation)(lambda_dot(this->w.size(), this->in, this->w));
//	this->out = (this->*activation)(recursive_dot(this->w.size(), this->in, this->w));
}

void perceptron::train()
{
	this->forward();
	int error(this->next[0]->out - this->out);
	for(int i=0; i<this->w.size(); i++) this->w[i] += error * this->previous[i]->out * this->lr[i];
}




typedef std::vector<std::vector<perceptron>> tensor2;
typedef std::vector<perceptron> tensor1;
typedef std::vector<perceptron> tensor0;

fpn forward(perceptron &nn, std::vector<perceptron> &x)
{
	for(int i=0; i<x.size(); i++) nn.previous[i]->out = x[i].out;
	nn.forward();

	return nn.out;
}

void train(perceptron &nn, std::vector<perceptron> &x, perceptron &t)
{
	for(int i=0; i<x.size(); i++) nn.previous[i]->out = x[i].out;
	nn.next[0]->out = t.out;
	nn.train();
}


#define D_NUM 4
#define W_NUM 3

int main()
{
	tensor2 x{{1,0,0}, {1,0,1}, {1,0,1}, {1,1,1}};
	tensor2 t{{0,0,0,1}/* AND */, {0,1,1,1}/* OR */, {0,1,1,0}/* XOR */};


	tensor1 in_layer(W_NUM);
	tensor0 out_layer(1);

	int teaching_set(0);
	int epoch(10);
	fpn learning_rate(0.1);
	std::string activation_function_name("STEP");



	perceptron nn;
	nn.init(learning_rate, 0.0, in_layer, out_layer, activation_function_name);

	for(int i=0; i<epoch; i++)
	{
		std::cout << "epoch " << i << " : ";
		for(int j=0; j<D_NUM; j++) train(nn, x[j], t[teaching_set][j]);
		for(int j=0; j<W_NUM; j++) std::cout << "w" << j << "=" << nn.w[j] << ",   "; std::cout << std::endl;
	}
	for(int i=0; i<D_NUM; i++) std::cout << forward(nn, x[i]) << " "; std::cout << std::endl;

	return 0;
}

/*                     future work
 *  20201206 ver 1.0 : normal version
 *  20220308 ver 2.0 : class version
 *  20220312 ver 2.2 : vector is tensor1 version, lambda
 *           ver 3.0 : multi fpn build
 *           ver 3.4 : adapting to half and quarter
 *           ver 4.0 : 
 */