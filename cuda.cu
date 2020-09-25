#include <stdio.h>
#include <stdlib.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void MatAdd(float *A, float *B, float *C)
{
	int i = threadIdx.x;
	int j = threadIdx.y;
//	C[i][j] = A[i][j] + B[i][j];
	*(C+i*j) = *(A+i*j) + *(B+i*j);
}

int main(int argc, char *argv[])
{
	float *A, *B, *C;
	int N = 2;
	int i, j;

	cudaMalloc((void**)&A, N*N*sizeof(float));
	cudaMalloc((void**)&B, N*N*sizeof(float));
	cudaMalloc((void**)&C, N*N*sizeof(float));
	float *a = (float *)malloc(N*N*sizeof(float));
	float *b = (float *)malloc(N*N*sizeof(float));
	float *c = (float *)malloc(N*N*sizeof(float));

	for(i=0; i<N; i++){ for(j=0; j<N; j++){ *(a+i*N+j) = (float)random(); *(b+i*N+j) = (float)random(); }}
	cudaMemcpy(A, a, N*N*sizeof(*A), cudaMemcpyHostToDevice);
	cudaMemcpy(B, b, N*N*sizeof(*B), cudaMemcpyHostToDevice);

	int numBlocks = 1;
	dim3 threadsPerBlock(N, N);
	MatAdd<<<numBlocks, threadsPerBlock>>>(A, B, C);

	cudaMemcpy(c, C, N*N*sizeof(*c), cudaMemcpyDeviceToHost);
	for(i=0; i<N; i++){ for(j=0; j<N; j++){ printf("i=%4d, j=%4d :%14.1f +%14.1f =%14.1f :%14.1f\n", i, j, *(a+i*N+j), *(b+i*N+j), *(c+i*N+j), *(a+i*N+j)+*(b+i*N+j)); }}

	cudaFree(A);
	cudaFree(B);
	cudaFree(C);
	free(a);
	free(b);
	free(c);

	return 0;
}
