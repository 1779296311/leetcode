/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_sliding_window.cpp
*     author   : @ JY
*     date     : 2020--10--02
**********************************************/
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <numeric>
#include <stack>
#include <stdlib.h>

class Solution{
    public:
//480. 滑动窗口中位数
        std::vector<double> medianSlidingWindow_multimap(std::vector<int> &nums, int k){
            std::multiset<int> mp(nums.begin(), nums.begin()+k);
            std::vector<double> res;
            auto mid = std::next(mp.begin(), k/2);
            for(int i=k; ; ++i){
                res.push_back(((double)(*mid) + *next(mid, k%2-1))*0.5);
                if(i==nums.size())break;
                mp.insert(nums[i]);
                if(nums[i] < *mid)--mid;
                if(nums[i-k] <= *mid)++mid;
                mp.erase(mp.lower_bound(nums[i-k]));
            }
            return res;
        }
        std::vector<double> medianSlidingWindow(std::vector<int> &nums, int k){
            std::vector<double> res;
            std::unordered_map<int, int> mp;
            std::priority_queue<int> lo;
            std::priority_queue<int, std::vector<int>, std::greater<int>> hi;
            int i=0;
            while (i < k) lo.push(nums[i++]);
            for (int j = 0; j < k / 2; j++)hi.push(lo.top()), lo.pop();
            while(true){
                res.push_back(k&1?lo.top():((double)lo.top()+(double)hi.top())/2);
                if(i>=nums.size())break;
                int out = nums[i-k];
                int in  = nums[i];
                int ba  = (out<=lo.top()?-1:1);
                ++mp[out];
                if(lo.size() && in<=lo.top()){
                    ++ba, lo.push(in);
                }else{
                    --ba, hi.push(in);
                }
                if(ba<0)lo.push(hi.top()), hi.pop();
                if(ba>0)hi.push(lo.top()), lo.pop();
                while(lo.size() && mp[lo.top()])--mp[lo.top()], lo.pop();
                while(hi.size() && mp[hi.top()])--mp[hi.top()], hi.pop();
                ++i;
            }
            return res;
        }
//1074. 元素和为目标值的子矩阵数量
        int numSubmatrixSubTarget(std::vector<std::vector<int>> &matrix, int target){
            int m = matrix.size();
            int n = matrix[0].size();
            std::vector<std::vector<int>> arr(m+1, std::vector<int>(n+1));
            for(int i=1; i<=m; ++i){
                for(int j=1; j<=n; ++j){
                    arr[i][j] = arr[i][j-1] + arr[i-1][j] - arr[i-1][j-1] + matrix[i-1][j-1];
                }
            }
            int res = 0;
            for(int i=1; i<=m; ++i){
                for(int k=i; k<=m; ++k){
                    std::unordered_map<int, int> mp = {{0, 1}};
                    for(int j=1; j<=n; ++j){
                        int t = arr[k][j] - arr[i-1][j];
                        if(mp.count(t-target))res += mp[t-target];
                        ++mp[t];
                    }
                }
            }
            return res;
        }
        int numSubmatrixSubTarget_fuck(std::vector<std::vector<int>> &matrix, int target){
            int m = matrix.size();
            int n = matrix[0].size();
            std::vector<std::vector<int>> arr(m+1, std::vector<int>(n+1));
            for(int i=1; i<=m; ++i){
                for(int j=1; j<=n; ++j){
                    arr[i][j] = arr[i][j-1] + arr[i-1][j] - arr[i-1][j-1] + matrix[i-1][j-1];
                }
            }
            std::function<int(int, int)> _calc = [&](int x, int y){
                int ans = 0;
                for(int i=x; i<=m; ++i){
                    for(int j=y; j<=n; ++j){
                        ans += (arr[i][j] + arr[x-1][y-1] - arr[i][y-1] - arr[x-1][j])==target;
                    }
                }
                return ans;
            };
            int res = 0;
            for(int i=1; i<=m; ++i){
                for(int j=1; j<=n; ++j){
                    res += _calc(i, j);
                }
            }
            return res;
        }
//1456. 定长子串中元音的最大数目
        int maxVowels(std::string s, int k){
            std::unordered_set<char> ori = {'a','e','i','o','u'};
            int res = 0;
            int cnt = 0;
            int len = s.size();
            for(int i=0; i<len; ++i){
                cnt += ori.count(s[i]);
                if(i>=k)cnt -= ori.count(s[i-k]);
                if(i>=k-1)res = std::max(res, cnt);
            }
            return res;
        }
//1438. 绝对差不超过限制的最长连续子数组
        int longestSubarrya(std::vector<int> &nums, int limit){
            std::map<int, int> mp;
            int l   = -1;
            int r   = -1;
            int len = nums.size();
            int res = 0;
            while(r < len-1){
                ++mp[nums[++r]];
                while(mp.rbegin()->first - mp.begin()->first > limit){
                    if(!--mp[nums[++l]])mp.erase(nums[l]);
                }
                res = std::max(res, r - l);
            }
            return res;
        }
//1033. 移动石子直到连续
        std::vector<int> numMovesStonesI(int a, int b, int c){
            std::vector<int> temp = { a, b, c };
            std::sort(temp.begin(), temp.end());
            a=temp[0], b=temp[1], c=temp[2];
            int res1 = (a==b-1?0:1) + (b==c-1?0:1);
            if(b-a==2 || c-b==2)res1 = 1;
            return {res1,c-a-2};
        }
//1040. 移动石子直到连续 II
        std::vector<int> numMovesStonesII(std::vector<int> &stones){
            std::sort(begin(stones), end(stones));
            int len = stones.size();
            int res1 = len, res2;
            res2 = std::max(stones[len-1]-stones[1], stones[len-2]-stones[0]) - len + 2;
            int j = 0;
            for(int i=0; i<len; ++i){
                while(j+1<len && stones[j+1]-stones[i]+1<=len)++j;
                int temp = len - (j - i + 1);
                if(temp==1 && stones[j]-stones[i]+1==len-1)temp = 2;
                res1 = std::min(res1, temp);
            }
            return {res1, res2};
        }
//485. 最大连续1的个数 I
        int longestOnesI(std::vector<int> &nums){
            int res = 0;
            int l   = 0;
            int len = nums.size();
            while(l<len&&!nums[l])++l;
            int r   = l;
            while(r < len){
                int t = r;
                while(r<len && !nums[r])++r;
                if(t!=r)l = r;
                res = std::max(res, r++ - l + 1);
            }
            return res;
        }

//最大连续1的个数 II
//给定一个二进制数组，你可以最多将 1 个 0 翻转为 1，找出其中最大连续 1 的个数。
        int longestOnesII(std::vector<int> &A){
            int res = 0;
            int l   = 0;
            int r   = 0;
            int len = A.size();
            int zeros = A[0]^1;
            while(r < len){
                if(!A[r]){
                    if(++zeros == 2){
                        --zeros;
                        while(A[l])++l;
                    }
                }
                res = std::max(res, ++r - l);
            }
            return res;
        }
//1004. 最大连续1的个数 III
        int longestOnesIII(std::vector<int> &A,  int K){
            int res = 0;
            int l   = 0;
            int r   = 0;
            int len = A.size();
            while(r < len){
                if(!A[r] && --K<0){
                    ++K;
                    while(A[l++]);
                }
                res = std::max(res, ++r - l);
            }
            return res;
        }
//567. 字符串的排列
        bool checkInclusion(std::string s1, std::string s2){
            int dif   = s1.size();
            int size2 = s2.size();
            int size1 = dif;
            if(size1 > size2)return false;
            std::unordered_map<char, int> need;
            for(auto &c : s1)++need[c];
            for(int i=0; i<size1; ++i){
                if(--need[s2[i]]>=0)--dif;
            }
            for(int i=size1; i<size2; ++i){
                if(!dif)return true;
                if(--need[s2[i]]>=0)--dif;
                if(++need[s2[i-size1]] > 0)++dif;
            }
            return !dif;
        }
//面试题 17.18. 最短超串
        std::vector<int> shorestSeq(std::vector<int> &big, std::vector<int> &small){
            int dif = small.size();
            std::unordered_map<int, int> need;
            for(int i=0; i<dif; ++i)++need[small[i]];
            int size = big.size();
            int resl = -1, resr = -1;
            int len = size;
            int l   = 0;
            int r   = -1;
            while(r < size-1){
                if(--need[big[++r]]>=0)--dif;
                if(!dif){
                    ++dif;
                    while(++need[big[l++]]<=0);
                    if(len > r-l+1){
                        len  = r - l + 1;
                        resl = l-1;
                        resr = r;
                    }
                }
            }
            if(resl==-1)return {};
            return {resl, resr};
        }
//995. K 连续位的最小翻转次数
        int minKBitFlips(std::vector<int> &A, int K){
            int len = A.size();
            int res = 0;
            std::queue<int> q;
            for(int i=0; i<len; ++i){
                if(q.size() && q.front()+K==i)q.pop();
                if((q.size()&1) == A[i]){
                    if(i+K > len)return -1;
                    ++res;
                    q.push(i);
                }
            }
            return res;
        }
        int minKBitFlips_fuck(std::vector<int> &A, int K){
            int res = 0;
            int size = A.size();
            for(int i=0; i<size; ++i){
                if(!A[i]){
                    if(i+K>size)return -1;
                    ++res;
                    for(int j=i; j<i+K; ++j)A[j] ^= 1;
                }
            }
            return res;
        }
//1208. 尽可能使字符串相等
        int equalSunstring(std::string s, std::string t, int maxCost){
            int len   = s.size();
            int left  = 0;
            int right = -1;
            int cost  = 0;
            int res   = 0 ;
            while(right < len-1){
                cost += abs(s[++right]-t[right]);
                if(cost > maxCost)cost -= (abs(s[left]-t[left++]));
                res = std::max(res, right - left + 1);
            }
            return res;
        }
//424. 替换后的最长重复字符
        int characterReplacement(std::string s, int k){
            int len   = s.size();
            if(!len || k>=len)return len;
            int res   = 0;
            int left  = 0;
            int right = -1;
            int cnt   = 0;
            std::vector<int> mp(26, 0);
            while(right < len-1){
                cnt = std::max(cnt, ++mp[s[++right]-'A']);
                if(right-left+1-cnt > k)--mp[s[left++]-'A'];
                res = std::max(res, right-left+1);
            }
            return res;
        }
//1052. 爱生气的书店老板
        int maxSatisfied(std::vector<int> &customers, std::vector<int> &grumpy, int X){
            int len   = customers.size();
            int sel_b = 0;
            int max_c = 0;
            int max_  = -1;
            for(int i=0; i<len; ++i){
                max_c += grumpy[i]?customers[i]:0;
                if(i>=X)max_c -=  grumpy[i-X]?customers[i-X]:0;
                if(i>=X-1 && max_c>max_)max_ = max_c, sel_b = i-X+1;
            }
            int res = 0;
            for(int i=sel_b; i<sel_b+X; ++i)grumpy[i] = 0;
            for(int i=0; i<len; ++i)res += grumpy[i]?0:customers[i];
            return res;
        }
};
