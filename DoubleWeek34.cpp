/*********************************************
*     ------------------------
*     ------------------------
*     file name: DoubleWeek34.cpp
*     author   : @ JY
*     date     : 2020--09--06
**********************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <functional>
#include <numeric>
#include <stdlib.h>

class Solution{
    int diagonalSUm(std::vector<std::vector<int>>& mat){
        int res = 0;
        int n = mat.size();
        for(int i=0; i<n; ++i)res += mat[i][i] + mat[i][n-i-1];
        if(n&1)res -= mat[n/2][n/2];
        return res;
    }
//5492. 分割字符串的方案数
    int numWays(std::string s){
        int MOD = 1e9 + 7;
        int len = s.length();
        std::vector<long long> ones(len, -1);
        int c = 0;
        for(int i=0; i<len; ++i)c+=s[i]=='1', ones[i]=s[i]=='1'?c:-1;
        if(c%3)return 0;
        if(!c)return (static_cast<long long>(len-2)*static_cast<long long>(len-1)%MOD)/2;
        c /= 3;
        long long t1, t2, t3, t4;
        int i = 0;
        for(; i<len && ones[i]!=c;   ++i);t1 = i++;
        for(; i<len && ones[i]==-1;  ++i);t2 = i;
        for(; i<len && ones[i]!=2*c; ++i);t3 = i++;
        for(; i<len && ones[i]==-1;  ++i);t4 = i;
        return ((t2-t1) * (t4-t3)) % MOD;
    }
    int findLongestOfShorestSubarray(std::vector<int>& arr){
        int len = arr.size();
        int le  = 0;
        int ri  = len - 1;
        int i;
        for(i=1; i<len && arr[i]>=arr[i-1]; ++i);
        if(i==len)return 0;
        le = i - 1;
        for(i=len-1; i>=0&&arr[i]>=arr[i-1]; --i);
        ri = i;
        int res = ri - le - 1;
        int l = 0, r = ri;
        while(l<=le && r<len){
            if(arr[l] > arr[r])++res, ++r;
            ++l;
        }
        return res;
    }
//5494. 统计所有可行路径
    int countRoutes(std::vector<int>& locations, int start, int finish, int fuel){
        int MOD = 1e9 + 7;
        int n   = locations.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(201, 0));
        dp[start][0] = 1;
        int t;
        for(int f=0; f<fuel; ++f){
            for(int i=0; i<n; ++i){
                for(int j=0; j<n; ++j){
                    if(i==j)continue;
                    if((t=f+abs(locations[i]-locations[j]))>200)continue;
                    dp[i][t] = (dp[i][t] + dp[j][f]) % MOD;
                }
            }
        }
        int res = 0;
        for(int i=0; i<=fuel; ++i)res += dp[finish][i];
        return res;
    }
};
