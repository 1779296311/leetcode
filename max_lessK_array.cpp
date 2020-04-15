/*********************************************
*     ------------------------
*     ------------------------
*     file name: max_lessK_array.cpp
*     author   : @ JY
*     date     : 2020--04--05
**********************************************/
#include <iostream>
#include <stdlib.h>
//最长 和小于K的子数组
using  namespace  std;
class Solution{
    public:
        int max_lessK_array(int *nums, int k, int size){
            int sums[size];
            int ends[size];
            sums[size-1] = nums[size-1];
            ends[size-1] = size-1;
            for(int i=size-2; i>=0; --i){
                if(sums[i+1] < 0){
                    sums[i] = sums[i+1] + nums[i];
                    ends[i] = ends[i+1];
                }else{
                    sums[i] = nums[i];
                    ends[i] = i;
                }
            }
            int __res = 0;
            int R     = 0;
            int sum   = 0;
            for(int i=0; i<size; ++i){
                while(R<size && sum+sums[R]<=k){
                    sum = sum + sums[R];
                    R   = ends[R]+1;
                }
                __res = max(__res,R-i);
                if(R>i){
                    sum = sum - nums[i];
                }else{
                    R   = i + 1;
                }
                //sum  -= R>i?nums[i]:0;
                //R     = max(R,i+1);
            }
            return __res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    int nums[] = {1,4,-5,0,0,0,0,0,700,-2,-3,0};
    cout<<te.max_lessK_array(nums,7,*(&nums+1)-nums)<<endl;
    return 0;
}
