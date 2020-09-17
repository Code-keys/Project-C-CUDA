#ifndef CUDAKENEL_CUH
#define CUDAKENEL_CUH


// 只能有一个 外部接口函数  

extern "C"
void _nms(int* keep_out, int* num_out, const float* boxes_host, int boxes_num,
          int boxes_dim, float nms_overlap_thresh, int device_id);

#endif