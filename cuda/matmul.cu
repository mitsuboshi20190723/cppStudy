/*
 *  2023.11.19
 *  matmul.cu
 *  ver.0.7
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <iostream>
#include <random>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "timer.h"

class matrix
{
public:
	int row; /* Gyou */
	int col; /* Retsu */
	float *mat;
};


__global__ void mat_mul_0(matrix a, matrix b, matrix c)
{
	int row = threadIdx.x;
	int col = threadIdx.y;

	float sum = (float)0;
	for(int i=0; i<a.col; i++) sum += a.mat[row*a.col+i] * b.mat[i*b.row+col];
	c.mat[row*c.col+col] = sum;

	printf("row=%d, col=%d : %f\n", row, col, sum);
}

#define INNER_PRODUCT c.mat[row*c.col+col]=0; for(int i=0; i<a.col; i++) c.mat[row*c.col+col] += a.mat[row*a.col+i] * b.mat[i*b.row+col];

__global__ void mat_mul_gpu(matrix a, matrix b, matrix c)
{
	int row = threadIdx.x;
	int col = threadIdx.y;

	INNER_PRODUCT
}

void mat_mul_cpu(matrix a, matrix b, matrix c)
{
	for(int col=0; col<a.col; col++)
	{
		for(int row=0; row<b.row; row++)
		{
			INNER_PRODUCT
		}
	}
}

void set_matrix(matrix m)
{
	int i, j;

	std::random_device rnd;
	std::uniform_real_distribution<> r1(0, 1);
	for(i=0; i<m.col; i++) for(j=0; j<m.row; j++) m.mat[i*m.col+j] = (float)r1(rnd);
}

void get_matrix(matrix m)
{
	int i, j;
	for(i=0; i<m.col; i++)
	{
		for(j=0; j<m.row; j++)
		{
			std::cout << *(m.mat + i*m.col + j) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int chk_arg(int argc, char **argv, int *r, int *d, int *c, int *gpu, int *cpu, int *print)
{
	int count = 0, num = 0;

	for(int i=1; i<argc; i++)
	{
		if(argv[i][0] == '-')
		{
			switch( argv[i][1] )
			{
			case 'g':
				*cpu = 0;
				break;
			case 'c':
				*gpu = 0;
				break;
			case 'p':
				*print = 1;
				break;
			default:
				std::cout << "-" << argv[i][1] << " : unknown option." << std::endl;
				exit(0);
			}
		}
		else
		{
			num = atoi(argv[i]);
			if(num > 0)
			{ 
				switch( count )
				{
				case 0:
					*r = atoi(argv[i]);
					break;
				case 1:
					*d = atoi(argv[i]);
					break;
				case 2:
					*c = atoi(argv[i]);
					break;
				}
				count++;
			}
			else
			{
				std::cout << "-" << argv[i] << " is but number." << std::endl;
				exit(0);
			}
		}
	}
	return count;
}

int main(int argc, char **argv)
{
	matrix a, b, c; /* for CPU */
	matrix d_a, d_b, d_c; /* for GPU */
	int R(1), D(1), C(1), GPU(1), CPU(1), PRINT(0);

	chk_arg(argc, argv, &R, &D, &C, &GPU, &CPU, &PRINT);


	a.row = c.row = R;
	a.col = b.row = D;
	b.col = c.col = C;

	d_a.row = a.row; d_a.col = a.col;
	d_b.row = b.row; d_b.col = b.col;
	d_c.row = c.row; d_c.col = c.col;

	cudaMalloc((void**)&d_a.mat, d_a.row*d_a.col*sizeof(float));
	cudaMalloc((void**)&d_b.mat, d_b.row*d_b.col*sizeof(float));
	cudaMalloc((void**)&d_c.mat, d_c.row*d_c.col*sizeof(float));
	a.mat = new float[a.row*a.col];
	b.mat = new float[b.row*b.col];
	c.mat = new float[c.row*c.col];

	std::cout << "Matrix a (" << a.row << " rows, " << a.col << " columns)" << std::endl;
	set_matrix(a); if(PRINT) get_matrix(a);
	std::cout << "Matrix b (" << b.row << " rows, " << b.col << " columns)" << std::endl;
	set_matrix(b); if(PRINT) get_matrix(b);

	if(GPU)
	{
		std::cout << "\n----- GPU -----" << std::endl;

TIMER_START
		cudaMemcpy(d_a.mat, a.mat, a.row*a.col*sizeof(float), cudaMemcpyHostToDevice);
		cudaMemcpy(d_b.mat, b.mat, b.row*b.col*sizeof(float), cudaMemcpyHostToDevice);
		dim3 BPG(1, 1); dim3 TPB(R, C); mat_mul_gpu<<<BPG, TPB>>>(d_a, d_b, d_c);
		cudaMemcpy(c.mat, d_c.mat, d_c.row*d_c.col*sizeof(float), cudaMemcpyDeviceToHost);
TIMER_STOP

		std::cout << "Matrix c=a*b (" << c.row << "rows, " << c.col << "columns)" << std::endl;
		if(PRINT) get_matrix(c);
	}


	if(CPU)
	{
		std::cout << "\n----- CPU -----" << std::endl;
TIMER_START
		mat_mul_cpu(a, b, c);
TIMER_STOP
		std::cout << "Matrix c=a*b (" << c.row << "rows, " << c.col << "columns)" << std::endl;
		if(PRINT) get_matrix(c);
	}


	cudaFree(d_a.mat);
	cudaFree(d_b.mat);
	cudaFree(d_c.mat);
	delete[] a.mat;
	delete[] b.mat;
	delete[] c.mat;

	return 0;
}
