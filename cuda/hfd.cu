/*
 *  2023.11.21
 *  hfd.cu
 *  ver.0.5
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <iostream>
#include <string>
#include <vector>
#include <cuda_fp16.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "timer.h"


/*
__global__ void but_sum_gpu(double *v, double *sum)
{
	int l = threadIdx.x;

	for(long i=0; i<v.size(); i++)
	{
		*sum += v[i];
	}
//error	std::cout << "sum=" << *sum << std::endl; in __global__ function.
}

void sum(std::vector<half> v)
{
	for(long i=0; i<v.size(); i++)
	{
		v[0] += v[i+1];
	}
}
*/


int main(int argc, char **argv)
{
	int *gpu;
	long l, len(10000);
	
	half h; std::vector<half> vh(len,1);
	float f; std::vector<float> vf(len,1);
	double d; std::vector<double> vd(len,1);

	if(argc == 1) h=f=d=0.0;
	else
	{
		if(/*std::isdigit(argv[1])*/ 1 == 0) h=f=d=0.0;
		else
		{
			h = (half)std::stof(argv[1]);
			f = std::stof(argv[1]);
			d = std::stod(argv[1]);
		}
	}


	std::cout << "size of half   : " << sizeof(half) << std::endl;
TIMER_START
//	for(l=0; l<vh.size(); l++) h = h + vh[l];
TIMER_STOP
	std::cout << std::endl;

	std::cout << "size of float  : " << sizeof(float) << std::endl;
TIMER_START
	for(l=0; l<vf.size(); l++) f += vf[l];
TIMER_STOP
	std::cout << std::endl;

	std::cout << "size of double : " << sizeof(double) << std::endl;
TIMER_START
	for(l=0; l<vd.size(); l++) d += vd[l];
TIMER_STOP
	std::cout << std::endl;


	cudaMalloc((void**)&gpu, len*sizeof(double));
/*
	cudaMemcpy(gpu, vd, len*sizeof(double), cudaMemcpyHostToDevice);

//error	but_sum_gpu<<<int numBlocks(1), dim3 threadsPerBlock(2, 2)>>>(gpu, ans); inisialize in <<< >>>>.
	dim3 BPG(1, 1); dim3 TPB(R, C); but_sum_gpu<<<BPG, TPB>>>(gpu, ans);

	cudaMemcpy(vd, gpu, len*sizeof(double), cudaMemcpyDeviceToHost);
*/
	cudaFree(gpu);

	return 0;
}
