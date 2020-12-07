/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_sort.cpp
*     author   : @ JY
*     date     : 2020--10--10
**********************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <numeric>
#include <queue>
#include <climits>
#include <stack>
#include <functional>
#include <cmath>
#include <sstream>
#include <stdlib.h>

struct ListNode{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode (int v) : val(v), left(NULL), right(NULL) {}
};
class Solution{
    public:
//973. 最接近原点的 K 个点
        std::vector<std::vector<int>> kCloest(std::vector<std::vector<int>> &points, int K){
            std::vector<std::pair<int, int>> po;
            for(auto &p : points)po.emplace_back(p[0], p[1]);
            std::sort(begin(po), end(po), [&](auto &a, auto &b){
                    return (a.first*a.first + a.second*a.second) <
                           (b.first*b.first + b.second*b.second); });
            std::vector<std::vector<int>> res;
            int len = 0;
            for(int i=0; i<K; ++i)res.push_back({po[i].first,po[i].second});
            return res;
        }
//853. 车队
        int carFleet(int target, std::vector<int> &position, std::vector<int> &speed){
            std::vector<std::pair<int, double>> p_t;
            int len = position.size();
            if(len<2)return len;
            for(int i=0; i<len; ++i){
                p_t.emplace_back(position[i], (double)(target-position[i])/speed[i]);
            }
            std::sort(begin(p_t), end(p_t));
            int res = 0;
            while(--len > 0){
                if(p_t[len].second < p_t[len-1].second){
                    ++res;
                }else{
                    p_t[len-1] = p_t[len];
                }
            }
            return ++res;
        }
//1424. 对角线遍历 II
        std::vector<int> findDiagonalOrder(std::vector<std::vector<int>> &nums){
            int m = nums.size();
            std::map<int, std::vector<int>> mp;
            for(int i=m-1; i>=0; --i){
                for(int j=nums[i].size()-1; j>=0; --j){
                    mp[i+j].push_back(nums[i][j]);
                }
            }
            std::vector<int> res;
            for(auto &&[k, v] : mp)res.insert(end(res), begin(v), end(v));
            return res;
        }
        std::vector<int> findDiagonalOrder_fuck(std::vector<std::vector<int>> &nums){
            int m = nums.size(), n = nums[0].size();
            for(int i=0; i<m; ++i)n = std::max(n, (int)nums[i].size());
            for(int i=0; i<m; ++i){
                while((int)nums[i].size() < n)nums[i].push_back(-1);
            }
            int i = 0, j = 0;
            std::vector<int> res;
            while(i<m-1 || j<n){
                int x = i, y = j;
                while(x>=0 && y<n){
                    if(nums[x][y] != -1){
                        res.push_back(nums[x][y]);
                    }
                    --x, ++y;
                }
                i == m-1 ? ++j : ++i;
            }
            return res;
        }
//面试题 16.21. 交换和
        std::vector<int> findSwapValues(std::vector<int> &array1, std::vector<int> &array2){
            int sum1 = std::accumulate(begin(array1), end(array1), 0);
            int sum2 = std::accumulate(begin(array2), end(array2), 0);
            int diff = std::max(sum1, sum2) - std::min(sum1, sum2);
            if(!diff || diff&1)return {};
            int _f = 0;
            auto &t1 = sum1 > sum2 ? (_f = 1, array1) : array2;
            auto &t2 = sum1 < sum2 ? array1 : array2;
            std::unordered_set<int> mp(begin(t2), end(t2));
            for(auto &x : t1){
                if(mp.count(x-diff/2)){
                    return _f ? std::vector<int>{x, x-diff/2} : std::vector<int>{x-diff/2, x};
                }
            }
            return {};
        }
//1353. 最多可以参加的会议数目
        int maxEvents(std::vector<std::vector<int>> &events){
            std::sort(begin(events), end(events));
            std::priority_queue<int, std::vector<int>, std::greater<>> q;
            int i = 0, len = events.size(), res = 0, begin = 0;
            while(i<len || q.size()){
                ++begin;
                while(q.size() && q.top() < begin)q.pop();
                while(i<len && events[i][0] == begin)q.push(events[i++][1]);
                if(!q.size())continue;
                q.pop();
                ++res;
            }
            return res;
        }
//1370. 上升下降字符串
        std::string sortString_buk(std::string s){
            std::vector<int> buk(26);
            for(auto &c : s)++buk[c-'a'];
            std::function<bool(void)> _has_char = [&](void){
                for(auto &x : buk)if(x>0)return true;
                return false; };
            std::string res;
            std::function<void(int)> _get_char = [&](int i){
                if(--buk[i]>=0)res.push_back(i+'a');
            };
            while(_has_char()){
                for(int i=0;  i<26; ++i)_get_char(i);
                for(int i=25; i>=0; --i)_get_char(i);
            }
            return res;
        }
        std::string sortString(std::string s){
            std::string res;
            std::sort(begin(s), end(s));
            while(1){
                res += s[0];
                s.erase(s.begin());
                if(!s.size())return res;
                while(1){
                    auto j = std::upper_bound(begin(s), end(s), res.back());
                    if(j==end(s))break;
                    res += *j;
                    s.erase(j);
                }
                if(!s.size())return res;
                res += s.back();
                s.pop_back();
                if(!s.size())return res;
                while(1){
                    int i = s.size() - 1;
                    for( ; i>=0; --i){
                        if(s[i] < res.back())break;
                    }
                    if(i==-1)break;
                    res += s[i];
                    s.erase(s.begin()+i);
                    if(!s.size())return res;
                }
                if(!s.size())return res;
            }
            return "";
        }
//148. 排序链表
        ListNode *sortList_11(ListNode *head){
            using ln = ListNode;
            std::function<ln *(ln *, int)> _split = [&](ln *head, int len){
                while(head && len--)head = head->next;
                if(!head)return head;
                ln *ans = head->next;
                head->next = nullptr;
                return ans;
            };
            std::function<ln *(ln *, ln *, ln**)> _merge = [&](ln *l, ln *r, ln **back_tail){
                ln head, *cur = &head, **h;
                while(l && r){
                    h         = l->val > r->val ? &r : &l;
                    cur->next = (*h);
                    *h        = (*h)->next;
                    cur       = cur->next;
                }
                cur->next = l ? l : r;
                while(cur->next)cur = cur->next;
                *back_tail = cur;
                return head.next;
            };
            ln H, *tail, *l = head, *r, *back_tail;
            H.next = head;
            int len = 1, size = 0;
            while(l)l=l->next, ++size;
            while(len < size){
                head = H.next;
                tail = &H;
                while(l){
                    l          = head;
                    r          = _split(l, len);
                    head       = _split(r, len);
                    tail->next = _merge(l, r, &back_tail);
                    tail       = back_tail;
                }
                len <<= 1;
            }
            return H.next;
        }
        ListNode *sortList(ListNode *head){
            std::function<ListNode *(ListNode *, int)> _cut = [&](ListNode *h, int n){
                while(h && --n)h = h->next;
                if(!h)return h;
                ListNode *ans = h->next;
                h->next = nullptr;
                return ans;
            };
            std::function<ListNode *(ListNode*, ListNode*, ListNode **)> _merge
                = [&](ListNode *h1, ListNode *h2, ListNode **t){
                    ListNode ans, *cur, **h;
                    cur = &ans;
                    while(h1 && h2){
                        h         = h1->val > h2->val ? &h2 : &h1;
                        cur->next = *h;
                        *h        = (*h)->next;
                        cur       = cur->next;
                    }
                    cur->next = h1 ? h1 : h2;
                    while(cur->next)cur = cur->next;
                    *t = cur;
                    return ans.next;
            };
            int len = 1, size = 0;
            ListNode H, *h = head, *left, *right, *tail, *cur;
            H.next = head;
            while(h)++size, h = h->next;
            while(len < size){
                head = H.next;
                tail = &H;
                while(head){
                    left       = head;
                    right      = _cut(left, len);
                    head       = _cut(right, len);
                    tail->next = _merge(left, right, &h);
                    tail       = h;
                }
                len <<= 1;
            }
            return H.next;
        }
//1288. 删除被覆盖区间
        int removeCoveredIntervals(std::vector<std::vector<int>> &intervals){
            std::vector<std::pair<int, int>> ans;
            for(auto &p : intervals)ans.emplace_back(p[0], p[1]);
            std::sort(begin(ans), end(ans), [&](auto &a, auto &b){
                return a.first==b.first ? a.second > b.second : a.first < b.first; });
            int res = 0, len = ans.size();
            for(int i=0; i<len; ){
                int r = ans[i].second;
                while(i<len && r>=ans[i].second)++i;
                ++res;
            }
            return res;
        }
//1030. 距离顺序排列矩阵单元格
        std::vector<std::vector<int>> allCellsDistOrder_bfs(int R, int C, int r0, int c0){
            std::vector<std::vector<int>> res;
            std::vector<int> _fun = {0, 1, 0, -1, 0};
            std::queue<std::pair<int, int>> q;
            std::vector<std::vector<int>> vi(R, std::vector<int>(C, 0));
            vi[r0][c0] = 1;
            q.push({r0, c0});
            res.push_back({r0, c0});
            while(q.size()){
                int size = q.size();
                for(int k=0; k<size; ++k){
                    auto [i, j] = q.front();q.pop();
                    for(int f=0; f<4; ++f){
                        int i1 = i + _fun[f];
                        int j1 = j + _fun[f+1];
                        if(i1<0 || j1<0 || i1>=R || j1>=C)continue;
                        if(vi[i1][j1])continue;
                        vi[i1][j1] = 1;
                        res.push_back({i1, j1});
                        q.push({i1, j1});
                    }
                }
            }
            return res;
        }
        std::vector<std::vector<int>> allCellsDistOrder_sort(int R, int C, int r0, int c0){
            std::vector<std::pair<int, int>> ans;
            for(int i=0; i<R; ++i){
                for(int j=0; j<C; ++j){
                    ans.emplace_back(i, j);
                }
            }
            std::sort(begin(ans), end(ans), [&](auto &a, auto &b){
                    return abs(a.first-r0) + abs(a.second-c0) <
                           abs(b.first-r0) + abs(b.second-c0);
                });
            std::vector<std::vector<int>> res;
            for(auto &&[i, j] : ans)res.push_back({i, j});
            return res;
        }
//面试题 17.14. 最小K个数
        std::vector<int> smallestK(std::vector<int> &arr, int k){
            if(!k)return {};
            std::priority_queue<int> q;
            for(auto &x : arr){
                if(q.size() < k){
                    q.push(x);
                }else if(q.top() > x){
                    q.pop();
                    q.push(x);
                }
            }
            std::vector<int> res;
            while(q.size()){
                res.push_back(q.top());
                q.pop();
            }
            return res;
        }
//976. 三角形的最大周长
        int largestPerimeter(std::vector<int> &A){
            int len = A.size();
            if(len < 3)return 0;
            std::function<bool(int, int, int)> _is_ok
                = [&](int a, int b, int c){
                    return (a+b) > c && (c-b) < a;
                };
            std::sort(begin(A), end(A));
            for(int i=len-3; i>=0; --i){
                if(_is_ok(A[i], A[i+1], A[i+2]))return A[i] + A[i+1] + A[i+2];
            }
            return 0;
        }
//1054. 距离相等的条形码
        std::vector<int> rearrangeBarrcodes(std::vector<int> &barcodes){
            using pii = std::pair<int, int>;
            struct _cmp{
                bool operator()(const pii &a, const pii &b) const {
                    return a.second < b.second; }
            };
            int k = 2;
            std::unordered_map<int, int> mp;
            for(auto &x : barcodes)++mp[x];
            std::priority_queue<pii, std::vector<pii>, _cmp> q(begin(mp), end(mp));
            std::vector<int> res;
            std::vector<pii> temp;
            while(q.size() >= k){
                int n = k;
                while(n--){
                    auto [k, v] = q.top();q.pop();
                    res.push_back(k);
                    if(--v)temp.emplace_back(k, v);
                }
                for(auto &x : temp)q.push(x);
                temp.clear();
            }
            while(q.size()){
                auto [k, v] = q.top();q.pop();
                res.push_back(k);
            }
            return res;
        }
//1451. 重新排列句子中的单词
        std::string arrangeWords(std::string text){
            text[0] = std::tolower(text[0]);
            std::vector<std::string> ans;
            std::stringstream ss(text);
            std::string res;
            while(ss >> res)ans.push_back(res);
            text[0] = std::tolower(text[0]);
            std::stable_sort(begin(ans), end(ans), [&](auto &a, auto &b){
                    return a.size() < b.size(); });
            res = "";
            for(auto &x : ans)res += x + " ";
            res.pop_back();
            res[0] = std::toupper(res[0]);
            return res;
        }
//1305. 两棵二叉搜索树中的所有元素
        std::vector<int>getAllElement_better(TreeNode *root1, TreeNode *root2){
            std::vector<int> res1, res2;
            std::function<void(TreeNode *, std::vector<int> &)> _calc
                = [&](TreeNode *root, std::vector<int> &res){
                    std::stack<TreeNode*> st;
                    while(root || st.size()){
                        if(root){
                            st.push(root);
                            root = root->left;
                        }else{
                            root = st.top();st.pop();
                            res.push_back(root->val);
                            root = root->right;
                        }
                    }
                };
            _calc(root1, res1), _calc(root2, res2);
            int len1 = res1.size(), len2 = res2.size();
            std::vector<int> res(len1 + len2);
            int i = 0, j = 0, cur = -1;
            while(i<len1 && j<len2){
                res[++cur] = res1[i] > res2[j] ? res2[j++] : res1[i++];
            }
            while(i<len1)res[++cur] = res1[i++];
            while(j<len2)res[++cur] = res2[j++];
            return res;
        }
        std::vector<int>getAllElement(TreeNode *root1, TreeNode *root2){
            std::vector<int> res;
            std::function<void(TreeNode *)> _calc = [&](TreeNode *root){
                std::stack<TreeNode *> st;
                while(root || st.size()){
                    if(root){
                        st.push(root);
                        root = root->left;
                    }else{
                        root = st.top();st.pop();
                        res.push_back(root->val);
                        root = root->right;
                    }
                }
            };
            _calc(root1), _calc(root2);
            std::sort(begin(res), end(res));
            return res;
        }
//1329. 将矩阵按对角线排序
        std::vector<std::vector<int>> diagonalSort(std::vector<std::vector<int>> &mat){
            int m = mat.size(), n = mat[0].size();
            std::vector<int> temp;
            int i = 0, j = n - 1;
            while(i<m || j>=0){
                int x = i, y = j;
                while(x<m && y<n)temp.push_back(mat[x++][y++]);
                std::sort(begin(temp), end(temp), std::greater<int>());
                int index = 0;
                temp.clear();
                while(--x>=0 && --y>=0)mat[x][y] = temp[index++];
                j > 0 ? --j : ++i;
            }
            return mat;
        }
//1387. 将整数按权重排序
        int getKth(int lo, int hi, int k){
            std::vector<int> ans(hi-lo+1);
            std::iota(begin(ans), end(ans), lo);
            std::unordered_map<int, int> dp;
            dp[1] = 0, dp[2] = 1;
            std::function<int(int)> _dfs = [&](int t){
                    if(dp.count(t))return dp[t];
                    return dp[t] = (t & 1 ? _dfs(t*3+1) : _dfs(t>>1)) + 1;
                };
            std::sort(begin(ans), end(ans), [&](auto &a, auto &b){
                    int a1 = _dfs(a), b1 = _dfs(b);
                    return a1==b1 ? a < b : a1 < b1;
                });
            return ans[k-1];
        }
//969. 煎饼排序
        std::vector<int> pancakeSort(std::vector<int> &arr){
            std::vector<int> res;
            for(int i=arr.size()-1; i>0; --i){
                int j = std::max_element(begin(arr), begin(arr) + i + 1) - begin(arr);
                if(j){
                    std::reverse(begin(arr), begin(arr) + j + 1);
                    res.push_back(j+1);
                }
                std::reverse(begin(arr), begin(arr)+i+1);
                res.push_back(i+1);
            }
            return res;
        }
//164. 最大间距
        int maximumGap(std::vector<int> &nums){
            int len = nums.size();
            if(len < 2)return 0;
            struct _node{
                bool _ok = 0;
                int _min = std::numeric_limits<int>::max();
                int _max = std::numeric_limits<int>::min();
            };
            int mini = *min_element(begin(nums), end(nums));
            int maxi = *max_element(begin(nums), end(nums));
            int bukV = std::max(1, (maxi-mini)/((int)nums.size()-1));
            int bukS = (maxi-mini) / bukV + 1;
            std::vector<_node> buk(bukS);
            for(auto &x : nums){
                int index = (x - mini) / bukV;
                buk[index]._ok  = 1;
                buk[index]._min = std::min(buk[index]._min, x);
                buk[index]._max = std::max(buk[index]._max, x);
            }
            int res = 0, pre = mini;
            for(auto &node : buk){
                if(!node._ok)continue;
                res = std::max(res, node._min - pre);
                pre = node._max;
            }
            return res;
        }
//1122. 数组的相对排序
        std::vector<int> relativeSortArray_buk(std::vector<int> &arr1, std::vector<int> &arr2){
            std::vector<int> buk(1001);
            for(auto &x : arr1)++buk[x];
            int index = 0;
            for(auto &x : arr2){
                while(buk[x]-- > 0)arr1[index++] = x;
            }
            for(int i=0; i<1001; ++i){
                while(buk[i]-- > 0)arr1[index++] = i;
            }
            return arr1;
        }
        std::vector<int> relativeSortArray(std::vector<int> &arr1, std::vector<int> &arr2){
            int len = arr2.size();
            std::unordered_map<int, int>  mp1;
            std::vector<std::vector<int>> mp2(len);
            for(int i=0; i<len; ++i)mp1[arr2[i]] = i;
            std::vector<int> res, temp;
            for(auto &x : arr1){
                if(mp1.count(x)){
                    mp2[mp1[x]].push_back(x);
                }else{
                    temp.push_back(x);
                }
            }
            for(auto &v : mp2)res.insert(end(res), begin(v), end(v));
            std::sort(begin(temp), end(temp));
            res.insert(end(res), begin(temp), end(temp));
            return res;
        }
//1356. 根据数字二进制下 1 的数目排序
        std::vector<int> ssortByBits(std::vector<int> &arr){
            std::sort(begin(arr), end(arr), [&](int a, int b){
                int a1 = __builtin_popcount(a);
                int b1 = __builtin_popcount(b);
                return a1==b1 ? a < b : a1 < b1; });
            return arr;
        }
//1403. 非递增顺序的最小子序列
        std::vector<int> minSubsequence(std::vector<int> &nums){
            std::sort(begin(nums), end(nums));
            int sum = accumulate(begin(nums), end(nums), 0);
            std::vector<int> res;
            int temp = 0;
            for(int i=nums.size()-1; i>=0; --i){
                temp += nums[i];
                if(temp > sum - temp){
                    res.push_back(nums[i]);
                    break;
                }
                res.push_back(nums[i]);
            }
            return res;
        }
//1333. 餐厅过滤器
        std::vector<int> fillterRestuarants(std::vector<std::vector<int>> &restaurants, int ve, int mP, int mD){
            std::vector<std::pair<int, int>> id_rank;
            for(auto &v : restaurants){
                if(ve && !v[2])continue;
                if(mP < v[3] || mD < v[4])continue;
                id_rank.emplace_back(v[0], v[1]);
            }
            std::sort(begin(id_rank), end(id_rank), [&](auto &p1, auto &p2){
                return p1.second==p2.second ? p1.first > p2.first : p1.second > p2.second; });
            std::vector<int> res;
            for(auto &&[k, v] : id_rank)res.emplace_back(k);
            return res;
        }
//1452. 收藏清单
        std::vector<int> peopleIndexes(std::vector<std::vector<std::string>> &f){
            int len = f.size();
            for(auto &v : f)std::sort(begin(v), end(v));
            std::vector<int> res;
            std::map<int, std::vector<int>> mp;
            for(int i=0; i<len; ++i)mp[f[i].size()].push_back(i);
            std::function<bool(int)> _include = [&](int p){
                for(auto &x : res){
                    if(std::includes(f[x].begin(), f[x].end(), f[p].begin(), f[p].end()))return true;
                }
                return false;
            };
            for(auto it=mp.rbegin(); it!=mp.rend(); ++it){
                for(auto &p : it->second){
                    if(it!=mp.rbegin() && _include(p))continue;
                    res.push_back(p);
                }
            }
            std::sort(begin(res), end(res));
            return res;
        }
//922. 按奇偶排序数组 II
        std::vector<int> sortArrayByParityII(std::vector<int> &A){
            int l = 0, r = 1;
            int len = A.size();
            while(l<len && r<len){
                while(l<len && !(A[l]&1))l += 2;
                while(r<len && A[r]&1)r += 2;
                if(l<len)std::swap(A[l], A[r]);
                l += 2, r += 2;
            }
            return A;
        }
//e 358. K 距离间隔重排字符串（
        std::string reorganizeStringK(std::string S, int k){
            using pci = std::pair<char, int>;
            struct _cmp{
                bool operator()(const pci &a, const pci &b) const {
                    return a.second < b.second; }
            };
            std::unordered_map<char, int> mp;
            for(auto &c : S)++mp[c];
            std::priority_queue<pci, std::vector<pci>, _cmp> q(begin(mp), end(mp));
            std::vector<pci> temp;
            std::string res;
            while(q.size() >= k){
                temp.clear();
                int dis = k;
                while(dis--){
                    auto [c, v] = q.top();q.pop();
                    res += c;
                    if(--v)temp.emplace_back(c, v);
                }
                for(auto &p : temp)q.push(p);
            }
            while(q.size()){
                if(q.top().second==1){
                    res += q.top().first;
                    q.pop();
                }else{
                    return "";
                }
            }
            return res;
        }
//767. 重构字符串
        std::string reorganizeString(std::string S){
            std::unordered_map<char, int> mp;
            int max_ = 0;
            for(auto &c : S)max_ = std::max(max_, ++mp[c]);
            std::vector<std::pair<char, int>> c_n(begin(mp), end(mp));
            std::sort(begin(c_n), end(c_n), [&](auto &a, auto &b){
                    return a.second > b.second; });
            int len = S.size();
            if(max_ > (len+1)/2)return "";
            std::string res(len,' ');
            for(int i=0,index=0; i<2; ++i){
                for(int j=i; j<len && c_n[index].second>0; j+=2){
                    res[j] = c_n[index].first;
                    if(!--c_n[index].second)++index;
                }
            }
            return res;
        }
//220. 存在重复元素 III
        bool containsNearbyAlmostDuplicates(std::vector<int> &nums, int k, int t){
            if(t<0)return false;
            using ll = long long;
            std::unordered_map<ll,ll> mp;
            int len = nums.size();
            ll MOD  = t + 1;
            for(int i=0; i<len; ++i){
                long long buk = nums[i] / MOD;
                if(nums[i] < 0)--buk;
                if(mp.count(buk))return true;
                if(mp.count(buk+1) && abs(mp[buk+1]-nums[i]) <= t)return true;
                if(mp.count(buk-1) && abs(mp[buk-1]-nums[i]) <= t)return true;
                mp[buk] = nums[i];
                if(i>=k)mp.erase(nums[i-k] / MOD);
            }
            return false;
        }
        bool containsNearbyAlmostDuplicates_fuck(std::vector<int> &nums, int k, int t){
            std::set<int> mp;
            int len = nums.size();
            for(int i=0; i<len; ++i){
                auto l_b = std::lower_bound(begin(mp), end(mp), static_cast<long long>(nums[i])-t);
                if(l_b!=mp.end() && *l_b <= static_cast<long long>(nums[i]) + t)return true;
                mp.insert(nums[i]);
                if(i>=k)mp.erase(nums[i-k]);
            }
            return false;
        }
//324. 摆动排序 II
        void wiggleSortII_better(std::vector<int> &nums){
#define A(i) nums[(1+(i)*2) % ((len)|1)]
            int len    = nums.size();
            auto midit = nums.begin() + len/2;
            std::nth_element(nums.begin(), midit, nums.end());
            int mid = *midit;
            int l = -1, r = len, cur = 0;
            while(cur < r){
                if(A(cur) > mid){
                    std::swap(A(cur++), A(++l));
                }else if(A(cur) < mid){
                    std::swap(A(cur), A(--r));
                }else{
                    ++cur;
                }
            }
        }
        void wiggleSortII(std::vector<int> &nums){
            std::function<void(int, int ,int)> _quickSelect
                = [&](int be, int en, int n){
                    int m = nums[en-1];
                    int l = be, r = be;
                    while(r < en){
                        if(nums[r] <= m){
                            std::swap(nums[r++], nums[l++]);
                        }else{
                            ++r;
                        }
                    }
                    if(l-1>n){
                        _quickSelect(be, l-1, n);
                    }else if(l <= n){
                        _quickSelect(l, en, n);
                    }
            };
            int len = nums.size();
            int n   = len / 2;
            _quickSelect(0, len, n);
            int mid = nums[n];
            int l = -1, r = len, cur = 0;
            while(cur < r){
                if(nums[cur] < mid){
                    std::swap(nums[++l], nums[cur++]);
                }else if(nums[cur] > mid){
                    std::swap(nums[--r], nums[cur]);
                }else{
                    ++cur;
                }
            }
            auto midit = nums.begin() + n + (len & 1);
            std::vector<int> temp1(nums.begin(), midit);
            std::vector<int> temp2(midit, nums.end());
            for(int i=0; i<temp1.size(); ++i){
                nums[i*2] = temp1[temp1.size()-i-1];
            }
            for(int i=0; i<temp2.size(); ++i){
                nums[i*2+1] = temp2[temp2.size()-i-1];
            }
        }
//1366. 通过投票对团队排名
        std::string rankTeams(std::vector<std::string> &votes){
            int m = votes.size();
            int n = votes[0].size();
            std::unordered_map<char, std::vector<int>> ranking;
            for(auto &c : votes[0])ranking[c].resize(n);
            for(auto &s : votes){
                for(int i=0; i<n; ++i)++ranking[s[i]][i];
            }
            using pcvi = std::pair<char, std::vector<int>>;
            std::vector<pcvi> temp(begin(ranking), end(ranking));
            std::sort(begin(temp), end(temp), [&](auto &a, auto &b){
               return a.second==b.second ? a.first < b.first : a.second > b.second; });
            std::string res;
            for(auto &&[k, v] : temp)res += k;
            return res;
        }
//147. 对链表进行插入排序
        ListNode *insertionSortList(ListNode *head){
            if(!head || !head->next)return head;
            ListNode *H = new ListNode(-1);
            H->next = head;
            head = head->next;
            H->next->next = NULL;
            ListNode *temp, *pre, *cur;
            while(head){
                temp = head->next;
                pre  = H, cur = H->next;
                while(cur && cur->val < head->val){
                    pre = pre->next;
                    cur = cur->next;
                }
                pre->next  = head;
                head->next = cur;

                head = temp;
            }
            head = H->next;
            delete H;
            return head;
        }
//1383. 最大的团队表现值
        int maxPreformance(int n, std::vector<int> &speed, std::vector<int> &efficiency, int k){
            using ll = long long;
            int MOD = 1e9 + 7;
            struct _node{
                int s, e;
                _node(int sp, int ei) : s(sp), e(ei) {}
                bool operator < (const _node &oth) const{
                    return s > oth.s; }
            };
            int len = speed.size();
            std::vector<_node> G;
            for(int i=0; i<len; ++i)G.emplace_back(speed[i], efficiency[i]);
            std::sort(begin(G), end(G), [&](auto &a, auto & b){
                    return a.e > b.e; });
            std::priority_queue<_node> q;
            ll res = 0, sum = 0, min_e;
            for(int i=0; i<len; ++i){
                min_e = G[i].e;
                res   = std::max(res, (sum += G[i].s) * min_e);
                q.push(G[i]);
                if(q.size() == k){
                    sum -= q.top().s;
                    q.pop();
                }
            }
            return res % MOD;
        }
//面试题 16.16. 部分排序
        std::vector<int> subSort(std::vector<int> &array){
            int max_ = INT_MIN, min_ = INT_MAX;
            int len  = array.size();
            int l = -1, r = -1;
            for(int i=0; i<len; ++i){
                if(array[i] < max_)r = i;
                max_ = std::max(max_, array[i]);
                if(array[len-i-1] > min_)l = len-i-1;
                min_ = std::min(min_, array[len-i-1]);
            }
            return {l, r};
        }
};
