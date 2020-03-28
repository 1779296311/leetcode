/*********************************************
*     ------------------------
*     ------------------------
*     file name: 72.cpp
*     author   : @ JY
*     date     : 2019--09--20
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
/*
给定两个单词 word1 和 word2，计算出将 word1 转换成 word2 所使用的最少操作数 。
你可以对一个单词进行如下三种操作：
    插入一个字符
    删除一个字符
    替换一个字符
*/
class Solution{
    public:
        int minDistance(string s1, string s2){
            int size_1 = s1.size();
            int size_2 = s2.size();
            vector<vector<int>> memo(size_1+1, vector<int>(size_2+1));
            for(int i=0; i<=size_1; i++){
                for(int j=0; j<=size_2; j++){
                    if(i == 0){
                        memo[i][j] = j;
                        continue;
                    }
                    if(j == 0){
                        memo[i][j] = i;
                        continue;
                    }
                                     //delete         //replace
                    memo[i][j] = min(memo[i-1][j]+1, memo[i-1][j-1]+1);
                                                    //add
                    memo[i][j] = min(memo[i][j], memo[i][j-1]+1);
                    if(s1[i-1] == s2[j-1]){
                        memo[i][j] = memo[i-1][j-1];
                    }
                }
            }
            return memo[size_1][size_2];
        }
};
