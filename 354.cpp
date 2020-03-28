/*********************************************
*     ------------------------
*     ------------------------
*     file name: 354.cpp
*     author   : @ JY    
*     data     : 2019--09--14
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using  namespace  std;

class Solution{
    public:
        int maxEnvelopes(vector<vector<int>>& envelopes){
            int len     = envelopes.size();
            int index   = len;
            int tmp     = 0;
            int Max     = -1;

            sort(envelopes.begin(), envelopes.end(),[](vector<int>& a, vector<int>& b){
                    return a[0] < b[0] || (a[0]==b[0]&&a[0]>b[0]);
                    });
            vector<int> memo(len,1);
            for(int i=0; i<len; i++){
                for(int j=0; j<i; j++){
                    if(envelopes[i][0] != envelopes[j][0] && envelopes[i][1] > envelopes[j][1] ){
                        memo[i] = max(memo[i],memo[j]+1);
                    }
                }
                MAX = max(memo[i],Max);
            }
            return Max;
        }
};

int main(int argc,const char *argv[]){
    Solution te;
    //int tmp[4][2] = {5,4,6,4,6,7,2,3};
    int tmp[14][2] = {{ 1,15 },{ 7,18 },{ 7,6 },{ 7,100 },{ 2,200 },{ 17,30 },{ 17,45 },{ 3,5 },{ 7,8 },{ 3,6 },{ 3,10 },{ 7,20 },{ 17,3 },{ 17,45 }};
    int len = 14;
    vector<vector<int>> nums(len, vector<int>(2));
    for(int i=0; i<len; i++){
        nums[i][0] = tmp[i][0];
        nums[i][1] = tmp[i][1];
    }
    //cout <<"ok";
    cout <<te.maxEnvelopes(nums);
    return 0;
}
