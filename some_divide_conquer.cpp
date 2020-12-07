/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_divide_conquer.cpp
*     author   : @ JY
*     date     : 2020--11--08
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <cmath>
#include <functional>
#include <stdlib.h>
class Node{
    public:
        int val;
        Node *left, *right;
        Node () {}
        Node(int x) : val(x),left(NULL),right(NULL) {}
        Node(int x, Node *l, Node *r) : val(x), left(l), right(r) {}
};
class Sea {
    public: bool hasShips(std::vector<int>topRight, std::vector<int>bottomLeft);
};
class Solution{
    public:
//1274：矩形内船只的数目
        int countShips(Sea sea, std::vector<int> tprt, std::vector<int> btlt){
            std::function<int(int, int, int, int)> _dfs
                = [&](int x1, int y1, int x2, int y2){
                    if(x1 < x2 || y1 < y2 || !sea.hasShips({x1, y1}, {x2, y2})){
                        return 0;
                    }
                    if(x1==x2 && y1==y2)return 1;
                    int mx = (x1 + x2) / 2, my = (y1 + y2) / 2, ans = 0;
                    ans += _dfs(mx, my, x2, y2);
                    ans += _dfs(x1, y2, mx+1, y2);
                    ans += _dfs(mx, y1, x2, my+1);
                    ans += _dfs(x1, y1, mx+11, my+1);
                    return ans;
                };
            return _dfs(tprt[0], tprt[1], btlt[0], btlt[1]);
        }
//241. 为运算表达式设计优先级
        std::vector<int> diffWaysToCompute(std::string input){
            std::vector<int> res, nums, ops;
            std::map<std::pair<int, int>, std::vector<int>> dp;
            std::function<std::vector<int>(int, int)> _dfs = [&](int l, int r){
                if(dp.count({l, r}))return dp[{l, r}];
                std::vector<int> ans;
                if(l == r){
                    ans.emplace_back(nums[l]);
                }else{
                    for(int i=l; i<r; ++i){
                        for(auto &x1 : _dfs(l, i)){
                            for(auto &x2 : _dfs(i+1, r)){
                                switch (ops[i]){
                                    case 0 :ans.emplace_back(x1 + x2); break;
                                    case 1 :ans.emplace_back(x1 - x2); break;
                                    case 2 :ans.emplace_back(x1 * x2); break;
                                }
                            }
                        }
                    }
                }
                return dp[{l, r}] = ans;
            };
            int val = 0;
            for(auto &c : input){
                if(std::isdigit(c)){
                    val = val * 10 + c - '0';
                }else{
                    nums.emplace_back(val);
                    val = 0;
                    switch (c){
                        case '+' : ops.emplace_back(0); break;
                        case '-' : ops.emplace_back(1); break;
                        case '*' : ops.emplace_back(2); break;
                        default  : break;
                    }
                }
            }
            nums.emplace_back(val);
            return _dfs(0, nums.size()-1);
        }
//面试题 17.10. 主要元素
        int majorityElement(std::vector<int> &nums){
            int cnt = 0, cur = nums[0], len = nums.size();
            for(auto &x : nums){
                if(cur == x){
                    ++cnt;
                }else if(!cnt--){
                    cur = x;
                    cnt = 0;
                }
            }
            if(cnt > len / 2)return cur;
            cnt = 0;
            for(auto &x : nums)cnt += cur == x;
            return cnt > len / 2 ? cur : -1;
        }
//932. 漂亮数组
        std::vector<int> beautifulArray(int N){
            std::vector<int> res;
            std::unordered_map<int, std::vector<int>> dp;
            std::function<std::vector<int>(int)> _dfs = [&](int n){
                if(dp.count(n))return dp[n];
                std::vector<int> ans(n);
                if(n==1){
                    ans[0] = 1;
                }else{
                    int i = 0;
                    for(auto &x : _dfs((n+1) >> 1))ans[i++] = 2 * x - 1;
                    for(auto &x : _dfs(n >> 1))ans[i++] = 2 * x;
                }
                return dp[n]= ans;
            };
            return _dfs(N);
        }
//282. 给表达式添加运算符
        std::vector<std::string> addOperators(std::string num, int target){
            if(!num.size())return {};
            using ll = long long;
            std::vector<std::string> res;
            std::string ans;
            int len = num.size();
            std::function<void(int, ll, ll, ll, int)> _dfs
                = [&](int i, ll add, ll mul, ll cur, int sign){
                    if(len == i + 1){
                        if(add + cur * mul * sign == target){
                            res.emplace_back(ans + num[i]);
                        }
                        return;
                    }
                    bool ok  = ans.back() < '0';
                    ans += num[i];
                    auto ori = ans;
                    int nb  = num[i + 1] - '0';
                    if(!(ok && num[i] == '0')){
                        _dfs(i+1, add, mul, cur*10+nb, sign);
                        ans = ori;
                    }
                    ans += '+';
                    _dfs(i+1, add+cur*mul*sign, 1, nb, 1);
                    ans  = ori;
                    ans += '-';
                    _dfs(i+1, add+cur*mul*sign, 1, nb, -1);
                    ans  = ori;
                    ans += '*';
                    _dfs(i+1, add, mul*cur, nb, sign);
                    ans = ori;
                };
            _dfs(0, 0, 1, num[0]-'0', 1);
            return res;
        }
        Node *treeToDoublyList(Node *root){
            if(!root)return root;
            std::function<Node*(Node *)> _dfs = [&](Node *root){
                if(!root)return root;
                Node *l = _dfs(root->left);
                Node *r = _dfs(root->right);
                if(l && r){
                    root->right    = r->right;
                    r->right->left = root;
                    root->left     = l;
                    r->right       = l->right;
                    l->right       = root;
                    return r;
                }else if(l){
                    root->right = l->right;
                    root->left  = l;
                    l->right    = root;
                    return root;
                }else if(r){
                    root->right    = r->right;
                    r->right->left = root;
                    r->right       = root;
                    return r;
                }
                root->right = root;
                return root;
            };
            auto ans = _dfs(root);
            ans->right->left = ans;
            return ans->right;
        }
};
