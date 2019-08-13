// https://stackoverflow.com/questions/57187912/how-to-differentiate-gpu-threads-in-a-single-gpu-for-different-host-cpu-thread
// nvcc cuda_std_thread.cu -o cuda_std_thread -std=c++11
#include <iostream>
#include <math.h>
#include <thread>
#include <vector>

#include <cuda.h>


using namespace std;

const unsigned NUM_THREADS = std::thread::hardware_concurrency();  //.. no. of core in the machine

// Kernel function to add the elements of two arrays
__global__
void add_2(int n, float *x, float *y)
{
    int i = blockIdx.x*blockDim.x + threadIdx.x;
    if(i < n) {
        y[i] = x[i] + y[i];
    }
}

//
void thread_func(int N, float *x, float *y, int idx_thread)
{
    cudaSetDevice(0); //.. set to current GPU. Since I have only one, this is set to 0. Can skip this line since by default, it is set to 0

    int blockSize;   // The launch configurator returned block size
    int minGridSize; // The minimum grid size needed to achieve the
    // maximum occupancy for a full device launch
    int gridSize;    // The actual grid size needed, based on input size

    cudaOccupancyMaxPotentialBlockSize( &minGridSize, &blockSize, add_2, 0, N);

    // sample size for each host thread
    int workSize = (N + NUM_THREADS - 1)/NUM_THREADS;

    // Round up according to array size
    gridSize = (workSize + blockSize - 1)/blockSize;

    cout<<"blockSize: "<<blockSize<<" minGridSize: "<<minGridSize<<" gridSize: "<<gridSize<<endl;

    // Run kernel on 1M elements on the GPU
    add_2<<<gridSize, blockSize>>>(workSize, x+idx_thread*workSize, y+idx_thread*workSize);


	// Wait for GPU to finish before accessing on host
	cudaDeviceSynchronize();
}

//
int main()
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

    //.. begin multithreading ..
    vector<std::thread> t;
    for(int i = 0; i<NUM_THREADS; i++) 
        t.push_back(thread(thread_func, N, x, y, i));

    for(int i = 0; i<NUM_THREADS; i++)
        t[i].join();

	// Check for errors (all values should be 3.0f)
	//float maxError = 0.0f;
	//for (int i = 0; i < N; i++) {
    //    if(!(i%100000000))
    //        std::cout<<i<<" "<<y[i]<<std::endl;
	//	maxError = fmax(maxError, fabs(y[i]-3.0f));
	//}
	//std::cout << "Max error: " << maxError << std::endl;

	// Free memory
	cudaFree(x);
	cudaFree(y);

    return 0;
}
