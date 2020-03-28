/*********************************************
*     ------------------------
*     ------------------------
*     file name: i_j_min_max.cpp
*     author   : @ JY
*     date     : 2020--03--26
**********************************************/
#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>
using  namespace  std;
//（给一个数组，求有多少个区间，满足区间内的最大值和最小值之差小于k）
class Solution{
    public:
        int i_j_min_max(int *nums, int k, int size){
            list<int> minT;
            list<int> maxT;
            int __res = 0;
            int index = 0;
            for(int i=0; i<size; ++i){
                while(index<size){
                    while(!minT.empty() && nums[minT.back()]>=nums[index]){
                        minT.pop_back();
                    }
                    minT.push_back(index);
                    while(!maxT.empty() && nums[maxT.back()]<=nums[index]){
                        maxT.pop_back();
                    }
                    maxT.push_back(index);
                    if(nums[maxT.front()]-nums[minT.front()]>k){
                        break;
                    }
                    ++index;
                }
                if(maxT.front() == i){
                    maxT.pop_front();
                }
                if(minT.front() == i){
                    minT.pop_front();
                }
                __res = __res + index - i;
            }
            return __res;
        }
        vector<int> get_max_by_winize(int *nums,int numSize, int winSize){
            list<int> maxT;
            vector<int> __res;
            int index = 0;
            while(index<numSize){
                while(!maxT.empty() && nums[maxT.back()] < nums[index]){
                    maxT.pop_back();
                }
                maxT.push_back(index);
                if(index-winSize == maxT.front()){
                    maxT.pop_front();
                }
                if(index>winSize-2){
                    __res.push_back(nums[maxT.front()]);
                }
                ++index;
            }
            return __res;
        }
        void debug(int *nums,int numSizel, int winSize){
            vector<int> __res = get_max_by_winize(nums,numSizel,winSize);
            for(int i=0; i<__res.size(); ++i){
                cout<<__res[i]<<endl;
            }
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    int nums[] = {4,4,5,1,6,8,12};
    te.debug(nums,*(&nums+1)-nums,5);
    te.
    //cout<<te.i_j_min_max(nums,5,*(&nums+1)-nums)<<endl;
    return 0;
}
