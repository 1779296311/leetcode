/*********************************************
*     ------------------------
*     ------------------------
*     file name: DoubleWeek28.cpp
*     author   : @ JY
*     date     : 2020--06--06
**********************************************/
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <stdlib.h>
#include <vector>
class Solutoin{
    public:
        bool canBeEqual(::std::vector<int>& t, ::std::vector<int>& arr){
            ::std::sort(t.begin(), t.end());
            ::std::sort(arr.begin(), arr.end());
            return t == arr;
        }
        bool hasAllCode(::std::string s, int k){
            int M = 0;
            ::std::unordered_set<int> mp;
            for(int i=0; i<s.size(); ++i){
                M =  M*2 + s[i]-'0';
                if(i>=k)M -= (s[i-k] - '0') << k;
                if(i>=k-1)mp.insert(M);
            }
            return mp.size() == (1<<k);
        }
        ::std::vector<bool> checkIfPrerequisite(int n,::std::vector<::std::vector<int>>& ps, ::std::vector<::std::vector<int>>& qs){
            ::std::vector<::std::vector<bool>> table(n,::std::vector<bool>(n,false));
            for(auto p : ps)table[p[0]][p[1]] = true;
            for(int k=0; k<n; ++k){
                for(int i=0; i<n; ++i){
                    for(int j=0; j<n; ++j){
                        if(table[i][k] && table[k][j]){
                            table[i][j] = true;
                        }
                    }
                }
            }
            ::std::vector<bool> res;
            for(auto q : qs)res.push_back(table[q[0]][q[1]]);
            return res;
        }
        int cherryPickup(::std::vector<::std::vector<int>>& grid) {
            int res   = 0;
            int size1 = grid.size();
            int size2 = grid[0].size();
            ::std::vector<::std::vector<::std::vector<int>>> dp(size1, ::std::vector<::std::vector<int>>(size2,::std::vector<int>(size2,-1)));
            dp[0][0][size2-1] = grid[0][0] + grid[0][size2-1];
            for(int k=1; k<size1; ++k){
                for(int i=0; i<size2; ++i){
                    for(int j=0; j<size2; ++j){
                        for(int a=i-1; a<=i+1; ++a){
                            for(int b=j-1; b<=j+1; ++b){
                                if(a<0 || b<0 || a>=size2 || b>=size2)continue;
                                if(dp[k-1][a][b]==-1)continue;
                                int t = grid[k][i] + dp[k-1][a][b];
                                if(i!=j)t += grid[k][j];
                                dp[k][i][j] = ::std::max(dp[k][i][j],t);
                            }
                        }
                        res = ::std::max(res,dp[k][i][j]);
                    }
                }
            }
            return res;
        }
};
int main(int argc,const char *argv[]){
    return 0;
}
