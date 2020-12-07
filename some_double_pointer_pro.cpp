/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_double_pointer_pro.cpp
*     author   : @ JY
*     date     : 2020--07--24
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>
#include <cmath>
#include <numeric>
#include <functional>
#include <unordered_map>
#include <stack>
#include <unordered_set>
#include <map>
#include <cstring>
#include <stdlib.h>
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {};
};
class Solution{
   public:
//828. 统计子串中的唯一字符
       int uniqueLetterStrign(std::string s){
           int MOD = 1e9 + 7, len = s.size();
           long long res = 0;
           std::unordered_map<char, std::vector<int>> mp;
           for(int i=0; i<len; ++i)mp[s[i]].emplace_back(i);
           for(auto &&[k, v] : mp){
               int l = -1, r = 0;
               int size = v.size();
               for(int i=0; i<size; ++i){
                   i==size-1 ? r = len : r = v[i+1];
                   res += (v[i]-l) * (r-v[i]);
                   l = v[i];
               }
           }
           return res % MOD;
      }
//面试题 17.21. 直方图的水量
       int trap1(std::vector<int> &height){
           int res = 0;
           int l = 0, r = height.size() - 1;
           int maxl = 0, maxr = 0;
           while(l < r){
               if(height[l] < height[r]){
                   maxl > height[l] ? (res += maxl-height[l]) : (maxl = height[l]);
                   ++l;
               }else{
                   maxr > height[r] ? (res += maxr-height[r]) : (maxr = height[r]);
                   --r;
               }
           }
           return res;
       }
//923. 三数之和的多种可能
       int threeSumMulti(std::vector<int> &A, int target){
           int MOD = 1e9 + 7;
           int size = A.size();
           int dp[size+1][4][target+1];
           bzero(dp, sizeof dp);
           for(int i=0; i<=size; ++i)dp[i][0][0] = 1;
           for(int i=1; i<=size; ++i){
               for(int j=1; j<4; ++j){
                   for(int k=0; k<=target; ++k){
                       dp[i][j][k] = (dp[i][j][k] + dp[i-1][j][k]) % MOD;
                       if(k >= A[i-1]){
                           dp[i][j][k] = (dp[i][j][k] + dp[i-1][j-1][k-A[i-1]]) % MOD;
                       }
                   }
               }
           }
           return dp[size][3][target];
       }
//532. 数组中的 k-diff 数对
       int findpairs(std::vector<int> &nums, int k){
           int res = 0;
           std::map<int, int> mp;
           for(auto &x : nums)++mp[x];
           if(!k){
               for(auto &[k1, v1] : mp)res += v1>1;
               return res;
           }
           for(auto [k1, v1] : mp){
               res += mp.count(k1-k) > 0;
               res += mp.count(k1+k) > 0;
               mp.erase(k1);
           }
           return res;
       }
//面试题 02.04. 分割链表
       ListNode * partition(ListNode *head, int x){
           if(!head)return head;
           ListNode H(-1);
           H.next = head;
           ListNode *cur = head->next;
           ListNode *pre = head;
           while(cur){
               if(cur->val < x){
                   pre->next = cur->next;
                   cur->next = H.next;
                   H.next    = cur;

                   cur = pre->next;
                   continue;
               }
               pre = cur;
               cur = cur->next;

           }
           return H.next;
       }
//844. 比较含退格的字符串
       bool backspaceCompare(std::string S, std::string T){
           std::function<std::string(std::string &)> _calc = [&](std::string &s){
               std::string ans;
               int len = s.size();
               for(int i=0; i<len; ++i){
                   if(s[i]!='#'){
                       ans += s[i];
                   }else if(ans.size()){
                       ans.erase(ans.end()-1);
                   }
               }
               return ans;
           };
           return _calc(S) == _calc(T);
       }
//面试题 17.11. 单词距离
       int findClosest(std::vector<std::string> &words, std::string word1, std::string word2){
           int w1 = -1, w2 = -1;
           int len = words.size();
           int res = INT_MAX;
           for(int i=0; i<len; ++i){
               if(!words[i].compare(word1)){
                   if(w2!=-1)res = std::min(res, i - w2);
                   w1 = i;
               }
               if(!words[i].compare(word2)){
                   if(w1!=-1)res = std::min(res, i - w1);
                   w2 = i;
               }
           }
           return res;
       }
//面试题 16.06. 最小差
       int smallestDifference(std::vector<int> &a, std::vector<int> &b){
           std::sort(begin(a), end(a));
           std::sort(begin(b), end(b));
           long long res = LLONG_MAX, x1, x2;
           int i = 0, j = 0;
           int size1 = a.size(), size2 = b.size();
           while(i<size1 && j<size2){
               x1  = a[i], x2 = b[j];
               res = std::min<long long>(res, abs(x1-x2));
               x1 > x2 ? ++j : ++i;
           }
           return res;
       }
//881. 救生艇
       int numRescueBoast(std::vector<int> &people, int limit){
           std::sort(begin(people),end(people));
           int l = 0, r = people.size() - 1;
           int res = 0;
           while(l <= r){
               if(people[r] + people[l] <= limit)++l;
               --r, ++res;
           }
           return res;
       }
//826. 安排工作以达到最大收益
       int maxProfitAssignment(std::vector<int> &difficulty, std::vector<int> &profit, std::vector<int>& worker){
           struct _cmp{
               bool operator()(const std::pair<int, int> &a , const std::pair<int, int> &b) const {
                   return a.first < b.first; } 
           };
           int res = 0;
           int len = profit.size();
           std::vector<std::pair<int, int>> mp;
           std::vector<int> mp_max(len);
           for(int i=0; i<len; ++i)mp.emplace_back(difficulty[i], profit[i]);
           std::sort(begin(mp), end(mp), [&](auto &p1, auto &p2){
               return p1.first == p2.first ? p1.second > p2.second: p1.first < p2.first; });
           mp_max[0] = mp[0].second;
           for(int i=1; i<mp.size(); ++i)mp_max[i] = std::max(mp[i].second, mp_max[i-1]);
           for(auto &x : worker){
               std::pair<int, int> t = {x,x};
               auto it = std::upper_bound(begin(mp), end(mp), t, _cmp()) - mp.begin();
               if(it)res += mp_max[--it];
           }
           return res;
       }
//k2. 接雨水
       int trap_stack(std::vector<int> &height){
           std::stack<int> st;
           st.push(0);
           int res = 0, len = height.size();
           for(int i=0; i<len; ++i){
               while(st.size() && height[st.top()] < height[i]){
                   int mid = st.top();st.pop();
                   if(st.size()){
                       int h = std::min(height[st.top()], height[i]) - height[mid];
                       res += h * (i - st.top() - 1);
                   }
               }
               st.push(i);
           }
           return res;
       }
       int trap(std::vector<int> &height){
           int l = 0, r = height.size() - 1;
           int lmax = 0, rmax = 0;
           int res = 0;
           while(l < r){
               if(height[l] < height[r]){
                   lmax > height[l] ? (res += lmax-height[l]) : (lmax = height[l]);
                   ++l;
               }else{
                   rmax > height[r] ? (res += rmax-height[r]) : (rmax = height[r]);
                   --r;
               }
           }
           return res;
       }
//713. 乘积小于K的子数组
       int numSubarrayProductLessThanK(std::vector<int> &nums, int k){
           int l = 0, r = -1;
           int len = nums.size();
           int res = 0;
           int mul = 1;
           while(r < len - 1){
               mul *= nums[++r];
               while(l <= r && mul >= k)mul /= nums[l++];
               res += r - l + 1;
           }
           return res;
       }
//1093. 大样本统计
       std::vector<double> sampeStates(std::vector<int> &count){
           double res0 = 266, res1 = 0, res2 = 0, res3, res4 = 0, all = 0;
           int l = 0, r = count.size();
           int cnt = 0;
           while(l < r){
               if(count[l]){
                    res0  = std::min((int)res0, l);
                    res1  = std::max((int)res1, l);
                    res2 += (count[l] * l);
                    all  += count[l];
                    if(count[res4] < count[l])res4 = l;
               }
               ++l;
           }
           l = 0;
           while(l < r){
               cnt += count[l];
               if(cnt >= all / 2){
                   if(cnt > all / 2){
                       res3 = l;
                   }else if((int)all%2==0){
                       res3 = (l+l+1)/2.0;
                   }else{
                       res3 = l + 1;
                   }
                   break;
               }
               ++l;
           }
           return {res0, res1, res2/all, res3, res4};
       }
//763. 划分字母区间
       std::vector<int> partitionLabels(std::string S){
           std::vector<int> mp(26);
           int size = S.size();
           for(int i=0; i<size; ++i)mp[S[i]-'a'] = i;
           int  l = 0, r = 0;
           std::vector<int> res;
           for(int i=0; i<size; ++i){
               r = std::max(r, mp[S[i]-'a']);
               if(i==r){
                   res.push_back(r - l + 1);
                   l = r + 1;
               }
           }
           return res;
       }
//344. 反转字符串
       void reverseString(std::vector<int> &s){
           int l = 0, r = s.size() - 1;
           while(l < r)std::swap(s[l++], s[r--]);
       }
//524. 通过删除字母匹配到字典里最长单词
       std::string findLongestWord(std::string s, std::vector<std::string> &d){
           std::sort(begin(d), end(d), [&](auto &a, auto &b){
              return a.size() == b.size() ? a < b : a.size() > b.size(); });
           int len = s.size();
           std::function<bool(std::string &)> _can = [&](std::string &w){
               int size = w.size();
               int i = 0, j = 0;
               while(i<len && j<size)if(s[i++]==w[j])++j;
               return j==size;
           };
           for(auto &w : d)if(_can(w))return w;
           return "";
       }
//283. 移动零
       void moveZeroes(std::vector<int> &nums){
           for(int i=0, j=0; i<nums.size(); ++i){
               if(nums[i])std::swap(nums[i], nums[j++]);
           }
       }
       void moveZeroes_better(std::vector<int> &nums){
           int len = nums.size();
           int r   = len;
           while(r > 0){
               if(nums[--r])continue;
               for(int i=r; i<len-1&&nums[i+1]; ++i){
                   std::swap(nums[i], nums[i+1]);
               }
           }
       }
//845. 数组中的最长山脉
       int longestMountain(std::vector<int> &A){
           int len = A.size();
           int res = 0;
           int l = 0, r = 0;
           while(r < len){
               while(l+1<len && A[l] >= A[l+1])++l;
               if(l==len-1)break;
               r = l;
               while(r+1<len && A[r] < A[r+1])++r;
               if(r==len-1)break;
               if(r!=len-1 && A[r] > A[r+1]){
                   while(r+1<len && A[r] > A[r+1])++r;
                   res = std::max(res, r - l + 1);
               }
               l = r;
           }
           return res;
       }
//457. 环形数组循环
       bool circularArrayLoop_bettee(std::vector<int> &nums){
           int len = nums.size();
           int INF = 10000;
           int l = 0, r = 0, f = 0, t;
           while(1){
               ++INF;
               f = nums[r] > 0;
               while(nums[r] != INF){
                   int k = nums[r];
                   if((f&&k<0) || (!f&&k>0))break;
                   nums[r] = INF;
                   int pre = r;
                   r = ((r+k) % len + len) % len;
                   if(pre==r)break;
                   if(nums[r]==INF)return true;
                   if(nums[r] > 10000)break;
               }
               t = l;
               l = (l+1) % len;
               while(t!=l && nums[l]>10000)l = (l+1) % len;
               if(t==l)return false;
               r = l;
           }
           return false;
       }
       bool circularArrayLoop(std::vector<int> &nums){
           int len = nums.size();
           int INF = 10000;
           std::function<bool(int, int)> _dfs = [&](int i, int f){
               if(!nums[i])return false;
               if(nums[i]==INF)return true;
               if(nums[i]>0!=f)return false;
               int j = ((i+nums[i])%len+len)%len;
               nums[i] = INF;
               if(j==i || !_dfs(j, f))return bool(nums[i]=false);
               return true;
           };
           for(int i=0; i<len; ++i){
               if(_dfs(i, nums[i]>0))return true;
           }
           return false;
       }
//1234. 替换子串得到平衡字符串
       int balancedString(std::string s){
           std::string tar;
           std::vector<int> mp(26);
           std::vector<int> need(26);
           int size = s.size();
           int len  = size >> 2;
           int dif  = 0;
           for(auto &c : s){
               if(++mp[c-'A'] > len)++need[c-'A'], ++dif;
           }
           if(!dif)return 0;
           int res = INT_MAX;
           int l = 0, r = -1;
           while(r < size - 1){
               if(--need[s[++r]-'A']>=0)--dif;
               if(!dif){
                   ++dif;
                   while(++need[s[l++]-'A']<=0);
                   res = std::min(res, r - l + 2);
               }
           }
           return res;
       }
//925. 长按键入
       bool isLongPressedName(std::string name, std::string typed){
           int l1 = name.size(), l2 = typed.size();
           if(l1 > l2)return false;
           int i = 0, j = 0;
           while(i<l1 && j<l2){
               if(name[i] != typed[j])return false;
               char c = name[i];
               int t  = 0;
               while(i<l1 && c==name[i])++i, ++t;
               while(j<l2 && c==typed[j])++j,--t;
               if(t>0 || (i==l1&&j!=l2))return false;
           }
           return i==l1;
       }
//986. 区间列表的交集
       std::vector<std::vector<int>> intervalIntersection(std::vector<std::vector<int>> &A,
               std::vector<std::vector<int>> &B){
           int l1 = A.size();
           int l2 = B.size();
           int i = 0, j = 0;
           std::vector<std::vector<int>> res;
           while(i<l1 && j<l2){
               if(A[i][0] < B[j][0]){
                   if(A[i][1] >= B[j][0]){
                       res.push_back({B[j][0], std::min(A[i][1], B[j][1])});
                   }
               }else{
                   if(A[i][0] <= B[j][1]){
                       res.push_back({A[i][0], std::min(B[j][1], A[i][1])});
                   }
               }
               (A[i][1])>(B[j][1]) ? ++j : ++i;
           }
           return res;
       }
//977. 有序数组的平方
       std::vector<int> sortedSquares(std::vector<int> &A){
           std::vector<int> res;
           int l = 0, r = A.size() - 1;
           while(l <= r){
               if(abs(A[l]) < abs(A[r])){
                   res.push_back((A[r]*A[r--]));
               }else{
                   res.push_back((A[l]*A[l++]));
               }
           }
           std::reverse(begin(res), end(res));
           return res;
       }
//面试题 02.02. 返回倒数第 k 个节点
       int kthToLast(ListNode *head, int k){
           ListNode *pre = head;
           ListNode *cur = head;
           while(pre && k--)pre = pre->next;
           while(pre && cur){
               pre = pre->next;
               cur = cur->next;
           }
           return cur->val;
       }
//1248. 统计「优美子数组」
       int numberOfSubarrays(std::vector<int> &nums, int k){
           int l = 0, r = 0;
           int b = -1, e = -1;
           int len = nums.size();
           int res = 0;
           while(r < len){
               if(b==-1 && nums[r]&1)b = r;
               if(nums[r]&1 && !--k){
                   e = r++;
                   while(r<len && !(nums[r]&1))++r;
                   res += (b-l+1) * (--r-e+1);
                   while(l<r && !(nums[l]&1))++l;
                   b = ++l;
                   while(b<=r && !(nums[b]&1))++b;
                   ++k;
               }
               ++r;
           }
           return res;
       }
//345. 反转字符串中的元音字母
       std::string reverseVomels(std::string s){
           std::unordered_set<char> mp = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
           int l = 0, r = s.size() - 1;
           while(l < r){
               while(l<r && !mp.count(s[l]))++l;
               while(l<r && !mp.count(s[r]))--r;
               std::swap(s[l++], s[r--]);
           }
           return s;
       }
//28. 实现 strStr()
       int strStr(std::string haystack, std::string needle){
           int l1 = haystack.size();
           int l2 = needle.size();
           if(!l2)return l2;
           if(l1 < l2)return -1;
           std::vector<int> next(l2+1);
           std::function<void(void)> _get_next = [&](void){
                    int r = 1;
                    int j = 0;
                    while(r < l2){
                        if(needle[j] == needle[r]){
                            next[++r] = ++j;
                        }else if(!j){
                            next[++r] = 0;
                        }else{
                            j = next[j];
                        }
                    }
                };
           _get_next();
           int i = 0, j = 0;
           while(i<l1 && j<l2){
               if(haystack[i] == needle[j]){
                   ++i, ++j;
               }else if(!j){
                   ++i;
               }else{
                   j = next[j];
               }
           }
           return j==l2?i-l2:-1;
       }
//904. 水果成篮
       int totalFruit(std::vector<int> &tree){
           int f1 = -1,f2 = -1;
           int l  = 0,  r = 0;
           int res = 0;
           int len = tree.size();
           while(r < len){
               if(f1==-1 || tree[r]==tree[f1]){
                   f1 = r;
               }else if(f2==-1 || tree[r]==tree[f2]){
                   f2 = r;
               }else{
                   f1 > f2 ? (l = f2 + 1, f2 = r) : (l = f1 + 1, f1 = r);
               }
               res = std::max(res, ++r - l);
           }
           return res;
       }
//413. 等差数列划分
        int numberOfArithmetic(std::vector<int>& A){
            int size = A.size();
            if(size<=2)return 0;
            int l = 0;
            int r = 1;
            int d = A[r++] - A[l];
            int res =  0;
            int n = 0;
            while(r<size){
                if(A[r]-A[r-1] != d){
                    if((n=r-l-2)>=1)res += (n*(n+1))>>1;
                    l = r - 1;
                    d = A[r] - A[r-1];
                }
                ++r;
            }
            if((n=r-l-2)>=1)res += (n*(n+1))>>1;
            return res;
        }
};
