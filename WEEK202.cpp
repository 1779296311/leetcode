/*********************************************
*     ------------------------
*     ------------------------
*     file name: WEEK202.cpp
*     author   : @ JY
*     date     : 2020--08--16
**********************************************/
#include <iostream>
#include <climits>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <stdlib.h>
class Solution{
    public:
//5185. 存在连续三个奇数的数组
        bool threeConsecutiveOdds(std::vector<int>& arr){
            int res = 0;
            for(int i=0; i<arr.size(); ++i){
                res += arr[i] & 1;
                if(i>=3)res -= arr[i-3] & 1;
                if(res >=3)return true;
            }
            return false;
        }
//5488. 使数组中所有元素相等的最小操作数
        int minOption(int n){
            return n*n>>2;
        }
//5489. 两球之间的磁力
        int maxDistance(std::vector<int>& p, int m){
            std::sort(p.begin(), p.end());
            int size = p.size();
            std::function<bool(int)> clac = [&](int mid){
                int n = 0;
                int t = p[0] + mid;
                for(int i=0; i<size-1; ++i){
                    if(p[i]<t && p[i+1]>=t){
                        t = p[i+1] + mid;
                        ++n;
                    }
                }
                return m-1<=n;
            };
            int r = p[size-1]/(m-1);
            int l = INT_MAX;
            for(int i=1; i<size; ++i){
                l = std::min(l, p[i]-p[i-1]);
            }
            while(l <= r){
                int mid = l + ((r - l)>>1);
                if(clac(mid)){
                    l = mid + 1;
                }else{
                    r = mid - 1;
                }
            }
            return --l;
        }
        std::unordered_map<int, int> mp;
        int minDays(int n){
            if(n<=2)return n;
            if(mp.count(n))return mp[n];
            return mp[n] = std::min(n%2 + minDays(n/2), n%3+minDays(n/3)) + 1;
        }
        int minDays_fuck(int n){
            std::unordered_map<int, int> dp;
            dp[n]   = 0;
            dp[n-1] = 1;
            int sum = 2;
            for(int i=n-2; i>=0; --i,++sum){
                dp[i] = dp[i+1] + 1;
                if(!(sum%2))dp[i] = std::min(dp[i], dp[std::min(i+(sum>>1), n)] + 1);
                if(!(sum%3))dp[i] = std::min(dp[i], dp[std::min(i+((sum/3)<<1), n)] + 1);
            }
            return dp[0];
        }
};
