/*********************************************
*     ------------------------
*     ------------------------
*     file name: WEEK192.cpp
*     author   : @ JY
*     date     : 2020--06--08
**********************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <stdlib.h>
class Solution{
    public:
        ::std::vector<int> shuffle(::std::vector<int>& nums, int n){
            ::std::vector<int> res;
            for(int i=0; i<n; ++i){
                res.push_back(nums[i]);
                res.push_back(nums[i+n]);
            }
            return res;
        }

        ::std::vector<int> getStrongest(::std::vector<int>& nums, int k){
            ::std::sort(nums.begin(), nums.end());
            int m = nums[(nums.size()-1)/2];
            ::std::sort(nums.begin(), nums.end(), [&](int a, int b){
                    return abs(a-m)==abs(b-m)?a>b:abs(a-m)>abs(b-m);
            });
            return ::std::vector<int>(nums.begin(),  nums.begin()+k);
        }

        int minCost(::std::vector<int>& houses, ::std::vector<::std::vector<int>>& cost, int m, int n, int target) {
            ::std::vector<::std::vector<::std::vector<int>>> dp(m, ::std::vector<::std::vector<int>>(m+1,::std::vector<int>(n+1,1e8)));
            if(houses[0]){
                dp[0][1][houses[0]] = 0;
            }else{
                for(int i=0; i<n; ++i){
                    dp[0][1][i+1] = cost[0][i];
                }
            }
            for(int i=1; i<=m; i++){
                for(int t=1; t<=target; ++t){
                    if(houses[i]){
                        int c = houses[i];
                        for(int p=1; p<=n; ++p){
                            if(p==c) dp[i][t][c] = ::std::min(dp[i][t][c], dp[i-1][t][p]);
                            else     dp[i][t][c] = ::std::min(dp[i][t][c], dp[i-1][t-1][p]);
                        }
                    }else{
                        for(int p1=1; p1<=n; ++p1){
                            for(int p2=1; p2<=n; ++p2){
                                if(p1==p2)dp[i][t][p1] = ::std::min(dp[i][t][p1], dp[i-1][t][p2]+cost[i][p1-1]);
                                else      dp[i][t][p1] = ::std::min(dp[i][t][p1], dp[i-1][t-1][p2]+cost[i][p1-1]);
                            }
                        }
                    }
                }
            }
            int res = 1e8;
            for(int i=1; i<=n; ++i)res = ::std::min(dp[m-1][target][i], res);
            return res==1e8?-1:res;
        }

        class BrowserHistory {
        public:
            ::std::vector<::std::string> lt;
            int cur;
            BrowserHistory(::std::string homepage) {
                lt.push_back(homepage);
                cur = 0;
            }
            
            void visit(::std::string url) {
                lt.erase(lt.begin()+cur+1, lt.end());
                lt.push_back(url);
                ++cur;
            }
            
            ::std::string back(int steps) {
                cur  = ::std::max(0,cur-steps);
                return lt[cur];
            }
            
            ::std::string forward(int steps) {
                cur      = ::std::min((int)lt.size()-1, cur+steps);
                return lt[cur];
            }
        };
};
