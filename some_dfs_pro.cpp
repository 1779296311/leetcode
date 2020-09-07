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
#include <unordered_set>
#include <climits>
#include <functional>
#include <numeric>
#include <stdlib.h>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution{
    public:
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
