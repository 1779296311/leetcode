/*********************************************
*     ------------------------
*     ------------------------
*     file name: minSort_needAd.cpp
*     author   : @ JY
*     date     : 2020--04--22
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        int minSort_need(int *nums, int size){
            int maxV = nums[0];
            int minV = nums[size-1];
            int d1   = 0;
            int d2   = size-1;
            for(int i=1; i<size; ++i){
                maxV = max(maxV,nums[i]);
                if(nums[i] < maxV){
                    d1 = i;
                }
            }
            for(int i=size-2; i>=0; --i){
                minV = min(minV,nums[i]);
                if(nums[i] > minV){
                    d2 = i;
                }
            }
            return d1-d2>0?d1-d2+1:0;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    int nums[] = {0,1,2,4,3,5};
    int size = *(&nums+1) - nums;
    cout<<te.minSort_need(nums, size)<<endl;
    return 0;
}
