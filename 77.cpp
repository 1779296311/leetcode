/*********************************************
*     ------------------------
*     ------------------------
*     file name: 77.cpp
*     author   : @ JY
*     date     : 2019--10--14
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        vector<vector<int>> combine(int n, int k){
            this->num = n;
            vector<int> tmp;
            backtrack(k,1,tmp);
            return res;
        }
    private:
        void backtrack(const int k, int first, vector<int>& tmp){
            if(tmp.size() == k){
                res.push_back(tmp);
                return;
            }
            for(int i=first; i<num; i++){
                tmp.push_back(i);
                backtrack(k,i+1,tmp);
                tmp.pop_back();
            }
        }
        vector<vector<int>> res;
        int num;
};
