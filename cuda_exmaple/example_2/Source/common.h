#ifndef COMMON_H
#define COMMON_H

#include <cuda.h>
#include <vector_types.h>

__global__ 
void add(int n, float *x, float *y);
#endif
