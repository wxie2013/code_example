#include <iostream>
#include <math.h>
#include <vector>

#define CUDA_ERROR_CHECK
#include "/home/wxie/AI/Spike/July_2019/Spike_July_2019/Spike/Backend/CUDA/Helpers/ErrorCheck.hpp"

using namespace std;

// Kernel function to add the elements of two arrays
__global__
void add(int n, float *x, float *y)
{
	int i = blockIdx.x*blockDim.x + threadIdx.x;
	if(i < n) {
		y[i] = x[i] + y[i];
	}
}


int main(void)
{
	int N = 1<<29; //..not sure why 1<<30 gives out of memory error
    float *d_x = NULL, *d_y = NULL;
    CudaSafeCall(cudaMalloc((void **)&d_x, sizeof(float)*N));
    CudaSafeCall(cudaMalloc((void **)&d_y, sizeof(float)*N));

	// Allocate Unified Memory – accessible from CPU or GPU
    vector<float> vx;
    vector<float> vy;

	// initialize x and y arrays on the host
	for (int i = 0; i < N; i++) {
		vx.push_back(1.0f);
		vy.push_back(2.0f);
	}

    CudaSafeCall(cudaMemcpy(d_x, vx.data(), N*sizeof(float), cudaMemcpyHostToDevice));
    CudaSafeCall(cudaMemcpy(d_y, vy.data(), N*sizeof(float), cudaMemcpyHostToDevice));

    //
    int blockSize;   // The launch configurator returned block size
    int minGridSize; // The minimum grid size needed to achieve the
    // maximum occupancy for a full device launch
    int gridSize;    // The actual grid size needed, based on input size

    cudaOccupancyMaxPotentialBlockSize( &minGridSize, &blockSize, add, 0, N);
    // Round up according to array size
    gridSize = (N + blockSize - 1) / blockSize;

    cout<<"blockSize: "<<blockSize<<" minGridSize: "<<minGridSize<<" gridSize: "<<gridSize<<endl;

    // calculate theoretical occupancy
    int maxActiveBlocks;
    cudaOccupancyMaxActiveBlocksPerMultiprocessor( &maxActiveBlocks, add, blockSize, 0);

    int device;
    cudaDeviceProp props;
    cudaGetDevice(&device);
    cudaGetDeviceProperties(&props, device);

    float occupancy = (maxActiveBlocks * blockSize / props.warpSize) /
        (float)(props.maxThreadsPerMultiProcessor /
                props.warpSize);

    printf("Launched blocks of size %d. Theoretical occupancy: %f\n",
            blockSize, occupancy);


	// Run kernel on 1M elements on the GPU
	add<<<gridSize, blockSize>>>(N, d_x, d_y);

	// Wait for GPU to finish before accessing on host
	CudaCheckError(); //.. defined in SPIKE include cudaDeviceSynchronize()

    //
    float *h_y = NULL;
    //CudaSafeCall(cudaMalloc((void **)&h_y, sizeof(float)*N)); //.. this will core dump. cudaMalloc only apply to device array
    //h_y = new float(N*sizeof(float)); //.. core dump for some reason
    h_y = (float*)malloc(N*sizeof(float));
    CudaSafeCall(cudaMemcpy(h_y, d_y, N*sizeof(float), cudaMemcpyDeviceToHost));
	// Check for errors (all values should be 3.0f)
	float maxError = 0.0f;
	for (int i = 0; i < N; i++) {
		maxError = fmax(maxError, fabs(h_y[i]-3.0f));
	}
	std::cout << "Max error: " << maxError << std::endl;

	// Free memory
	CudaSafeCall(cudaFree(d_x));
	CudaSafeCall(cudaFree(d_y));

	return 0;
}
