#include <cudakenel.cuh>

#include "cuda_runtime.h"  
#include "device_launch_parameters.h"
// #include "device_functions.h"

#include <stdio.h>
#include <malloc.h>
#include <iostream>

#include<boost/timer.hpp>  // test time 

// suanli 7.5
// 定义总数据矩阵的行数和列数  1024 1024  64
// global:主机呼叫，设备执行
// host:主机呼叫，主机执行
// device:设备呼叫，设备执行

// 控制一次计算占用显存的大小：CONfloatROL_ROWS*ROWS*8（字节）< 显存 
// 定义每一块内的线程个数，Gfloat720最多是1024
#define NUM_THREADS 1024

__device__ void gpuhello(void){
    printf("inserted function!\n");
}
__global__ void add( float dev_a[],float dev_b[],float dev_c[],int n)
{
    //dim3 BD = blockDim;
    int x =threadIdx.x;
    int y =threadIdx.y;
    int where = y*blockDim.x+x;
    gpuhello();

    if (where<n){
        for (int i = 0; i<int(blockDim.x/2);++i){
            dev_c[where] = dev_a[i]+dev_b[i];
        }
    }
};

extern "C"
void Interface(float *aa, float *bb, float *cc, int n){
    /*
    aa:输入矩阵 　　内存
    bb:输入矩阵　　内存
    cc:　输出矩阵　内存
    n" 线程数目　或矩阵元素总数　栈
    */
    float* dev_a;
    float* dev_b;
    float* dev_c;
    
    InitCUDA();
    _set_device(0);	
    CUDA_CHECK(cudaDeviceReset());

    CUDA_CHECK( cudaMalloc((void**)&dev_a, sizeof(float)));
    CUDA_CHECK( cudaMalloc((void**)&dev_b, sizeof(float)));
    CUDA_CHECK( cudaMalloc((void**)&dev_c, n*sizeof(float)));
    CUDA_CHECK(cudaMemcpy(dev_a, aa, sizeof(float), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(dev_b, bb, sizeof(float), cudaMemcpyHostToDevice));

    if(dev_c == NULL)exit(0);
    if(dev_b == NULL)exit(0);
    if(dev_a == NULL)exit(0);

    dim3 grid(1, 1);
    dim3 block(32, 32, 1); 

    boost::timer t;
    add<<<grid,block>>>(dev_a,dev_b,dev_c,n);
    std::cout<<"运行时间："<<t.elapsed() <<"　s"<<std::endl;//输出已流失的时间

    CUDA_CHECK(cudaMemcpy(cc,dev_c,n*sizeof(float) ,cudaMemcpyDeviceToHost));
    CUDA_CHECK (cudaFree(dev_a));//释放GPU内存
    CUDA_CHECK (cudaFree(dev_b));//释放GPU内存
    CUDA_CHECK (cudaFree(dev_c));//释放GPU内存
    CUDA_CHECK (cudaDeviceReset());


    for  (int i = 0; i< 1; ++i){
        printf("answer :  %f\n", cc[i]);
    };
    return;
};


int main(int argc, char const *argv[])
{    
    int n = 5;
    int size = sizeof(float);
    float * a =new float;
    float *b = new float;
    float *c = new float[n];
    // float* a = (float*) malloc(  sizeof(float));
    // float* b = (float*) malloc(  sizeof(float));
    // float* c = (float*) malloc(  n* sizeof(float));

    int temp[6] = {0,1,2,3,4,5};

    std:: vector<std::vector<int> > Matrix(5, std::vector<int>(6)); 
    for (std::vector<int> i:Matrix){
        std::copy(temp,temp+6,i.begin());
        std::cout <<i.data()<<std::endl;
    } 

    float *dev_a ;
    float *dev_b ;
    float *dev_c ;

    *a = 1.0;
    *b = 5.0;

    for (int j = 0; j < n; ++j)
    {
        c[j]= 2.0+0.9*j;
    }

    // 准备数据 在栈里   申请主机;内存
    // Choose which GPU to run on, change this on a multi-GPU system.
    // InitCUDA();
    //_set_device(0);	
    // CUDA_CHECK (cudaDeviceReset());
    //3.请求CUDA设备的内存（显存），执行CUDA函数   只能访问设备内存
    InitCUDA();
    _set_device(0);	
    CUDA_CHECK (cudaDeviceReset());

    CUDA_CHECK ( cudaMalloc((void**)&dev_c, n *size));
    CUDA_CHECK ( cudaMalloc((void**)&dev_a,size));
    CUDA_CHECK ( cudaMalloc((void**)&dev_b, size));
    //4.从主机复制数据到设备上

    if(dev_c == NULL)exit(0);
    if(dev_b == NULL)exit(0);
    if(dev_a == NULL)exit(0);

    CUDA_CHECK(cudaMemcpy(dev_a, a, sizeof(float), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(dev_b, b, sizeof(float), cudaMemcpyHostToDevice));

    //调用核函数在GPU上执行。数据较少，使用一个Block，含有1024个线程    使用1024个Block  ( 1024*1024*64)   ：：：1400个cuda核心
    //add<<<1,5>>>(dev_a,dev_b,dev_c);
    dim3 grid(1, 1);
    dim3 block(5, 1, 1); 

    add<<<grid,block>>>(dev_a,dev_b,dev_c,n);
   
    // cudaDeviceSynchronize();

    CUDA_CHECK(cudaMemcpy(c,dev_c,5*sizeof(float) ,cudaMemcpyDeviceToHost));
    // CUDA_CHECK (cudaDeviceReset());
    CUDA_CHECK (cudaFree(dev_a));//释放GPU内存
    CUDA_CHECK (cudaFree(dev_b));//释放GPU内存
    CUDA_CHECK (cudaFree(dev_c));//释放GPU内存
    //CUDA_CHECK (cudaDeviceReset());


    for  (int i = 0; i< 5; ++i){
        printf("answer :  %f\n", c[i]);
    }
    bye("GO !");


    return  0;
}

bool InitCUDA(void)
{
     int count;
     cudaGetDeviceCount(&count);
     if (count == 0) {
         printf("floathere is no device.\n");
         return 0;
        }
     int i;
     for (i = 0; i < count; i++) {
         cudaDeviceProp prop;
         if (cudaGetDeviceProperties(&prop, i) == cudaSuccess) {
             if (prop.major >= 1) {
                 break;
                }
            }
        if (i == count) {
            printf("floathere is no device supporting CUDA 1.x.\n");
            return 0;
            }
        cudaSetDevice(i);
        };
        return  1;
}

void _set_device(int device_id) {
    int current_device;
    CUDA_CHECK(cudaGetDevice(&current_device));
    if (current_device == device_id) {
        return;
        }
    // floathe call to cudaSetDevice must come before any calls to Get, which
    // may perform initialization using the GPU.
    CUDA_CHECK(cudaSetDevice(device_id));
}
