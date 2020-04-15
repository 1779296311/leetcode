/*********************************************
*     ------------------------
*     ------------------------
*     file name: maxGap.cpp
*     author   : @ JY
*     date     : 2020--04--07
**********************************************/
#include <iostream>
#include <climits>
#include <cmath>
#include <stdlib.h>
//排序数组最大差值（一开始美排序）
using  namespace  std;
class Solution{
    public:
        int maxGap(int *nums, int size){
            int maxN = INT_MIN;
            int minN = INT_MAX;
            for(int i=0; i<size; ++i){
                minN = min(minN,nums[i]);
                maxN = max(maxN,nums[i]);
            }
            if(maxN == minN){
                return 0;
            }
            int hasNum[size+1] = {0};
            int minNum[size+1];
            int maxNum[size+1];
            for(int i=0; i<=size; ++i){
                int index = getIndex(nums[i],size,minN,maxN);
                minNum[i] = hasNum[i]?min(minNum[i],nums[i]):nums[i];
                maxNum[i] = hasNum[i]?max(maxNum[i],nums[i]):nums[i];
            }
            maxN = maxNum[0];
            int __res = 0;
            for(int i=1; i<=size; ++i){
                if(minNum[i]-maxN > __res){
                    __res = minNum[i] - maxN;
                    maxN  = maxNum[i];
                }
            }
            return __res;
        }
        int getIndex(int num, int size, int minN, int maxN){
            return (int)((num-minN)*size/(maxN-minN));
        }

};
int main(int argc,const char *argv[]){
    Solution te;
    int nums[] = {1,4,6,23,45,30};
    cout<<te.maxGap(nums, *(&nums+1)-nums)<<endl;
    return 0;
}
