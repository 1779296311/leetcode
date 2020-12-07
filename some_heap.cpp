/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_heap.cpp
*     author   : @ JY
*     date     : 2020--10--14
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <set>
#include <map>
#include <functional>
#include <climits>
#include <unordered_map>
#include <cmath>
#include <unordered_set>
#include <stdlib.h>

class MedianFinder{
    public:
        MedianFinder(){}
        std::priority_queue<int> big;
        std::priority_queue<int, std::vector<int>, std::greater<>> small;
        void addNum(int num){
            int diff = big.size() > small.size();
            if(big.size() && big.top() > num){
                big.push(num);
                ++diff;
            }else{
                small.push(num);
                --diff;
            }
            if(diff > 1)small.push(big.top()), big.pop();
            if(diff < 0)big.push(small.top()), small.pop();
        }
        double findMedian(){
            if((small.size() + big.size()) & 1)return big.top();
            return (small.top() + big.top()) / 2.;
        }
};
class Solution{
    public:
//373. 查找和最小的K对数字
        std::vector<std::vector<int>> kSmallestPairs_pii(std::vector<int> &nums1, std::vector<int> &nums2, int k){
            int _f = 0;
            if(nums1.size() > nums2.size())std::swap(nums1, nums2), _f = 1;
            int len1 = nums1.size(), len2 = nums2.size();
            if(!len1 || !len2)return {};
            using pii   = std::pair<int, int>;
            using pipii = std::pair<int, pii>;
            std::vector<std::vector<int>> res;
            std::priority_queue<pipii, std::vector<pipii>, std::greater<>> q;
            for(int i=0; i<len1; ++i)q.push({nums1[i]+nums2[0], {nums1[i], 0}});
            while(k-- && q.size()){
                auto [sum, v] = q.top(); q.pop();
                auto [n1, i2] = v;
                if(_f)  res.push_back({nums2[i2], n1});
                if(!_f) res.push_back({n1, nums2[i2]});
                if(++i2 >= len2)continue;
                q.push({n1+nums2[i2], {n1, i2}});
            }
            return res;
        }
        std::vector<std::vector<int>> kSmallestPairs(std::vector<int> &nums1, std::vector<int> &nums2, int k){
            using pii   = std::pair<int, int>;
            using pipii = std::pair<int, pii>;
            std::vector<std::vector<int>> res;
            struct _cmp{
                bool operator () (const pipii &a, const pipii &b) const {
                    return a.first + a.second.first > b.first  + b.second.first; }
            };
            std::priority_queue<pipii, std::vector<pipii>, _cmp> q;
            int len1 = nums1.size(), len2 = nums2.size();
            for(int i=0; i<len1; ++i)q.push({nums1[i], {nums2[0], 0}});
            while(k-- && q.size()){
                auto [v1, s1] = q.top();q.pop();
                auto [v2, i2] = s1;
                res.push_back({v1, v2});
                if(++i2 < len2){
                    q.push({v1 ,{nums2[i2], i2}});
                }
            }
            return res;
        }

//1046. 最后一块石头的重量
        int lastStoneWeight(std::vector<int> &stones){
            std::priority_queue<int> q(begin(stones), end(stones));
            while(q.size() > 1){
                int x = q.top();q.pop();
                int y = q.top();q.pop();
                if(x==y)continue;
                q.push(abs(x-y));
            }
            return q.size() ? q.top() : 0;
        }
//218. 天际线问题
        std::vector<std::vector<int>> getSkyline(std::vector<std::vector<int>> &buildings){
            std::multiset<std::pair<int, int>> mst;
            std::vector<std::vector<int>> res;
            for(auto &p : buildings){
                mst.insert({p[0], -p[2]});
                mst.insert({p[1], p[2]});
            }
            std::multiset<int> heights({0});
            int max_h = 0;
            for(auto &&[i, h] : mst){
                if(h < 0){
                    heights.insert(-h);
                }else{
                    heights.erase(heights.find(h));
                }
                int max_ = *heights.rbegin();
                if(max_ != max_h){
                    max_h = max_;
                    res.push_back({i, max_h});
                }
            }
            return res;
        }
//313. 超级丑数
        int nthSuperUglyNumber_dp(int n, std::vector<int> &primes){
            std::vector<long long> dp(n, 0);
            std::unordered_map<int, int> mp;
            for(auto &p : primes)mp[p] = 0;
            dp[0] = 1;
            for(int i=1; i<n; ++i){
                long long temp = dp[i-1] * primes[0];
                for(auto &p : primes){
                    temp = std::min(temp, dp[mp[p]]*p);
                }
                for(auto &&[k, v] : mp){
                    if(temp == dp[v] * k)++v;
                }
                dp[i] = temp;
            }
            return dp[n-1];
        }
        int nthSuperUglyNumber(int n, std::vector<int> &primes){
            std::unordered_set<long long> mp;
            std::priority_queue<long long, std::vector<long long>, std::greater<>> q;
            q.push(1);
            int res = 1;
            while(n--){
                res = q.top();q.pop();
                for(long long x : primes){
                    long long temp = x * res;
                    if(temp>INT32_MAX || !mp.insert(temp).second)continue;
                    q.push(temp);
                }
            }
            return res;
        }
//871. 最低加油次数
        int minRefuelStopes(int target, int startFuel, std::vector<std::vector<int>> &stations){
            stations.push_back({target, 0});
            std::priority_queue<int> q;
            int res = 0;
            for(auto &p : stations){
                if(startFuel >= target)return res;
                while(startFuel < p[0] && q.size()){
                    ++res;
                    startFuel += q.top();
                    q.pop();
                }
                if(startFuel < p[0])return -1;
                q.push(p[1]);
            }
            return startFuel<target ? -1 : res;
        }
//857. 雇佣 K 名工人的最低成本
        double mincostToHireWorkes(std::vector<int> &quality, std::vector<int> &wage, int K){
            using pdi = std::pair<double, int>;
            int len = quality.size();
            std::vector<pdi> mp(len);
            for(int i=0; i<len; ++i){
                mp[i] = {(double)wage[i]/quality[i], quality[i]};
            }
            std::sort(begin(mp), end(mp));
            std::priority_queue<int> q;
            double res = INT_MAX, sum = 0;
            for(auto [r, v] : mp){
                if(q.size() < K){
                    q.push(v);
                    sum += v;
                }
                if(q.size()==K){
                    res = std::min<double>(res, r * sum);
                    sum -= q.top();
                    q.pop();
                }
            }
            return res;
        }
//面试题 17.09. 第 k 个数
        int getKthMagicNumber_dp(int k){
            std::vector<int> dp(k+1);
            int i3 = 0, i5 = 0, i7 = 0;
            dp[0] = 1;
            for(int i=1; i<k; ++i){
                dp[i] = std::min(dp[i3]*3, std::min(dp[i5]*5, dp[i7]*7));
                if(dp[i]==dp[i3]*3)++i3;
                if(dp[i]==dp[i5]*5)++i5;
                if(dp[i]==dp[i7]*7)++i7;
            }
            return dp[k-1];
        }
//659. 分割数组为连续子序列
        bool isPossible_dp(std::vector<int> &nums){
            int len = nums.size();
            int dp_1 = 0, dp_2 = 0, dp_3 = 0;
            for(int i=0; i<len; ){
                int start = i;
                while(i<len && nums[start]==nums[i])++i;
                int cnt = i - start;
                if(start > 0 && nums[start] != nums[start-1] + 1){
                    if(dp_1 + dp_2)return false;
                    dp_1 = cnt;
                    dp_2 = dp_3 = 0;
                }else{
                    if(dp_1 + dp_2 > cnt)return false;
                    int remain = cnt - dp_1 - dp_2;
                    int add = std::min(dp_3, remain);
                    dp_3 = add + dp_2;
                    dp_2 = dp_1;
                    dp_1 = remain - add;
                }
            }
            return !dp_1 && !dp_2;
        }
        bool isPossible(std::vector<int> &nums){
            using pii  = std::pair<int, int>;
            using vpii = std::vector<pii>;
            std::priority_queue<pii, vpii, std::greater<pii>> q;
            std::unordered_map<int, int> mp;
            for(auto &x : nums)++mp[x];
            for(auto &&[k, v] : mp)q.push({k, v});
            while(q.size()){
                vpii temp;
                auto [cur, n] = q.top();q.pop();
                if(n-1)temp.emplace_back(cur, n-1);
                int cnt = 1;
                while(q.size()){
                    auto [k, v] = q.top();
                    if(k-cur > 1 || n > v)break;
                    q.pop();
                    cur = k;
                    n   = v;
                    if(n-1)temp.emplace_back(cur, n-1);
                    ++cnt;
                }
                if(cnt < 3)return false;
                for(auto &p : temp)q.push(p);
            }
            return true;
        }
//1439. 有序矩阵中的第 k 个最小数组和
        int kthSmallest_vio(std::vector<std::vector<int>> &mat, int k){
            std::vector<int> ans(mat[0]);
            int m = mat.size();
            for(int i=1; i<m; ++i){
                std::multiset<int> mt;
                for(auto &x : ans){
                    for(auto &y : mat[i])mt.insert(x+y);
                }
                ans.assign(begin(mt), end(mt));
                ans.resize(std::min(k, (int)ans.size()));
            }
            return ans.back();
        }
        int kthSmallest_heap(std::vector<std::vector<int>> &mat, int k){
            using vi   = std::vector<int>;
            using pivi = std::pair<int, vi>;
            struct _cmp{
                bool operator () (const pivi &a, const pivi &b) const {
                    return a.first > b.first; }
            };
            std::priority_queue<pivi, std::vector<pivi>, _cmp> q;
            std::set<vi> mp;
            int base = 0, m = mat.size(), n = mat[0].size();
            for(auto &v : mat)base += v.front();
            q.push({base, vi(m,0)});
            for(int i=0; i<k; ++i){
                auto [s, v] = q.top();q.pop();
                for(int j=1; j<m; ++j){
                    if(v[j] + 1 >= n)continue;
                    auto temp = v;
                    ++temp[j];
                    if(!mp.insert(temp).second)continue;
                    int sum = s + mat[j][temp[j]] - mat[j][temp[j]-1];
                    q.push({sum, temp});
                }
            }
            return q.top().first;
        }
        int kthSmallest_bsearch(std::vector<std::vector<int>> &mat, int k){
            int m = mat.size();
            int l = 0, r = 0;
            for(int i=0; i<m; ++i)l+=mat[i][0] , r+=mat[i].back();
            std::function<void(int, int, int&, int)> _dfs = [&](int i, int sum, int& cnt, int max_){
                if(i>=m)return;
                if(cnt > k || sum > max_)return;
                _dfs(i+1, sum, cnt, max_);
                for(int j=1; j<mat[i].size(); ++j){
                    int temp = sum + mat[i][j] - mat[i][0];
                    if(temp > max_)return;
                    _dfs(i+1, temp, ++cnt, max_);
                }
            };
            int base = l;
            while(l < r){
                int mid = l + ((r-l)>>1);
                int cnt = 1;
                _dfs(0, base, cnt, mid);
                if(cnt < k){
                    l = mid + 1;
                }else{
                    r = mid;
                }
            }
            return r;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    std::vector<std::vector<int>>mat =
{{ 53,58,146,234,245,247,261,357,361,375 },{77,97,183,260,282,293,296,356,363,365},{9,39,162,194,229,240,291,318,338,344},{42,157,198,212,265,268,290,314,378,384},{74,123,139,243,247,249,268,344,366,377},{21,40,98,106,111,173,194,198,214,243},{33,48,86,104,130,142,145,163,222,369},{3,88,101,189,322,341,346,359,385,400},{90,158,158,180,184,283,297,312,322,376},{12,18,24,143,152,161,161,169,210,220},{15,53,131,132,166,274,283,293,366,372},{28,35,63,91,135,162,184,256,272,351},{49,75,76,106,188,225,265,319,330,331},{15,19,65,83,176,269,310,361,376,389},{91,127,132,180,191,228,246,263,352,396},{9,43,49,188,208,260,286,304,311,383},{133,155,212,251,308,322,356,374,377,377},{1,71,108,110,158,180,202,221,392,395},{39,77,109,147,150,162,175,231,244,319},{76,149,231,240,275,303,342,366,382,398}};
    ::std::cout<<te.kthSmallest_bsearch(mat, 36)<<::std::endl;
    return 0;
}
