/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_bfs_pro.cpp
*     author   : @ JY
*     date     : 2020--09--18
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
#include <deque>
#include <functional>
#include <numeric>
#include <stdlib.h>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution{
public:
//for(auto &ss : e){
    //std::cout<<ss.first<<"----";
    //for(auto &s : ss.second){
        //std::cout<<s<<"  ";
    //}
    //std::cout<<std::endl;
//}
////913. 猫和老鼠
    int catMouseGame(std::vector<std::vector<int>> &graph){
        using vi   = std::vector<int>;
        using vvi  = std::vector<vi>;
        using vvvi = std::vector<vvi>;
        int n = graph.size();
        vvvi dp(n*2,vvi(n, vi(n, -1)));
        std::function<int(int, int, int)> _dfs = [&](int len, int c, int m){
            if(len==2*n)return 0;
            if(c==m)return 2;
            if(!m)return 1;
            if(dp[len][c][m] != -1)return dp[len][c][m];
            auto &res = dp[len][c][m];
            if(len&1){
                int lose = 1;
                for(auto to : graph[c]){
                    if(!to)continue;
                    int ans = _dfs(len+1, to, m);
                    if(ans==2)return res = 2;
                    if(ans==0)lose = 0;
                }
                return res = lose;
            }
            int lose = 2;
            for(auto to : graph[m]){
                if(!to)return res = 1;
                int ans =_dfs(len+1, c, to);
                if(ans==1)return res = 1;
                if(ans==0)lose = 0;
            }
            return res = lose;
        };
        return _dfs(0, 2, 1);
    }
//126. 单词接龙 II
    std::vector<std::vector<std::string>> findLadders(std::string beginWord, std::string endWord,
            std::vector<std::string> &wordList){
        std::vector<std::string> word_id;
        std::unordered_map<std::string, int> id_mp;
        std::vector<std::vector<int>> e;
        std::function<bool(std::string &, std::string &)> _can_change
            = [&](std::string &a, std::string &b){
                int ans = 0;
                int len = a.length();
                for(int i=0; i<len; ++i){
                    if(a[i]!=b[i] && ++ans>1)return false;
                }
                return true;
        };
        int n  = wordList.size();
        int id = 0;
        for(auto &w : wordList){
            if(!id_mp.count(w)){
                id_mp[w] = id++;
                word_id.push_back(w);
            }
        }
        if(!id_mp.count(endWord))return {};
        if(!id_mp.count(beginWord)){
            id_mp[beginWord] = id++;
            word_id.push_back(beginWord);
        }
        e.resize(id);
        for(int i=0; i<id; ++i){
            for(int j=i+1; j<id; ++j){
                if(_can_change(word_id[i], word_id[j])){
                    e[i].push_back(j);
                    e[j].push_back(i);
                }
            }
        }
        std::vector<int> cost(id, INT_MAX);
        cost[id_mp[beginWord]] = 0;
        std::vector<std::vector<std::string>> res;
        int end_id = id_mp[endWord];
        std::queue<std::vector<int>> q;
        q.push({id_mp[beginWord]});
        while(q.size()){
                auto used    = q.front();q.pop();
                auto last_id = used.back();
                std::cout<<word_id[last_id]<<std::endl;
                if(last_id == end_id){
                    std::vector<std::string> temp;
                    for(auto &i : used)temp.push_back(word_id[i]);
                    res.push_back(temp);
                }else{
                    for(auto &to : e[last_id]){
                        if(cost[to] < cost[last_id]+1)continue;
                        cost[to] = cost[last_id] + 1;
                        auto temp = used;
                        temp.push_back(to);
                        q.push(temp);
                    }
                }
        }
        return res;
    }
    std::vector<std::vector<std::string>> findLadders_fuck(std::string beginWord, std::string endWord,
            std::vector<std::string> &wordList){
        using pss = std::pair<std::string, std::string>;
        int n = wordList.size();
        std::unordered_map<std::string, std::unordered_set<int>> e;
        std::function<bool(std::string &, std::string &)> _can_change
            = [&](std::string &a, std::string &b){
                int ans = 0;
                int len = a.length();
                for(int i=0; i<len; ++i){
                    if(a[i]!=b[i] && ++ans>1)return false;
                }
                return true;
        };
        int f = 0;
        for(int i=0; i<n; ++i){
            if(!endWord.compare(wordList[i]))f=1;
            for(int j=i+1; j<n; ++j){
                if(_can_change(wordList[i], wordList[j])){
                    e[wordList[i]].insert(j);
                    e[wordList[j]].insert(i);
                }
            }
        }
        if(!f)return {};
        for(int i=0; i<n; ++i){
            if(wordList[i].compare(beginWord) && _can_change(wordList[i], beginWord)){
                e[beginWord].insert(i);
            }
        }
        std::queue<pss> q;
        std::unordered_set<std::string> paths;
        q.push({beginWord, beginWord});

        while(q.size()){
            int size = q.size();
            while(size--){
                auto [cur, used] = q.front();q.pop();
                for(auto &to : e[cur]){
                    if(used.find(wordList[to]) != std::string::npos)continue;
                    if(!wordList[to].compare(endWord)){
                        paths.insert(used);
                        continue;
                    }
                    auto new_used = used + "|" + wordList[to];
                    q.push({wordList[to], new_used});
                }
            }
            if(paths.size())break;
        }
        //for(auto &s : paths)std::cout<<s<<"  ";
        std::vector<std::vector<std::string>> res;
        for(auto &pa : paths){
            std::vector<std::string> temp;
            int pos1 = 0;
            int pos2 = pa.find('|');
            while(pos2 != std::string::npos){
                temp.push_back(pa.substr(pos1, pos2++-pos1));
                pos1 = pos2;
                pos2 = pa.find('|');
            }
            temp.push_back(endWord);
            res.push_back(temp);
        }
        return res;
    }
//1298. 你能从盒子里获得的最大糖果数
    int maxCandies(std::vector<int> &status, std::vector<int> &candies, std::vector<std::vector<int>> &keys,
            std::vector<std::vector<int>> &containedBoxes, std::vector<int> &initialBoxes){
        int n = initialBoxes.size();
        if(!n)return n;
        int res = 0;
        std::queue<int> q;
        std::unordered_set<int> vi;
        std::unordered_set<int> boxes;
        for(auto &b : initialBoxes){
            if(status[b])q.push(b);
            boxes.insert(b);
        }
        while(q.size()){
            while(q.size()){
                int cur = q.front();q.pop();
                res += candies[cur];
                for(auto &k : keys[cur])status[k]=1;
                for(auto &cb : containedBoxes[cur])boxes.insert(cb);
                vi.insert(cur);
            }
            for(auto &bx : boxes){
                if(status[bx] && !vi.count(bx))q.push(bx);
            }
        }
        return res;
    }
//面试题 04.03. 特定深度节点链表
    std::vector<ListNode *> listofDepth(TreeNode *root){
        if(!root)return {};
        ListNode *cur = nullptr;
        ListNode *rt  = nullptr;
        std::vector<ListNode *> res;
        std::queue<TreeNode *> q;
        q.push(root);
        while(q.size()){
            int size = q.size();
            rt       = nullptr;
            while(size--){
                TreeNode *temp = q.front();q.pop();
                if(temp->left)q.push(temp->left);
                if(temp->right)q.push(temp->right);
                if(rt)cur->next = new ListNode(temp->val), cur = cur->next;
                if(!rt)cur = rt = new ListNode(temp->val);
            }
            res.push_back(rt);
        }
        return res;
    }
//407. 接雨水 II
    int trapRainWater(std::vector<std::vector<int>> &heightMap){
        using pii = std::pair<int, int>;
        int m = heightMap.size();
        int n = heightMap[0].size();
        std::vector<int> _fun = {0, 1, 0, -1, 0};
        int res = 0;
        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
        std::unordered_set<int> vi;
        for(int i=0; i<m; ++i){
            vi.insert(i*n);
            vi.insert(i*n+n-1);
            q.push({heightMap[i][0], i*n});
            q.push({heightMap[i][n-1], i*n+n-1});
        }
        for(int j=1; j<n-1; ++j){
            vi.insert(j);
            vi.insert((m-1)*n+j);
            q.push({heightMap[0][j], j});
            q.push({heightMap[m-1][j], (m-1)*n+j});
        }
        while(q.size()){
            auto [h, pos] = q.top();q.pop();
            int i = pos / n;
            int j = pos % n;
            for(int f=0; f<4; ++f){
                int i1  = i + _fun[f];
                int j1  = j + _fun[f+1];
                int pos = i1 * n + j1;
                if(i1<0 || j1<0 || i1>=m || j1>=n)continue;
                if(!vi.insert(pos).second)continue;
                if(h > heightMap[i1][j1])res += h-heightMap[i1][j1];
                q.push({std::max(h, heightMap[i1][j1]), pos});
            }
        }
        return res;
    }
//993. 二叉树的堂兄弟节点
    bool isCousins(TreeNode *root, int x, int y){
        if(!root)return false;
        std::queue<std::pair<TreeNode *, int>> q;
        q.push({root, -1});
        while(q.size()){
            int size = q.size();
            int x1=0,xp1, y1=0,yp1;
            while(size--){
                auto [cur, p] = q.front();q.pop();
                if(cur->left)q.push({cur->left, cur->val});
                if(cur->right)q.push({cur->right, cur->val});
                if(cur->val==x)x1=1, xp1=p;
                if(cur->val==y)y1=1, yp1=p;
                if(x1 && y1 && xp1 != yp1)return true;
            }
            if(x1 || y1)return false;
        }
        return false;
    }
//994. 腐烂的橘子
    int orangestRotting(std::vector<std::vector<int>> &grid){
        int m = grid.size();
        int n = grid[0].size();
        std::vector<int> _fun = {0, 1, 0, -1, 0};
        std::queue<int> q;
        std::unordered_set<int> vi;
        int good = 0;
        for(int i=0; i<m; ++i){
            for(int j=0; j<n; ++j){
                if(grid[i][j]==1)++good;
                if(grid[i][j]!=2 || !vi.insert(i*n+j).second)continue;
                q.push(i*n+j);
            }
        }
        if(!good)return good;
        int step = 0;
        while(q.size()){
            ++step;
            int size = q.size();
            while(size--){
                const int cur = q.front();q.pop();
                const int i   = cur / n;
                const int j   = cur % n;
                for(int f=0; f<4; ++f){
                    int i1  = i + _fun[f];
                    int j1  = j + _fun[f+1];
                    int pos = i1 * n + j1;
                    if(i1<0 || j1<0 || i1>=m ||j1>=n)continue;
                    if(grid[i1][j1]!=1 || !vi.insert(pos).second)continue;
                    if(!--good)return step;
                    q.push(pos);
                }
            }
        }
        return -1;
    }
//1311. 获取你好友已观看的视频
    std::vector<std::string> watchVideosByFriends(std::vector<std::vector<std::string>> &watchedVideos,
            std::vector<std::vector<int>> &friends, int id, int level){
        using psi  = std::pair<std::string, int>;
        using vpsi = std::vector<psi>;
        struct _cmp{
            bool operator()(const psi &a, const psi &b) const{
                return  a.second == b.second
                      ? a.first  > b.first
                      : a.second > b.second;
            }
        };
        int n = friends.size();
        std::unordered_set<int> ans;
        std::unordered_set<int> vi;
        vi.insert(id);
        std::queue<int> q;
        q.push(id);
        ++level;
        while(q.size() && level--){
            int size = q.size();
            while(size--){
                int cur = q.front();q.pop();
                if(!level){
                    ans.insert(cur);
                    continue;
                }
                for(auto &ne : friends[cur]){
                    if(!vi.insert(ne).second)continue;
                    q.push(ne);
                }
            }
        }
        std::unordered_map<std::string, int> mp;
        for(auto &i : ans){
            for(auto &s : watchedVideos[i])++mp[s];
        }
        std::priority_queue<psi, vpsi, _cmp> pq(mp.begin(), mp.end());
        std::vector<std::string> res;
        while(pq.size()){
            res.push_back(pq.top().first);
            pq.pop();
        }
        return res;
    }
//752. 打开转盘锁
    int openlock(std::vector<std::string> &deadends, std::string target){
        std::unordered_set<std::string> mp(deadends.begin(), deadends.end());
        std::string begin = "0000";
        if(!mp.insert(begin).second)return -1;
        if(!begin.compare(target))return 0;
        std::queue<std::string> q;
        q.push(begin);
        std::function<bool(std::string &)> _calc = [&](std::string &ori){
            std::function<bool(int)>  _bfs = [&](int i){
                std::string temp = ori;
                char c = temp[i]=='9'?'0':temp[i]+1;
                temp[i] = c;
                if(!temp.compare(target))return true;
                if(mp.insert(temp).second)q.push(temp);

                temp = ori;
                c = temp[i]=='0'?'9':temp[i]-1;
                temp[i] = c;
                if(!temp.compare(target))return true;
                if(mp.insert(temp).second)q.push(temp);

                return false;
            };
            return _bfs(0) || _bfs(1) || _bfs(2) || _bfs(3);
        };
        int step = 0;
        while(q.size()){
            ++step;
            int size = q.size();
            while(size--){
                auto cur = q.front();q.pop();
                if(_calc(cur))return step;
            }
        }
        return -1;
    }
//1284. 转化为全零矩阵的最少反转次数
    int minFlips(std::vector<std::vector<int>> &mat){
        using vvi = std::vector<std::vector<int>>;
        std::vector<int> _fun = {0, 0, 1, 0, -1, 0};
        int m = mat.size();
        int n = mat[0].size();
        std::function<int(vvi &)> _encode = [&](vvi &mat){
            int ans = 0;
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    ans = (ans<<1) + mat[i][j];
                }
            }
            return ans;
        };
        std::function<vvi(int)> _decode = [&](int c){
            vvi ans(m, std::vector<int>(n));
            for(int i=m-1; i>=0; --i){
                for(int j=n-1; j>=0; --j){
                    ans[i][j] = c & 1;
                    c >>= 1;
                }
            }
            return ans;
        };
        std::function<void(vvi &, int, int)> _xor = [&](vvi &ma, int x, int y){
            for(int i=0; i<5; ++i){
                int i1 = x + _fun[i];
                int j1 = y + _fun[i+1];
                if(i1<0 || j1<0 || i1>=m || j1>=n)continue;
                ma[i1][j1] ^= 1;
            }
        };
        std::queue<int> q;
        std::unordered_set<int> vi;
        int begin = _encode(mat);
        if(!begin)return 0;
        q.push(begin);
        vi.insert(begin);
        int step = 0;
        int code = 0;
        while(q.size()){
            ++step;
            int size = q.size();
            while(size--){
                auto ma = _decode(q.front()); q.pop();
                for(int i=0; i<m; ++i){
                    for(int j=0; j<n; ++j){
                        _xor(ma, i, j);
                        if( !(code = _encode(ma)) )return step;
                        _xor(ma, i, j);
                        if(!vi.insert(code).second)continue;
                        q.push(code);
                    }
                }
            }
        }
        return -1;
    }
//1091. 二进制矩阵中的最短路径
    int shorestPathBinaryMatrix(std::vector<std::vector<int>> &grid){
        int n = grid.size();
        if(n==1 && grid[0].size()==1)return 1;
        if(grid[0][0])return -1;
        std::vector<int> _fun = {1,1,-1,-1,0,1,0,-1,1};
        std::queue<int> q;
        std::unordered_set<int> vi;
        q.push(0);
        vi.insert(0);
        int step = 1;
        while(q.size()){
            ++step;
            int size = q.size();
            while(size--){
                int cur = q.front();q.pop();
                int i   = cur / n;
                int j   = cur % n;
                for(int f=0; f<8; ++f){
                    int i1 = i + _fun[f];
                    int j1 = j + _fun[f+1];
                    int ps = i1 * n + j1;
                    if(i1<0 ||j1<0 ||i1>=n || j1>=n)continue;
                    if(i1==n-1 && j1==n-1)return step;
                    if(!vi.insert(ps).second || grid[i1][j1])continue;
                    q.push(ps);
                }
            }
        }
        return -1;
    }
//773. 滑动谜题
    int slidingPuzzle(std::vector<std::vector<int>> &board){
        using qstr = std::queue<std::string>;
        std::string ans = "123450";
        std::string begin;
        std::unordered_set<std::string> vi;
        for(int i=0; i<2; ++i){
            for(int j=0; j<3; ++j){
                begin += std::to_string(board[i][j]);
            }
        }
        std::function<bool(qstr &, const std::string &)> _calc
            = [&](qstr &q, const std::string &cur){
                std::function<bool(int, int)> _can = [&](int a, int b){
                    std::string temp = cur;
                    std::swap(temp[a], temp[b]);
                    if(!ans.compare(temp))return true;
                    if(!vi.count(temp)){
                        q.push(temp);
                        vi.insert(temp);
                    }
                    return false;
                };
                const int zero = cur.find('0');
                if(zero!=0 && zero!=3 && _can(zero, zero-1))return true;
                if(zero!=2 && zero!=5 && _can(zero, zero+1))return true;
                if(zero<3  && _can(zero, zero+3))return true;
                if(zero>2  && _can(zero, zero-3))return true;
                return false;
        };
        if(!ans.compare(begin))return 0;
        std::queue<std::string> q;
        q.push(begin);
        vi.insert(begin);
        int step = 0;
        while(q.size()){
            ++step;
            int size = q.size();
            while(size--){
                const auto cur = q.front();q.pop();
                if(_calc(q, cur))return step;
            }
        }
        return -1;
    }
//815. 公交路线
    int numBusesTodestination(std::vector<std::vector<int>> &routes, int S, int T){
        if(S==T)return 0;
        int n = routes.size();
        std::vector<std::unordered_set<int>> mp;
        for(auto &b : routes)mp.push_back({b.begin(), b.end()});
        std::function<bool(int, int)> _calc  = [&](int i, int j){
            for(auto x : mp[j]){
                if(mp[i].count(x))return true;
            }
            return false;
        };
        std::vector<std::vector<int>> e(n);
        for(int i=0; i<n; ++i){
            for(int j=i+1; j<n; ++j){
                if(!_calc(i, j))continue;
                e[i].push_back(j);
                e[j].push_back(i);
            }
        }
        std::unordered_set<int> stop;
        std::unordered_set<int> vi;
        std::queue<int> q;
        for(int i=0; i<n; ++i){
            if(mp[i].count(S)){
                q.push(i);
                vi.insert(i);
            }
            if(mp[i].count(T))stop.insert(i);
        }
        int step = 0;
        while(q.size()){
            ++step;
            int size = q.size();
            while(size--){
                int cur = q.front();q.pop();
                if(stop.count(cur))return step;
                for(auto &to : e[cur]){
                    if(vi.count(to))continue;
                    vi.insert(to);
                    q.push(to);
                }
            }
        }
        return -1;
    }
//787. K 站中转内最便宜的航班
    int findCheapestPrices(int n, std::vector<std::vector<int>> &flights, int src, int dst, int K){
        using pii   = std::pair<int, int>;
        using vpii  = std::vector<pii>;
        std::vector<vpii> e(n);
        for(auto &p : flights)e[p[0]].push_back({p[1], p[2]});
        std::queue<pii> q;
        q.push({src, 0});
        int step = -1;
        int res  = INT_MAX;
        while(q.size() && ++step<=K){
            int size = q.size();
            while(size--){
                auto [cur, dis] = q.front();q.pop();
                for(auto &[n_pos, n_dis] : e[cur]){
                    if(dis+n_dis >= res)continue;
                    if(n_pos==dst)res = std::min(res, dis+n_dis);
                    q.push({n_pos, dis+n_dis});
                }
            }
        }
        return res==INT_MAX?-1:res;
    }
//675. 为高尔夫比赛砍树
    int cutoffTree(std::vector<std::vector<int>> &forest){
        int m = forest.size();
        int n = forest[0].size();
        using pii = std::pair<int, int>;
        std::vector<int> _fun = {1, 0, -1, 0, 1};
        std::vector<pii> trees;
        for(int i=0; i<m; ++i){
            for(int j=0; j<n; ++j){
                int t = forest[i][j];
                if(t>1)trees.push_back({t, i*n+j});
            }
        }
        std::function<int(int, int, int, int)> _bfs = [&](int ri, int rj, int ti, int tj){
            std::queue<int> q;
            q.push(ri*n+rj);
            int step = 0;
            std::vector<int> vi(n*m);
            while(q.size()){
                ++step;
                int size = q.size();
                while(size--){
                    int pos = q.front();q.pop();
                    int i = pos / n;
                    int j = pos % n;
                    for(int f=0; f<4; ++f){
                        int i1 = i + _fun[f];
                        int j1 = j + _fun[f+1];
                        if(i1<0 || j1<0 ||i1>=m || j1>=n)continue;
                        if(i1==ti && j1==tj)return step;
                        if(vi[i1*n+j1])continue;
                        if(!forest[i1][j1])continue;
                        vi[i1*n+j1] = 1;
                        q.push(i1*n+j1);
                    }
                }
            }
            return -1;
        };
        std::sort(trees.begin(), trees.end());
        int res = 0;
        int ri=0, rj=0;
        for(auto t : trees){
            int ti = t.second / n;
            int tj = t.second % n;
            int d  = _bfs(ri, rj, ti, tj);
            if(d==-1)return -1;
            res += d;
            ri = ti;
            rj = tj;
        }
        return res;
    }
//1210. 穿过迷宫的最少移动次数
    int minimumMoves(std::vector<std::vector<int>> &grid){
        using pii  = std::pair<int, int>;
        using qpii = std::queue<pii>;
        int n = grid.size();
        struct _cmp{
            int operator()(const pii &a) const {
                return a.first*100 + a.second;
            }
        };
        std::unordered_set<pii, _cmp> vi;
        std::function<bool(qpii &, int, int, int, int)> _calc =
            [&](qpii &q, int ti, int tj, int hi, int hj){
                std::function<bool(int, int, int, int)> _can = [&](int nti, int ntj, int nhi, int nhj){
                    if(!grid[nti][ntj] && !grid[nhi][nhj]){
                        if(ntj==n-2 && nti==n-1 && nhj==n-1 && nhi==n-1){
                            return true;
                        }
                        if(vi.count({nti*n+ntj, nhi*n+nhj}))return false;
                        vi.insert({nti*n+ntj, nhi*n+nhj});
                        q.push({nti*n+ntj, nhi*n+nhj});
                    }
                    return false;
                };
                if(hi<n-1 && _can(ti+1, tj, hi+1, hj))return true;
                if(hj<n-1 && _can(ti, tj+1, hi, hj+1))return true;
                if(tj<hj && hi<n-1){
                    if(!grid[hi+1][hj-1] && !grid[hi+1][hj]){
                        if(vi.count({ti*n+tj, (hi+1)*n + (hj-1)}))return false;
                        vi.insert({ti*n+tj, (hi+1)*n + (hj-1)});
                        q.push({ti*n+tj, (hi+1)*n + (hj-1)});
                    }
                }
                if(ti<hi && hj<n-1){
                    if(!grid[hi-1][hj+1] && !grid[hi][hj+1]){
                        if(vi.count({ti*n+tj, (hi-1)*n + (hj+1)}))return false;
                        vi.insert({ti*n+tj, (hi-1)*n + (hj+1)});
                        q.push({ti*n+tj, (hi-1)*n + (hj+1)});
                    }
                }
                return false;
        };
        qpii q;
        q.push({0, 1});
        vi.insert({0, 1});
        int step = 0;
        while(q.size()){
            ++step;
            int size = q.size();
            while(size--){
                auto [tail, head] = q.front();q.pop();
                int ti = tail / n;
                int tj = tail % n;
                int hi = head / n;
                int hj = head % n;
                if(_calc(q, ti, tj, hi, hj))return step;
            }
        }
        return -1;
    }
//864. 获取所有钥匙的最短路径
    int shortestPathAllKeys(std::vector<std::string> &grid){
        int m = grid.size();
        int n = grid[0].size();
        int b_x, b_y;
        std::vector<int> _fun = {-1, 0, 1, 0, -1};
        int k_size = 0;
        for(int i=0; i<m; ++i){
            for(int j=0; j<n; ++j){
                char c = grid[i][j];
                if(c=='@'){
                    b_x = i;
                    b_y = j;
                }else if(std::islower(c)){
                    ++k_size;
                }
            }
        }
        std::queue<std::pair<int,int>> q;
        int vi[m*n][(1<<k_size)];
        bzero(vi, sizeof vi);
        vi[b_x*n+b_y][0] = 1;
        q.push({b_x*n+b_y, 0});
        int step = 0;
        while(q.size()){
            ++step;
            int size = q.size();
            while(size--){
                auto [cur, state] = q.front(); q.pop();
                int i = cur / n;
                int j = cur % n;
                for(int f=0; f<4; ++f){
                    int i1 = i + _fun[f];
                    int j1 = j + _fun[f+1];
                    int to = i1 * n + j1;
                    int ns = state;
                    if(i1<0 || j1<0 || i1>=m || j1>=n)continue;
                    char c = grid[i1][j1];
                    if(c=='#')continue;
                    if(std::isupper(c) && !((1<<(c-'A'))&state) ) continue;
                    if(std::islower(c))ns = ns | (1<<(c-'a'));
                    if(ns==(1<<k_size)-1)return step;
                    if(vi[to][ns])continue;
                    q.push({to, ns});
                    vi[to][ns] = 1;
                }
            }
        }
        return -1;
    }
//310. 最小高度树
    std::vector<int> findMinHeightTrees(int n, std::vector<std::vector<int>> &edges){
        std::vector<std::vector<int>> e(n);
        std::vector<int> in(n);
        for(auto &p : edges){
            e[p[0]].push_back(p[1]);
            e[p[1]].push_back(p[0]);
            ++in[p[0]];
            ++in[p[1]];
        }
        std::queue<int> q;
        for(int i=0; i<n; ++i){
            if(1==in[i])q.push(i);
        }
        while(n>2){
            int size = q.size();
            n -= size;
            while(size--){
                int cur = q.front();q.pop();
                for(auto &t : e[cur]){
                    --in[cur];
                    if(--in[t]==1)q.push(t);
                }
            }
        }
        std::vector<int> res;
        while(q.size()){
            res.push_back(q.front());
            q.pop();
        }
        return res.size()?res:std::vector<int>{0};
    }
    std::vector<int> findMinHeightTrees_fuck(int n, std::vector<std::vector<int>> &edges){
        std::vector<std::vector<int>> e(n);
        for(auto &p : edges){
            e[p[0]].push_back(p[1]);
            e[p[1]].push_back(p[0]);
        }
        std::function<int(int, int)> _dfs = [&](int i, int pre){
            int res = 0;
            for(auto & to : e[i]){
                if(to==pre)continue;
                res = std::max(res, _dfs(to, i));
            }
            return res + 1;
        };
        std::vector<int> dep(n);
        for(int i=0; i<n; ++i)dep[i]=_dfs(i, -1);
        int min_ = *std::min_element(dep.begin(), dep.end());
        std::vector<int> res;
        for(int i=0; i<n; ++i){
            if(dep[i]==min_)res.push_back(i);
        }
        return res;
    }
//127. 单词接龙
    int ladderLength(std::string &beginWord, std::string endWord, std::vector<std::string> &wordList){
        std::unordered_map<std::string, std::vector<std::string>> e;
        std::function<bool(std::string& , std::string &)> _can = [&](std::string &a, std::string &b){
            int n = 0;
            for(int i=0; i<a.length(); ++i){
                if(a[i]!=b[i] && ++n>1)return false;
            }
            return true;
        };
        int size = wordList.size();
        for(int i=0; i<size; ++i){
            for(int j=i+1; j<size; ++j){
                if(_can(wordList[i], wordList[j])){
                    e[wordList[i]].push_back(wordList[j]);
                    e[wordList[j]].push_back(wordList[i]);
                }
            }
        }
        for(auto &s : wordList){
            if(_can(beginWord, s)){
                e[beginWord].push_back(s);
                e[s].push_back(beginWord);
            }
        }
        std::queue<std::string> q;
        q.push(beginWord);
        int step = 0;
        std::unordered_set<std::string> vi;
        vi.insert(beginWord);
        while(q.size()){
            ++step;
            int size = q.size();
            while(size--){
                auto cur = q.front();q.pop();
                for(auto &s : e[cur]){
                    if(s==endWord)return step;
                    if(vi.count(s))continue;
                    vi.insert(s);
                    q.push(s);
                }
            }
        }
        for(auto &ss : e){
            std::cout<<ss.first<<"--  ";
            for(auto s : ss.second){
                std::cout<<s<<"  ";
            }
            std::cout<<std::endl;
        }
        return 0;
    }
//909. 蛇梯棋
    int snackAndLadders(std::vector<std::vector<int>> &board){
        int N = board.size();
        std::function<int(int)> _calc = [&](int n){
            int row = N - 1 - (n-1)/N;
            int col = (row&1)!=(N&1)?(n-1)%N:N - 1 - (n-1)%N;
            return row*N + col; };
        std::unordered_set<int> vi;
        std::queue<int> q;
        q.push(1);
        int step = 0;
        while(q.size()){
            ++step;
            int size = q.size();
            while(size--){
                int cur = q.front(); q.pop();
                for(int i=cur+1; i<=std::min(cur+6, N*N); ++i){
                    int to = _calc(i);
                    if(i==N*N)return step;
                    int i1 = to / N;
                    int j1 = to % N;
                    int ne = board[i1][j1]==-1?i:board[i1][j1];
                    if(ne==N*N)return step;
                    if(vi.count(ne))continue;
                    vi.insert(ne);
                    q.push(ne);
                }
            }
        }
        return -1;
    }
//1036. 逃离大迷宫
    bool isEscapePossiable(std::vector<std::vector<int>> &blocked,
            std::vector<int> &source, std::vector<int> &target){
#define ll(n) (static_cast<long long>(n))
        long long limit = 1e6;
        std::vector<int> _fun = {0, 1, 0, -1, 0};
        std::unordered_set<long long> bl;
        for(auto &p : blocked){
            bl.insert(ll(p[0])*(limit)+ll(p[1]));
        }
        std::function<bool(std::vector<int> &, std::vector<int> &)> _bfs
            = [&](std::vector<int> &t, std::vector<int> &b){
                std::unordered_set<long long> vi;
                vi.insert(ll(t[0])*limit + ll(t[1]));
                std::queue<long long> q;
                q.push(ll(t[0])*limit + ll(t[1]));
                while(q.size()){
                    long long c = q.front();q.pop();
                    long long i = c / limit;
                    long long j = c % limit;
                    for(int f=0; f<4; ++f){
                        long long i1 = i + _fun[f];
                        long long j1 = j + _fun[f+1];
                        if(i1<0 || j1<0 || i1>=limit || j1>=limit)continue;
                        if(i1==b[0] && j1==b[1])return true;
                        long long p = i1 * limit + j1;
                        if(vi.count(p) || bl.count(p))continue;
                        vi.insert(p);
                        q.push(p);
                    }
                    if(vi.size()==20000)return true;
                }
                return false;
        };
        return _bfs(target, source) && _bfs(source, target);
    }
//1129. 颜色交替的最短路径
    std::vector<int> shortestAlternatingPaths_bfs
        (int n, std::vector<std::vector<int>> &red_edges, std::vector<std::vector<int>> &blue_edges){
            std::vector<std::vector<int>> re(n);
            std::vector<std::vector<int>> be(n);
            std::vector<std::vector<int>> temp;
            for(auto &p : red_edges) re[p[0]].push_back(p[1]);
            for(auto &p : blue_edges)be[p[0]].push_back(p[1]);
            bool vi[n][n][2];
            memset(vi, false, sizeof vi);
            std::vector<int> res(n, INT_MAX);
            std::queue<std::pair<int, int>> q;
            q.push({0, 1});
            q.push({0, 0});
            int step = 0;
            while(q.size()){
                int size = q.size();
                ++step;
                for(int i=0; i<size; ++i){
                    auto [cur, color] = q.front();q.pop();
                    color?temp=re:temp=be;
                    for(auto &to : temp[cur]){
                        if(!vi[cur][to][!color]){
                            vi[cur][to][!color] = true;
                            res[to] = std::min(res[to], step);
                            q.push({to, !color});
                        }
                    }
                }
            }
            res[0] = 0;
            for(int i=1; i<n; ++i)if(res[i]==INT_MAX)res[i]=-1;
            return res;
        }

    std::vector<int> shortestAlternatingPaths
        (int n, std::vector<std::vector<int>> &red_edges, std::vector<std::vector<int>> &blue_edges){
        int INF = 0x3f3f3f3f;
        std::vector<std::vector<int>> rd(n), bu(n);
        for(auto &p : red_edges) rd[p[0]].push_back(p[1]);
        for(auto &p : blue_edges)bu[p[0]].push_back(p[1]);
        std::vector<std::vector<std::vector<int>>> g{rd, bu};
        std::function<void(int, int, std::vector<std::vector<int>>&)> _dfs
            = [&](int i, int c, std::vector<std::vector<int>> &ans){
                for(auto &t : g[c][i]){
                    if(ans[i][c]+1 < ans[t][!c]){
                        ans[t][!c] = ans[i][c] + 1;
                        _dfs(t, !c, ans);
                    }
                }
        };
        std::vector<std::vector<int>> ans(n, {INF, INF});
        ans[0] = {0,0};
        _dfs(0, 0, ans);
        _dfs(0, 1, ans);
        std::vector<int> res(n);
        for(int i=0; i<n; ++i){
            res[i] = std::min(ans[i][0],ans[i][1]);
            if(res[i]==INF)res[i] = -1;
        }
        return res;
    }
//1263. 推箱子
    int PushBox_better(std::vector<std::vector<int>> &grid){
        std::vector<int> _fun = {-1, 0, 1, 0, -1};
        int m = grid.size();
        int n = grid[0].size();
        int b_x, b_y;
        int p_x, p_y;
        int e_x, e_y;
        for(int i=0; i<m; ++i){
            for(int j=0; j<n; ++j){
                if(grid[i][j]=='B'){
                    b_x = i;
                    b_y = j;
                    std::cout<<i<<"-----"<<j<<std::endl;
                }else if(grid[i][j]=='T'){
                    e_x = i;
                    e_y = j;
                }else if(grid[i][j]=='S'){
                    p_x = i;
                    p_y = j;
                }
            }
        }
        struct _node{
            int bx, by, px, py;
            _node(){};
            _node(int bx1, int by1, int px1, int py1) : bx(bx1), by(by1), px(px1), py(py1) {}
            int _key() const {return ((bx*20+by)<<16) | (px*20+py);}
        };
        std::function<bool(_node &, int, int)> _can_arrive = [&](_node &cur, int tx, int ty){
            std::vector<int> vi(n*m+2);
            std::function<bool(int, int)> _dfs = [&](int x, int y){
                if(x<0 || y<0 || x>=m || y>=n || grid[x][y]=='#')return false;
                if(vi[x*n + y]++)return false;
                if(x==cur.bx && y==cur.by)return false;
                if(x==tx && y==ty)return true;
                return _dfs(x+1,y) || _dfs(x, y+1) || _dfs(x-1, y) || _dfs(x, y-1);
            };
            return _dfs(cur.px, cur.py);
        };
        std::function<bool(_node &, int , int, _node&)> _can_push = [&](_node &cur, int fx, int fy, _node &after){
            int btx = cur.bx + fx;
            int bty = cur.by + fy;
            if(btx<0 || bty<0 || btx>=m || bty>=n || grid[btx][bty]=='#')return false;
            int ptx = cur.bx - fx;
            int pty = cur.by - fy;
            if(!_can_arrive(cur, ptx, pty))return false;
            after = {btx, bty, cur.bx, cur.by};
            return true;
        };
        std::unordered_set<int> vi;
        _node start = {b_x, b_y, p_x, p_y};
        vi.insert(start._key());
        std::queue<_node> q;
        q.push(start);
        int step = 0;
        while(q.size()){
            int size = q.size();
            ++step;
            while(size--){
                auto cur = q.front(); q.pop();
                for(int i=0; i<4; ++i){
                    _node a_node;
                    if(!_can_push(cur, _fun[i], _fun[i+1], a_node)
                         || vi.count(a_node._key()))continue;
                    if(a_node.bx==e_x && a_node.by==e_y)return step;
                    vi.insert(a_node._key());
                    q.push(a_node);
                }
            }
        }
        return -1;
    }
    int PushBox(std::vector<std::vector<int>> &grid){
        std::vector<std::vector<int>> _fun = {{1,0}, {0, 1}, {-1,0}, {0,-1}};
        int m = grid.size();
        int n = grid[0].size();
        int b_x, b_y;
        int s_x, s_y;
        int e_x, e_y;
        for(int i=0; i<m; ++i){
            for(int j=0; j<n; ++j){
                if(grid[i][j]=='B'){
                    grid[i][j] = '.';
                    b_x = i;
                    b_y = j;
                }else if(grid[i][j]=='T'){
                    grid[i][j] = '.';
                    e_x = i;
                    e_y = j;
                }else if(grid[i][j]=='S'){
                    grid[i][j] = '.';
                    s_x = i;
                    s_y = j;
                }
            }
        }
        struct _node{
            int bx,  by, sx, sy;
            _node(int bx1, int by1, int sx1, int sy1) :
                bx(bx1), by(by1), sx(sx1), sy(sy1) {}
        };
        int di[m][n][m][n];
        memset(di, -1, sizeof di);
        di[b_x][b_y][s_x][s_y] = 0;
        std::queue<_node> q;
        q.push({b_x, b_y, s_x, s_y});
        while(q.size()){
            std::queue<_node> tmp;
            while(q.size()){
                auto node = q.front();q.pop();
                for(auto &f : _fun){
                    int sx1 = node.sx + f[0];
                    int sy1 = node.sy + f[1];
                    if(sx1<0||sy1<0||sx1>=m||sy1>=n)continue;
                    if(node.bx==sx1 && node.by==sy1){
                        int bx1 = node.bx + f[0];
                        int by1 = node.by + f[1];
                        if(bx1<0||by1<0||bx1>=m||by1>=n)continue;
                        if(grid[bx1][by1]=='.' && di[bx1][by1][sx1][sy1]==-1){
                            tmp.push({bx1, by1, sx1, sy1});
                            di[bx1][by1][sx1][sy1] = di[node.bx][node.by][node.sx][node.sy] + 1;
                            if(bx1==e_x && by1==e_y)return di[bx1][by1][sx1][sy1];
                        }
                    }else if(grid[sx1][sy1]=='.' && di[node.bx][node.by][sx1][sy1]==-1){
                        q.push({node.bx, node.by, sx1, sy1});
                        di[node.bx][node.by][sx1][sy1] = di[node.bx][node.by][node.sx][node.sy];
                    }
                }
            }
            q = tmp;
        }
        return -1;
    }
//1162. 地图分析
    int maxDistance_dij(std::vector<std::vector<int>> &grid){
        struct _node{
            int i, j, d;
            _node(int _i, int _j, int _d) : i(_i), j(_j), d(_d) {}
            bool operator < (const _node& b) const {return this->d > b.d;}
        };
        int INF = 0x3f3f3f3f;
        int m   = grid.size();
        int n   = grid[0].size();
        std::vector<std::vector<int>> _fun = {{1,0}, {0, 1}, {-1, 0}, {0, -1}};
        std::priority_queue<_node> q;
        std::vector<std::vector<int>> di(m, std::vector<int>(n, INF));
        //bool vi[m][n];
        //memset(vi, false, sizeof vi);
        for(int i=0; i<m; ++i){
            for(int j=0; j<n; ++j){
                if(grid[i][j])di[i][j] = 0,q.push({i, j, 0});
            }
        }
        while(q.size()){
            auto node = q.top();q.pop();
            int x     = node.i;
            int y     = node.j;
            //if(vi[x][y])continue;
            //vi[x][y]  = 1;
            for(auto &f : _fun){
                int i1 = x + f[0];
                int j1 = y + f[1];
                if(i1<0 || j1<0 || i1>=m || j1>=n)continue;
                if(di[i1][j1] <= node.d+1)continue;
                di[i1][j1] = node.d + 1;
                q.push({i1, j1, di[i1][j1]});
            }
        }
        int res = -1;
        for(auto &l : di)res = std::max(res, *std::max_element(l.begin(), l.end()));
        return res==INF||res==0 ? -1 : res;
    }
    int maxDistance(std::vector<std::vector<int>> &grid){
        struct _node{
            int x,y,l;
            _node(int _x, int _y, int _l) : x(_x), y(_y), l(_l){}
        };
        std::vector<std::vector<int>> _fun = {{0, 1},{1, 0}, {0, -1}, {-1, 0}};
        int m = grid.size();
        int n = grid[0].size();
        std::function<int(int, int)> _bfs = [&](int i, int j){
            bool vi[m][n];
            memset(vi, false, sizeof vi);
            std::queue<_node> q;
            q.push({i, j, 0});
            vi[i][j] = 1;
            while(q.size()){
                auto node = q.front();q.pop();
                int x = node.x;
                int y = node.y;
                for(auto &f : _fun){
                    int i1 = x + f[0];
                    int j1 = y + f[1];
                    if(i1<0 || j1<0 ||i1>=m || j1>=n)continue;
                    if(grid[i1][j1])return node.l+1;
                    if(vi[i1][j1])continue;
                    q.push({i1, j1, node.l+1});
                    vi[i1][j1] = 1;
                }
           }
            return -1;
        };
        int res = -1;
        for(int i=0; i<m; ++i){
            for(int j=0; j<n; ++j){
                if(!grid[i][j])res = std::max(res, _bfs(i, j));
            }
        }
        return res;
    }
//1293. 网格中的最短路径
    int shorestPath_bfs(std::vector<std::vector<int>> &grid, int k){
        int m = grid.size();
        int n = grid[0].size();
        if (k >=m+n-3) return m+n-2;
        struct _node{
            int i,j,l;
            _node(int _i, int _j, int _l) : i(_i), j(_j), l(_l){}
        };
        std::vector<std::vector<int>> _fun = {{0, 1},{1, 0}, {0, -1}, {-1, 0}};
        bool vi[m][n][k+1];
        memset(vi, false, sizeof vi);
        std::queue<_node> q;
        k = std::min(k, m+n-3);
        q.push({0,0,k});
        int res = 0;
        while(q.size()){
            ++res;
            int size = q.size();
            for(int i=0; i<size; ++i){
                auto node = q.front();q.pop();
                int x = node.i;
                int y = node.j;
                for(auto &f : _fun){
                    int i1 = x + f[0];
                    int j1 = y + f[1];
                    if(i1<0 || j1<0 || i1>=m || j1>=n)continue;
                    if(i1==m-1 && j1==n-1)return res;
                    int t1 = node.l - grid[i1][j1];
                    if(t1>=0 && !vi[i1][j1][t1])q.push({i1, j1, t1}), vi[i1][j1][t1]=1;
                }
            }
        }
        return -1;
    }
    int shorestPath_dfs(std::vector<std::vector<int>> &grid, int k){
        int m   = grid.size();
        int n   = grid[0].size();
        if (k >=m+n-3) return m+n-2;
        int res = INT_MAX;
        std::vector<std::vector<int>> _fun = {{0, 1},{1, 0}, {0, -1}, {-1, 0}};
        std::vector<std::vector<std::vector<int>>> vi(m, std::vector<std::vector<int>>(n, std::vector<int>(k+1)));
        std::function<void(int, int, int, int)> _dfs = [&](int t, int i, int j, int r){
            if(t<0)return;
            if(r > res)return;
            if(i==m-1 && j==n-1){
                res = r;
                return;
            }
            vi[i][j][t] = 1;
            for(auto &f : _fun){
                int i1 = i + f[0];
                int j1 = j + f[1];
                if(i1<0 || j1<0 || i1>=m || j1>=n || vi[i1][j1][t])continue;
                _dfs(t-grid[i1][j1], i1, j1, r+1);
            }
        };
        _dfs(k, 0, 0, 0);
        return res==INT_MAX?-1:res;
    }
//1368. 使网格图至少有一条有效路径的最小代价
    int minCost_0_1_bfs(std::vector<std::vector<int>> &grid){
        int INF = 0x3f3f3f3f;
        int m = grid.size();
        int n = grid[0].size();
        std::vector<std::vector<int>> _fun = {{0,0},{0,1},{0,-1},{1,0},{-1,0}};
        std::vector<int> di(n*m, INF);
        std::vector<int> vi(n*m);
        vi[0] = 1;
        di[0] = 0;
        std::deque<int> q;
        q.push_front(0);
        while(q.size()){
            int pos = q.front();q.pop_front();
            if(vi[pos])continue;
            vi[pos] = 1;
            int i = pos / n;
            int j = pos % n;
            for(int f=1; f<=4; ++f){
                int i1 = i + _fun[f][0];
                int j1 = j + _fun[f][1];
                int new_pos = i1*n + j1;
                int new_dis = di[pos] + (grid[i][j]!=f);
                if(i1>=0 && j1>=0 && i1<m && j1<n && di[new_pos] > new_dis){
                    di[new_pos] = new_dis;
                    if(grid[i][j]==f){
                        q.push_front(new_pos);
                    }else{
                        q.push_back(new_pos);
                    }
                }
            }
        }
        return di[n*m-1];
    }
    int minCost_dij(std::vector<std::vector<int>> &grid){
        typedef std::pair<int, int> pii;
        int INF = 0x3f3f3f3f;
        int m   = grid.size();
        int n   = grid[0].size();
        std::vector<std::vector<int>> _fun = {{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        std::vector<int> di(m*n, INF);
        std::vector<int> vi(m*n);
        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
        q.push({0, 0});
        di[0] = 0;
        while(q.size()){
            auto[dis, pos] = q.top();q.pop();
            if(vi[pos])continue;
            vi[pos] = 1;
            int i   = pos / n;
            int j   = pos % n;
            for(int f=1; f<=4; ++f){
                int i1 = i + _fun[f][0];
                int j1 = j + _fun[f][1];
                int new_pos = i1 * n + j1;
                int new_dis = dis + (grid[i][j] != f);
                if(i1>=0 && j1>=0 && i1<m && j1<n && new_dis < di[new_pos]){
                    di[new_pos] = new_dis;
                    q.push({new_dis, new_pos});
                }
            }
        }
        return di[m*n-1];
    }
    int minCost_spf(std::vector<std::vector<int>> &grid){
        int INF   = 0x3f3f3f3f;
        int m     = grid.size();
        int n     = grid[0].size();
        std::vector<std::vector<int>> _fun = {{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        std::vector<int> di(m*n, INF);
        std::vector<int> vi(m*n);
        std::queue<int> q;
        q.push( 0);
        di[0] = 0;
        vi[0] = 1;
        while(q.size()){
            auto pos = q.front();q.pop();
            vi[pos] = 0;
            int i   = pos / n;
            int j   = pos % n;
            for(int f=1; f<=4; ++f){
                int i1 = i + _fun[f][0];
                int j1 = j + _fun[f][1];
                int new_pos = i1 * n + j1;
                int new_dis = di[pos] + (grid[i][j] != f);
                if(i1<0 || j1<0 || i1>=m || j1>=n)continue;
                if(di[new_pos] > new_dis){
                    di[new_pos] = new_dis;
                    if(!vi[new_pos])q.push(new_pos), vi[new_pos]=1;
                }
            }
        }
        return di[n*m-1];
    }
};
