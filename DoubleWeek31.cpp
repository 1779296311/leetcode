/*********************************************
*     ------------------------
*     ------------------------
*     file name: DoubleWeek31.cpp
*     author   : @ JY
*     date     : 2020--07--26
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdlib.h>
class Solution{
    public:
        int count0dds(int l, int h){
            if(l&1 || h&1)return ((h - l)>>1) + 1;
            return ((h - l)>>1);
        }
        int numOfSubarrar(std::vector<int>& nums){
            int res  = 0;
            int MOD  = 1e9 + 7;
            int e = 0, o = 1;
            int sum  = 0;
            for(auto &n : nums){
                sum += n;
                if(sum & 1){
                    ++e;
                    res  = (o + res) % MOD;
                }else{
                    res  = (e + res) % MOD;
                    ++o;
                }
            }
            return res % MOD;
        }
        int numOfSubarrar_fuck(std::vector<int>& nums){
            int size = nums.size();
            int res  = 0;
            std::vector<std::vector<int>> sums(size, std::vector<int>(size, 0));
            for(int i=0; i<size; ++i){
                for(int j=i; j<size; ++j){
                    if(i==j){
                        if((sums[i][j] = nums[i]) % 1) ++res;
                        continue;
                    }
                    if((sums[i][j]=sums[i][j-1]+nums[j])%1)++res;
                }
            }
            return res;
        }
        int numSplit(std::string& s){
            std::vector<int> l(26, 0), r(26, 0);
            int right = 0, left = 0;
            int res   = 0;
            for(auto &c : s)right += (!r[c-'a']++);
            for(auto &c : s){
                if( (left  += (!l[c-'a']++))
                           == 
                    (right -= (!--r[c-'a'])) )++res;
            }
            return res;
        }
        int minNumberOperations(std::vector<int>& target){
            int res = target[0];
            for(int i=1; i<target.size(); ++i){
                res += std::max(target[i] - target[i-1], 0);
            }
            return res;
        }
        int minNumberOperations_fuck(std::vector<int>& target){
            int res = 0;
            int s   = 0;
            for(int i=0; i<target.size(); ++i){
                if(!target[i]){
                    res += dfs(s, i-1, target);
                    s    = i+1;
                }
            }
            res += dfs(s, target.size()-1, target);
            return res;
        }
        int dfs(int l, int r, std::vector<int>& t){
            if(l>r)return 0;
            if(l==r)return t[l];
            int res  = 0;
            int m    = *max_element(t.begin()+l, t.begin()+r+1);
            auto tmp = t;
            for(int i=l; i<=r; ++i)tmp[i] -= m;
            int s = l;
            for(int i=l; i<=r; ++i){
                if(t[i]==m){
                    res += dfs(s, i-1, tmp);
                    s    = i+1;
                }
            }
            return res + m + dfs(s, r, tmp);
        }
};
