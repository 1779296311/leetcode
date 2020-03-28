/*********************************************
*     ------------------------
*     ------------------------
*     file name: 350.cpp
*     author   : @ JY
*     date     : 2020--02--20
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution {
public:
    /*vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int> __res;
        int _size1 = nums1.size();
        int _size2 = nums2.size();
        if(!_size1 || !_size2){
            return __res;
        }
        int _tmp1  = nums1[0];
        int _tmp2  = nums2[0];
        for(int i=0; i<_size1; i++){
            if(_tmp1 < nums1[i]){
                _tmp1 = nums1[i];
            }
        }
        for(int i=0; i<_size2; i++){
            if(_tmp2 < nums2[i]){
                _tmp2 = nums2[i];
            }
        }
        int _size    = (_tmp1>_tmp2?_tmp2:_tmp1)+1;
        int c[_size] = {0};
        int b[_size] = {0};
        for(int i=0; i<_size1; ++i){
            if(nums1[i] >= _size){
                continue;
            }
            ++c[nums1[i]];
        }
        for(int i=0; i<_size2; ++i){
            if(nums2[i] >= _size){
                continue;
            }
            ++b[nums2[i]];
        }

        for(int i=0; i<_size; ++i){
            if(c[i] > b[i]){
                c[i] = b[i];
            }
        }
        for(int i=0; i<_size; ++i){
            while(c[i]-- > 0){
                __res.push_back(i);
            }
        }
        return __res;
    }*/
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2){
        vector<int> __res;
        int _size1 = nums1.size();
        int _size2 = nums2.size();
        if(!_size1 || !_size2){
            return __res;
        }
        for(int i=0; i<_size1-1; ++i){
            for(int j=i+1; j<_size1; ++j){
                if(nums1[i] > nums1[j]){
                    nums1[i] = nums1[i] ^ nums1[j];
                    nums1[j] = nums1[i] ^ nums1[j];
                    nums1[i] = nums1[i] ^ nums1[j];
                }
            }
        }
        for(int i=0; i<_size2-1; ++i){
            for(int j=i+1; j<_size2; ++j){
                if(nums2[i] > nums2[j]){
                    nums2[i] = nums2[i] ^ nums2[j];
                    nums2[j] = nums2[i] ^ nums2[j];
                    nums2[i] = nums2[i] ^ nums2[j];
                }
            }
        }
        int i = 0;
        int j = 0;
        while(i<_size1 && j<_size2){
            if(nums1[i] > nums2[j]){
                ++j;
            }else if(nums1[i] < nums2[j]){
                ++i;
            }else{
                while(i<_size1 && j<_size2 && nums1[i] == nums2[j]){
                    __res.push_back(nums1[i]);
                    ++i;
                    ++j;
                }
            }
        }
        return __res;
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    //vector<int> a = {-2147483648,1,2,3};
    //vector<int> b = {1,-2147483648,-2147483648};
    vector<int> a = {1,2,2,1};
    vector<int> b = {2,2};
    vector<int> c;
    c = te.intersect(a,b);
    for(int i=0; i<c.size(); ++i){
        cout<<c[i]<<endl;
    }
    return 0;
}
