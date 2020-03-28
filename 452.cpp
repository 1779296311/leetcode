/*********************************************
*     ------------------------
*     ------------------------
*     file name: 452.cpp
*     author   : @ JY
*     date     : 2020--03--16
**********************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        int findMinArrowShots(vector<vector<int>> &points){
            int size = points.size();
            if(!size || size==1){
                return size;
            }
            sort(points.begin(),points.end(),[](vector<int>& a, vector<int>& b){
                    return a[0]<b[0];
                    });
            int begin = points[0][0];
            int end   = points[0][1];
            int __res = 1;
            for(int i=1; i<size; ++i){
                if(end >= points[i][0]){
                    end   = min(end,points[i][1]);
                }else{
                    end   = points[i][1];
                    ++__res;
                }
                begin = points[i][0];
            }
            return __res;
        }
};
