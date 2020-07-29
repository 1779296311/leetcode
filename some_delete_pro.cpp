/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_delete_pro.cpp
*     author   : @ JY
*     date     : 2020--07--28
**********************************************/
#include <iostream>
#include <unordered_set>
#include <stdlib.h>
#include <vector>
class Solution{
    public:
//944. 删列造序
        int  minDeletionSize_I(std::vector<std::string>& A){
            int size_0 = A[0].size();
            int size_1 = A.size();
            int res  = 0;
            for(int i=0; i<size_0; ++i){
                for(int j=1; j<size_1; ++j){
                    if(A[j][i]<A[j-1][i]){
                        ++res;
                        break;
                    }
                }
            }
            return res;
        }

//给定由 N 个小写字母字符串组成的数组 A，其中每个字符串长度相等。 选取一个删除索引序列，对于 A 中的每个字符串，删除对应每个索引处的字符。 比如，有 A = ["abcdef", "uvwxyz"]，删除索引序列 {0, 2, 3}，删除后 A 为["bef", "vyz"]。
        int minDeletionSize_II(std::vector<std::string>& A){
            int size_0 = A[0].size();
            int size_1 = A.size();
            int res    = 0;
            int comm   = 0;
            std::vector<int> mp(size_0, 0);
            for(int j=1,i=0; i<size_0; ++i){
                comm = 0;
                for(j=1; j<size_1; ++j){
                    if(A[j][i] < A[j-1][i]){
                        if(!i){
                            ++res;
                            ++mp[i];
                            break;
                        }else{
                            int k = i - 1;
                            for(; k>=0; --k){
                                if(!mp[k] && A[j][k]>A[j-1][k])break;
                            }
                            if(k!=-1)continue;
                            ++res,++mp[i];
                            break;
                        }
                    }else if(A[j][i] == A[j-1][i]){
                        ++comm;
                    }
                }
                if(!comm && j==size_1)return res;
            }
            return res;
        }
//960. 删列造序 III
    int minDeletionSize_III(std::vector<std::string>& A){
        const int size = A.size();
        const int len  = A[0].length();
        int   res = -1;
        std::vector<int> dp(len, 1);
        for(int i=0; i<len; ++i){
            for(int j=0,k=0; j<i; ++j){
                for(k=0; k<size; ++k){
                    if(A[k][j] > A[k][i])break;
                }
                if(k<size)continue;
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
            res = std::max(res, dp[i]);
        }
        return len - res;
    }
};
};
