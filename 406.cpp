/*********************************************
*     ------------------------
*     ------------------------
*     file name: 406.cpp
*     author   : @ JY
*     date     : 2020--03--16
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
using  namespace  std;
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(),people.end(),[](vector<int>& a, vector<int>& b){
                return a[0]>b[0] || a[0]==b[0]&&a[1]<b[1];
                });
        vector<vector<int>> __res;
        for(int i=0; i<people.size(); ++i){
            __res.insert(__res.begin()+people[i][1],people[i]);
        }
        return __res;
    }
};
