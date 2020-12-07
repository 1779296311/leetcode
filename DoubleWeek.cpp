/*********************************************
*     ------------------------
*     ------------------------
*     file name: DoubleWeek.cpp
*     author   : @ JY
*     date     : 2020--09--20
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>
#include <climits>
#include <set>
#include <map>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <cstring>
#include <stdlib.h>
struct ListNode{
    int val;
    ListNode *next;
    ListNode() : val(0) , next(NULL) {}
    ListNode(int x) : val(x) , next(NULL) {}
    ListNode(int x, ListNode *n) : val(x) , next(n) {}
};
namespace DE40{
    class FrontMiddleBackQueue{
        std::deque<int> l, r;
        FrontMiddleBackQueue(){ }
        void pushFront(int val){
            l.push_front(val);
            if(l.size() > r.size() + 1){
                r.push_front(l.back());
                l.pop_back();
            }
        }
        void pushMiddle(int val){
            if(l.size() > r.size()){
                r.push_front(l.back());
                l.pop_back();
            }
            l.push_back(val);
        }
        void pushBack(int val){
            r.push_back(val);
            if(r.size() > l.size()){
                l.push_back(r.front());
                r.pop_front();
            }
        }
        int popFront(){
            int ans = -1;
            if(l.size()){
                ans = l.front();
                l.pop_front();
                if(l.size() < r.size()){
                    l.push_back(r.front());
                    r.pop_front();
                }
            }
            return ans;
        }
        int popMiddle(){
            int ans = -1;
            if(l.size()){
                ans = l.back();
                l.pop_back();
                if(l.size() < r.size()){
                    l.push_back(r.front());
                    r.pop_front();
                }
            }
            return ans;
        }
        int popBack(){
            int ans = -1;
            if(r.size()){
                ans = r.back();
                r.pop_back();
                if(l.size() > r.size() + 1){
                    r.push_front(l.back());
                    l.pop_back();
                }
            }else if(l.size()){
                ans = l.back();
                l.pop_back();
            }
            return ans;
        }

    };
    int minimimMountainRemovals(std::vector<int> &nums){
        int max_ = -1e8, len = nums.size();
        for(int i=1; i<len-1; ++i){
            if(max_ < nums[i])max_ = nums[i];
        }
        std::vector<int> idx;
        for(int i=1; i<len-1; ++i){
            if(max_ == nums[i])idx.push_back(i);
        }
        std::function<std::vector<int>(int f)> _dp = [&](int f){
                if(!f)std::reverse(begin(nums), end(nums));
                std::vector<int> dp(len, 1);
                for(int i=0; i<len; ++i){
                    for(int j=i; j>=0; --j){
                        if(nums[i] > nums[j]){
                            dp[i] = std::max(dp[i], dp[j] + 1);
                        }
                    }
                }
                if(!f)std::reverse(begin(dp), end(dp));
                return dp;
            };
        auto l = _dp(1);
        auto r = _dp(0);
        int ans = 1e5;
        for(int i=1; i<len-1; ++i)ans = std::min(ans,len - (l[i] + r[i] - 1));
        return ans;
    }
    ListNode *mergeInBetween(ListNode *list1, int a, int b, ListNode *list2){
        ListNode *l = list1, *r = list1, *t = list2;;
        while(--a)l = l->next;
        while(b--)r = r->next;
        while(t && t->next)t = t->next;
        l->next = list2;
        t->next = r->next;
        r->next = nullptr;
        return list1;
    }
    int maxRepeating(std::string sequence, std::string word){
        int k = 0, len = sequence.size(), len2 = word.size();
        std::string wd = word;
        for(int i=1; i<=len/len2; ++i){
            if(sequence.find(word) != std::string::npos){
                k = i;
            }
            word += wd;
        }
        return k;
    }
};
namespace DW39{
    class Solution{
        public:
//5553. 分配重复整数
            bool canDistribute(std::vector<int> &nums, std::vector<int> &quantity){
                std::unordered_map<int, int> temp;
                for(auto &x : nums) ++temp[x];
                std::vector<int> cnt;
                for(auto &[c, n] : temp)cnt.emplace_back(n);
                int n = cnt.size(), m = quantity.size();
                std::vector<int> sum(1 << m);
                for(int i=0; i<m; ++i)sum[1 << i] = quantity[i];
                for(int i=0; i<(1 << m); ++i)sum[i] = sum[i^(i&-i)] + sum[i&-i];
                //for(int i=1; i<(1 << m); ++i){
                    //for(int j=0; j<m; ++j){
                        //if(!(i & (1 << j)))continue;
                        //int l = i ^ (1 << j) ;
                        //sum[i] = sum[l] + quantity[j];
                        //break;
                    //}
                //}
                std::vector<std::vector<bool>> dp(n, std::vector<bool>(1 << m));
                for(int i=0; i<n; ++i)dp[i][0] = true;
                for(int i=0; i<n; ++i){
                    for(int state=0; state<(1 << m); ++state){
                        if(i && dp[i-1][state]){
                            dp[i][state] = true;
                            continue;
                        }
                        for(int pre=state; pre; pre=(pre-1) & state){
                            int p = i ? dp[i-1][state ^ pre] : !(state^pre);
                            if(p && sum[pre] <= cnt[i]){
                                dp[i][state] = true;
                                break;
                            }
                        }
                    }
                }
                return dp[n-1][(1 << m) - 1];
            }
            bool canDistribute_fuck(std::vector<int> &nums, std::vector<int> &quantity){
                std::unordered_map<int, int> mp;
                for(auto &x : nums)++mp[x];
                std::priority_queue<int> q;
                for(auto &[c, n] : mp)q.emplace(n);
                std::sort(begin(quantity), end(quantity), [&](auto &a, auto &b){
                        return a > b; });
                std::vector<int> temp;
                int j = 0, m = quantity.size();
                while(q.size() && j<m){
                    if(q.top() < quantity[j])return false;
                    temp.clear();
                    int dif = INT_MAX, idx = -1, t = 0;
                    while(q.size() && q.top() >= quantity[j]){
                        int tmp = q.top();q.pop();
                        if(tmp - quantity[j] < dif){
                            dif = tmp - quantity[j];
                            idx = t;
                        }
                        temp.emplace_back(tmp);
                        ++t;
                    }
                    temp[idx] -= quantity[j++];
                    if(j==m)return true;
                    for(auto &x : temp){
                        if(x < quantity.back())continue;
                        q.push(x);
                    }
                }
                return j==m;
            }
//5552. 到家的最少跳跃次数
            int minimumJumps_(std::vector<int> &forbidden, int a, int b, int x){
                std::vector<int> dp(4001, INT_MAX);
                for(auto &x : forbidden)dp[x] = -1;
                std::function<void(int, int, int)> _dfs = [&](int i, int cnt, int s){
                    if(i<0 || i>4000 || dp[i] <= s)return;
                    dp[i] = s;
                    if(!cnt)_dfs(i - b, 1, s + 1);
                    _dfs(i + a, 0, s + 1);
                };
                _dfs(0, 0, 0);
                return dp[x] == INT_MAX ? -1 : dp[x];
            }
            int minimumJumps(std::vector<int> &forbidden, int a, int b, int x){
                int res = INT_MAX;
                std::vector<int> vi(6001);
                std::function<void(int, int, int)> _dfs = [&](int i, int cnt, int s){
                    if(i == 0){
                        res = std::min(res, s);
                        return;
                    }
                    if(i>=a && !vi[i-a]){
                        vi[i-a] = 1;
                        _dfs(i-a, 0, s + 1);
                    }
                    if(i+b < 6001 && !vi[i+b] && !cnt){
                        vi[i+b] = 1;
                        _dfs(i+b, 1, s + 1);
                        vi[i+b] = 0;
                    }
                };
                for(auto &x : forbidden)vi[x] = 1;
                _dfs(x, 0, 0);
                return res == INT_MAX  ? -1 : res;
            }
//5551. 使字符串平衡的最少删除次数
            int minimumDeletions_dp(std::string s){
                int len = s.size();
                std::vector<int> dpa(len), dpb(len);
                dpa[0] = s[0] == 'b';
                dpb[0] = s[0] == 'a';
                for(int i=1; i<len; ++i){
                    dpa[i] = dpa[i-1] + (s[i] == 'b');
                    dpb[i] = std::min(dpa[i-1], dpb[i-1]) + (s[i] == 'a');
                }
                return std::min(dpa[len-1], dpb[len-1]);
            }
            int minimumDeletions(std::string s){
                int len = s.size();
                std::vector<int> a(len), b(len);
                for(int i=0; i<len; ++i){
                    a[i] = (s[i] == 'b') + (i ? a[i-1] : 0);
                }
                for(int i=len-1; i>=0; --i){
                    b[i] = (s[i] == 'a') + (i<len-1 ? b[i+1] : 0);
                }
                int res = len;
                for(int i=0; i<len; ++i)res = std::min(res, a[i] + b[i]);
                return --res;
            }
//5550. 拆炸弹
            std::vector<int> decrypt(std::vector<int> &code, int k){
                std::vector<int> res;
                int len = code.size(), f = k > 0 ? 1 : -1;
                k = abs(k);
                for(int i=0; i<len; ++i){
                    int j = i, t = k, a = 0;
                    while(t--)a += code[((j += f) + len) % len];
                    res.emplace_back(a);
                }
                return res;
            }
    };
};
namespace DW208{
    class Solution{
        public:
//5542. 通过给定词典构造目标字符串的方案数
            int numWays(std::vector<std::string> &words, std::string target){
                int MOD = 1e9 + 7;
                int n = words.size(), len = words[0].size(), size = target.size();
                std::vector<std::vector<long long>> cnt(len, std::vector<long long>(26));
                for(int i=0; i<n; ++i){
                    for(int j=0; j<len; ++j){
                        ++cnt[j][words[i][j]-'a'];
                    }
                }
                std::vector<std::vector<long long>> dp(size, std::vector<long long>(len));
                dp[0][0] = cnt[0][target[0]-'a'];
                for(int i=1; i<len; ++i)dp[0][i] = dp[0][i-1] + cnt[i][target[0]-'a'];
                for(int i=1; i<size; ++i){
                    for(int j=i; j<len; ++j){
                        dp[i][j] = ((dp[i-1][j-1] * cnt[j][target[i]-'a'])%MOD + dp[i][j-1]) % MOD;
                    }
                }
                return dp[size-1][len-1];
            }
//5541. 统计只差一个字符的子串数目
            int countSubstring_dp(std::string s, std::string t){
                int m = s.size(), n = t.size();
                int row = 0, col = n - 1;
                int i, j;
                int res = 0, len = 0, ans = 0;
                while(row < m){
                    i = row, j = col;
                    len = ans = 0;
                    while(i<m && j<n){
                        if(s[i] == t[j]){
                            ++len;
                        }else{
                            ans = len + 1;
                            len = 0;
                        }
                        res += ans;
                        ++i, ++j;
                    }
                    col ? --col : ++row;
                }
                return res;
            }
            int countSubstring(std::string s, std::string t){
                int m = s.size(), n = t.size();
                int res = 0;
                for(int i=0; i<m; ++i){
                    for(int j=0; j<n; ++j){
                        int dif = 0;
                        for(int k=0; i+k<m && j+k<n; ++k){
                            dif += s[i+k] != t[j+k];
                            if(dif > 1)break;
                            res += dif;
                        }
                    }
                }
                return res;
            }
//5540. 两点之间不包含任何点的最宽垂直面积
            int maxWidthOfVertcalArea(std::vector<std::vector<int>> &points){
                std::sort(begin(points), end(points), [&](auto &a, auto &b){
                        return a[0] < b[0]; });
                int res = 0, pre = points[0][0];
                for(auto &p : points){
                    res = std::max(res, p[0] - pre);
                    pre = p[0];
                }
                return res;
            }
//5539. 按照频率将数组升序排序
            std::vector<int> frequencySort(std::vector<int> &nums){
                std::unordered_map<int, int> mp;
                for(auto &n : nums)++mp[n];
                std::vector<int> res;
                std::vector<std::pair<int, int>> temp(begin(mp), end(mp));
                std::sort(begin(temp), end(temp), [&](auto &a, auto &b){
                    return a.second == b.second ? a.first > b.first : a.second < b.second; });
                for(auto &[k, v] : temp)res.insert(end(res), v, k);
                return res;
            }
    };
};
namespace DW207{
    class Fancy_fuck{
        public:
            Fancy_fuck(){ }
            void append(int val){
                //nums.emplace_back(val, time);
                nums1[index++] = { val, time };
            }
            void addAll(int inc){
                op1[time++] = {1, inc};
                //++time;
                //op.push_back({1, inc});
            }
            void multAll(int m){
                op1[time++] = {2, m};
                //++time;
                //op.push_back({2, m});
            }
            int getIndex(int idx){
                if(idx >= index)return -1;
                //auto [val, t] = nums[idx];
                auto [val, t] = nums1[idx];
                long long res = val;
                for(int i=t; i<time; ++i){
                    if(op1[i].f==1){
                        res = (res + op1[i].s) % MOD;
                    }else{
                        res = (res * op1[i].s) % MOD;
                    }
                }
                return (res % MOD);
            }
        private:
            struct _node{
                int f,  s;
                _node(int t=0,int v=0) : f(t), s(v) {}
            };
            _node nums1[100001], op1[100001];
            int time = 0, MOD = 1e9 +7, index = 0;
            //std::vector<_node> nums;
            //std::vector<_node> op;
    };
    class Solution{
        public:
//5527. 大小为 K 的不重叠线段的数目
            int numberofSets(int n, int k){
                int MOD = 1e9 + 7;
                std::vector<int> dp_1(k+1, 0), dp_0(k+1, 0);
                std::vector<int> sums(k+1, 0);
                for(int i=1; i<n; ++i){
                    dp_1[0] = i * (i+1) / 2;
                    for(int j=1; j<k; ++j){
                        dp_1[j] = (dp_0[j] + sums[j-1]) % MOD;
                    }
                    dp_0 = dp_1;
                    for(int j=0; j<k; ++j)sums[j] = (sums[j] + dp_0[j]) % MOD;
                }
                return dp_0[k-1];
            }
//5528. 网络信号最好的坐标
            std::vector<int> bestCoordinate(std::vector<std::vector<int>> &towers, int radius){
                std::vector<int> res {-1, -1};
                int ans = -1;
                for(int i=0; i<=50; ++i){
                    for(int j=0; j<=50; ++j){
                        int sum = 0;
                        for(auto &p : towers){
                            double d = std::pow((i-p[0]), 2)  + std::pow((j-p[1]), 2);
                            d = std::sqrt(d);
                            if(d<=radius){
                                sum += p[2] / (d+1);
                            }
                        }
                        if(sum > ans)ans = sum, res = {i, j};
                    }
                }
                return res;
            }
//5122. 删除某些元素后的数组均值
            double triMean(std::vector<int> &arr){
                int size  = arr.size();
                int dsize = size / 20;
                std::sort(begin(arr), end(arr));
                double sum = std::accumulate(begin(arr)+dsize, end(arr)-dsize, 0);
                return sum / (size - dsize * 2);
            }
    };
};
namespace DW206{
    class ParkingSystem{
        int bi;
        int me;
        int sm;
        ParkingSystem(int big, int medium, int small) : bi(big), me(medium), sm(small) {}
        bool addCar(int cartype){
            switch(cartype){
                case 1:
                    if(--bi < 0)return false;
                    return true;
                    break;
                case 2:
                    if(--me < 0)return false;
                    return true;
                    break;
                case 3:
                    if(--sm < 0)return false;
                    return true;
                    break;
            }
            return false;
        }
    };
    class Solution{
//5517. 找到处理最多请求的服务器
        std::vector<int> busiestServers(int k, std::vector<int> &arrival, std::vector<int> &load){
            std::set<int> st;
            for(int i=0; i<k; ++i)st.insert(i);
            std::vector<int> cnt(k), res;
            int n = arrival.size();
            std::priority_queue<std::pair<long long, int>> pq;
            for(int i=0; i<n; ++i){
                int now  = arrival[i];
                int cost = load[i];
                while(pq.size() && -pq.top().first <= now){
                    st.insert(pq.top().second);
                    pq.pop();
                }
                if(!st.size())continue;
                int pos = i % k;
                auto it = st.lower_bound(pos);
                if(it==st.end())it = st.begin();
                pos = *it;
                st.erase(pos);
                ++cnt[pos];
                pq.push({-(now+cost), pos});
            }
            int max_ = *max_element(begin(cnt), end(cnt));
            for(int i=0; i<k; ++i){
                if(max_==cnt[i])res.push_back(i);
            }
            return res;
        }
//1065. 给定行和列的和求可行矩阵
        std::vector<std::vector<int>> restoreMatrix_better
            (std::vector<int> &rowSum, std::vector<int> &colSum){
                int m = rowSum.size(), n = colSum.size();
                std::vector<std::vector<int>> res(m, std::vector<int>(n));
                for(int i=0; i<m; ++i){
                    for(int j=0; j<n; ++j){
                        res[i][j] = std::min(rowSum[i], colSum[j]);
                        rowSum[i] -= res[i][j];
                        colSum[j] -= res[i][j];
                    }
                }
                return res;
            }
        std::vector<std::vector<int>> restoreMatrix(std::vector<int> &rowSum, std::vector<int> &colSum){
            int m = rowSum.size();
            int n = colSum.size();
            std::vector<std::vector<int>> res(m, std::vector<int>(n));
            for(int k=0; k<m+n; ++k){
                int ni = -1, nj = -1;
                for(int i=0; i<m; ++i){
                    if(!rowSum[i])continue;
                    if(ni==-1 || (rowSum[ni] > rowSum[i]))ni = i;
                }
                for(int i=0; i<n; ++i){
                    if(!colSum[i])continue;
                    if(nj==-1  || (colSum[nj] > colSum[i]))nj = i;
                }
                if(nj==-1 || ni==-1)break;
                res[ni][nj] = std::min(rowSum[ni], colSum[nj]);
                rowSum[ni] -= res[ni][nj];
                colSum[nj] -= res[ni][nj];
            }
            return res;
        }
        std::vector<std::string> alertNames(std::vector<std::string> &keyName, std::vector<std::string> &keyTime){
            std::function<int(int)> _get_time = [&](int a){
                auto t = keyTime[a];
                return ((t[0]-'0')*10 + t[1]-'0')*60 + (t[3]-'0')*10+t[4]-'0';
            };
            std::map<std::string, std::vector<int>> mp;
            int size = keyName.size();
            for(int i=0; i<size; ++i){
                mp[keyName[i]].push_back(_get_time(i));
            }
            std::vector<std::string> res;
            for(auto &[name, v] : mp){
                if(v.size() < 2)continue;
                auto be = v.begin();
                auto en = v.end();
                std::sort(be, en);
                while(be+2 != en){
                    auto it = be + 2;
                    if(*it - *be <= 60){
                        res.push_back(name);
                        break;
                    }
                    ++be;
                }
            }
            return res;
        }
    };
};
class Solution{
    public:

//5506. 奇怪的打印机 II
        bool isPrintable(std::vector<std::vector<int>> &targetGrid){
            int m = targetGrid.size();
            int n = targetGrid[0].size();
            std::vector<int> top(61, m), bottom(61), left(61, n), right(61);
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    int c     = targetGrid[i][j];
                    top[c]    = std::min(i, top[c]);
                    bottom[c] = std::max(i, bottom[c]);
                    left[c]   = std::min(j, left[c]);
                    right[c]  = std::max(j, right[c]);
                }
            }
            std::vector<std::vector<int>> e(61);
            std::vector<std::vector<int>> vi(61, std::vector<int>(61));
            std::vector<int> in(61);
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    int c = targetGrid[i][j];
                    for(int color=1; color<=60; ++color){
                        if(top[color]>i || bottom[color]<i ||
                           left[color]>j  || right[color]<j)continue;
                        if(color==c || vi[color][c])continue;
                        vi[color][c] = 1;
                        e[color].push_back(c);
                        ++in[c];
                    }
                }
            }
            std::queue<int> q;
            for(int i=0; i<=60; ++i)if(!in[i])q.push(i);
            int res = 0;
            while(q.size()){
                int i = q.front();q.pop();
                --res;
                for(auto &t : e[i]){
                    if(!--in[t])q.push(t);
                }
            }
            return !res;
        }
//5504. 使数组和能被 P 整除
        int minSubarray(std::vector<int> &nums, int p){
            int size      = nums.size();
            long long mod = 0;
            for(int i=0; i<size; ++i)mod = (mod + nums[i]) % p;
            if(!mod)return mod;
            std::unordered_map<long long, int> mp;
            mp[0]         = -1;
            int res       = size;
            long long sum = 0;
            for(int i=0; i<size; ++i){
                sum += static_cast<long long>(nums[i]);
                int cur_mod = sum % p;
                mp[cur_mod] = i;
                int target_mod = (cur_mod-mod)+(cur_mod>=mod?0:p);
                if(mp.count(target_mod))res = std::min(res, i-mp[target_mod]);
            }
            return res==size?-1:res;
        }
//5505. 所有排列中的最大和
        int maxSumRangeQuery(std::vector<int> &nums, std::vector<std::vector<int>> requests){
            int MOD = 1e9 + 7;
            int n   = nums.size();
            std::vector<long long> mp(n+1);
            for(auto &p : requests)++mp[p[0]],--mp[p[1]+1];
            for(int i=1; i<n; ++i)mp[i] += mp[i-1];
            mp.pop_back();
            int res = 0;
            std::sort(mp.rbegin(), mp.rend());
            std::sort(nums.rbegin(), nums.rend());
            for(int i=0; i<n&&mp[i]; ++i){
                res = (res + (mp[i]*nums[i])) % MOD;
            }
            return res % MOD;
        }
        int maxSumRangeQuery_fuck(std::vector<int> &nums, std::vector<std::vector<int>> requests){
            int MOD = 1e9 + 7;
            int n   = nums.size();
            std::vector<int> mp(n);
            for(auto &p : requests){
                for(int i=p[0]; i<=p[1]; ++i)++mp[i];
            }
            std::sort(nums.rbegin(), nums.rend());
            std::sort(mp.rbegin(), mp.rend());
            long long res = 0;
            for(int i=0; i<n && mp[i]; ++i){
                res = (res + (mp[i]*nums[i])) % MOD;
            }
            return res % MOD;
        }

//5503. 所有奇数长度子数组的和
        int sumOdddLengthSubarry_better(std::vector<int> &arr){
            int res = 0;
            for(int i=0; i<arr.size(); ++i){
                int l = i + 1;
                int r = arr.size() - i;
                int le = (l+1)/2, lo=(l)/2;
                int re = (r+1)/2, ro=(r)/2;
                res += (le*re + lo*ro)* arr[i];
            }
            return res;
        }
        int sumOdddLengthSubarry(std::vector<int> &arr){
            int res = 0;
            std::vector<int> sums(arr);
            for(int i=1; i<arr.size(); ++i)sums[i] += sums[i-1];
            for(int l=1; l<=arr.size(); l+=2){
                int tmp = sums[l-1];
                res += tmp;
                for(int j=l; j<arr.size(); ++j){
                    tmp += arr[j];
                    tmp -= arr[j-l];
                    res += tmp;
                }
            }
            return res;
        }
};
