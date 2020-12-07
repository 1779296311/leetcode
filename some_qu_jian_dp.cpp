/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_qu_jian_dp.cpp
*     author   : @ JY
*     date     : 2020--10--07
**********************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
#include <cmath>
#include <cstring>
#include <numeric>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <stdlib.h>
class Solution{
    public:
//面试题 08.14. 布尔运算
        int countEval(std::string s, int result){
            int len = s.size();
            std::vector<std::vector<int>> dp_0(len, std::vector<int>(len));
            std::vector<std::vector<int>> dp_1(len, std::vector<int>(len));
            for(int j=0; j<len; ++j){
                for(int i=j; i>=0; --i){
                    if(i==j){
                        if(std::isdigit(s[i])){
                            dp_0[i][j] = s[i] == '0';
                            dp_1[i][j] = s[i] == '1';
                        }
                        continue;
                    }
                    for(int k=i; k<j; ++k){
                        if(std::isdigit(s[k]))continue;
                        char c = s[k];
                        if(c=='|'){
                            dp_1[i][j] += (dp_1[i][k-1] * (dp_1[k+1][j] + dp_0[k+1][j]) +
                                           dp_0[i][k-1] *  dp_1[k+1][j]);
                            dp_0[i][j] += (dp_0[i][k-1] * dp_0[k+1][j]);
                        }else if(c=='&'){
                            dp_1[i][j] += (dp_1[i][k-1] * dp_1[k+1][j]);
                            dp_0[i][j] += (dp_0[i][k-1] * (dp_0[k+1][j] + dp_1[k+1][j]) +
                                           dp_0[k+1][j] * dp_1[i][k-1]);
                        }else if(c=='^'){
                            dp_1[i][j] += (dp_1[i][k-1] * dp_0[k+1][j] + dp_0[i][k-1] * dp_1[k+1][j]);
                            dp_0[i][j] += (dp_1[i][k-1] * dp_1[k+1][j] + dp_0[i][k-1] * dp_0[k+1][j]);
                        }
                    }
                }
            }
            return result ? dp_1[0][len-1] : dp_0[0][len-1];
        }
//1039. 多边形三角剖分的最低得分
        int minScoreTriangulation(std::vector<int> &A){
            int len = A.size();
            std::vector<std::vector<int>> dp(len, std::vector<int>(len));
            for(int j=2; j<len; ++j){
                for(int i=j-2; i>=0; --i){
                    if(j-i==2){
                        dp[i][j] = A[i] * A[i+1] * A[j];
                        continue;
                    }
                    dp[i][j] = INT_MAX;
                    for(int k=i+1; k<j; ++k){
                        dp[i][j] = std::min(dp[i][j], A[i]*A[k]*A[j] + dp[i][k] + dp[k][j]);
                    }
                }
            }
            return dp[0][len-1];
        }
//1130. 叶值的最小代价生成树
        int mcFromLeafValues(std::vector<int> &arr){
            int len = arr.size();
            std::vector<std::vector<int>> dp(len, std::vector<int>(len));
            for(int j=0; j<len; ++j){
                for(int i=j-1; i>=0; --i){
                    if(j-i==1){
                        dp[i][j] = arr[i] * arr[j];
                        continue;
                    }
                    dp[i][j] = INT_MAX;
                    for(int k=i; k<j; ++k){
                        int sum = *max_element(begin(arr)+i, begin(arr)+k+1) *
                                  *max_element(begin(arr)+k+1, begin(arr)+j+1);
                        dp[i][j] = std::min(dp[i][j], sum + dp[i][k] + dp[k+1][j]);
                    }
                }
            }
            return dp[0][len-1];
        }
};
