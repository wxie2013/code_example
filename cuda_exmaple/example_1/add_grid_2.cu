#include <iostream>
#include <math.h>

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
	int N = 1<<30;
	float *x, *y;

	// Allocate Unified Memory – accessible from CPU or GPU
	cudaMallocManaged(&x, N*sizeof(float));
	cudaMallocManaged(&y, N*sizeof(float));

	// initialize x and y arrays on the host
	for (int i = 0; i < N; i++) {
		x[i] = 1.0f;
		y[i] = 2.0f;
	}

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
	add<<<gridSize, blockSize>>>(N, x, y);

	// Wait for GPU to finish before accessing on host
	cudaDeviceSynchronize();

	// Check for errors (all values should be 3.0f)
	float maxError = 0.0f;
	for (int i = 0; i < N; i++) {
		maxError = fmax(maxError, fabs(y[i]-3.0f));
	}
	std::cout << "Max error: " << maxError << std::endl;

	// Free memory
	cudaFree(x);
	cudaFree(y);

	return 0;
}

