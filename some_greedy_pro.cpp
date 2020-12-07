/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_greedy_pro.cpp
*     author   : @ JY
*     date     : 2020--11--12
**********************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <climits>
#include <cmath>
#include <numeric>
#include <functional>
#include <stdlib.h>
struct Interval{
    int start, end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class Solution{
    public:
//1055. 形成字符串的最短路径
        int shorestWay_better(std::string source , std::string target){
            int i = 0, j = 0, len0 = source.size(), len1 = target.size(), res = 0;
            while(i<len1 && res<=i){
                while(j<len0 && source[j]!=target[i])++j;
                if(j == len0){
                    ++res;
                    j = 0;
                }else{
                    ++i, ++j;
                }
            }
            return res<=i ? res+1 : -1;
        }
        int shorestWay(std::string source , std::string target){
            std::vector<int> mp(26);
            for(auto &c : source)++mp[c-'a'];
            for(auto &c : target){
                if(!mp[c-'a'])return -1;
            }
            int i, j = 0, res = 0,
                len = target.size(), len1 = source.size();
            while(j < len){
                i = -1, ++res;
                while(j<len && ++i < len1){
                    j += source[i] == target[j];
                }
            }
            return res;
        }
//LeetCode 484. 寻找排列
        std::vector<int> findPermutation(std::string s){
            s.push_back('I');
            int l = -1, r = -1, len = s.size();
            std::vector<int> res(len);
            std::iota(begin(res) , end(res), 1);
            while(++r<len){
                if(s[r] == 'D'){
                    if(l==-1)l = r;
                }else if(s[r] == 'I'){
                    if(l==-1)continue;
                    reverse(begin(res)+l, begin(res)+r+1);
                    l = -1;
                }
            }
            return res;
        }
//1564. 把箱子放进仓库里 I
        int maxBoxesInWarehouse_better
            (std::vector<int> boxes, std::vector<int> warehouse){
                int len = boxes.size(), res = 0, len1 = warehouse.size();
                int l = 0, r = warehouse.size();
                std::vector<int> min_(warehouse);
                for(int i=1; i<len; ++i){
                    min_[i] = std::min(min_[i], min_[i-1]);
                }
                std::sort(begin(boxes), end(boxes));
                while(--r>=0 && l<len){
                    if(min_[r] >= boxes[l]){
                        ++l, ++res;
                    }
                }
                return res;
        }
        int maxBoxesInWarehouse(std::vector<int> boxes, std::vector<int> warehouse){
            std::sort(begin(boxes), end(boxes));
            int r = warehouse.size(), res = 0, l = 0, len = boxes.size();
            while(r >= 0 && l<len){
                int t = 0;
                while(t<r && boxes[l] <= warehouse[t])++t;
                if(t==0)break;
                ++res;
                ++l;
                r = t-1;
            }
            return res;
        }
//759. Employee Free Time 
        std::vector<Interval> emploteeFreeTime_better(std::vector<std::vector<Interval>> &schedule){
            std::map<int, int> mp;
            std::vector<Interval> res;
            for(auto &v : schedule){
                for(auto &x : v){
                    ++mp[x.start];
                    --mp[x.end];
                }
            }
            int cnt = 0;
            auto it = mp.begin(), t = mp.begin();
            while(it != end(mp)){
                cnt += it->second;
                t = it;
                if(++it!=end(mp) && !cnt){
                    res.emplace_back(t->first, it->first);
                }
            }
            return res;
        }
        std::vector<Interval> emploteeFreeTime(std::vector<std::vector<Interval>> &schedule){
            int len = schedule.size();
            std::vector<Interval> all, deal, res;
            for(int i=0; i<len; ++i){
                for(auto &x : schedule[i]){
                    all.push_back(x);
                }
            }
            std::sort(begin(all), end(all), [&](auto &a, auto &b){
                return a.start == b.start ? a.end < b.end : a.start < b.start; });
            deal.push_back(all[0]);
            len = all.size();
            for(int i=1; i<len; ++i){
                if(deal.back().end >= all[i].start){
                    deal.back().end = std::max(deal.back().end, all[i].end);
                }else{
                    deal.push_back(all[i]);
                }
            }
            len = deal.size();
            for(int i=0; i<len - 1; ++i){
                //if(deal[i].end < deal[i+1].start){
                    res.emplace_back(deal[i].end, deal[i+1].start);
                //}
            }
            return res;
        }
//[LeetCode] 651. 四键键盘
        int maxA(int N){
            std::vector<int> dp(N);
            dp[0] = 1, dp[1] = 2, dp[2] = 3;
            for(int i=3; i<N; ++i){
                dp[i] = std::max(dp[i], dp[i-1] + 1);
                for(int j=0; j<i-1; ++j){
                    dp[i] = std::max(dp[i], dp[j] * (i-j-1));
                }
            }
            return dp[N-1];
        }
//-1231. 分享巧克力
        int maximizeSweetness(std::vector<int> &sweetness, int k){
            int sum = std::accumulate(begin(sweetness), end(sweetness), 0);
            std::function<bool(int)> _judge = [&](int x){
                int m = 0, t = 0;
                for(auto &sw : sweetness){
                    if((m += sw) >= x){
                        m = 0;
                        ++t;
                    }
                }
                return t>k;
            };
            int l = 1, r = sum / (k + 1);
            while(l <= r){
                int m = l + ((r - l) >> 1);
                if(_judge(m)){
                    l = m + 1;
                }else{
                    r = m - 1;
                }
            }
            return --l;
        }
//253. 会议室 II
        int minMeetingRooms(std::vector<std::vector<int>> &intervals){
            std::sort(begin(intervals), end(intervals),[&](auto &a, auto&b){
                    return a[0] == b[0] ? a[1] < b[1] : a[0] < b[0]; });
            std::priority_queue<int, std::vector<int>, std::greater<int>> q;
            for(auto &x : intervals){
                if(q.size() && q.top()<=x[0]){
                    q.pop();
                }
                q.push(x[1]);
            }
            return q.size();
        }
//252 会议室（数组
        bool cnaAttendMeetings(std::vector<std::vector<int>> &intervals){
            std::sort(begin(intervals), end(intervals), [&](auto &a, auto &b){
                    return a[0] == b[0] ? a[1] < b[1] : a[0] < b[0]; });
            int pre = -1;
            for(auto &x : intervals){
                if(pre > x[0])return false;
                pre = x[1];
            }
            return true;
        }
//1167 连接棒材的最低费用（贪心，哈夫曼编码）
        int connestSticks(std::vector<int> &sticks){
            std::priority_queue<int, std::vector<int>, std::greater<int>>
                q(begin(sticks), end(sticks));
            int res = 0;
            while(q.size() > 1){
                int a = q.top();q.pop();
                int b = q.top();q.pop();
                res += a + b;
                q.push(a + b);
            }
            return res;
        }
//LeetCode-1058-3. 最小化舍入误差以满足目标
        std::string minimmizeError(std::vector<std::string> &prices, int target){
            int de;
            std::vector<int> decimal;
            for(auto &x : prices){
                target -= std::stoi(x);
                de = std::stoi(x.substr(x.size()-3));
                if(de)decimal.emplace_back(de);
            }
            if(decimal.size() < target || 0 > target)return "-1";
            std::sort(rbegin(decimal), rend(decimal));
            float ans = 0;
            for(auto &x : decimal){
                if(target){
                    ans += 1000 - x;
                    --target;
                }else if(target==0){
                    ans += x;
                }
            }
            char res[8];
            sprintf(res, "%.3f", ans / 1000);
            return std::string(res);
        }
//1221. 分割平衡字符串
        int balancedStringSplit(std::string s){
            int l = 0, res = 0;
            for(auto &c : s){
                l += c == 'L';
                l -= c == 'R';
                res += !l;
            }
            return res;
        }
//621. 任务调度器
        int leastInterval_better(std::vector<char> &tasks, int n){
            std::vector<int> mp(26);
            for(auto &c : tasks)++mp[c-'A'];
            std::sort(begin(mp), end(mp));
            int cnt = 0;
            for(int i=mp.size()-1; i>=0 && mp[i] == mp.back(); --i)++cnt;
            return std::max((int)tasks.size(), cnt + (n+1) * (mp.back() - 1));
        }
        int leastInterval(std::vector<char> &tasks, int n){
            using pic = std::pair<int, char>;
            std::unordered_map<char, int> mp(26);
            for(auto &c : tasks)++mp[c];
            std::priority_queue<pic> q;
            for(auto &[c, n] : mp)q.emplace(n, c);
            std::vector<pic> temp;
            int res = 0, k = ++n, t = 0;
            while(q.size()){
                k = std::min(n, (int)q.size()), t = 0;
                while(k--){
                    auto [i, c] = q.top();q.pop();
                    if(--i)temp.emplace_back(i, c);
                    ++t;
                }
                res += temp.size() ? n : t;
                for(auto &v : temp)q.push(v);
                temp.clear();
            }
            return res;
        }

//1247. 交换字符使得字符串相同
        int minimumSwap(std::string s1, std::string s2){
            int x = 0, y = 0, len = s1.size();
            for(int i=0; i<len; ++i){
                if(s1[i] == s2[i])continue;
                x += s1[i] == 'x';
                y += s1[i] == 'y';
            }
            if((x & 1) ^ (y & 1))return -1;
            return ((x >> 1) + (y >> 1)) + ((x & 1) << 1);
        }
//649. Dota2 参议院
        std::string predictPartyVictory(std::string senate){
            std::queue<int> q;
            std::vector<int> bans(2), people(2);
            for(auto &c : senate){
                int x = c=='R';
                q.emplace(x);
                ++people[x];
            }
            while(people[0] && people[1]){
                int x = q.front();q.pop();
                if(bans[x ^ 1]){
                    --bans[x ^ 1];
                    --people[x];
                }else{
                    ++bans[x];
                    q.emplace(x);
                }
            }
            return people[0] ? "Dire" : "Radiant";
        }
//948. 令牌放置
        int bagOfTokensScore(std::vector<int> &tokens, int P){
            std::sort(begin(tokens), end(tokens));
            int ans = 0, res = 0;
            int l = 0, r = tokens.size()-1;
            while(l <= r){
                if(P >= tokens[l]){
                    P -= tokens[l++];
                    res = std::max(res, ++ans);
                }else if(ans > 0 && P + tokens[r] > tokens[l]){
                    --ans;
                    P += tokens[r--];
                }else{
                    break;
                }
            }
            return res;
        }
//738. 单调递增的数字
        int monotoeIncreasingDigits_dfs(int N){
            using ll = long long;
            std::function<ll(ll)> _dfs = [&](ll n){
                if(n==N)return n;
                if(n > N)return n / 10;
                ll lo = n==0 ? 1 : n % 10, ans = 0;
                for(int i=lo; i<10; ++i){
                    ans = std::max(ans, _dfs(n*10+i));
                }
                return ans;
            };
            return _dfs(0);
        }
        int monotoeIncreasingDigits(int N){
            std::string num = std::to_string(N);
            int l = num.size();
            for(int i=l-1; i>0; --i){
                if(num[i] < num[i-1]){
                    l = i;
                    --num[i-1];
                }
            }
            while(l < num.size())num[l++] = '9';
            return std::stoi(num);
        }
//1094. 拼车
        bool carPooling(std::vector<std::vector<int>> &trips, int capacity){
            using pii = std::pair<int, int>;
            std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
            for(auto &p : trips){
                q.push({p[1], p[0]});
                q.push({p[2], -p[0]});
            }
            while(q.size()){
                auto [p, n] = q.top();q.pop();
                if((capacity-=n)<0)return false;
            }
            return true;
        }
//861. 翻转矩阵后的得分
        int matrixScore_better(std::vector<std::vector<int>> &A){
            int m = A.size(), n = A[0].size(), res = 0;
            for(int j=0; j<n; ++j){
                int zero = 0;
                for(int i=0; i<m; ++i){
                    zero += A[i][j] ^ A[i][0];
                }
                res += std::max(zero, m - zero) * (1<<(n - j - 1));
            }
            return res;
        }
        int matrixScore(std::vector<std::vector<int>> &A){
            int m = A.size(), n = A[0].size(), res = 0;
            std::vector<int> col(n);
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    col[j] += A[i][j];
                }
            }
            for(int state=0; state<(1<<m); ++state){
                int reverse = state ^ (state - 1);
                for(int i=state?0:m; i<m; ++i){
                    if(!(reverse & (1 << i)))continue;
                    for(int j=0; j<n; ++j){
                        col[j] += A[i][j] == 1 ? -1 : 1;
                        A[i][j] ^= 1;
                    }
                }
                int ans = 0;
                for(int j=0; j<n; ++j)ans += std::max(col[j], m-col[j]) * (1<<(n-1-j));
                res = std::max(res, ans);
            }
            return res;
        }
//908. 最小差值 I
        int smallestRangeI(std::vector<int> &A, int K){
            return std::max(0, *std::max_element(begin(A), end(A)) -
                               *std::min_element(begin(A), end(A)) - (K << 1));
        }
//910. 最小差值 II
        int smallestRangeII(std::vector<int> &A, int K){
            int len = A.size();
            std::sort(begin(A), end(A));
            int res = A.back() - A[0];
            for(int i=0; i<len-1; ++i){
                int r = std::min(A[i+1] - K, A[0] + K);
                int l = std::max(A[i] + K, A.back() - K);
                res = std::min(res, l - r);
            }
            return res;
        }
//1005. K 次取反后最大化的数组和
        int largestSumAfterKNegations_heap(std::vector<int> &A, int K){
            std::priority_queue<int, std::vector<int>, std::greater<int>>q(begin(A), end(A));
            while(K--){
                int cur = q.top() * -1;q.pop();
                q.emplace(cur);
            }
            int ans = 0;
            while(q.size()){
                ans += q.top();q.pop();
            }
            return ans;
        }
        int largestSumAfterKNegations(std::vector<int> &A, int K){
            std::sort(begin(A), end(A));
            int i = 0, len = A.size();
            while(K-- && i<len && A[i]<=0)A[i++] *= -1;
            int ans = std::accumulate(begin(A),end(A), 0);
            if(K & 1)return ans;
            return ans - 2**std::min_element(begin(A), end(A));
        }
//1276. 不浪费原料的汉堡制作方案
        std::vector<int> numOfBurgers(int tomatoSlices, int cheeseSlices){
            if(tomatoSlices & 1)return {};
            if(tomatoSlices < cheeseSlices<<1) return{};
            int x = (tomatoSlices - (cheeseSlices<<1))>>1;
            int y = cheeseSlices - x;
            if(y<0)return {};
            return {x, y};
        }
//135. 分发糖果
        int cnady_3(std::vector<int> &ratings){
            std::function<int(int)> _calc = [&](int n){
                return (n * (n+1)) / 2; };
            int res = 0, up = 0, down = 0,
                fun1 = 0, fun2 = 0, len = ratings.size();
            for(int i=1; i<len; ++i){
                fun2 = ratings[i] > ratings[i-1] ? 1 : (ratings[i]==ratings[i-1] ? 0 : -1);
                if(fun2==0 || (fun1==-1 && fun2!=-1)){
                    res += std::max(up, down) + _calc(up) + _calc(down);
                    up = down = 0;
                }
                if(fun2 == -1)++down;
                if(fun2 == 0)++res;
                if(fun2 == 1)++up;
                fun1 = fun2;
            }
            return res + std::max(up, down) + _calc(up) + _calc(down) + 1;
        }
        int cnady_2(std::vector<int> &ratings){
            int len = ratings.size();
            std::vector<int> c(len, 1);
            for(int i=1; i<len; ++i){
                if(ratings[i] > ratings[i-1])c[i] = c[i-1] + 1;
            }
            int res = c.back();
            for(int i=len-2; i>=0; --i){
                if(ratings[i] > ratings[i+1])c[i] = std::max(c[i], c[i+1] + 1);
                res += c[i];
            }
            return res;
        }
        int cnady_1(std::vector<int> &ratings){
            int len = ratings.size();
            std::vector<int> left(len, 1), right(len, 1);
            for(int i=1; i<len; ++i){
                if(ratings[i] > ratings[i-1])left[i] = left[i-1] + 1;
            }
            for(int i=len-2; i>=0; --i){
                if(ratings[i] > ratings[i+1])right[i] = right[i+1] + 1;
            }
            int res = 0;
            for(int i=0; i<len; ++i)res += std::max(left[i], right[i]);
            return res;
        }
        int cnady_0(std::vector<int> &ratings){
            int len = ratings.size();
            std::vector<int> c(len, 1);
            bool f = 1;
            while(f){
                f ^= 1;
                for(int i=0; i<len-1; ++i){
                    if(ratings[i] > ratings[i+1] && c[i] <= c[i+1]){
                        c[i] = c[i+1] + 1;
                        f = 1;
                    }
                }
                for(int i=1; i<len; ++i){
                    if(ratings[i] > ratings[i-1] && c[i] <= c[i-1]){
                        c[i] = c[i-1] + 1;
                        f = 1;
                    }
                }
            }
            return std::accumulate(begin(c), end(c), 0);
        }
//e 358. K 距离间隔重排字符串（
        std::string reorganizeStringK(std::string S, int k){
            using pic = std::pair<int, char>;
            std::unordered_map<int, char> mp;
            for(auto &c : S)++mp[c];
            std::priority_queue<pic> q;
            std::vector<pic> temp;
            std::string res;
            for(auto &[c, n] : mp)q.emplace(n, c);
            int len = S.size();
            while(q.size()){
                int d = std::min(k, len);
                if(q.size() < d)return "";
                len -= d;
                while(d--){
                    auto [n, c] = q.top();q.pop();
                    res += c;
                    if(--n)temp.emplace_back(n, c);
                }
                for(auto &v : temp)q.push(v);
                temp.clear();
            }
            return res;
        }

//984. 不含 AAA 或 BBB 的字符串
        std::string strWithout3a3b(int A, int B){
            int len = A + B;
            std::string res;
            while(A || B){
                bool wa = false;
                int i = res.size();
                if(res.size() >= 2 && res[i-2] == res[i-1]){
                    wa = res[i-1] == 'b';
                }else{
                    wa = A >= B;
                }
                if(wa){
                    --A;
                    res.push_back('a');
                }else{
                    --B;
                    res.push_back('b');
                }
            }
            return res;
        }
//991. 坏了的计算器
        int brokenCalc(int X, int Y){
            int res = 0;
            while(X < Y){
                ++res;
                if(Y & 1){
                    Y = ++Y >> 1;
                    ++res;
                }else{
                    Y >>= 1;
                }
            }
            return res + X - Y;
        }
//1354. 多次求和构造目标数组
        bool isPossible(std::vector<int> &target){
            if(target.size() == 1)return target[0] == 1;
            using ll = long long;
            std::priority_queue<ll> q;
            ll cur_sum = 0;
            for(auto &x : target){
                if(x<=0)return false;
                q.emplace(x);
                cur_sum += x;
            }
            while(cur_sum > target.size()){
                ll max_ = q.top(); q.pop();
                ll diff = cur_sum - max_;
                if(max_ <= diff)return false;
                ll scaler = (max_ - q.top() - 1) / diff + 1;
                if(max_ - diff * scaler <= 0)return false;
                q.emplace(max_ - diff * scaler);
                cur_sum -= diff * scaler;
            }
            return true;
        }
//757. 设置交集大小至少为2
        int intersectionSizeTwo(std::vector<std::vector<int>> &intervals, int k = 2){
            std::sort(begin(intervals), end(intervals), [&](auto &a, auto &b){
                    return a[1] == b[1] ? a[0] > b[0] : a[1] < b[1]; });
            int len = intervals.size();
            std::set<int> mp;
            for(auto &p : intervals){
                int l = p[0], r = p[1], cnt = 0;
                for(auto it=rbegin(mp); it!=rend(mp) && (*it)>=l && ++cnt<k; ++it);
                while(k > cnt){
                    if(!mp.count(r))mp.insert(r), ++cnt;
                    --r;
                }
            }
            return mp.size();
        }
//1400. 构造 K 个回文字符串
        bool canCOnstruct(std::string s, int k){
            if(s.size() < k)return false;
            int t = 0;
            std::vector<int> mp(26);
            for(auto &c : s)++mp[c-'a'];
            for(auto &x : mp)t += x & 1;
            if(t > k)return false;
            return  true;
        }
//1433. 检查一个字符串是否可以打破另一个字符串
        bool checkIfCanBreak(std::string s1, std::string s2){
            auto a = s1, b = s2;
            std::sort(begin(s1), end(s1));
            std::sort(begin(s2), end(s2));
            int f = -1, len = s1.size();
            for(int i=0; i<len; ++i){
                if(s1[i] < s2[i] && f==1)return false;
                if(s1[i] > s2[i] && f==0)return false;
                if(s1[i] < s2[i])f = 0;
                if(s1[i] > s2[i])f = 1;
            }
            return true;
        }
//874. 模拟行走机器人
        int robotSim(std::vector<int> &commands,
                std::vector<std::vector<int>> &obstacles){
            std::set<std::pair<int, int>> mp;
            std::map<int, std::vector<int>> fun {{-2, {3, 0, 1, 2}}, {-1, {1, 2, 3, 0}}};
            for(auto &p : obstacles)mp.emplace(p[0], p[1]);
            int res = 0, len = commands.size(), f = 0, curx = 0, cury = 0;
            for(int i=0; i<len; ++i){
                int x = commands[i];
                if(x < 0){
                    f = fun[x][f];
                }else{
                    int i = 0;
                    switch (f){
                        case 0:
                            while(i++<x && !mp.count({curx, cury+1}))++cury;
                            break;
                        case 1:
                            while(i++<x && !mp.count({curx+1, cury}))++curx;
                            break;
                        case 2:
                            while(i++<x && !mp.count({curx, cury-1}))--cury;
                            break;
                        case 3:
                            while(i++<x && !mp.count({curx-1, cury}))--curx;
                            break;
                    }
                    res = std::max(res, curx*curx + cury*cury);
                }
            }
            return res;
        }
//1253. 重构 2 行二进制矩阵
        std::vector<std::vector<int>> reconstructMatrix
            (int upper, int lower, std::vector<int> &colsum){
                int len = colsum.size();
                std::vector<std::vector<int>> res(2, std::vector<int>(len, -1));
                for(int i=0; i<len; ++i){
                    if(colsum[i]==0 || colsum[i]==2){
                        res[0][i] = res[1][i] = colsum[i]?1:0;
                        upper -= res[0][i];
                        lower -= res[1][i];
                    }
                }
                if(upper<0 || lower<0)return {};
                for(int i=0; i<len; ++i){
                    if(res[0][i] != -1)continue;
                    if(upper){
                        --upper;
                        res[0][i] = 1;
                        res[1][i] = 0;
                    }else{
                        res[1][i] = 1;
                        res[0][i] = 0;
                        --lower;
                    }
                }
                if(!lower && !upper)return res;
                return {};
        }
//1282. 用户分组
        std::vector<std::vector<int>> groupThePeople(std::vector<int> &groupSizes){
            std::vector<std::vector<int>> res;
            std::unordered_map<int, std::vector<std::vector<int>>> mp;
            int len = groupSizes.size();
            for(int i=0; i<len; ++i){
                if(!mp.count(groupSizes[i]) ||
                        mp[groupSizes[i]].back().size() >= groupSizes[i]){
                    mp[groupSizes[i]].push_back({i});
                }else{
                    mp[groupSizes[i]].back().emplace_back(i);
                }
            }
            for(auto &[k, v] : mp){
                for(auto &x : v)res.emplace_back(x);
            }
            return res;
        }
//330. 按要求补齐数组
        int minPatches(std::vector<int> &nums, int n){
            long long res = 0, i = 0, miss = 1, len = nums.size();
            while(miss <= n){
                if(i < len && miss >= nums[i]){
                    miss += nums[i++];
                }else{
                    miss <<= 1;
                    ++res;
                }
            }
            return res;
        }
//630. 课程表 III
         int sheduleCourse(std::vector<std::vector<int>> &courses){
            std::sort(begin(courses), end(courses), [&](auto &a, auto &b){
                    return a[1] < b[1]; });
            std::priority_queue<int> q;
            int all = 0;
            for(auto &c : courses){
                if(all + c[0] <= c[1]){
                    q.push(c[0]);
                    all += c[0];
                }else if(q.size() && q.top() > c[0]){
                    all -= q.top(); q.pop();
                    q.push(c[0]);
                    all += c[0];
                }
            }
            return q.size();
        }
//936. 戳印序列
        std::vector<int> movesToStamp(std::string stamp, std::string target){
            std::vector<int> res;
            int st = stamp.size(), ta = target.size();
            int cnt = 0, f = 1;
            while(f){
                f = 0;
                for(int start=0; start+st<=ta; ++start){
                    int j = 0, i = start, _f = 0;
                    while(j < st){
                        if(stamp[j] != target[i] && target[i] != '?'){
                            break;
                        }else if(stamp[j] == target[i]){
                            _f = 1;
                        }
                        ++i, ++j;
                    }
                    f |= _f && j==st;
                    if(_f && j==st){
                        res.emplace_back(start);
                        while(--i >= start){
                            cnt += target[i] != '?';
                            target[i] = '?';
                        }
                    }
                }
            }
            if(cnt != ta)return {};
            reverse(begin(res), end(res));
            return res;
        }
//1029. 两地调度
        int twoCitySchedCost_better(std::vector<std::vector<int>> costs){
            std::sort(begin(costs), end(costs),
                    [&](auto &a, auto &b){
                    return a[0] - a[1] < b[0] - b[1];
                });
            int res = 0;
            int len = costs.size() >> 1;
            for(int i=0; i<len; ++i)res += costs[i][0] + costs[i+len][1];
            return res;
        }
        int twoCitySchedCost(std::vector<std::vector<int>> costs){
            int len = costs.size();
            std::vector<std::vector<int>> dp(len, std::vector<int>(len));
            dp[0][0] = costs[0][1];
            dp[0][1] = costs[0][0];
            for(int i=1; i<len; ++i)dp[i][0] = dp[i-1][0] + costs[i][1];
            for(int i=2; i<len; ++i)dp[0][i] = 0x3f3f3f3f;
            for(int i=1; i<len; ++i){
                for(int j=1; j<=len>>1; ++j){
                    dp[i][j] = std::min(dp[i-1][j-1] + costs[i][0],
                                        dp[i-1][j] + costs[i][1]);
                }
            }
            return dp[len-1][len>>1];
        }
};

int main(int argc,const char *argv[]){
    Solution te;
    std::string source {"xyz"};
    std::string target {"xyz"};
    //std::string source {"xyz"};
    //std::string target {"xzyxz"};
    std::cout<<te.shorestWay(source, target)<<std::endl;
    std::cout<<te.shorestWay_better(source, target)<<std::endl;
    //std::string k  {"DI"};
    //std::string k  {"DDIIDIIID"};
    //auto arr = te.findPermutation(k);
    //for(auto &x : arr)std::cout<<x<<"  ";
    //std::vector<int> boxes {4,3,4,1};
    //std::vector<int> house {5,3,3,4,1};
    //std::vector<int> boxes {1,2,2,3,4};
    //std::vector<int> house {3,4,1,2};
    //std::vector<int> boxes {1,2,3};
    //std::vector<int> house {1,2,3,4};
    //std::cout<<te.maxBoxesInWarehouse(boxes, house)<<std::endl;
    //std::cout<<te.maxBoxesInWarehouse_better(boxes, house)<<std::endl;
    //std::vector<std::vector<Interval>> schedule { {{1,2}, {5, 6}}, {{1, 3}}, {{4, 10}} };
    //std::vector<std::vector<Interval>> schedule { {{1,3}, {6, 7}}, {{2, 4}}, {{2, 5}, {9, 12}} };
    //auto arr1 = te.emploteeFreeTime(schedule);
    //for(auto &x : arr1){
        //std::cout<<x.start<<"   "<<x.end<<std::endl;
    //}
    //std::cout<<"------------------\n";
    //auto arr0 = te.emploteeFreeTime_better(schedule);
    //for(auto &x : arr0){
        //std::cout<<x.start<<"   "<<x.end<<std::endl;
    //}
    //int N = 7;
    //std::cout<<te.maxA(N)<<std::endl;
    //std::vector<int> sw {1,2,3,4,5,6,7,8,9};
    //std::vector<int> sw {1,2,2,1,2,2,1,2,2};
    //int k = 5;
    //int k = 2;
    //int k = 8;
    //std::cout<<te.maximizeSweetness(sw, k)<<std::endl;
    //std::vector<std::string> prices {"0.700","2.800","4.900"};
    //int t = 8;
    //std::cout<<te.minimmizeError(prices, t)<<std::endl;
    //std::string s {"aabbcc"};
    //int k = 3;
    //std::string s {"aaadxxbbcc"};
    //int k = 2;
    //std::cout<<te.reorganizeStringK(s, k)<<std::endl;
    return 0;
}
