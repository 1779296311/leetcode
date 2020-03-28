/********************************************* 
*     ------------------------                 
*     ------------------------                 
*     file name: mininumTotal.cpp
*     author   : @ JY    
*     data     : 2019--09--10
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
using  namespace  std;

class Solution{
    public:
        int munimunTotal(vector<vector<int>>& triangle){

            int len  = triangle.size();
            vector<vector<int>> memo(len, vector<int>(len));
            for(int i=0; i<len; i++){
                memo[len-1][i] = triangle[len-1][i];
            }
            int index = len -1;
            for(int i = len -2; i>=0; i--){
                for(int j=0; j<index; j++){
                 memo[i][j] = min(memo[i+1][j]+triangle[i][j],memo[i+1][j+1] + triangle[i][j]);
                }
                index--;
            }
            return memo[0][0];
        }

};
int main(int argc,const char *argv[]){
    Solution te;
    vector<vector<int>> nums = {{2},{3,4},{6,5,7},{4,1,8,3}};
    cout <<te.munimunTotal(nums)<<endl;
    return 0;
}
