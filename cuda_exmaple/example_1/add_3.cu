#include <iostream>
#include <math.h>
#include <vector>
//
#define CUDA_ERROR_CHECK  // enable error check in cuda
#include "/home/wxie/AI/Spike/July_2019/Spike_July_2019/Spike/Backend/CUDA/Helpers/ErrorCheck.hpp"

using namespace std;


// Kernel function to do nested loops
__global__
void add(int max_x, int max_y, float *tot, float *x, float *y)
{
	int i = blockIdx.x*blockDim.x + threadIdx.x;
    int j = blockIdx.y*blockDim.y + threadIdx.y;
	if(i < max_x && j<max_y) {
        atomicAdd(tot, x[i] + y[j]);
	}
}


int main(void)
{
	int Nx = 1<<15; 
	int Ny = 1<<15; 
    float *d_x = NULL, *d_y = NULL;
    float *d_tot = NULL;
    CudaSafeCall(cudaMalloc((void **)&d_x, sizeof(float)*Nx));
    CudaSafeCall(cudaMalloc((void **)&d_y, sizeof(float)*Ny));
    CudaSafeCall(cudaMalloc((void **)&d_tot, sizeof(float)));

	// Allocate Unified Memory – accessible from CPU or GPU
    vector<float> vx;
    vector<float> vy;

	// initialize x and y arrays on the host
	for (int i = 0; i < Nx; i++) 
		vx.push_back(i);

	for (int i = 0; i < Ny; i++) 
		vy.push_back(i*10);

    //
    float tot = 0;
    for(int i = 0; i<vx.size(); i++)
        for(int j = 0; j<vy.size(); j++) 
            tot += vx[i] + vy[j];

    cout<<"CPU: tot: "<<tot<<endl;


    //
    CudaSafeCall(cudaMemcpy(d_x, vx.data(), vx.size()*sizeof(float), cudaMemcpyHostToDevice));
    CudaSafeCall(cudaMemcpy(d_y, vy.data(), vy.size()*sizeof(float), cudaMemcpyHostToDevice));

    //
    int blockSize;   // The launch configurator returned block size
    int minGridSize; // The minimum grid size needed to achieve the
    cudaOccupancyMaxPotentialBlockSize( &minGridSize, &blockSize, add, 0, Nx+Ny);

    //.. bx*by can not go beyond the blockSize, or hardware limit, which is 1024;
    //.. bx*bx = blockSize && bx/by=Nx/Ny, solve the equation
    int bx = sqrt(blockSize*Nx/(float)Ny);
    int by = bx*Ny/(float)Nx;
    dim3 blockSize_3D(bx, by); 
    dim3 gridSize_3D((Nx+bx-1)/bx, (Ny+by+1)/by);   

    cout<<"blockSize: "<<blockSize<<endl;
    cout<<"bx: "<<bx<<" by: "<<by<<" gx: "<<gridSize_3D.x<<" gy: "<<gridSize_3D.y<<endl;

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
    tot = 0;
	add<<<gridSize_3D, blockSize_3D>>>(Nx, Ny, d_tot, d_x, d_y);

	// Wait for GPU to finish before accessing on host
	CudaCheckError(); //.. defined in SPIKE include cudaDeviceSynchronize()

    //
    CudaSafeCall(cudaMemcpy(&tot, d_tot, sizeof(float), cudaMemcpyDeviceToHost));

    //
    cout<<" GPU: tot: "<<tot<<endl;

	// Free memory
	CudaSafeCall(cudaFree(d_x));
	CudaSafeCall(cudaFree(d_y));
	CudaSafeCall(cudaFree(d_tot));

	return 0;
}
