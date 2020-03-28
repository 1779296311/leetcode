/*********************************************
*     ------------------------
*     ------------------------
*     file name: 97.cpp
*     author   : @ JY
*     date     : 2019--09--20
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
/*
给定三个字符串 s1, s2, s3, 验证 s3 是否是由 s1 和 s2 交错组成的。
示例 1:
输入: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
输出: true*/
class Solution{
    public:
        bool inInterleave(string s1, string s2, string s3){
            int size_1 = s1.size();
            int size_2 = s2.size();
            int size_3 = s3.size();
            if(size_1 + size_2 != size_3){
                return false;
            }
            // memo[i][j] : X qian i+j shi fou shi s1:0~i-1, s2:0~j-1 zu cheng
            vector<vector<bool>> memo(size_1+1, vector<bool>(size_2+1, false));
            for(int i=0; i<=size_1; i++){
                for(int j=0; j<=size_2; j++){
                    if(i==0 &&  j==0){
                        memo[i][j] = true;
                        continue;
                    }
                    if(i>0 && s3[i+j-1] == s1[i-1]){
                        memo[i][j] = memo[i-1][j];
                    }
                    if(j>0 && s3[i+j-1] == s2[j-1]){
                        memo[i][j] = memo[i][j] || memo[i][j-1];
                    }
                }
            }
            return memo[size_1][size_2];
        }
};

