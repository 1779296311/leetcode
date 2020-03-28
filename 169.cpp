/*********************************************
*     ------------------------
*     ------------------------
*     file name: 169.cpp
*     author   : @ JY
*     date     : 2020--02--18
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        /*int __size = nums.size();
        if(!__size){
            return nums[0];
        }
        int j = 0;
        int i = 0;
        for(i=0; i<__size; ++i){
            int __tmp = nums[i];
            for(j=1; j<i; ++j){
                if(nums[j] == __tmp){
                    j == 0;
                    break;
                }
            }
            if(!j){
                continue;
            }
            int __num = 0;
            for(int m=1; m<__size; ++m){
                if(nums[m] == __tmp){
                    ++__num;
                }
                if(__num >= __size/2){
                    return __tmp;
                }
            }
        }
        return 0;
    */
    /////
    int __size = nums.size();
    if(__size == 1 || __size == 2){
        return nums[0];
    }
    int __tmp = 1;
    int __num = nums[0];
    for(int i=1; i<__size-1; ++i){
        if(__num == nums[i]){
            ++__tmp;
        }else if(!--__tmp){
            __num = nums[++i];
            ++__tmp;
        }
        if(__tmp > __size/2){
            return __num;
        }
        //cout<<"aa"<<endl;
        //cout<<__num<<endl;
    }
    return __num;
    }
};
int main(int argc,const char *argv[]){
    vector<int> nums = {2,2,1,1,1,2,2};
    Solution te;
    cout<<te.majorityElement(nums)<<endl;
}
