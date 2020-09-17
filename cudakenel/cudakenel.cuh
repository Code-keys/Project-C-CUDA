#ifndef CUDAKENEL_CUH
#define CUDAKENEL_CUH
#include <vector> // for  vector
#include <iostream> // for cout
#include <memory>  // for ptr

#include "cuda_runtime.h"  
#include "device_launch_parameters.h"

#define CUDA_CHECK(condition) \
  /* Code block avoids redefinition of cudaError_t error */ \
  do { \
    cudaError_t error = condition; \
    if (error != cudaSuccess) { \
      printf("cudaGetErrorString(error) \n");\
    } \
  } while (0)

// 只能有一个 外部接口函数  
void _set_device(int device_id);

bool InitCUDA(void);

__host__ void  bye(std::string s){std::cout << s << std::endl;};

extern "C"
void Interface(float *a, float *b, float *c, int DX);

template<typename  T>
class interface{
  public:
  int x;
  int y;
  int na;
  int nb;
  int nc;
  float * a =new float[na];
  float *b = new float[nb];
  float *c = new float[nc];
  // float* a = (float*) malloc(  sizeof(float));
  // float* b = (float*) malloc(  sizeof(float));
  // float* c = (float*) malloc(  n* sizeof(float));

  interface(int row,int cols):x(row),y(cols){
    float * a =new float[na];
    float *b = new float[nb];
    float *c = new float[nc];
  };


  private:
  size = sizeof(T);
  float *dev_a ;
  float *dev_b ;
  float *dev_c ;
  std::vector <std::vector<T>> Matrix(x, std::vector<T>(y)); 
  bool init(){
    InitCUDA();
    _set_device(0);	
    CUDA_CHECK (cudaDeviceReset());
    CUDA_CHECK ( cudaMalloc((void**)&dev_c, nc *size));
    CUDA_CHECK ( cudaMalloc((void**)&dev_a,na*size));
    CUDA_CHECK ( cudaMalloc((void**)&dev_b, nb*size));
    if(dev_c == NULL)exit(0);
    if(dev_b == NULL)exit(0);
    if(dev_a == NULL)exit(0); 
    };
  
  void kenel(){Interface();};
  void _set_device(){};
  void InitCUDA();
  void CUDA_CHECK(){};


public:
 ~ interface(){};
};

template<typename T>
bool  interface<T>::InitCUDA(void)
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

template<typename T>
void interface<T>::CUDA_CHECK(cudaError_t condition){
  do { \
    cudaError_t error = condition; \
    if (error != cudaSuccess) { \
      printf("cudaGetErrorString(error) \n");\
    } \
  } while (0);
 }

template<typename T>
void interface<T>:: _set_device(int device_id) {
    int current_device;
    CUDA_CHECK(cudaGetDevice(&current_device));
    if (current_device == device_id) {
        return;
        }
    // floathe call to cudaSetDevice must come before any calls to Get, which
    // may perform initialization using the GPU.
    CUDA_CHECK(cudaSetDevice(device_id));
}





#endif