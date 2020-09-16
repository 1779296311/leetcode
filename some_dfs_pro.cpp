/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_dfs_pro.cpp
*     author   : @ JY
*     date     : 2020--09--01
**********************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include <cmath>
#include <unordered_set>
#include <climits>
#include <functional>
#include <numeric>
#include <stdlib.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };
class Node1 {
public:
    int val;
    Node1* prev;
    Node1* next;
    Node1* child;
};
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};
class Solution{
public:
//947. 移除最多的同行或同列石头
    int removeStones(vector<vector<int>>& stones) {
            int m = stones.size();
            int n = stones[0].size();
            std::vector<int> _f(20000);
            std::iota(_f.begin(), _f.end(), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i]==i?i:_f[i]=_find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                _f[_find(a)] = _f[_find(b)]; };
            for(auto &s : stones){
                _union(s[0], s[1]+10000);
            }
            std::unordered_set<int> mp;
            for(auto &s : stones){
                mp.insert(_find(s[0]));
            }
            return m - mp.size();
    }
//337. 打家劫舍 III
    int rob(TreeNode* root) {
            typedef std::pair<int, int> pii;
            std::function<pii(TreeNode *)> _dfs = [&](TreeNode *root){
                if(!root)return pii{0, 0};
                auto left  = _dfs(root->left);
                auto right = _dfs(root->right);
                int  no_s  =  std::max(left.first, left.second) +
                              std::max(right.first, right.second);
                int  yes_s = root->val + left.first + right.first;
                return pii{no_s, yes_s};
            };
            auto res = _dfs(root);
            return std::max(res.first, res.second);
    }
//302. 层数最深叶子节点的和
    int deepestLeavesSum(TreeNode* root) {
            int res   = 0;
            int max_d = 0;
            std::function<void(TreeNode *, int)> _dfs = [&](TreeNode *root, int d){
                if(!root)return ;
                if(d==max_d){
                    res += root->val;
                }else if(d > max_d){
                    res   = root->val;
                    max_d = d;
                }
                _dfs(root->left,  d+1);
                _dfs(root->right, d+1);
            };
            _dfs(root, 0);
            return res;
    }
//1203. 项目管理
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
            int g_size = m ;
            for(int i=0; i<n; ++i){
                if(group[i]==-1)group[i] = g_size++;
            }
            std::vector<int> in_gp(g_size);
            std::vector<int> in_pj(n);
            std::vector<int> pj[n];
            std::unordered_set<int> gp[g_size];

            for(int i=0; i<n; ++i){
                int gi = group[i];
                for(auto &p : beforeItems[i]){
                    if(gi==group[p]){
                        pj[p].push_back(i);
                        ++in_pj[i];
                    }else if(!gp[group[p]].count(gi)){
                        gp[group[p]].insert(gi);
                        ++in_gp[gi];
                    }
                }
            }
            std::queue<int> q;
            for(int i=0; i<g_size; ++i){
                if(!in_gp[i])q.push(i);
            }
            std::vector<int> ordered_gp;
            while(q.size()){
                int ng = q.front();q.pop();
                ordered_gp.push_back(ng);
                for(auto &x : gp[ng]){
                    if(!--in_gp[x])q.push(x);
                }
            }
            if(ordered_gp.size() != g_size)return {};
            std::vector<int> gp_pj[g_size];
            for(int i=0; i<n; ++i)gp_pj[group[i]].push_back(i);
            std::vector<int> res;
            std::function<bool(int)> _calc = [&](int g){
                std::queue<int> q;
                for(auto &p : gp_pj[g]){
                    if(!in_pj[p])q.push(p);
                }
                int cnt = gp_pj[g].size();
                while(q.size()){
                    int np = q.front(); q.pop();
                    res.push_back(np);
                    --cnt;
                    for(auto &x: pj[np]){
                        if(!--in_pj[x])q.push(x);
                    }
                }
                return !cnt;
            };
            for(auto &g : ordered_gp){
                if(!_calc(g))return {};
            }
            return res;
    }
//1559. 二维网格图中探测环
  bool containsCycle(vector<vector<char>>& grid) {
            int m = grid.size();
            int n = grid[0].size();
            std::vector<std::vector<int>> fun = {{1, 0},{-1, 0},{0, 1},{0, -1}};
            std::vector<std::vector<int>>vi(m, std::vector<int>(n, 0));
            std::function<bool(char, int, int, int, int)> dfs = [&](char c, int x, int y, int pre_x, int pre_y){
                if(x<0 || y<0 || x>=m || y>=n)return false;
                if(grid[x][y] != c)return false;
                if(vi[x][y])return true;
                vi[x][y] = 1;
                for(auto &f : fun){
                    int x1 = x + f[0];
                    int y1 = y + f[1];
                    if(x1==pre_x && y1==pre_y)continue;
                    if(dfs(c, x1, y1, x, y))return true;
                }
                vi[x][y]   = 0;
                grid[x][y] = '^';
                return false;
            };
            std::function<bool(void)> calc = [&](){
                for(int i=0; i<m; ++i){
                    for(int j=0; j<n; ++j){
                        if(grid[i][j]=='^')continue;
                        if(dfs(grid[i][j], i, j, -1, -1))return true;
                    }
                }
                return false;
            };
            return calc();
    }
//1448. 统计二叉树中好节点的数目
    int goodNodes(TreeNode* root) {
            std::function<int(TreeNode *, int)> _dfs = [&](TreeNode *root, int max_){
                if(!root)return 0;
                return _dfs(root->left,  std::max(root->val, max_))+
                       _dfs(root->right, std::max(root->val, max_)) + (root->val>=max_);
            };
            return _dfs(root, INT_MIN);
    }
//733. 图像渲染
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
            int oldColor = image[sr][sc];
            if(newColor==oldColor)return image;
            int m        = image.size();
            int n        = image[0].size();
            std::vector<std::vector<int>> _fun = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
            std::function<void(int, int)> _dfs = [&](int i, int j){
                if(image[i][j] != oldColor)return;
                image[i][j] = newColor;
                for(auto &f : _fun){
                    int i1 = i + f[0];
                    int j1 = j + f[1];
                    if(i1<0 || j1<0 || i1>=m || j1>=n){
                        continue;
                    }
                    _dfs(i1, j1);
                }
            };
            _dfs(sr, sc);
            return image;
    }
//1254. 统计封闭岛屿的数目
    int closedIsland(vector<vector<int>>& grid) {
            std::vector<std::vector<int>> _fun = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
            int res  = 0;
            int flag = 1;
            int m    = grid.size();
            int n    = grid[0].size();
            std::function<void(int, int)> _dfs = [&](int i, int j){
                grid[i][j] = 1;
                for(auto &f : _fun){
                    int i1 = i + f[0];
                    int j1 = j + f[1];
                    if(i1<0 || j1<0 || i1>=m || j1>=n){
                        flag = 0;
                        continue;
                    }
                    if(grid[i1][j1])continue;
                    _dfs(i1, j1);
                }
            };
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    flag = 1;
                    if(!grid[i][j])_dfs(i, j), res += flag;
                }
            }
            return res;
    }
//685. 冗余连接 II
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
            int n = edges.size();
            std::vector<int> _f(n+1);
            std::iota(_f.begin(), _f.end(), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i]==i?i:_f[i]=_find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                _f[_find(a)] = _f[_find(b)]; };
            std::vector<int> _in(n+1);
            int node_in_2;
            for(auto &e : edges){
                if(++_in[e[1]] > 1){
                    node_in_2 = e[1];
                    break;
                }
            }
            std::vector<std::vector<int>> E;
            int x, y;
            for(auto &e : edges){
                if(e[1]==node_in_2){
                    E.push_back(e);
                    continue;
                }
                if(_find(e[0]) != _find(e[1])){
                    _union(e[0], e[1]);
                }else{
                    x = e[0];
                    y = e[1];
                }
            }
            for(auto &e : E){
                if(_find(e[0]) != _find(e[1])){
                    _union(e[0], e[1]);
                }else{
                    x = e[0];
                    y = e[1];
                }
            }
            return {x, y};
    }
//988. 从叶结点开始的最小字符串
    string smallestFromLeaf(TreeNode* root) {
            struct _cmp{
                bool operator()(const std::string& a, const std::string &b){
                    int al = a.size();
                    int bl = b.size();
                    while(--al>=0 && --bl>=0){
                        if(a[al] > b[bl])return 1;
                        if(a[al] < b[bl])return 0;
                    }
                    return al > bl;
                }
            }cmp;
            std::string res = "|";
            std::function<void(TreeNode*, std::string)> _dfs = [&](TreeNode *root, std::string s){
                if(!root)return;
                s += root->val+'a';
                if(!root->left && !root->right){
                    if(cmp.operator()(res, s))res = s;
                    return;
                }
                _dfs(root->left, s);
                _dfs(root->right, s);
            };
            _dfs(root, "");
            reverse(res.begin(), res.end());
            return res;
    }
//979. 在二叉树中分配硬币
    int distributeCoins(TreeNode* root) {
            int res = 0;
            std::function<int(TreeNode*)> _dfs = [&](TreeNode *root){
                if(!root)return 0;
                int l = _dfs(root->left);
                int r = _dfs(root->right);
                res  += abs(l) + abs(r);
                return l + r + root->val - 1;
            };
            _dfs(root);
            return res;
    }
//301. 删除无效的括号
    vector<string> removeInvalidParentheses(string s) {
            int el = 0;
            int er = 0;
            for(int i=0; i<s.length(); ++i){
                if(s[i]=='(')++el;
                if(s[i]==')')!el?++er:--el;
            }
            std::vector<std::string> res;
            std::unordered_set<std::string> temp;
            std::function<void(int, std::string&, int,int, int)> _dfs =
                [&](int i, std::string& r, int el, int er, int c){
                    if(c>0 || el < 0 || er < 0)return;
                    if(i==s.length()){
                        if(!c) temp.insert(r);
                        return;
                    }
                    if(s[i]!='(' && s[i]!=')'){
                        r += s[i];
                        _dfs(i+1, r, el, er, c);
                        r.erase(r.length()-1, 1);
                    }else{
                        r += s[i];
                        int add = s[i]=='(';
                        _dfs(i+1, r, el, er,c+(add?-1:1));
                        r.erase(r.length()-1, 1);
                        _dfs(i+1, r, el-add, er-!add, c);
                    }
            };
            std::string r;
            _dfs(0, r, el, er, 0);
            for(auto &r : temp)res.push_back(r);
            return res;
    }
//863. 二叉树中所有距离为 K 的结点
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
            std::vector<int> res;
            std::function<void(TreeNode*, int)> _calc = [&](TreeNode *root, int d){
                if(!root)return;
                if(d==0){
                    res.push_back(root->val);
                    return ;
                }
                _calc(root->left,  d-1);
                _calc(root->right, d-1);
            };
            TreeNode *father = nullptr;
            std::function<bool(TreeNode*, TreeNode*)> _dfs = [&](TreeNode *root, TreeNode *pre){
                if(!root)return false;
                if(root==target){
                    father = pre;
                    return true;
                }
                if(_dfs(root->left, root)){
                    root->left = pre;
                    return true;
                }
                if(_dfs(root->right, root)){
                    root->right = pre;
                    return true;
                }
                return false;
            };
            _dfs(root, nullptr);
            _calc(target, K);
            _calc(father, K-1);
            return res;
    }
//1489. 找到最小生成树里的关键边和伪关键边
        ::std::vector<int> par;
        int find(int x){
            if(par[x] != x)par[x] = find(par[x]);
            return par[x];
        }
        int work1(int n, int k, ::std::vector<::std::vector<int>>& edges){
            for(int i=0; i<par.size(); ++i)par[i] = i;
            int res = 0;
            int t   = n - 1;
            for(auto tmp : edges){
                if(tmp[3]==k)continue;
                int p1 = find(tmp[1]);
                int p2 = find(tmp[2]);
                if(p1 != p2){
                    par[p1] = p2;
                    --t;
                    res += tmp[0];
                }
            }
            return !t?res:INT_MAX;
        }
        int work2(int n, int k, ::std::vector<::std::vector<int>>& edges){
            for(int i=0; i<par.size(); ++i)par[i] = i;
            int res = 0;
            int t   = n - 1;
            for(auto tmp : edges){
                if(tmp[3] == k){
                    par[find(tmp[1])] =  find(tmp[2]);
                    --t;
                    res += tmp[0];
                    break;
                }
            }
            for(auto tmp : edges){
                int p1 = find(tmp[1]);
                int p2 = find(tmp[2]);
                if(p1 != p2){
                    par[p1] = p2;
                    --t;
                    res += tmp[0];
                }
            }
            return !t?res:INT_MAX;
        }
        ::std::vector<::std::vector<int>> findCriticalAndPseudoCriticalEdges(int n, ::std::vector<::std::vector<int>>& edges){
            par = ::std::vector<int>(n);
            for(int i=0; i<edges.size(); ++i){
                auto& tmp = edges[i];
                ::std::swap(tmp[2], tmp[0]);
                tmp.push_back(i);
            }
            sort(edges.begin(), edges.end());
            int cost = work1(n,-1,edges);
            ::std::vector<::std::vector<int>> res(2);
            for(int i=0; i<edges.size(); ++i){
                if(cost != work1(n,i,edges)){
                    res[0].push_back(i);
                }else if(cost == work2(n,i,edges)){
                    res[1].push_back(i);
                }
            }
            return res;
        }
//面试题 04.02. 最小高度树
    TreeNode* sortedArrayToBST(vector<int>& nums) {
            std::function<TreeNode*(int, int)> _dfs = [&](int left, int right){
                if(left > right)return static_cast<TreeNode*>(nullptr);
                int mid        = left + ((right-left)>>1);
                TreeNode *root = new TreeNode(nums[mid]);
                root->left     = _dfs(left,  mid-1);
                root->right    = _dfs(mid+1, right);
                return root;
            };
            return _dfs(0, nums.size()-1);
    }
//有序链表转换二叉搜索树
    TreeNode* sortedListToBST(ListNode* head) {
        if(!head){
            return NULL;
        }
        return my_fun(head, 0);
    }
    TreeNode* my_fun(ListNode* __b, ListNode* __e){
        if(__e != __b){
            ListNode* __t1 = __b;
            ListNode* __t2 = __b;
            while(__t1 && __t1->next && __t1 != __e && __t1->next != __e){
                __t1 = __t1->next;
                __t1 = __t1->next;
                __t2 = __t2->next;
            }
             TreeNode* __root = new TreeNode(__t2->val);
              __root->left  = my_fun(__b, __t2);
              __root->right = my_fun(__t2->next, __e);
            return __root;
            }
        return NULL;
    }
//100. 相同的树
    bool isSameTree(TreeNode* p, TreeNode* q) {
            if(!p && !q)return true;
            if(p && !q)return false;
            if(!p && q)return false;
            if(p->val != q->val)return false;
            return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
//802. 找到最终的安全状态
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
            int n = graph.size();
            std::vector<int> dp(n);
            std::vector<int> vi(n);
            std::function<bool(int)> _dfs = [&](int i){
                if(vi[i]>0)return vi[i]==2;
                vi[i] = 1;
                for(int to : graph[i]){
                    if(vi[to]==2)continue;
                    if(vi[to]==1 || !_dfs(to))return false;
                }
                vi[i] = 2;
                return true;
            };
            std::vector<int> res;
            for(int i=0; i<n; ++i){
                if(_dfs(i))res.push_back(i);
            }
            return res;
    }
//210. 课程表 II
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
            typedef  std::vector<int> vi;
            typedef  std::vector<vi> vvi;
            int n = numCourses;
            vi _vi(n);
            vi res;
            vvi edges(n);
            for(auto &p : prerequisites){
                edges[p[0]].push_back(p[1]);
            }
            int flag = 0;
            std::function<void(int)> _dfs = [&](int i){
                _vi[i] = 1;
                for(auto &p : edges[i]){
                    if(_vi[p]==1){
                        flag = 1;
                        return;
                    }
                    if(_vi[p]==0)_dfs(p);
                    if(flag)return;
                }
                _vi[i] = 2;
                res.push_back(i);
            };
            for(int i=0; i<n; ++i)if(!_vi[i])_dfs(i);
            if(flag)return {};
          //  reverse(res.begin(), res.end());
            return res;
    }
    vector<int> findOrder_better(int numCourses, vector<vector<int>>& prerequisites) {
            std::vector<int> _in(numCourses);
            std::vector<std::vector<int>> edges(numCourses);
            for(auto &p : prerequisites){
                ++_in[p[0]];
                edges[p[1]].push_back(p[0]);
            }
            std::queue<int> q;
            for(int i=0; i<numCourses; ++i){
                if(!_in[i])q.push(i);
            }
            std::vector<int> res;
            while(q.size()){
                int b = q.front();q.pop();
                res.push_back(b);
                for(auto &t : edges[b]){
                    if(!--_in[t])q.push(t);
                }
            }
            return res.size()==numCourses?res:std::vector<int>{};
    }
//491. 递增子序列
    vector<vector<int>> findSubsequences(vector<int>& nums) {
            typedef  std::vector<std::vector<int>> vvi;
            vvi res;
            std::function<void(int, int, std::vector<int>& )> _dfs =
                [&](int cur, int pre, std::vector<int> &t){
                    if(cur==nums.size()){
                        if(t.size()>1)res.push_back(t);
                        return;
                    }
                    if(nums[cur] >= pre){
                        t.push_back(nums[cur]);
                        _dfs(cur+1, nums[cur], t);
                        t.pop_back();
                    }
                    if(nums[cur] != pre){
                        _dfs(cur+1, pre, t);
                    }
            };
            std::vector<int> t;
            _dfs(0, INT_MIN, t);
            return res;
    }
//1026. 节点与其祖先之间的最大差值
    int maxAncestorDiff(TreeNode* root) {
            if(!root)return 0;
            int res = 0;
            std::function<void(TreeNode *, int, int)> _dfs = [&](TreeNode *root, int max_, int min_){
                if(!root)return;
                res  = std::max(res, abs(root->val - max_));
                res  = std::max(res, abs(root->val - min_));
                max_ = std::max(max_, root->val);
                min_ = std::min(min_, root->val);
                _dfs(root->left, max_, min_);
                _dfs(root->right, max_, min_);
            };
            _dfs(root ,root->val, root->val);
            return res;
    }
//546. 移除盒子
#define ve   ::std::vector<int>
#define vve  ::std::vector<ve>
#define vvve ::std::vector<vve>
        int removeBoxes(::std::vector<int>& boxs){
            int size = boxs.size();
            vvve dp(size, vve(size, ve(size, 0)));
            return dfs(boxs, dp, 0, size-1, 0);
        }
        int dfs(ve& boxs, vvve&dp, int l, int r, int n){
            if(l>r)return 0;
            if(dp[l][r][n])return dp[l][r][n];
            while(r>l && boxs[r]==boxs[r-1]){
                --r;
                ++n;
            }
            dp[l][r][n] = dfs(boxs, dp, l, r-1, 0) + (n+1)*(n+1);
            for(int i=l; i<r; ++i){
                if(boxs[i]==boxs[r]){
                    dp[l][r][n] = ::std::max(dp[l][r][n], dfs(boxs, dp, l, i, n+1)+dfs(boxs, dp, i+1, r-1, 0));
                }
            }
            return dp[l][r][n];
        }
//473. 火柴拼正方形
    bool makesquare(vector<int>& nums) {
            if(nums.size() < 4)return false;
            typedef long long ll;
            ll len = 0;
            for(auto &x : nums) len += x;
            if(len%4)return false;
            len >>= 2;
            std::vector<ll> part(4);
            std::sort(nums.begin(), nums.end(), greater<int>());
            std::function<bool(int)> _dfs = [&](int i){
                if(i==nums.size()){
                    return part[0]==part[1]&&part[1]==part[2]&&part[2]==part[3]; }
                for(auto &p : part){
                    if(p+nums[i] > len)continue;
                    p += nums[i];
                    if(_dfs(i+1))return true;
                    p -= nums[i];
                }
                return false;
            };
            return _dfs(0);
    }
    bool makesquare_better(vector<int>& nums) {
            if(nums.size() < 4)return false;
            typedef long long ll;
            ll len = 0;
            for(auto &x : nums) len += x;
            if(len%4)return false;
            len >>= 2;
            std::sort(nums.begin(), nums.end());
            std::vector<ll> res;
            int size = 1<<nums.size();
            for(int i=0; i<size; ++i){
                int t = 0;
                for(int j=0; j<nums.size(); ++j){
                    if(i&(1<<j))t += nums[j];
                }
                if(t==len)res.push_back(i);
            }
            if(res.size()<4)return false;
            std::vector<ll> tmp;
            for(int i=0; i<res.size(); ++i){
                for(int j=i+1; j<res.size(); ++j){
                    if(!(res[i]&res[j]))tmp.push_back(res[i]|res[j]);
                }
            }
            if(tmp.size()<2)return false;
            for(int i=0; i<tmp.size(); ++i){
                for(int j=1; j<tmp.size(); ++j){
                    if(!(tmp[i]&tmp[j]))return true;
                }
            }
            return false;
    }
//116. 填充每个节点的下一个右侧节点指针
    Node* connect(Node* root) {
            if(!root)return {};
            std::queue<Node*> q;
            q.push(root);
            Node* pre = nullptr;
            Node* now = nullptr;
            while(q.size()){
                int size = q.size();
                pre = q.front();
                for(int i=0; i<size; ++i){
                    now = q.front();q.pop();
                    if(now->left)q.push(now->left);
                    if(now->right)q.push(now->right);
                    if(i)pre->next = now, pre = now;
                }
            }
            return root;
    }
//1376. 通知所有员工所需的时间
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
            std::vector<std::vector<int>> g(n);
            for(int i=0; i<n; ++i){
                int tmp = manager[i];
                if(tmp==-1)tmp = headID;
                if(tmp==i)continue;
                g[tmp].push_back(i);
            }
            std::function<int(int)> _dfs = [&](int i){
                int res = 0;
                for(auto &y : g[i]){
                    res = std::max(res, _dfs(y));
                }
                return informTime[i]+res;
            };
            return _dfs(headID);
    }
//98. 验证二叉搜索树
    bool isValidBST(TreeNode* root) {
            typedef long long ll;
            ll pre = LONG_MIN;
            std::function<bool(TreeNode*)> _dfs = [&](TreeNode *root){
                if(!root)return true;
                bool left  = _dfs(root->left);
                if(root->val <= pre || !left)return false;
                pre = root->val;
                return _dfs(root->right);
            };
            return _dfs(root);
    }
//1192. 查找集群内的「关键连接」
vector<vector<int>> criticalConnections(int n, vector<vector<int>> &connections) {
            std::vector<int> visit(n);
            std::vector<int> last_parent(n);
            std::vector<std::vector<int>> res;
            std::vector<std::vector<int>> g(n);
            for(auto &c : connections){
                g[c[1]].push_back(c[0]);
                g[c[0]].push_back(c[1]);
            }
            std::function<int(int, int, int&)> _dfs = [&](int pre, int cur, int& dep){
                visit[cur]       = 1;
                last_parent[cur] = dep;
                int cur_time     = dep;
                for(int c : g[cur]){
                    if(pre==c)continue;
                    if(!visit[c]){
                        int cp = _dfs(cur, c, ++dep);
                        last_parent[cur] = std::min(last_parent[cur], cp);
                        if(cp > cur_time)res.push_back({c, cur});
                    }else{
                        last_parent[cur] = std::min(last_parent[cur], last_parent[c]);
                    }
                }
                return last_parent[cur];
            };
            int dep = 0;
            _dfs(-1, 0, dep);
            return res;
    }
//753. 破解保险箱
    string crackSafe(int n, int k) {
            const int tn = pow(k, n);
            std::string res(n, '0');
            std::unordered_set<std::string> mp{res};
            std::function<bool()> _dfs = [&](){
                if(mp.size() == tn)return true;
                std::string next = res.substr(res.length()-n+1, n-1);
                for(char c='0'; c<'0'+k; ++c){
                    if(mp.count(next+c))continue;
                    mp.insert(next+c);
                    res += c;
                    if(_dfs())return true;
                    res.pop_back();
                    mp.erase(next+c);
                }
                return false;
            };
            return _dfs()?res:"";
    }
//690. 员工的重要性
    int getImportance(vector<Employee*> employees, int id) {
            int m   = employees.size();
            int res = 0;
            std::unordered_set<int> _v;
            std::unordered_map<int, Employee*> mp;
            for(auto &e : employees)mp[e->id] = e;
            std::function<void(int)> _dfs = [&](int id){
                Employee *deal = mp[id];
                if(deal==nullptr)return;
                res += deal->importance;
                _v.insert(id);
                for(auto &e : deal->subordinates){
                    if(!_v.count(e))_dfs(e);
                }
            };
            _dfs(id);
            return res;
    }
//1123. 最深叶节点的最近公共祖先
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
            int h = 0;
            std::function<TreeNode*(TreeNode*, int&)> _dfs = [&](TreeNode *root, int& t){
                if(!root){
                    t = -1;
                    return root;
                }
                int left  = t;
                int right = t;
                auto l    = _dfs(root->left,  left);
                auto r    = _dfs(root->right, right);
                t = std::max(left, right)+1;
                if(left==right)return root;
                if(left<right)return r;
                return l;
            };
            return _dfs(root, h);
    }
//934. 最短的桥
   int shortestBridge(vector<vector<int>>& A) {
            int m = A.size();
            int n = A[0].size();
            std::vector<std::pair<int, int>> b_1;
            std::vector<std::pair<int, int>> b_2;
            std::vector<std::vector<int>> _fun = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
            std::function<bool(int, int)> _can = [&](int i, int j){;
                return i>=0&&j>=0&&i<m&&j<n; };
            std::function<void(int, int, std::vector<std::pair<int, int>>&)> _dfs =
                [&](int i, int j, std::vector<std::pair<int, int>>& b){
                    bool flag = 1;
                    A[i][j]   = 2;
                    for(auto &f : _fun){
                        int i1 = i + f[0];
                        int j1 = j + f[1];
                        bool c = _can(i1, j1) && A[i1][j1]==1;
                        if(c)_dfs(i1, j1, b);
                        flag = c && flag;
                    }
                    if(!flag)b.push_back({i, j});
            };
            std::function<void(std::vector<std::pair<int, int>>&)> _get_b =
                [&](std::vector<std::pair<int, int>>& b){
                for(int i=0; i<m; ++i){
                    for(int j=0; j<n; ++j){
                        if(A[i][j]==1){
                            _dfs(i, j, b);
                            return;
                        }
                    }
                }
            };
            _get_b(b_1);
            _get_b(b_2);
            int res = INT_MAX>>1;
            for(auto &p1 : b_1){
                for(auto &p2 : b_2){
                    res = std::min(res, abs(p1.first-p2.first)+abs(p1.second-p2.second)-1);
                }
            }
            return res;
    }
//1443. 收集树上所有苹果的最少时间
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
            std::unordered_map<int, std::vector<int>> mp;
            for(auto &e : edges){
                mp[e[0]].push_back(e[1]);
                mp[e[1]].push_back(e[0]);
            }
            std::vector<int> _v(n);
            std::function<bool(int)> _dfs = [&](int i){
                _v[i] = 1;
                bool res = hasApple[i];
                for(auto &x : mp[i]){
                    res |= (!_v[x]&&_dfs(x));
                }
                if(!res)mp.erase(i);
                return res;
            };
            _dfs(0);
            return mp.size()?(mp.size()-1)*2:0;
    }
//二叉树展开为链表
    void flatten(TreeNode* root) {
            if(!root){
                return;
            }
            flatten(root->left);
            flatten(root->right);
            if(root->left){
                TreeNode* tmp = root->left;
                while(tmp->right){
                    tmp = tmp->right;
                }
                tmp->right  = root->right;
                root->right = root->left;
                root->left  = NULL;
            }
            return;
        }
//968. 监控二叉树
    int minCameraCover(TreeNode* root) {
            std::function<std::vector<int>(TreeNode *root)> _dfs = [&](TreeNode *root){
                if(!root)return std::vector<int>{0, 0, INT_MAX>>1};
                auto left  = _dfs(root->left);
                auto right = _dfs(root->right);
                int l12    = std::min(left[1], left[2]);
                int r12    = std::min(right[1], right[2]);
                int r0 = left[1] + right[1];
                int r1 = std::min(left[2]+r12, right[2]+l12);
                int r2 = 1 + std::min(left[0], l12) + std::min(right[0], r12);
                return std::vector<int>{r0, r1, r2};
            };
            auto res = _dfs(root);
            return std::min(res[1], res[2]);
    }
//1315. 祖父节点值为偶数的节点和
    int sumEvenGrandparent(TreeNode* root) {
            int res = 0;
            std::function<void(TreeNode*, bool, bool)> _dfs =
                [&](TreeNode *root, bool pre, bool ppre){
                    if(!root)return ;
                    if(ppre)res += root->val;
                    _dfs(root->left, !(root->val&1), pre);
                    _dfs(root->right, !(root->val&1), pre);
            };
            _dfs(root, 0, 0);
            return res;
    }
//841. 钥匙和房间
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
            int n = rooms.size();
            std::vector<int> _f(n);
            std::vector<int> _v(n);
            std::iota(_f.begin(), _f.end(), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i]==i?i:_f[i]=_find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                _f[_find(a)] = _f[_find(b)]; };
            std::function<int(void)> _check = [&](){
                int res = 0;
                for(int i=0; i<n; ++i)res += _find(i)==i;
                return res; };
            std::function<void(int)> _dfs = [&](int i){
                _v[i] = 1;
                for(auto &k : rooms[i]){
                    if(_v[k])continue;
                    _union(i, k);
                    _dfs(k);
                }
            };
            _dfs(0);
            return _check()<=1;
    }
//514. 自由之路
        int findRotateSteps(string ring, string key) {
            std::vector<std::vector<int>> dp(ring.length(), std::vector<int>(key.length(), -1));
            return dfs(dp, ring,key, 0, 0) + key.length();
        }
        int dfs(std::vector<std::vector<int>>& dp, std::string& ring, std::string& key, int r, int k){
            if(k>=key.length())return 0;
            if(dp[r][k] !=-1)return dp[r][k];

            int r1 = r;
            int r2 = r;
            int n1 = 0;
            int n2 = 0;

            while(ring[r1]!=key[k] && ++n1)r1 = (r1+1)%ring.length();
            while(ring[r2]!=key[k] && ++n2)r2 = (r2-1+ring.length())%ring.length();

            int a  = dfs(dp, ring, key, r1, k+1) + n1;
            int b  = dfs(dp, ring, key, r2, k+1) + n2;

            return dp[r][k] = std::min(a,b);
        }
//679. 24 点游戏
    private:
        const double esp = 1e-5;
    public:
        bool judgePoint24(std::vector<int>& nums){
            std::deque<double> q;
            q.push_back(nums[0]);
            q.push_back(nums[1]);
            q.push_back(nums[2]);
            q.push_back(nums[3]);
            return get_res(q);
        }
        bool get_res(std::deque<double>& q){
            int size = q.size();
            if(size==1)return abs(q.front() - 24) < esp;
            for(int i=0; i<size; ++i){
                double a = q.front();
                q.pop_front();
                for(int j=1; j<size; ++j){
                    double b = q.front();
                    q.pop_front();

                    q.push_back(a+b);
                    if(get_res(q))return true;
                    q.pop_back();

                    q.push_back(a-b);
                    if(get_res(q))return true;
                    q.pop_back();

                    q.push_back(a*b);
                    if(get_res(q))return true;
                    q.pop_back();

                    q.push_back(a/b);
                    if(b && get_res(q))return true;
                    q.pop_back();

                    q.push_back(b);
                }
                q.push_back(a);
            }
            return false;
        }
//1110. 删点成林
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
            std::vector<TreeNode*> res;
            std::unordered_set<int> mp(to_delete.begin(), to_delete.end());
            std::function<void(TreeNode *, bool)> _dfs = [&](TreeNode *root, bool is_d){
                if(!root)return;
                TreeNode *left  = root->left;
                TreeNode *right = root->right;
                if(left  && mp.count(left->val))root->left   = nullptr;
                if(right && mp.count(right->val))root->right = nullptr;

                if(is_d && !mp.count(root->val)){
                    res.push_back(root);
                }
                is_d = mp.count(root->val);
                _dfs(left,  is_d);
                _dfs(right, is_d);
            };
            _dfs(root, 1);
            return res;
    }
//130. 被围绕的区域
    void solve(vector<vector<char>>& board) {
            if(!board.size())return;
            int m = board.size();
            int n = board[0].size();
            std::vector<std::vector<int>> _fun = {{1, 0},{0, 1},{-1, 0},{0, -1}};
            std::function<bool(int, int)> _can = [&](int i,int j){
                return i>=0 && j>=0 && i<m && j<n; };
            std::function<void(int, int)> _dfs = [&](int i, int j){
                board[i][j] = '1';
                for(auto &f : _fun){
                    int i1 = i + f[0];
                    int j1 = j + f[1];
                    if(!_can(i1, j1) || board[i1][j1]!='O')continue;
                    _dfs(i1, j1);
                }
            };

            for(int i=0; i<m; ++i)if(board[i][0]=='O')_dfs(i, 0);
            for(int i=0; i<n; ++i)if(board[0][i]=='O')_dfs(0, i);
            for(int i=0; i<m; ++i)if(board[i][n-1]=='O')_dfs(i, n-1);
            for(int i=0; i<n; ++i)if(board[m-1][i]=='O')_dfs(m-1, i);

            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    if(board[i][j]=='O')board[i][j] = 'X';
                    if(board[i][j]=='1')board[i][j] = 'O';
                }
            }
    }
//928. 尽量减少恶意软件的传播 II
   int minMalwareSpreadII(vector<vector<int>>& graph, vector<int>& initial) {
            int n = graph.size();
            std::vector<int> _f(n);
            std::vector<int> _s(n, 1);
            std::iota(_f.begin(), _f.end(),0);
            std::function<int(int)> _find = [&](int i){
                return _f[i]==i?i:_f[i]=_find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                int pa = _find(a);
                int pb = _find(b);
                if(pa != pb){
                    if(_s[pa] < _s[pb]){
                        _f[pa] = pb;
                        _s[pb] += _s[pa];
                    }else{
                        _f[pb] = pa;
                        _s[pa] += _s[pb];
                    }
                }
            };
            std::function<int(int)> _size = [&](int i){
                return _s[i];
            };
            std::set<int> bad(initial.begin(), initial.end());
            std::unordered_map<int, std::unordered_set<int>> mp;
            for(int i=0; i<n; ++i){
                for(int j=0; j<n; ++j){
                    if(!graph[i][j] || bad.count(i) || bad.count(j))continue;
                    _union(i, j);
                }
            }
            for(auto &b : bad){
                for(int i=0; i<n; ++i){
                    if(!graph[b][i] || i==b || bad.count(i))continue;
                    mp[ _find(i)].insert(b);
                }
            }
            std::vector<int> bad_res(n);
            for(auto&& [k, v] : mp){
                if(v.size()==1)bad_res[*v.begin()] += _size(k);
            }
            int res  = 0;
            int max_ = -1;
            for(auto&i : bad){
                cout<<bad_res[i]<<"--"<<i<<endl;
                if(bad_res[i] > max_){
                    max_ = bad_res[i];
                    res = i;
                }
            }
            return res;
    }
//924. 尽量减少恶意软件的传播
    int minMalwareSpreadI(vector<vector<int>>& graph, vector<int>& initial) {
            int n = graph.size();
            std::vector<int> _f(n);
            std::iota(_f.begin(), _f.end(),0);
            std::function<int(int)> _find = [&](int i){
                return _f[i]==i?i:_f[i]=_find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                _f[_find(a)] = _f[_find(b)]; };
            std::function<int(int)> _size = [&](int i){
                int res = 0;
                for(int i=0; i<n; ++i)res += i==_f[i];
                return res; };
            std::unordered_set<int> bad(initial.begin(), initial.end());
            std::unordered_map<int, std::unordered_set<int>> mp;
            for(int i=0; i<n; ++i){
                for(int j=0; j<n; ++j){
                    if(!graph[i][j] || bad.count(i) || bad.count(j))continue;
                    _union(i, j);
                }
            }
            for(auto &b : bad){
                for(int i=0; i<n; ++i){
                    if(!graph[b][i] || i==b || bad.count(i))continue;
                    mp[ _find(i)].insert(b);
                }
            }
            std::vector<int> bad_res(n);
            for(auto&& [k, v] : mp){
                if(v.size()==1)bad_res[*v.begin()] += _size(k);
            }
            int res  = 0;
            int max_ = -1;
            for(auto&i : bad)
                if(bad_res[i] > max_){
                    max_ = bad_res[i];
                    res = i;
                }
            return res;
    }
//1319. 连通网络的操作次数
    int makeConnected(int n, vector<vector<int>>& connections) {
            std::vector<int> _f(n);
            std::iota(_f.begin(), _f.end(), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i]==i?i:_f[i]=_find(_f[i]); };
            std::function<int(int, int)> _union = [&](int a, int b){
                int pa = _find(a);
                int pb = _find(b);
                if(pa==pb)return 1;
                _f[_find(a)] = _f[_find(b)];
                return 0;
            };
            int line = 0;
            for(auto &c : connections){
                line += _union(c[0], c[1]); }
            int need = 0;
            for(int i=0; i<n; ++i)need += i==_find(i);
            return line>=--need?need:-1;
    }
//112. 路径总和
    bool hasPathSum(TreeNode* root, int sum) {
            if(!root)return false;
            if(!root->left && !root->right){
                return root->val==sum; 
            }
            return hasPathSum(root->left, sum-root->val) || hasPathSum(root->right, sum-root->val);
    }
//695. 岛屿的最大面积
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int __res  = 0;
        int __size = grid.size();
        for(int i=0; i<__size; ++i){
            for(int j=0; j<grid[0].size(); ++j){
                if(grid[i][j] == 1){
                    int num = 0;
                    dfs(grid,i,j,num);
                    if(num > __res){
                        __res = num;
                    }
                }
            }
        }
        return __res;
    }
    void dfs(vector<vector<int>>& grid, int x, int y, int &num){
        if(x < 0 || y < 0 || x>=grid.size() || y>=grid[0].size() || grid[x][y] != 1){
            return;
        }
        ++num;
        grid[x][y] = 0;
        dfs(grid,x+1,y,num);
        dfs(grid,x-1,y,num);
        dfs(grid,x,y+1,num);
        dfs(grid,x,y-1,num);
    }
//576. 出界的路径数
        int findPaths(int m, int n, int N, int I, int J) {
            int MOD = 1e9 + 7;
            std::vector<std::vector<long long>> dp_0(m+2, std::vector<long long>(n+2, 1));
            std::vector<std::vector<long long>> dp_1(m+2, std::vector<long long>(n+2, 1));
            for(int i=1; i<=m; ++i)fill(dp_0[i].begin()+1, dp_0[i].end()-1, 0);
            for(int k=0; k<N; ++k){
                for(int i=1; i<=m; ++i){
                    for(int j=1; j<=n; ++j){
                        dp_1[i][j] = (dp_0[i+1][j] + dp_0[i-1][j]+
                                      dp_0[i][j+1] + dp_0[i][j-1]) % MOD;
                    }
                }
                dp_0 = dp_1;
            }
            return !N ? 0 : dp_0[++I][++J];
        }
//749. 隔离病毒
    int containVirus(vector<vector<int>>& grid) {
            typedef std::vector<std::pair<int, int>> vp;
            typedef std::vector<vp> vvp;
            int m = grid.size();
            int n = grid[0].size();
            std::vector<std::vector<int>> vi(m, std::vector<int>(n));
            std::vector<std::vector<int>> _fun = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
            std::function<void(void)> _zero = [&](){
                for(auto &v : vi)v.assign(n, 0); };
            std::function<bool(int, int)> _can = [&](int i,int j){
                return i>=0 && j>=0 && i<m && j<n; };
            std::function<void(int i, int j, vp&)> _dfs = [&](int i, int j, vp& mp){
                for(auto &f : _fun){
                    int i1 = i + f[0];
                    int j1 = j + f[1];
                    if(!_can(i1, j1) || grid[i1][j1]!=1 || vi[i1][j1])continue;
                    vi[i1][j1] = 1;
                    mp.push_back({i1, j1});
                    _dfs(i1, j1, mp);
                }
            };
            std::function<int(vp&)> _calc = [&](vp& v){
                int res = 0;
                for(auto &p : v){
                    for(auto &f : _fun){
                        int i1 = p.first  + f[0];
                        int j1 = p.second + f[1];
                        if(_can(i1, j1) && grid[i1][j1]==0 &&!vi[i1][j1])++res, vi[i1][j1]=1;
                    }
                }
                return res;
            };
            std::function<int(vp&)> _deal = [&](vp& v){
                int res = 0;
                for(auto &p : v){
                    int i = p.first;
                    int j = p.second;
                    grid[i][j] = 2;
                    for(auto &f : _fun){
                        int i1 = p.first  + f[0];
                        int j1 = p.second + f[1];
                        if(_can(i1, j1) && grid[i1][j1]==0)++res;
                    }
                }
                return res;
            };
            std::function<void(vvp&)> _infect = [&](vvp& tmp){
                for(auto &vp : tmp){
                    if(grid[vp[0].first][vp[0].second]==2)continue;
                    for(auto &p : vp){
                        int i = p.first;
                        int j = p.second;
                        if(grid[i][j]==1){
                            for(auto &f : _fun){
                                int i1 = i + f[0];
                                int j1 = j + f[1];
                                if(!_can(i1, j1) || grid[i1][j1])continue;
                                grid[i1][j1] = 1;
                            }
                        }
                    }
                }
            };
            int res = 0;
            while(true){
                vvp tmp;
                _zero();
                for(int i=0; i<m; ++i){
                    for(int j=0; j<n; ++j){
                        if(grid[i][j]==1 && !vi[i][j]){
                            vi[i][j] = 1;
                            vp mp;
                            mp.push_back({i, j});
                            _dfs(i, j, mp);
                            tmp.push_back(mp);
                        }
                    }
                }
                if(!tmp.size())break;
                int max_ = -1;
                vp d;
                for(int i=0; i<tmp.size(); ++i){
                    _zero();
                    int x = _calc(tmp[i]);
                    if(x>max_)max_=x, d=tmp[i];
                }
                res += _deal(d);
                _infect(tmp);
            }
            return res;
    }
//329. 矩阵中的最长递增路径
    int longestIncreasingPath(vector<vector<int>>& matrix) {
            if(!matrix.size())return 0;
            int m   = matrix.size();
            int n   = matrix[0].size();
            int res = 1;
            std::vector<std::vector<int>> dp(m, std::vector<int>(n));
            std::vector<std::vector<int>> _fun = {{0, 1},{1, 0},{0, -1},{-1, 0}};
            std::function<bool(int, int)> _valid = [&](int a, int b){
                return a>=0 && b>=0 && a<m && b<n; };
            std::function<int(int, int)> _dfs = [&](int x, int y){
                if(dp[x][y])return dp[x][y];
                ++dp[x][y];
                for(auto &f : _fun){
                    int x1 = x + f[0];
                    int y1 = y + f[1];
                    bool t = _valid(x1, y1);
                    if(t && matrix[x1][y1]>matrix[x][y]){
                        dp[x][y] = std::max(_dfs(x1, y1)+1, dp[x][y]);
                    }
                }
                return dp[x][y];
            };
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    res = std::max(res, _dfs(i, j));
                }
            }
            return res;
    }
//1034. 边框着色
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int r0, int c0, int color) {
            int m = grid.size();
            int n = grid[0].size();
            std::vector<std::vector<int>> res(grid);
            std::vector<std::vector<int>> _fun = {{0, 1},{1, 0},{0, -1},{-1, 0}};
            std::function<bool(int, int)> _valid = [&](int a, int b){
                return a>=0 && b>=0 && a<m && b<n; };
            std::function<void(int, int)> _dfs = [&](int x, int y){
                res[x][y] *= -1;
                bool c = 0;
                for(auto &f : _fun){
                    int x1 = x + f[0];
                    int y1 = y + f[1];
                    bool t = _valid(x1, y1);
                    if(!t || grid[x1][y1] != grid[r0][c0])c = 1;
                    if(t && res[x1][y1]==grid[r0][c0])_dfs(x1, y1);
                }
                res[x][y] *= -1;
                if(c)res[x][y] = color;
            };
            _dfs(r0, c0);
            return res;
    }
//494. 目标和
    int findTargetSumWays(vector<int>& nums, int S) {
            int size = nums.size();
            std::vector<int> dp_0(2000+5, 0);
            std::vector<int> dp_1(2000+5, 0);
            dp_0[ nums[0]+1000]  = 1;
            dp_0[-nums[0]+1000] += 1;
            for(int i=1; i<size; ++i){
                for(int j=-1000; j<=1000; ++j){
                    if(dp_0[j+1000]>0){
                        dp_1[j+1000-nums[i]] += dp_0[j+1000];
                        dp_1[j+1000+nums[i]] += dp_0[j+1000];
                    }
                }
                dp_0 = dp_1;
                fill(dp_1.begin(), dp_1.end(), 0);
            }
            return S>1000?0:dp_0[S+1000];
    }
//1457. 二叉树中的伪回文路径
    int pseudoPalindromicPaths (TreeNode* root) {
            std::function<int(TreeNode*, std::vector<int>)> _dfs = [&](TreeNode* root, std::vector<int> mp){
                if(!root)return 0;
                ++mp[root->val];
                if(!root->left && !root->right){
                    int t = 0;
                    for(int i=1; i<=9; ++i)t += mp[i]&1;
                    return t<2?1:0;
                }
                return _dfs(root->left, mp) + _dfs(root->right, mp);
            };
            std::vector<int> mp(10);
            return _dfs(root, mp);
    }
//980. 不同路径 III
    int uniquePathsIII(vector<vector<int>>& grid) {
            int m   = grid.size();
            int n   = grid[0].size();
            int res = 0;
            int ok  = 0;
            int bi,bj;
            std::vector<std::vector<int>> _fun = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
            std::vector<std::vector<int>> vi(m, std::vector<int>(n));
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    int t = grid[i][j];
                    if(t ==-1)vi[i][j]=1;
                    if(t == 0)++ok;
                    if(t == 1)vi[i][j]=1,bi=i,bj=j;
                }
            }
            std::function<bool(int, int)> _can = [&](int i,int j){
                return i>=0 && j>=0 && i<m && j<n; };
            std::function<void(int, int, int)> _dfs = [&](int i, int j, int ok){
                if(grid[i][j]==2){
                    res += ok==-1;
                    return ;
                }
                for(auto &f : _fun){
                    int i1 = i + f[0];
                    int j1 = j + f[1];
                    if(!_can(i1, j1) || vi[i1][j1])continue;
                    vi[i1][j1] = 1;
                    _dfs(i1, j1, ok-1);
                    vi[i1][j1] = 0;
                }
            };
            _dfs(bi, bj, ok);
            return res;
    }
//430. 扁平化多级双向链表
    Node1* flatten(Node1* head) {
        if(!head)return head;
            Node1 *H = new Node1;
            H->next = head;
            Node1 *cur=H, *pre=H;
            std::stack<Node1*> st;
            st.push(head);
            while(st.size()){
                cur = st.top();st.pop();
                pre->next = cur;
                cur->prev = pre;
                if(cur->next)st.push(cur->next);
                if(cur->child)st.push(cur->child),cur->child = nullptr;
                pre = cur;
            }
            head = H->next;
            head->prev = nullptr;
            delete H;
            return head;
    }
//1145. 二叉树着色游戏
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
            bool res = false;
            int  xl  = 0;
            int  xr  = 0;
            int  xp  = 0;
            std::function<int(TreeNode*)> _dfs = [&](TreeNode* root){
                if(!root)return 0;
                int l = _dfs(root->left);
                int r = _dfs(root->right);
                if(root->val==x){
                    xl = l;
                    xr = r;
                    return 0;
                }
                return 1 + l + r;
            };
            _dfs(root);
            xp = n - xl - xr - 1;
            return xl>(xr+xp+1) || xr>(xl+xp+1) || xp>(xr+xl+1);
    }
//756. 金字塔转换矩阵
    bool pyramidTransition(string bottom, vector<string>& allowed) {
            int size = allowed.size();
            std::unordered_map<std::string, std::vector<char>> mp;
            for(auto &s : allowed)mp[s.substr(0,2)].push_back(s[2]);
            std::function<bool(std::string, std::string, int)> _dfs = [&](std::string pre, std::string now, int i){
                int size = pre.size();
                if(size==1)return true;
                if(now.size()==size-1)return _dfs(now, "", 0);
                std::string ah = {pre[i], pre[i+1]};
                if(!mp.count(ah))return false;
                for(auto &c : mp[ah])if(_dfs(pre, now+c, i+1))return true;
                return false;
            };
            return _dfs(bottom,"",0);
    }
//638. 大礼包
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
            int res = INT_MAX;
            int n   = special.size();
            int ds  = needs.size();
            std::function<void(std::vector<int>, int sum)> _dfs = [&](std::vector<int> ns, int sum){
                if(!*max_element(ns.begin(), ns.end())){
                    res = std::min(res, sum);
                    return ;
                }
                for(int i=0; i<n; ++i){
                    auto tmp = ns;
                    int j    = 0;
                    for(; j<ds; ++j){
                        if((tmp[j]-=special[i][j])<0)break;
                    }
                    if(j!=ds)continue;
                    _dfs(tmp, sum+special[i].back());
                }
               for(int i=0; i<ds; ++i){
                   sum += ns[i]*price[i];
               }
               res = std::min(res, sum);
            };
            _dfs(needs, 0);
            return res;
    }
//1080. 根到叶路径上的不足节点
    TreeNode* sufficientSubset(TreeNode* root, int limit) {
            std::function<bool (TreeNode* root, int sum)> _dfs = [&](TreeNode* root, int sum){
                if(!root)return true;
                if(!root->left && !root->right)return root->val+sum < limit;
                bool r1 = _dfs(root->left,  root->val+sum);
                bool r2 = _dfs(root->right, root->val+sum);
                if(r1)root->left  = nullptr;
                if(r2)root->right = nullptr;
                return r1 && r2;
            };
            if(_dfs(root, 0))return nullptr;
            return root;
    }
//199. 二叉树的右视图
    vector<int> rightSideView(TreeNode* root) {
            if(!root)return {};
            std::vector<int> res;
            std::queue<TreeNode*> q;
            q.push(root);
            while(q.size()){
                int size = q.size();
                res.push_back(q.front()->val);
                for(int i=0; i<size; ++i){
                    TreeNode* now = q.front();q.pop();
                    if(now->right)q.push(now->right);
                    if(now->left)q.push(now->left);
                }
            }
            return res;
    }
//1028. 从先序遍历还原二叉树
    TreeNode* recoverFromPreorder(string s) {
            std::function<int(int&)> _get_dig = [&](int& b){
                int res = 0;
                for(; b<s.length() && isdigit(s[b]); ++b){
                    res = res*10 + s[b]-'0';
                }
                return res;
            };
            int len = s.length();
            int pos   = 0;
            std::stack<TreeNode*> st;
            while(pos < len){
                int level = 0;
                while(pos < len && s[pos]=='-')++level,++pos;
                int val = _get_dig(pos);
                TreeNode* node = new TreeNode(val);
                if(level==st.size()){
                    if(level)st.top()->left = node;
                }else{
                    while(level != st.size())st.pop();
                    st.top()->right = node;
                }
                st.push(node);
            }
            while(st.size()>1)st.pop();
            return st.top();
    }
//. 填充每个节点的下一个右侧节点指针 II
     Node* connectII(Node* root) {
            if(!root)return {};
            std::queue<Node*> q;
            q.push(root);
            Node* pre = nullptr;
            while(q.size()){
                int size = q.size();
                pre = q.front();
                for(int i=0; i<size; ++i){
                    Node* now = q.front();q.pop();
                    if(now->left)q.push(now->left);
                    if(now->right)q.push(now->right);
                    if(i)pre->next = now, pre = now;
                }
            }
            return root;
    }
//1377. T 秒后青蛙的位置
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
            double res = 0;
            std::vector<std::vector<int>> ed(n+1, std::vector<int>(n+1));
            std::vector<int> vi(n+1);
            for(auto &e : edges){
                ed[e[0]][e[1]] = 1;
                ed[e[1]][e[0]] = 1;
            }
            std::function<void(double, int, int)> _dfs = [&](double r, int t, int tar){
                if(!t && tar!=target)return;
                if(!t && tar==target){
                    res = r;
                    return;
                }
                int cnt = 0;
                for(int i=1; i<=n; ++i){
                    if(ed[tar][i] && !vi[i])++cnt;
                }
                if(cnt==0 && tar==target){
                    res = r;
                    return;
                }
                vi[tar] = 1;
                for(int i=1; i<=n; ++i){
                    if(ed[tar][i] && !vi[i]){
                        _dfs(r*(1.0/cnt), t-1, i);
                        if(res)return;
                    }
                }
            };
            _dfs(1.0, t, 1);
            return res;
    }
//1577. 数的平方等于两数乘积的方法数
    int numTriplets(vector<int>& nums1, vector<int>& nums2) {
            int m = nums1.size();
            int n = nums2.size();
            std::unordered_map<long long, int> mp;
            for(int i=0; i<m; ++i){
                for(int j=i+1; j<m; ++j){
                    ++mp[(static_cast<long long>(nums1[i])*static_cast<long long>(nums1[j]))];
                }
            }
            int res = 0;
            for(int i=0; i<n; ++i)res += mp[(static_cast<long long>(nums2[i])*static_cast<long long>(nums2[i]))];
            mp.clear();
            for(int i=0; i<n; ++i){
                for(int j=i+1; j<n; ++j){
                    ++mp[(static_cast<long long>(nums2[i])*static_cast<long long>(nums2[j]))];
                }
            }
            for(int i=0; i<m; ++i)res += mp[(static_cast<long long>(nums1[i])*static_cast<long long>(nums1[i]))];
            return res;
    }
//1576. 替换所有的问号
    std::string modifyString(std::string s) {
            int len = s.length();
            if(s[0]=='?' && len==1)return "a";
            if(len==1)return s;
            if(s[0]=='?')s[0]=s[1]=='?'?'a':(s[1]=='a'?s[1]+1:s[1]-1);
            for(int i=1; i<len-1; ++i){
                if(s[i] != '?')continue;
                s[i] =
                    (s[i+1]=='?')
                            ?
                    (s[i-1]=='a'?s[i-1]+1:s[i-1]-1)
                            :
                    (({char x='a';for(; x<='z'&&(x==s[i-1]||x==s[i+1]); ++x); x;}));

            }
            if(s[len-1]=='?')s[len-1] = s[len-2]=='a'?'b':s[len-2]-1;
            return s;
    }
//17. 电话号码的字母组合
        std::vector<std::string> letterCombination(std::string digits){
            if(!digits.size())return {};
            int len = digits.length();
            std::vector<std::string> lp = {
                "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz",};
            std::vector<std::string> res;
            std::function<void(int, std::string)> _dfs = [&](int i, std::string r){
                if(i==len){
                    res.push_back(r);
                    return;
                }
                for(auto &c : lp[digits[i]-'0'])_dfs(i+1, r+c);
            };
            _dfs({},{});
            return res;
        }
//959. 由斜杠划分区域
        int regionsBySlashes(std::vector<std::string>& grid){
            int n = grid.size();
            std::vector<int> _f(n*n*4);
            std::iota(_f.begin(), _f.end(), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i]==i?i:_f[i]=_find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                _f[_find(a)] = _find(b); };
            for(int i=0; i<n; ++i){
                for(int j=0; j<n; ++j){
                    int b = 4*(i*n+j);
                    if(grid[i][j]== ' '){
                        _union(b, b+1);
                        _union(b, b+2);
                        _union(b+1, b+3);
                        _union(b+2, b+3);
                    }else if(grid[i][j]=='/'){
                        _union(b,   b+1);
                        _union(b+2, b+3);
                    }else{
                        _union(b,  b+2);
                        _union(b+1,b+3);
                    }
                    if(i<n-1) _union(b+3, b+4*n);
                    if(j<n-1) _union(b+2, b+5);
                }
            }
            int res = 0;
            for(int i=0; i<4*n*n; ++i)res += _find(i)==i;
            return res;
        }

//面试题 17.22. 单词转换
        std::vector<std::string> findLadders(std::string bw, std::string ew, std::vector<std::string> wl){
            int len = bw.length();
            int n   = wl.size();
            std::unordered_map<std::string, int> vi;
            std::vector<std::string> res = {bw,};
            ++vi[bw];
            std::function<bool(std::string&, std::string&)> _similar = [&](std::string& a, std::string&b){
                if(len != b.length())return false;
                int c = 0;
                for(int i=0; i<len ; ++i)c += a[i]!=b[i];
                return c < 2;
            };
            std::function<bool(std::string&)> _dfs = [&](std::string& to){
                if(to==ew)return true;
                for(int i=0; i<n; ++i){
                    if(vi[wl[i]] || !_similar(to, wl[i]))continue;
                    ++vi[wl[i]];
                    res.push_back(wl[i]);
                    if(_dfs(wl[i]))return true;
                    res.pop_back();
                }
                return false;
            };
            if(_dfs(bw))return res;
            return {};
        }
//124. 二叉树中的最大路径和
        int amxSumPath(TreeNode* root){
            int res = INT_MIN;
            std::function<int(TreeNode*)> dfs = [&](TreeNode* root){
                if(!root)return 0;
                int left  = std::max(dfs(root->left), 0);
                int right = std::max(dfs(root->right), 0);
                res       = std::max(res, root->val+left+right);
                return root->val + std::max(left, right);
            };
            dfs(root);
            return res;
        }

//542. 01 矩阵
        std::vector<std::vector<int>> updateMatrix(std::vector<std::vector<int>>& matrix){
            int m = matrix.size();
            int n = matrix[0].size();
            std::vector<std::vector<int>> res(m, std::vector<int>(n, INT_MAX));
            std::vector<std::vector<int>> fun = {{1, 0},{0, 1},{-1, 0},{0, -1}};
            std::queue<std::pair<int, int>> q;
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    if(!matrix[i][j]){
                        q.push({i, j});
                        res[i][j] = 0;
                    }
                }
            }
            while(q.size()){
                auto [i, j] = q.front();q.pop();
                for(auto &f : fun){
                    int i1 = i + f[0];
                    int j1 = j + f[1];
                    if(i1<0 || j1<0 || i1>=m || j1>=n)continue;
                    if(res[i1][j1] > res[i][j]+1){
                        res[i1][j1] = res[i][j] + 1;
                        q.push({i1, j1});
                    }
                }
            }
            return res;
        }
//515. 在每个树行中找最大值
        std::vector<int> largestValues(TreeNode* root){
            if(!root)return {};
            std::vector<int> res;
            std::queue<TreeNode*> q;
            q.push(root);
            while(q.size()){
                int size = q.size();
                int _r   = INT_MIN;
                for(int i=0; i<size; ++i){
                    auto tmp = q.front();q.pop();
                    if(tmp->left)q.push(tmp->left);
                    if(tmp->right)q.push(tmp->right);
                    _r = std::max(_r, tmp->val);
                }
                res.push_back(_r);
            }
            return res;
        }

//332. 重新安排行程
        std::vector<std::string> findItnerary(std::vector<std::vector<std::string>>& tickets){
            int size = tickets.size();
            std::unordered_map<std::string, std::map<std::string, int>> mp;
            std::vector<std::string> res;
            res.push_back("JFK");
            for(int i=0; i<size; ++i)mp[tickets[i][0]][tickets[i][1]]++;
            std::function<bool(void)> dfs = [&](){
                if(res.size()==size+1)return true;
                for(auto &[to, n] : mp[res.back()]){
                    if(n){
                        --n;
                        res.push_back(to);
                        if(dfs())return true;
                        ++n;
                        res.pop_back();
                    }
                }
                return false;
            };
            dfs();
            return res;
        }
//897. 递增顺序查找树
        TreeNode* increaseingBST(TreeNode* root){
            if(!root)return nullptr;
            TreeNode* res = new TreeNode(0);
            TreeNode* pre = res;
            std::stack<TreeNode*> st;
            TreeNode* tmp = root;
            while(tmp || st.size()){
                if(tmp){
                    st.push(tmp);
                    tmp = tmp->left;
                }else{
                    tmp        = st.top();st.pop();
                    pre->right = new TreeNode(tmp->val);
                    pre        = pre->right;
                    tmp        = tmp->right;
                }
            }
            return res->right;
        }

//839. 相似字符串组
        int numSimilarGrouss(std::vector<std::string>& A){
            int size = A.size();
            int len  = A[0].length();
            std::unordered_map<std::string, std::string> _f;
            for(int i=0; i<size; ++i)_f[A[i]] = A[i];
            std::function<std::string(std::string&)> _find = [&](std::string& a){
                return _f[a]==a?a:_f[a]=_find(_f[a]); };
            std::function<void(std::string&, std::string&)> _union = [&](std::string& a, std::string& b){
                _f[_find(a)] = _find(b); };
            std::function<bool(std::string&, std::string&)> _similar = [&](std::string& s1, std::string& s2){
                int dif = 0;
                for(int i=0; i<len; ++i)dif += s1[i]!=s2[i];
                return dif<=2;
            };
            for(int i=0; i<size; ++i){
                for(int j=i+1; j<size; ++j){
                    if(_similar(A[i], A[j]))_union(A[i], A[j]);
                }
            }
            int res = 0;
            for(auto &s : _f)res += _f[s.first]==s.first;
            return res;
        }
//1391. 检查网格中是否存在有效路径
        bool hasValidPath(std::vector<std::vector<int>>& grid){
            int N = grid.size();
            int M = grid[0].size();
            std::vector<std::vector<int>> pipe = {      // [n][from] = to;
                                            {-1,-1,-1,-1},
                                            {-1,1,-1,3},
                                            {0,-1,2,-1},
                                            {-1,0,3,-1},
                                            {-1,-1,1,0},
                                            {3,2,-1,-1},
                                            {1,-1,-1,2}};
            std::vector<std::vector<int>> fun = {{1,0},{0,1},{-1,0},{0,-1}};
            std::vector<std::vector<int>> vi(N, std::vector<int>(M));
            std::function<bool(int, int, int)> dfs = [&](int i, int j, int d){
                if(i==N-1&&j==M-1)return true;
                vi[i][j] = 1;
                int i1 = i + fun[d][0];
                int j1 = j + fun[d][1];
                if(i1<0 || j1<0 || i1>=N || j1>=M || vi[i1][j1])return false;
                int next = grid[i1][j1];
                if(pipe[next][d]==-1)return false;
                return dfs(i1, j1, pipe[next][d]);
            };
            int b = grid[0][0];
            for(int i=0; i<4; ++i){
                if(pipe[b][i]!=-1 && dfs(0, 0, pipe[b][i]))return true;
            }
            return false;
        }
//面试题 04.06. 后继者
        TreeNode* inorderedSuccessor(TreeNode* root, TreeNode* p){
            if(!p)return nullptr;
            TreeNode* tmp = root;
            TreeNode* res = nullptr;
            int val = p->val;
            while(tmp){
                if(tmp->val > val){
                    res = tmp;
                    tmp = tmp->left;
                }else{
                    tmp = tmp->right;
                }
            }
            return res;
        }
//113. 路径总和 II
        std::vector<std::vector<int>> pathSum(TreeNode* root, int sum){
            std::vector<std::vector<int>> res;
            std::function<void(TreeNode*, std::vector<int>, int)> dfs = [&](TreeNode* root, std::vector<int>r, int sum){
                if(!root)return;
                r.push_back(root->val);
                sum -= root->val;
                if(!root->left && !root->right && !sum){
                    res.push_back(r);
                    return;
                }
                dfs(root->left, r, sum);
                dfs(root->right, r, sum);
            };
            std::vector<int> r;
            dfs(root, r, sum);
            return res;
        }
//513. 找树左下角的值
    int findBottomLeftValue(TreeNode* root) {
        std::queue<TreeNode*> q;
        if(!root)return -1;
        int res = -1;
        q.push(root);
        while(q.size()){
            int s = q.size();
            int f = 0;
            for(int i=0; i<s; ++i){
                TreeNode* r = q.front();q.pop();
                if(r->left)q.push(r->left);
                if(r->right)q.push(r->right);
                if(!i)res = r->val;
            }
        }
        return res;
    }

//394. 字符串解码
        std::string decodeString(std::string s){
            int l = s.length();
            std::function<int(int&)> _get_dig = [&](int& i){
                int res = 0;
                while(i<l && std::isdigit(s[i])){
                    res = res * 10 + s[i++]-'0';
                }
                return res;
            };
            std::function<std::string(int&)> dfs = [&](int& b){
                if(b>=l || s[b]==']')return std::string{};
                std::string r;
                if(std::isdigit(s[b])){
                    int t = _get_dig(b);
                    std::string ts = dfs(++b);
                    ++b;
                    while(t--)r += ts;
                }else if(std::isalpha(s[b])){
                    r = s[b++];
                }
                return r + dfs(b);
            };
            int i = 0;
            return dfs(i);
        }

        std::vector<std::string> binaryTreePaths(TreeNode* root) {
            std::vector<std::string> res;
            std::function<void(TreeNode* root, std::string)> dfs = [&](TreeNode* root, std::string s){
                if(!root)return;
                s += (s.size()?"->":"") + std::to_string(root->val);
                if(!root->left && !root->right){
                    res.push_back(s);
                    return;
                }
                dfs(root->left, s);
                dfs(root->right, s);
            };
            std::string s = "";
            dfs(root, s);
            return res;
        }
//886. 可能的二分法
        bool possibleBipartition_better(int N, std::vector<std::vector<int>>& dislikes){
            std::vector<int> _f(N*2+1);
            std::iota(_f.begin(), _f.end(), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i]==i?i:_f[i]=_find(_f[i]);
            };
            std::function<void(int, int)> _union = [&](int a, int b){
                int _a = _find(a);
                int _b = _find(b);
                if(_a != _b)_f[_a] = _b;
            };
            for(auto &d : dislikes){
                int a = d[0];
                int b = d[1];
                if(_find(a) == _find(b))return false;
                _union(a, b+N);
                _union(b, a+N);
            }
            return true;
        }
        bool possibleBipartition(int N, std::vector<std::vector<int>>& dislikes){
            std::vector<int> color(N+1, -1);
            std::unordered_map<int, std::unordered_set<int>> M;
            for(int i=0; i<dislikes.size(); ++i){
                M[dislikes[i][0]].insert(dislikes[i][1]);
                M[dislikes[i][1]].insert(dislikes[i][0]);
            }
            std::function<bool(int)> dfs = [&](int i){
                int nowcol = !color[i];
                for(auto &m : M[i]){
                    if(color[m]==color[i])return false;
                    if(color[m]==-1){
                        color[m] = nowcol;
                        if(!dfs(m))return false;
                    }
                }
                return true;
            };
            for(int i=1; i<=N; ++i){
                if(color[i]==-1){
                    color[i] = 1;
                    if(!dfs(i))return false;
                }
            }
            for(int i=1; i<=N; ++i)std::cout<<color[i]<<"  ";
            return true;
        }

//面试题 17.07. 婴儿名字
        std::vector<std::string> trulyMostPopular(std::vector<std::string>& na, std::vector<std::string>& sy){
            std::unordered_map<std::string, std::string> f;
            std::function<std::string(std::string&)> _find = [&](std::string& k){
                return f.count(k)?f[k]=_find(f[k]):k;
            };
            std::function<void(std::string&, std::string&)> _union = [&](std::string& a, std::string& b){
                auto pa = _find(a);
                auto pb = _find(b);
                if(pa!=pb)pa<pb?f[pb]=pa:f[pa]=pb;
            };
            for(auto &s : sy){
                int  m  = s.find(",");
                auto s1 = s.substr(1,m-1);
                auto s2 = s.substr(m+1, int(s.size())-m-2);
                _union(s1, s2);
            }
            std::unordered_map<std::string, int> mp;
            for(auto &s : na){
                auto m    = s.find('(');
                auto name = s.substr(0, m);
                auto n    = std::stoi(s.substr(m+1, int(s.size())-m-2));
                mp[_find(name)] += n;
            }
            std::vector<std::string> res;
            for(auto &r : mp){
                res.push_back(r.first + '(' + std::to_string(r.second) + ')');
            }
            return res;
        }
//872. 叶子相似的树
        bool leafSimilar(TreeNode* root1, TreeNode* root2){
            std::vector<int> l1;
            std::vector<int> l2;
            std::function<void(std::vector<int>&, TreeNode*)> dfs = [&](std::vector<int>& l, TreeNode* root){
                if(!root)return;
                if(!root->left && !root->right){
                    l.push_back(root->val);
                    return;
                }
                dfs(l, root->left);
                dfs(l, root->right);
            };
            dfs(l1, root1);
            dfs(l2, root2);
            return l1==l2;
        }
//547. 朋友圈
        int findCircleNum_better(std::vector<std::vector<int>>& M){
            int N = M.size();
            std::vector<int> f(N);
            std::iota(f.begin(), f.end(), 0);
            std::function<int(int)> _find = [&](int i){
                return f[i]==i?i:f[i]=_find(f[i]);
            };
            std::function<void(int, int)> _union = [&](int a, int b){
                int pa = _find(a);
                int pb = _find(b);
                if(pa != pb)f[pa] = pb;
            };
            for(int i=0; i<N; ++i){
                for(int j=0; j<N; ++j){
                    if(M[i][j] && i-j){
                        _union(i, j);
                    }
                }
            }
            int res = 0;
            for(int i=0; i<N; ++i)res += f[i]==i;
            return res;
        }
        int findCircleNum(std::vector<std::vector<int>>& M){
            int m  = M.size();
            std::vector<int> vi(m);
            std::function<void(int i)> dfs = [&](int i){
                vi[i] = 1;
                for(int j=0; j<m; ++j){
                    if(!vi[j] && M[i][j]){
                        dfs(j);
                    }
                }
            };
            int res = 0;
            for(int i=0; i<m; ++i){
                if(!vi[i]){
                    ++res;
                    dfs(i);
                }
            }
            return res;
        }

//721. 账户合并
        std::vector<std::vector<std::string>> accountsMerge(std::vector<std::vector<std::string>>& accounts){
            int size = accounts.size();
            std::vector<int>  f(size, 0);
            std::unordered_set<std::string> appear;
            std::unordered_map<std::string, int> mp;
            std::function<int(int)> _find = [&](int i){
                return i==f[i]?i:f[i]=_find(f[i]);
            };
            std::function<void(int, int)> _union = [&](int a, int b){
                int pa = _find(a);
                int pb = _find(b);
                if(pa!=pb)f[pa] = pb;
            };
            std::iota(f.begin(), f.end(), 0);
            for(int i=0; i<size; ++i){
                for(int j=1; j<accounts[i].size(); ++j){
                    if(!appear.count(accounts[i][j])){
                        appear.insert(accounts[i][j]);
                        mp[accounts[i][j]] = i;
                    }else{
                        _union(mp[accounts[i][j]], i);
                    }
                }
            }
            std::vector<std::vector<std::string>> res;
            std::unordered_map<int, std::set<std::string>> tmp;
            for(int i=0; i<size; ++i){
                int t = _find(i);
                for(int j=1; j<accounts[i].size(); ++j){
                    tmp[t].insert(accounts[i][j]);
                }
            }
            for(auto &t : tmp){
                std::vector<std::string> ans;
                ans.push_back(accounts[t.first][0]);
                for(auto &r : t.second){
                    ans.push_back(r);
                }
                res.push_back(ans);
            }
            return res;
        }
//面试题 04.04. 检查平衡性
        bool isBalanced(TreeNode* root){
            std::function<int(TreeNode* root)> dfs = [&](TreeNode* root){
                if(!root) return 0;
                int left = dfs(root->left);
                if(left==-1)return -1;
                int right = dfs(root->right);
                if(right==-1)return -1;
                if(abs(left-right) > 1)return -1;
                return std::max(left, right) + 1;
            };
            return dfs(root) != -1;
        }

//529. 扫雷游戏
        std::vector<std::vector<char>> updateBorder(std::vector<std::vector<char>>&board, std::vector<int>&click){
            int m = board.size();
            int n = board[0].size();
            int x = click[0];
            int y = click[1];
            if(board[x][y]=='M'){
                board[x][y] = 'X';
                return board;
            }
            std::vector<std::vector<int>> fun = {{1,1},{1,0},{1,-1},{-1,1},{-1,-1},{-1,0},{0,1},{0,-1}};
            std::function<void(int x, int y)> dfs = [&](int x, int y){
                int count = 0;
                for(auto &f : fun){
                    int a = x + f[0];
                    int b = y + f[1];
                    if(a>=0 && b>=0 && a<m && b<n && board[a][b]=='M'){
                        ++count;
                    }
                }
                if(count){
                    board[x][y] = '0' + count;
                }else{
                    board[x][y] = 'B';
                    for(auto &f : fun){
                        int a = x + f[0];
                        int b = y + f[1];
                        if(a>=0 && b>=0 && a<m && b<n && board[a][b]=='E'){
                            dfs(a, b);
                        }
                    }
                }
            };
            dfs(x, y);
            return board;
        }

//971. 翻转二叉树以匹配先序遍历
        std::vector<int> flipMatchVoyage(TreeNode* root, std::vector<int>& voyage){
            int size = voyage.size();
            std::vector<int> res;
            std::function<bool(TreeNode*, int&)> dfs = [&](TreeNode* root, int& index){
                if(!root)return true;
                if(index>=size || root->val != voyage[index++])return false;
                if(root->left && index<size && root->left->val != voyage[index]){
                    res.push_back(root->val);
                    return dfs(root->right, index) && dfs(root->left, index);
                }else{
                    return dfs(root->left, index) && dfs(root->right, index);
                }
            };
            int index = 0;
            if(dfs(root, index))return res;
            return {-1};
        }

//16.19. 水域大小
        std::vector<int> pondSizes(std::vector<std::vector<int>>& land){
            int m = land.size();
            int n = land[0].size();
            std::vector<int> res;
            std::vector<std::vector<int>> fun = {{1,1},{1,0},{1,-1},{-1,1},{-1,-1},{-1,0},{0, 1},{0, -1}};
            std::function<int (int, int)> dfs = [&](int x, int y){
                land[x][y] = 1;
                int res    = 1;
                for(auto &f : fun){
                    int a = x + f[0];
                    int b = y + f[1];
                    if(a>=0 && b>=0 && a<m && b<n && !land[a][b]){
                        res += dfs(a, b);
                    }
                }
                return res;
            };
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    if(!land[i][j])res.push_back(dfs(i,j));
                }
            }
            std::sort(res.begin(), res.end());
            return res;
        }
};
