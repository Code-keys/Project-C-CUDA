#include <math.h>
#include <thread>
#include <time.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <memory>

#include <torch/script.h> //  FOR ,MODEL INFER AND TRAIN
#include <torch/torch.h>

#include <opencv2/opencv.hpp> // FOR  PROCESS PICTURE/VIDEO...
#include <opencv2/highgui.hpp>

// #include "NumCpp.hpp" // FOR COMPUTER OPTIMIZE

/*
 * include  一些实用的工具 
 *      class  TEMPLATE：
 *              CVprocess（）
 *              C
 *              C
 *              C
 *              C
 *              C
 *              C
 *              C
 *              C
 *              C
 * 
 * 
 * 
 *      function：
 *              getfile（）f： os.listdir（）
 *              F
 *              F
 *              F
 *              F
 *              F
 *              F
 *              F
*/

template<typename T1, typename T2>
class CVprocess< T1, T2> {

private:
    T1 A;
    T2 B;
    std::string path;
    std::vector<std::string> pngnames;

public:
    CVprocess<>(std::string path1){
        this.path = path1;
        cv::glob(path1+"/*.png",this.pngnames,false);
        std::cout << this.pngnames << std::endl;
        };

   void  getFiles(std::string path, std::string postFix,std::vector<std::string> pngnames){return 
        cv::glob(path+"/*."+postFix,pngnames,false) };



    ~CVprocess(){
         pngnames;
    }

} ;
