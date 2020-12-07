/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_recursion_pro.cpp
*     author   : @ JY
*     date     : 2020--11--06
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <functional>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(TreeNode *l, TreeNode *r) : val(0), left(l), right(r) {};
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {};
};
class Solution{
    public:
//LeetCode 625. 最小因式分解
//给定一个正整数 a，找出最小的正整数 b 使得 b 的所有数位相乘恰好等于 a。 如果不存在这样的结果或者结果不是 32 位有符号整数，返回 0。
        int smallestFactorization(int a){
            if(a < 10)return a;
            long long res = 0, base = 1;
            for(int i=9; i>=2; --i){
                while(!(a % i)){
                    res += i * base;
                    a /= i;
                    base *= 10;
                    if(res > INT_MAX)return 0;
                }
            }
            return res==1 ? res : 0;
        }
//LeetCode 246. 中心对称数
        bool isStrobogrammaticI(std::string num){
            std::unordered_map<char, char> mp {{'6', '9'}, {'9', '6'}, {'8', '8'}, {'0', '0'}, {'1', '1'}};
            std::string ans;
            for(auto &c : num){
                if(!mp.count(c))return false;
                ans += mp[c];
            }
            return std::string{rbegin(ans), rend(ans)} == num;
        }
//LeetCode 247. 中心对称数 II
        std::vector<std::string> findStrobogrammaticII(int n){
            std::vector<std::string> res;
            std::vector<char> l {'0', '1', '6', '8', '9'};
            std::vector<char> r {'0', '1', '9', '8', '6'};
            std::function<void(std::string)> _dfs = [&](std::string num){
                if(num.size() > n)return;
                if(num.size()==n && num[0]!='0')res.emplace_back(num);
                for(int i=0; i<5; ++i)_dfs(l[i] + num + r[i]);
            };
            _dfs(""), _dfs("0"), _dfs("1"), _dfs("8");
            return res;
        }
//LeetCode 248. 中心对称数 III
        int strobogrammaricInRangeIII(std::string low, std::string high){
            std::vector<char> l {'0', '1', '6', '8', '9'};
            std::vector<char> r {'0', '1', '9', '8', '6'};
            int res = 0, s1 = low.size(), s2 = high.size();
            std::function<void(std::string)> _dfs = [&](std::string num){
                int size = num.size();
                if(size > s2)return;
                if(size == s2 && num > high)return;
                if(size >= s1){
                    if((size>s1&&num[0]!='0') || (num>low))++res;
                }
                for(int i=0; i<5; ++i) _dfs(l[i] + num + r[i]);
            };
            _dfs(""), _dfs("0"), _dfs("1"), _dfs("8");
            return res;
        }

//LeetCode 776. 拆分二叉搜索树
        std::vector<TreeNode *> splitBST(TreeNode *root, int V){
            using vtp = std::vector<TreeNode *>;
            std::function<vtp(TreeNode *)> _dfs = [&](TreeNode *root){
                if(!root)return vtp{NULL, NULL};
                if(root->val > V){
                    auto l = _dfs(root->left);
                    root->left = l[1];
                    return vtp{l[0], root};
                }else{
                    auto r = _dfs(root->right);
                    root->right = r[0];
                    return vtp{root, r[1]};
                }
            };
            return _dfs(root);
        }
//LeetCode 544. 输出比赛匹配对
        std::string findContestMatch_a(int n){
            std::vector<std::string> res(n, "");
            for(int i=1; i<=n; ++i)res[i-1] = i + '0';
            while(n){
                for(int i=0; i<(n >> 1); ++i){
                    res[i] = "(" + res[i] + "," + res.back() + ")";
                    res.pop_back();
                }
                n >>= 1;
            }
            return res[0];
        }
        std::string findContestMatch(int n){
            std::vector<std::string> ans, temp;
            int l = 1, r = n, t = 1;
            while(n >>= 1)++t;
            while(l < r)ans.emplace_back("(" + std::to_string(l++) + "," + std::to_string(r--) + ")");
            while(--t){
                l = 0, r = ans.size();
                while(l < r)temp.emplace_back("(" + (ans[l++]) + "," + ans[r--] + ")");
                ans = temp;
                temp.clear();
            }
            return ans[0];
        }
//剑指 Offer 07. 重建二叉树
        TreeNode *buildTree(std::vector<int> &preorder, std::vector<int> &inorder){
            std::stack<TreeNode *>st;
            TreeNode *head = new TreeNode(preorder[0]), *cur = head;
            int len = preorder.size(), index = 0;
            for(int i=1; i<len; ++i){
                if(cur->val != inorder[index]){
                    cur->left = new TreeNode(preorder[i]);
                    st.push(cur);
                    cur = cur->left;
                }else{
                    while(st.size() && st.top()->val == inorder[index]){
                        cur = st.top();
                        st.pop();
                        ++index;
                    }
                    cur = cur->right = new TreeNode(preorder[i]);
                }
            }
            return head;
        }
        TreeNode *buildTree_rec(std::vector<int> &preorder, std::vector<int> &inorder){
            int len = preorder.size(), index = 0;
            std::function<TreeNode *(int, int)> _dfs
                = [&](int l, int r){
                    TreeNode *head = NULL;
                    if(index == len || l == r)return head;
                    for(int i=l; i<r; ++i){
                        if(inorder[i] == preorder[index]){
                            head = new TreeNode(preorder[index++]);
                            head->left = _dfs(l, i);
                            head->right = _dfs(i+1, r);
                            break;
                        }
                    }
                    return head;
            };
            return _dfs(0, len);
        }

//剑指 Offer 10- II. 青蛙跳台阶问题
        int numWays(int n){
            int MOD = 1e9 + 7;
            std::vector<long long> dp(101, -1);
            std::function<long long(int)> _dfs = [&](int n){
                if(!n)return (long long)1;
                if(n < 3)return (long long)n;
                if(dp[n] != -1)return dp[n];
                return dp[n] = (_dfs(n-1) + _dfs(n-2)) % MOD;
            };
            return _dfs(n) % MOD;
        }
//938. 二叉搜索树的范围和
        int rangesSumSBT(TreeNode *root, int low, int high){
            std::stack<TreeNode *> st;
            TreeNode *cur = root;
            int sum = 0;
            while(st.size() || cur){
                if(cur){
                    st.push(cur);
                    cur = cur->left;
                }else{
                    cur = st.top();
                    if(cur->val >=low && high>=cur->val)sum += cur->val;
                    cur = st.top()->right;
                    st.pop();
                }
            }
            return sum;
        }
//563. 二叉树的坡度
        int findTilt(TreeNode *root){
            int res = 0;
            std::function<int(TreeNode *)> _dfs = [&](TreeNode *root){
                if(!root)return 0;
                int l = _dfs(root->left);
                int r = _dfs(root->right);
                res += abs(l - r);
                return l + r + root->val;
            };
            _dfs(root);
            return res;
        }
//面试题 08.06. 汉诺塔问题
        void hanota(std::vector<int> &A, std::vector<int> &B, std::vector<int> &C){
            std::function<void(int, std::vector<int> &, std::vector<int> &, std::vector<int> &)> _dfs
                = [&](int n, std::vector<int> &N, std::vector<int> &B, std::vector<int> &C){
                if(n == 1){
                    C.emplace_back(A.back());
                    A.pop_back();
                    return;
                }
                _dfs(n-1, A, C, B);
                C.emplace_back(A.back());
                A.pop_back();
                _dfs(n-1, B, A, C);
            };
            _dfs(A.size(), A, B, C);
        }
//894. 所有可能的满二叉树
        std::vector<TreeNode *> allPossibleFBT(int N){
            std::vector<TreeNode *> res;
            std::map<int, std::vector<TreeNode*>> dp;
            std::function<std::vector<TreeNode *>(int)> _dfs = [&](int n){
                if(dp.count(n))return dp[n];
                std::vector<TreeNode *> ans;
                if(n==1){
                    ans.emplace_back(new TreeNode());
                    return ans;
                }
                for(int i=0; i<n; ++i){
                    if(!(i & 1))continue;
                    for(auto &l : _dfs(i)){
                        for(auto &r : _dfs(n-i-1)){
                            auto head = new TreeNode();
                            head->left  = l;
                            head->right = r;
                            ans.emplace_back(head);
                        }
                    }
                }
                return dp[n]=ans;
            };
            return _dfs(N);
        }
//783. 二叉搜索树节点最小距离
        int minDIffInBST(TreeNode *root){
            int res = INT_MAX, INF = 0x3f3f3f3f;
            struct _node{
                int max_, min_;
                _node(int m1, int m2) : max_(m1), min_(m2) {}
            };
            std::function<_node(TreeNode *)> _dfs = [&](TreeNode *root){
                if(!root) return _node{-INF, INF};
                auto l = _dfs(root->left);
                auto r = _dfs(root->right);
                res = std::min({res, root->val-l.max_, r.min_-root->val});
                return _node{std::max({root->val, l.max_, r.max_}),
                             std::min({root->val, l.min_, r.min_})};
            };
            _dfs(root);
            return res;
        }
//面试题 08.05. 递归乘法
        int multiply(int A, int B){
            std::function<int(int, int)> _dfs = [&](int a, int b){
                if(!a)return a;
                if(a==1)return b;
                return (b << 1) + _dfs(a-2, b);
            };
            return _dfs(std::min(A, B), std::max(A, B));
        }
//面试题 17.12. BiNode
        TreeNode *convertBiNode(TreeNode *root){
            if(!root)return root;
            std::function<TreeNode*(TreeNode *root)> _dfs = [&](TreeNode *root){
                if(!root)return root;
                auto l = _dfs(root->left);
                auto r = _dfs(root->right);
                root->left = nullptr;
                if(l && r){
                    auto head = l->right;
                    l->right = root;
                    root->right = r->right;
                    r->right = head;
                    return r;
                }else if(l){
                    root->right = l->right;
                    l->right = root;
                    return root;
                }else if(r){
                    root->right = r->right;
                    r->right = root;
                    return r;
                }
                root->right = root;
                return root;
            };
            auto ans = _dfs(root);
            auto res = ans->right;
            ans->right = nullptr;
            return res;
        }
//p面试题 16.11. 跳水板
        std::vector<int> divingBoard(int shorter, int longer, int k){
            if(k == 0)return {};
            if(shorter == longer)return {k};
            std::vector<int> res(k+1);
            for(int i=0; i<=k; ++i){
                res[i] = shorter * (k - i) + longer * i;
            }
            return res;
        }
        std::vector<int> divingBoard_fuck(int shorter, int longer, int k){
            if(!k)return {};
            if(shorter == longer)return {k};
            std::set<int> mp;
            std::set<std::pair<int, int>> dp;
            std::function<void(int, int, int)> _dfs = [&](int s, int l, int len){
                if(dp.count({s, l}))return;
                if(s + l == k){
                    if(len)mp.insert(len);
                    return;
                }
                _dfs(s, l+1, len+longer);
                _dfs(s+1, l, len+shorter);
                dp.insert({s, l});
            };
            _dfs(0, 0, 0);
            return {begin(mp), end(mp)};
        }
//1137. 第 N 个泰波那契数
        int tribonacci(int n){
            std::vector<int> dp(50, -1);
            dp[0] = 0, dp[1] = dp[2] = 1;
            std::function<int(int)> _dfs = [&](int n){
                if(dp[n] != -1)return dp[n];
                return dp[n] = _dfs(n-1) + _dfs(n-2) + _dfs(n-3);
            };
            return _dfs(n);
        }
//761. 特殊的二进制序列
        std::string makeLargestSpecial(std::string S){
            int len = S.size();
            std::vector<int> mp(len);
            std::stack<int> st;
            for(int i=0; i<len; ++i){
                if(S[i] == '1'){
                    st.push(i);
                }else{
                    mp[st.top()] = i;
                    st.pop();
                }
            }
            std::function<void(int, int)> _dfs = [&](int l, int r){
                if(l > r)return;
                std::multiset<std::string> mst;
                for(int i=l; i<r; i=mp[i]+1){
                    _dfs(i+1, mp[i]-1);
                    mst.insert(S.substr(i, mp[i]-i+1));
                }
                for(auto it=rbegin(mst); it!=rend(mst); ++it){
                    for(auto &c : *it)S[l++] = c;
                }
            };
            _dfs(0, len-1);
            return S;
        }
//687. 最长同值路径
        int longestUnivaluePath(TreeNode *root){
            int res = 0;
            std::function<int(TreeNode *)> _dfs = [&](TreeNode *root){
                if(!root)return 0;
                int l = _dfs(root->left);
                int r = _dfs(root->right);
                int ans = 1;
                if(!l && !r)return ans;
                if(l && root->val != root->left->val){
                    l = 0;
                }
                if(r && root->val != root->right->val){
                    r = 0;
                }
                res = std::max(res, std::max(ans = (std::max(l, r)), l+r));
                return ans + 1;
            };
            _dfs(root);
            return res;
        }
//794. 有效的井字游戏
        bool validTicTcaToe(std::vector<std::string> &board){
            int cnt0 = 0, cnt1 = 0;
            for(auto &l : board){
                for(auto &c : l){
                    cnt0 += (c=='X');
                    cnt1 += (c=='O');
                }
            }
            if(cnt0-cnt1!=0 && cnt0-cnt1!=1)return false;
            std::function<bool(int)> _win = [&](int c){
                for(int i=0; i<3; ++i){
                    if(c==board[0][i] && c==board[1][i] && c==board[2][i])return true;
                    if(c==board[i][0] && c==board[i][1] && c==board[i][2])return true;
                }
                if(c==board[0][0] && c==board[1][1] && c==board[2][2])return true;
                if(c==board[2][0] && c==board[1][1] && c==board[0][2])return true;
                return false;
            };
            if(_win('X') && cnt0 != cnt1+1)return false;
            if(_win('O') && cnt0 != cnt1)return false;
            return true;
        }
//779. 第K个语法符号
        int kthGrammar(int N, int K){
            if(N == 1)return 0;
            if(K <= (1<<(N-2)))return kthGrammar(N-1, K);
            return kthGrammar(N-1, K - (1<<(N-2))) ^ 1;
        }
};
template<class T>
void debug(std::vector<T> &arr, std::string M=""){
    for(auto &x : arr)std::cout<<x<<"   "+M;
    std::cout<<std::endl;
}
int main(int argc,const char *argv[]){
    Solution te;
    //int a = 48;
    int a = 15;
    std::cout<<te.smallestFactorization(a)<<std::endl;
    //std::string num {"69"};
    //std::cout<<te.isStrobogrammaticI(num)<<std::endl;
    //int n = 3;
    //auto arr = te.findStrobogrammaticII(n);
    //debug(arr);
    //std::string low {"50"}, high {"100"};
    //std::cout<<te.strobogrammaricInRangeIII(low, high)<<std::endl;
    return 0;
}
