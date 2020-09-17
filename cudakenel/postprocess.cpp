#include "postprocess.hpp"

void main()
{

        CTest cTest;

        cTest.Evolution();

        system("pause");
}

/*
namespace cpu{

        torch::from_blob(arr, {1,9}, at::kFloat); 

        torch::Tensor foo = torch::rand({12, 12});

        // assert foo is 2-dimensional and holds floats.
        auto foo_a = foo.accessor<float,2>();
        float trace = 0;

        for(int i = 0; i < foo_a.size(0); i++) {
        // use the accessor foo_a to get tensor data.
        trace += foo_a[i][i];
}
namespace gpu{
        __global__ void packed_accessor_kernel(
        PackedTensorAccessor64<float, 2> foo,
        float* trace) {
        int i=threadIdx.x
        gpuAtomicAdd(trace, foo[i][i])
        }

        torch::Tensor foo = torch::rand({12, 12});

        // assert foo is 2-dimensional and holds floats.
        auto foo_a = foo.packed_accessor64<float,2>();
        float trace = 0;

        packed_accessor_kernel<<<1, 12>>>(foo_a, &trace);
}
*/