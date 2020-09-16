/*********************************************
*     ------------------------
*     ------------------------
*     file name: WEEK206.cpp
*     author   : @ JY
*     date     : 2020--09--13
**********************************************/
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <numeric>

class Solution{
    public:
//5514. 检查字符串是否可以通过排序子字符串得到另一个字符串
        bool isTransformable(std::string s, std::string t){
            std::vector<std::queue<int>> vq;
            for(int i=0; i<s.length(); ++i){
                vq[s[i]-'0'].push(i);
            }
            for(int i=0; i<t.length(); ++i){
                int x = t[i] - '0';
                if(!vq[x].size())return false;
                for(int j=0; j<x; ++j){
                    if(vq[j].size() && vq[j].front() < vq[x].front()){
                        return false;
                    }
                }
                vq[x].pop();
            }
            return true;
        }
//5513. 连接所有点的最小费用
        struct Node{
            int i, j, d;
            Node(int i1, int j1, int d1) : i(i1), j(j1), d(d1) {}
            bool operator < (const Node &a){return d < a.d; }
        };
        int minCostConnectPoints_better(std::vector<std::vector<int>> &points){
            typedef  std::pair<int,int> pii;
            typedef  std::vector<pii> vpii;
            struct _cmp{
                bool operator()(const pii &a, const pii &b){
                    return a.second > b.second; }
            };
            int n = points.size();
            std::vector<vpii> edges(n);
            for(int i=0; i<n; ++i){
                int i1 = points[i][0];
                int j1 = points[i][1];
                for(int j=i+1; j<n; ++j){
                    int d = abs(i1-points[j][0]) + abs(j1-points[j][1]);
                    edges[i].push_back({j, d});
                    edges[j].push_back({i, d});
                }
            }
            std::vector<bool> _vi(n);
            std::priority_queue<pii,vpii,_cmp> q;
            _vi[0] = true;
            for(auto &p : edges[0])q.push(p);
            int total = n - 1;
            int res   = 0;
            while(q.size()){
                auto [to, dis] = q.top();q.pop();
                if(_vi[to])continue;
                _vi[to] = true;
                res += dis;
                if(!--total)return res;
                for(auto &p : edges[to])q.push(p);
            }
            return res;
        }
        std::vector<int> _f;
        std::vector<Node> e;
        int minCostConnectPoints(std::vector<std::vector<int>> &points){
            int n = points.size();
            for(int i=0; i<n; ++i)_f.push_back(i);
            std::function<int(int)> _find = [&](int i){
                return _f[i]==i?i:_f[i]=_find(_f[i]); };
            for(int i=0; i<n; ++i){
                int xi = points[i][0];
                int yi = points[i][1];
                for(int j=i+1; j<n; ++j){
                    int d = abs(xi-points[j][0]) + abs(yi-points[j][1]);
                    e.push_back({i, j, d});
                }
            }
            std::sort(e.begin(), e.end());
            int res = 0;
            int num = n - 1;
            for(auto &g : e){
                int a = _find(g.i);
                int b = _find(g.j);
                if(a==b)continue;
                _f[a] = b;
                res += g.d;
                if(!--num)return res;
            }
            return res;
        }
//5512. 统计不开心的朋友
        int unhappyFriends(int n, std::vector<std::vector<int>> &preferences, std::vector<std::vector<int>> &pairs){
            int res = 0;
            std::function<int(int, int)> _f = [&](int i, int f1){
                int res = 0;
                for(; res<n&&preferences[i][res]!=f1; ++res);
                return res;
            };
            std::vector<int> vi(n);
            std::function<void(int, int)> _dfs = [&](int a, int b){
                int ok = _f(a, b);
                for(auto &p :pairs){
                    int f1 = p[0];
                    int f2 = p[1];
                    if(f1==a || f1==b)continue;
                    for(int i=0; i<2; ++i){
                        std::swap(f1, f2);
                        if(_f(a, f1)>=ok)continue;
                        if(_f(f1, a) >= _f(f1, f2))continue;
                        vi[a] = res += vi[a]==0;
                    }
                }
            };
            for(auto &p : pairs)_dfs(p[0], p[1]), _dfs(p[1], p[0]);
            return res;
        }
//5511. 二进制矩阵中的特殊位置
        int numSpecial(std::vector<std::vector<int>>& mat){
            int m = mat.size();
            int n = mat[0].size();
            std::function<bool(int i, int j)> _calc = [&](int i, int j){
                int tt = i;
                while(tt<m)if(mat[tt++][j])return false;
                tt = i;
                while(tt>=0)if(mat[tt--][j])return false;
                tt = j;
                while(tt<n)if(mat[i][tt++])return false;
                tt = j;
                while(tt>=0)if(mat[i][tt--])return false;
                return true;
            };
            int res = 0;
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    if(mat[i][j] || _calc(i, j))break;
                    ++res;
                }
            }
            return res;
        }
};
