#include <math.h>
#include <thread>
#include <time.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <memory>
#include "cudakenel/cudakenel.hpp"

//#include <torch/script.h> //  FOR ,MODEL INFER AND TRAIN
//#include<torch/torch.h>
//#include <opencv2/opencv.hpp> // FOR  PROCESS PICTURE/VIDEO...
//#include <opencv2/highgui.hpp>

// #include  "utils.hpp"
#include "NumCpp.hpp"



// extern "C" void cudakenel(int a,int b,int c );

// using namespace std;
//using namespace cv;

//using namespace nc;

/*
* a test  interface !
*/
int print(void)
{
    std::vector<std::string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    std::unique_ptr<int> aptr(new int);

    for (const std::string& word : msg)
    {
        std::cout << word << " ";
    }
    std::cout << std::endl;
    int a = 4;
    int size = 4;
    int b = 0 ;//(int)malloc(size*sizeof(int));
    // system("pause");
    return 0;
}
 
void test_libtorch(void){

    std::cout << "module input ok\n";
    // Create a vector of inputs.
    //std::vector<torch::jit::IValue> inputs;
    //inputs.push_back(torch::ones({1, 3, 256, 192}));

};

void test_tensorRT(void){
    return;
};

void test_opencv(void){
    /*cv::Mat image;
    image = cv::imread("test.jpg",0);
    if ( !image.data )
    {
        printf("No image data \n");
        return ;
    }

    cv::imshow("image", image);*/

};
/*
void test_numNc(void){

    auto a7 = nc::NdArray<int>(3, 4) = 0;

    nc::NdArray<int> a = { {1, 2}, {3, 4}, {5, 6} };
    a.reshape(2,3);
    a.astype<double>();
    std::cout << a(nc::Slice(0, 1), a.rSlice()) << std::endl;

    nc::Shape  a(1,2);
    nc::random::seed(666);
    nc::random::rand<double>(nc::Shape(3,4));
    auto a1 = nc::random::randInt<int>({3, 4},0,10);
    std::cout << a1 <<std::endl;
}
*/

void test_cuda(void){
    //cudakenel();
    int a = 1;
    int b = 5;
    int c ;
    cudakenel(a,b,c);
};
int main(int argc, char** argv )
{
    print();

    test_libtorch();

    test_tensorRT();

    // test_opencv();

   //   test_numNc();

    test_cuda();

    std::cout <<"PASSED !"<<std::endl;

    return 0;
}
