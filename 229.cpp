/*********************************************
*     ------------------------
*     ------------------------
*     file name: 229.cpp
*     author   : @ JY
*     date     : 2020--02--18
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums){
        vector<int> __res;
        int __size;
        if(!(__size = nums.size())){
            return __res;
        }
        if(__size == 1){
            __res.push_back(nums[0]);
            return __res;
        }
        int __f    = __size/3+1;
        int _num0  = nums[0];
        int _num1  = nums[0];
        int _tmp0  = 0;
        int _tmp1  = 0;
        for(int i=1; i<__size; ++i){
            if(nums[i] == _num0){
                ++_tmp0;
                continue;
            }
            if(nums[i] == _num1){
                ++_tmp1;
                continue;
            }
            if(!_tmp0){
                _num0 = nums[i];
                ++_tmp0;
                continue;
            }
            if(!_tmp1){
                _num1 = nums[i];
                ++_tmp1;
                continue;
            }
            --_tmp0;
            --_tmp1;
        }
        _tmp0  = 0;
        _tmp1  = 0;
        //cout<<_num0<<endl;
        //cout<<_num1<<endl;
        for(int i=0; i<__size; i++){
            if(nums[i] == _num0){
                ++_tmp0;
            }
            if(nums[i] == _num1){
                ++_tmp1;
            }
        }
        if(_num0 != _num1){
            if(_tmp0 >= __f){
                __res.push_back(_num0);
            }
            if(_tmp1 >= __f){
                __res.push_back(_num1);
            }
        }else{
            if(_tmp0 >= __f){
                __res.push_back(_num0);
            }
        }
        return __res;
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    //vector<int> a = {1,1,1,3,3,2,2,2};
    vector<int> a = {6,6,6,7,7};
    //vector<int> a = {23,9,3,9,3,9,3,9,3,9};
    vector<int> b;
    b = te.majorityElement(a);
    for(int i=0; i<b.size(); i++){
        cout<<b[i]<<endl;
    }
    return 0;
}
