/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ57.cpp
*     author   : @ JY
*     date     : 2020--05--20
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        int l = 1;
        int r = 2;
        vector<vector<int>> res;
        while(l<r){
            if(((l+r)*(r-l+1))>>1 == target){
                int i = l;
                vector<int>tmp;
                while(i<=r){
                    tmp.push_back(i++);
                }
                res.push_back(tmp);
                ++l;
            }else if(((l+r)*(r-l+1))>>1<target){
                ++r;
            }else{
                ++l;
            }
        }
        return res;
    }
};
