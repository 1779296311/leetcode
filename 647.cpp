/*********************************************
*     ------------------------
*     ------------------------
*     file name: 647.cpp
*     author   : @ JY
*     date     : 2019--09--23
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
/*
给一个整数数组，调整每个数的大小，使得相邻的两个数的差不大于一个给定的整数target，调整每个数的代价为调整前后的差的绝对值，求调整代价之和最小是多少*/
class Solution{
    public:
        int countSubstring(string s){
            int size = s.size();
            int res  = 0;
            vector<vector<bool>> memo(size, vector<bool>(size, false));
            for(int i=0; i<size; i++){
                memo[i][i] = true;
            }
            for(int i=1; i<size; i++){
                for(int j=0; j<i; j++){
                    if(s[i] == s[j] && (i == j+1 || memo[i-1][j+1])){
                        memo[i][j] = true;
                        res++;
                    }
                }
                cout <<"__ ";
            }
            return res + size;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    string s = "aaa";
    cout<<te.countSubstring(s)<<endl;
    return 0;
}
