/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_uf_pro.cpp
*     author   : @ JY
*     date     : 2020--10--27
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <climits>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <queue>
#include <stdlib.h>

class Solution{
    public:
<<<<<<< HEAD
//最低成本联通所有城市
        int minimumCost_prim(int N, std::vector<std::vector<int>> &connections){
            using pii = std::pair<int, int>;
            std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
            std::vector<std::vector<pii>> e(N);
            std::vector<int> vi(N);
            for(auto &c : connections){
                e[c[0]-1].emplace_back(c[2], c[1]-1);
                e[c[1]-1].emplace_back(c[2], c[0]-1);
            }
            int res = 0;
            for(auto &x : e[0])q.push(x);
            vi[0] = 1;
            while(q.size()){
                auto [dis, to] = q.top();q.pop();
                if(vi[to])continue;
                res += dis;
                vi[to] = 1;
                --N;
                for(auto &[d, t] : e[to]){
                    if(!vi[t]){
                        q.emplace(d, t);
                    }
                }
            }
            return N==1 ? res : -1;
        }
//给你一些可连接的选项 conections，其中每个选项 conections[i] = [city1, city2, cost] 表示将城市 city1 和城市 city2 连接所要的成本。（连接是双向的，也就是说城市 city1 和城市 city2 相连也同样意味着城市 city2 和城市 city1 相连）。
        int minimumCost_kru(int N, std::vector<std::vector<int>> &connections){
            std::vector<int> _f(N);
            std::iota(begin(_f), end(_f), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i] == i ? i : _f[i] = _find(_f[i]); };
            std::sort(begin(connections), end(connections), [&](auto &a, auto &b){
                return a[2] < b[2]; });
            int res = 0;
            for(auto &c : connections){
                int pa = _find(c[0]-1), pb = _find(c[1]-1);
                if(pa == pb)continue;
                res += c[2];
                _f[pa] = pb;
                if(--N == 1)break;
            }
            return N==1 ? res : -1;
        }

//以图判树（全部连通+边数=V-1）
////给定从 0 到 n-1 标号的 n 个结点，和一个无向边列表（每条边以结点对来表示 请编写一个函数用来判断这些边是否能够形成一个合法有效的树结构。
        bool validTree(int n, std::vector<std::vector<int>> &edges){
            std::vector<int> _f(n);
            std::iota(begin(_f), end(_f), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i] == i ? i : _f[i] = _find(_f[i]); };
            for(auto &p : edges){
                int pa = _find(p[0]);
                int pb = _find(p[1]);
                if(pa == pb)return false;
                --n;
            }
            return n == 1;
        }
//737. 句子相似性 II
//给定两个句子 words1, words2 （每个用字符串数组表示），和一个相似单词对的列表 pairs ，判断是否两个句子是相似的。
//例如，当相似单词对是 pairs = [["great", "fine"], ["acting","drama"], ["skills","talent"]]的时候，words1 = ["great", "acting", "skills"] 和 words2 = ["fine", "drama", "talent"] 是相似的
        bool areSenrencesSimilarTwo(std::vector<std::string> &words1,
                                    std::vector<std::string> &words2,
                                    std::vector<std::vector<std::string>> &pairs){
            std::unordered_map<std::string, int> mp;
            int n = 0, len = words1.size();
            if(len != words2.size())return false;
            for(auto &p : pairs){
                if(!mp.count(p[0]))mp[p[0]] = n++;
                if(!mp.count(p[1]))mp[p[1]] = n++;
            }
            std::vector<int> _f(n);
            std::function<int(int)> _find = [&](int i){
                return _f[i] == i ? i : _f[i] = _find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                _f[_find(a)] = _find(_f[b]); };
            std::iota(begin(_f), end(_f), 0);
            for(auto &p : pairs){
                _union(mp[p[0]], mp[p[1]]);
            }
            for(int i=0; i<len; ++i){
                auto w1 = words1[i], w2 = words2[i];
                if(w1 == w2)continue;
                if(!mp.count(w1) || !mp.count(w2))return false;
                if(_find(mp[w1]) != _find(mp[w2]))return false;
            }
            return true;
        }
//LeetCode 1101. 彼此熟识的最早时间（排序+并查集）
//在一个社交圈子当中，有 N 个人。每个人都有一个从 0 到 N-1 唯一的 id 编号。
//我们有一份日志列表 logs，其中每条记录都包含一个非负整数的时间戳，以及分属两个人的不同 id，logs[i] = [timestamp, id_A, id_B]。 每条日志标识出两个人成为好友的时间，友谊是相互的：如果 A 和 B 是好友，那么 B 和 A 也是好友。 如果 A 是 B 的好友，或者 A 是 B 的好友的好友，那么就可以认为 A 也与 B 熟识。 返回圈子里所有人之间都熟识的最早时间。如果找不到最早时间，就返回 -1 。
        int earliestAcq(std::vector<std::vector<int>> &logs, int N){
            std::sort(begin(logs), end(logs), [&](auto &a, auto &b){
                    return a[0] < b[0]; });
            std::vector<int> _f(N);
            std::iota(begin(_f), end(_f), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i] == i ? i : _f[i] = _find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                int pa = _find(a), pb = _find(b);
                if(pa == pb)return;
                _f[pa] = pb;
                --N;
            };
            for(auto &p : logs){
                _union(p[1], p[2]);
                if(N == 1)return p[0];
            }
            return -1;
        }
 //1061. 按字典序排列最小的等效字符串
//给出长度相同的两个字符串：A 和 B，其中 A[i] 和 B[i] 是一组等价字符。
 //举个例子，如果 A = "abc" 且 B = "cde"，那么就有 'a' == 'c', 'b' == 'd', 'c' == 'e'。
//等价字符遵循任何等价关系的一般规则：
//自反性：'a' == 'a' 对称性：'a' == 'b' 则必定有 'b' == 'a' 传递性：'a' == 'b' 且 'b' == 'c' 就表明 'a' == 'c'
//例如，A 和 B 的等价信息和之前的例子一样，
	//那么 S = "eed", "acd" 或 "aab"，这三个字符串都是等价的，
	//而 "aab" 是 S 的按字典序最小的等价字符串
//利用 A 和 B 的等价信息，找出并返回 S 的按字典序排列最小的等价字符串。
        std::string smallestEquivalentString(std::string A, std::string B, std::string S){
            std::vector<int> _f(26);
            std::iota(begin(_f), end(_f), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i] == i ? i : _f[i] = _find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                int pa = _find(a), pb = _find(b);
                if(pa == pb)return;
                if(pa < pb)std::swap(pa, pb);
                _f[pa] = pb;
            };
            int len = A.size();
            for(int i=0; i<len; ++i)_union(A[i]-'a', B[i]-'a');
            std::string res;
            for(auto &c : S)res += _find(c-'a') + 'a';
            return res;
        }
//323.无向连通图中的连通分量个数
//给定编号从 0 到 n-1 的 n 个节点和一个无向边列表（每条边都是一对节点），请编写一个函数来计算无向图中连通分量的数目。
        int countComponents(int n, std::vector<std::vector<int>> edges){
            int cnt = n;
            std::vector<int> _f(n);
            std::iota(begin(_f), end(_f), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i] == i ? i : _f[i] = _find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                int pa = _find(_f[a]), pb = _find(_f[b]);
                if( pa == pb )return;
                _f[pa] = pb;
                --cnt;
            };
            for(auto &p : edges)_union(p[0], p[1]);
            return cnt;
        }
//村里面一共有 n 栋房子。我们希望通过建造水井和铺设管道来为所有房子供水。 对于每个房子 i，我们有两种可选的供水方案：
//一种是直接在房子内建造水井，成本为 wells[i]；
//另一种是从另一口井铺设管道引水，数组 pipes 给出了在房子间铺设管道的成本，其中每个 pipes[i] = [house1, house2, cost] 代表用管道将 house1 和 house2 连接在一起的成本。当然，连接是双向的。
        int minCostToSubpplyWatter(int n, std::vector<int> &wells,
                std::vector<std::vector<int>> &pipes){
            std::vector<int> _f(n+1);
            std::iota(begin(_f), end(_f), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i] == i ? i : _f[i] = _find(_f[i]); };
            struct _node{
                int f, t, val;
                _node(int f, int t, int val) : f(f), t(t), val(val) {}
                bool operator < (const _node &other) const {
                    return val < other.val; }
            };
            std::vector<_node> e;
            for(auto &p : pipes)e.emplace_back(p[0], p[1], p[2]);
            for(int i=1; i<=n; ++i)e.emplace_back(0, i, wells[i-1]);
            int res = 0;
            std::sort(begin(e), end(e));
            for(auto &[f, t, val] : e){
                int pa = _find(f), pb = _find(t);
                if(pa==pb)continue;
                res += val;
                _f[pa] = pb;
                if(--n < 0)break;
            }
            return res;
        }
//305. 岛屿数量 II
//题目描述：m*n的网格区域，刚开始都是水，addLand操作会把某个区域变成陆地；动态求出所有addLand操作后的陆地连通区域数量；
        std::vector<int> numIslandsII(int m, int n, std::vector<std::vector<int>> &pos){
            int cnt = 0;
            std::vector<int> _f(n*m);
            std::iota(begin(_f), end(_f), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i] == i ? i : _f[i] = _find(_f[i]); };
            std::function<void (int, int)> _union = [&](int a, int b){
                int pa = _find(a), pb = _find(b);
                if(pa == pb)return ;
                _f[pa] = pb;
                --cnt;
            };
            std::set<std::pair<int, int>> mp;
            std::vector<int> _fun { 0, 1, 0, -1, 0 };
            std::vector<int> res;
            for(auto &p : pos){
                int x = p[0], y = p[1];
                ++cnt;
                for(int f=0; f<4; ++f){
                    int i = x + _fun[f];
                    int j = y + _fun[f + 1];
                    if(!mp.count({i, j}))continue;
                    _union(i*n+j, x*n+y);
                }
                mp.insert({x, y});
                res.push_back(cnt);
            }
            return res;
        }
//200. 岛屿数量
        int numIslandsI(std::vector<std::vector<int>> &grid){
            int m = grid.size(), n = grid[0].size();
            std::vector<int> _f(n*m);
            std::iota(begin(_f), end(_f), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i] == i ? i : _f[i] = _find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                _f[_find(a)] = _f[_find(b)]; };
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    if(grid[i][j] == '0')continue;
                    if(i && grid[i-1][j] == '1')_union(i*n+j, (i-1) * n + j);
                    if(j && grid[i][j-1] == '1')_union(i*n+j, i * n + j - 1);
                }
            }
            std::unordered_set<int> mp;
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    if(grid[i][j] == '0')continue;
                    mp.insert(_find(i*n+j));
                }
            }
            return mp.size();
        }
=======
>>>>>>> 9769624 (10-28)
//765. 情侣牵手
        int minSwapCouples(std::vector<int> &row){
            int n = row.size(), ans = 0;
            std::vector<int> _f(n/2);
            std::iota(begin(_f), end(_f), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i] == i ? i : _f[i] = _find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                _f[_find(a)] = _f[_find(b)]; };
            for(int i=0; i<n-1; i+=2){
                _union(row[i]/2, row[i+1]/2);
            }
<<<<<<< HEAD
            for(int i=0; i<n/2; ++i)ans += i!=_find(i);
            return ans;
=======
            for(int i=0; i<n/2; ++i)ans += i==_find(i);
            return n/2 - ans;
>>>>>>> 9769624 (10-28)
        }
//Leetcode 1102：得分最高的路径
//给你一个R行C列的整数矩阵A矩阵上的路径从[0,0] 开始在[R-1,C-1]结束路径沿四个基本方向上下左右展开从一个已访问单元格移动到任一相邻的未访问单元格路径的得分是该路径上的最小值例如路径8→4 → 5 → 9 的为。 找出所有路径中得分 最高 的那条路径，返回其 得分。
        int maximumMininumPath(std::vector<std::vector<int>> &A){
            struct _node{
                int i, j, val;
                _node(int i, int j, int val) : i(i), j(j), val(val) {};
                bool operator < (const _node &other) const {
                    return val < other.val; };
            };
            int m = A.size(), n = A[0].size();
            std::vector<int> _fun = {0, 1, 0, -1, 0};
            std::vector<int> vi;
            std::priority_queue<_node> q;
            int res = A[0][0];
            q.push({0, 0, res});
            while(q.size()){
                int i = q.top().i;
                int j = q.top().j;
                res = std::min(res, q.top().val);
                q.pop();
                if(i==m-1 && j==n-1)return res;
                if(vi[i *n + j])continue;
                vi[i * n + j] = 1;
                for(int f=0; f<4; ++f){
                    int i1 = i + _fun[f];
                    int j1 = j + _fun[f+1];
                    if(i1<0 || j1<0 || i1>=m || j1>=n)continue;
                    if(vi[i1*n + j1])continue;
                    q.push({i1, j1, A[i1][j1]});
                }
            }
            return res;
        }
//399. 除法求值
        std::vector<double> clacEquation_uf(
                std::vector<std::vector<std::string>> &equations,
                std::vector<double> &values,
                std::vector<std::vector<std::string>> &queries){
            std::unordered_map<std::string, std::string> _f;
            std::unordered_map<std::string, double> _d;
            std::function<std::string(std::string &)> _find = [&](std::string &i){
                if(_f[i] == i)return i;
                auto p = _find(_f[i]);
                _d[i] *= _d[_f[i]];
                _f[i]  = p;
                return _f[i];
            };
            int len = values.size();
            for(int i=0; i<len; ++i){
                auto s1 = equations[i][0],
                     s2 = equations[i][1];
                _f[s1] = s1, _f[s2] = s2;
                _d[s1] = _d[s2] = 1.0;
            }
            for(int i=0; i<len; ++i){
                auto s1 = equations[i][0];
                auto s2 = equations[i][1];
                auto pa = _find(s1);
                _f[pa] = s2;
                _d[pa] = values[i] / _d[s1];
            }
            std::vector<double> res;
            for(auto &ss : queries){
                std::string s1 = ss[0], s2 = ss[1];
                if(!_f.count(s1) || !_f.count(s2) || _find(s1) != _find(s2)){
                    res.emplace_back(-1.);
                }else{
                    res.emplace_back(_d[s1] / _d[s2]);
                }
            }
            return res;
        }
        std::vector<double> clacEquation_floyd(
                std::vector<std::vector<std::string>> &equations,
                std::vector<double> &values,
                std::vector<std::vector<std::string>> &queries){
            int n = 0, len = values.size();
            std::unordered_map<std::string, int> mp;
            for(int i=0; i<len; ++i){
                std::string s1 = equations[i][0];
                std::string s2 = equations[i][1];
                if(!mp.count(s1)) mp[s1] = n++;
                if(!mp.count(s2)) mp[s2] = n++;
            }
            std::vector<std::vector<double>> e(n, std::vector<double>(n, -1.0));
            for(int i=0; i<n; ++i)e[i][i] = 1.0;
            for(int i=0; i<len; ++i){
                std::string s1 = equations[i][0],
                            s2 = equations[i][1];
                e[mp[s1]][mp[s2]] = values[i];
                e[mp[s2]][mp[s1]] = 1. / values[i];
            }
            std::function<void(void)> _floyd = [&](void){
                for(int i=0; i<n; ++i){
                    for(int j=0; j<n; ++j){
                        for(int k=0; k<n; ++k){
                            if(e[j][i] >=0 && e[i][k]>=0){
                                e[j][k] = e[j][i] * e[i][k];
                            }
                        }
                    }
                }
            };
            _floyd();
            std::vector<double> res;
            for(auto &ss : queries){
                std::string s1 = ss[0], s2 = ss[1];
                if(!mp.count(s1) ||
                     !mp.count(s2) ||
                      e[mp[s1]][mp[s2]]<0){
                    res.emplace_back(-1.0);
                }else{
                    res.emplace_back(e[mp[s1]][mp[s2]]);
                }
            }
            return res;
        }
        std::vector<double> clacEquation(
                std::vector<std::vector<std::string>> &equations,
                std::vector<double> &values,
                std::vector<std::vector<std::string>> &queries){
            struct _node{
                std::string _name;
                double val;
                _node(std::string &s, double v) : _name(s), val(v) {};
            };
            std::unordered_map<std::string, std::vector<_node>> e;
            int len = values.size();
            for(int i=0; i<len; ++i){
                std::string n1 = equations[i][0];
                std::string n2 = equations[i][1];
                e[n1].emplace_back(n2, values[i]);
                e[n2].emplace_back(n1, 1. / values[i]);
            }
            //for(auto &[s, v] : e){
                //std::cout<<s<<std::endl;
                //for(auto &[n, k] : v){
                    //std::cout<<n<<"   "<<k<<std::endl;
                //}
                //std::cout<<"----------------"<<std::endl;
            //}
            std::unordered_set<std::string> vi;
            std::function<double(std::string &, std::string &)> _dfs
                = [&](std::string &a, std::string &b){
                    if(!e.count(a) || !e.count(b))return -1.;
                    if(!a.compare(b))return 1.0;
                    double ans;
                    for(auto &[s, val] : e[a]){
                        if(!vi.insert(s).second)continue;
                        if((ans = _dfs(s, b)) > 0){
                            return val * ans;
                        }
                    }
                    return -1.0;
                };
            std::vector<double> res;
            for(auto &ss : queries){
                vi = {};
                res.emplace_back(_dfs(ss[0], ss[1]));
            }
            return res;
        }
//803. 打砖块
        std::vector<int> hitBricks(std::vector<std::vector<int>> &grid,
                std::vector<std::vector<int>> &hits){
            int m = grid.size(), n = grid[0].size();
<<<<<<< HEAD
            std::vector<int> _fun {0, 1, 0, -1, 0};
=======
            std::vector<int> _fun {0, 1, 0, -1, 0, -1};
>>>>>>> 9769624 (10-28)
            std::vector<int> _f(n*m+1), _n(n*m+1, 1);
            std::iota(begin(_f), end(_f), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i] == i ? i : _f[i] = _find(_f[i]); };
            std::function<int(void)> _top = [&](void){
                return _n[_find(_f.size() - 1)]; };
            std::function<void(int, int)> _union = [&](int a, int b){
                int pa = _find(a), pb = _find(b);
                if(pa == pb)return;
                _f[pa]  = pb;
                _n[pb] += _n[pa];
            };
            for(auto &p : hits){
                if(grid[p[0]][p[1]]){
                    grid[p[0]][p[1]] = 0;
                }else{
                    p[0] = -1;
                }
            }
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    if(!grid[i][j])continue;
                    if(!i)_union(i*n+j, n*m);
                    if(i && grid[i-1][j])_union(i*n+j, (i-1) * n + j);
                    if(j && grid[i][j-1])_union(i*n+j, i * n + j - 1);
                }
            }
            int len = hits.size();
            std::vector<int> res(len);
            for(int i=len-1; i>=0; --i){
                int x = hits[i][0], y = hits[i][1];
                if(x==-1)continue;
                grid[x][y] = 1;
                int pre = _top();
                if(!x)_union(x*n+y, n*m);
                for(int f=0; f<4; ++f){
                    int x1 = x + _fun[f];
                    int y1 = y + _fun[f+1];
                    if(x1<0 || y1<0 || x1>=m || y1>= n)continue;
                    if(!grid[x1][y1])continue;
                    _union(x*n+y, x1*n+y1);
                }
                res[i] = std::max(0, _top() - pre - 1);
            }
            return res;
        }
//952. 按公因数计算最大组件大小
        int largestComponentSize_better(std::vector<int> &A){
            int len = A.size(), max_ = 0;
            std::vector<int> _f(100001), _n(100001, 1), _ispri(100001, 1), _hs(100001, -1);
            for(int i=0; i<len; ++i){
                max_  = std::max(max_, A[i]);
                _f[i] = i;
                _hs[A[i]] = i;
            }
            std::function<int(int)> _find = [&](int i){
                return _f[i] == i ? i : _f[i] = _find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                int pa = _find(a), pb = _find(b);
                if(pa == pb)return;
                _f[pa]  = pb;
                _n[pb] += _n[pa];
            };
            for(int i=2; i<=max_; ++i){
                if(!_ispri[i])continue;
                int t = _hs[i] >= 0 ? _hs[i] : -1;
                for(int j=i+i; j<=max_; j+=i){
                    if(_hs[j]>=0){
                        if(t==-1){
                            t = _hs[j];
                        }else{
                            _union(t, _hs[j]);
                        }
                    }
                    _ispri[j] = 1;
                }
            }
            return *std::max_element(begin(_n), end(_n));
        }
        int largestComponentSize(std::vector<int> &A){
            std::vector<int> _f(100001), _n(100001, 1);
            std::iota(begin(_f), end(_f), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i] == i ? i : _f[i] = _find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                int pa = _find(a), pb = _find(b);
                if(pa == pb)return;
                _f[pa]  = pb;
                _n[pb] += _n[pa];
            };
            std::function<int(int, int)> _gcd = [&](int a, int b){
                return b ? _gcd(b, a%b) : 0; };
            int len = A.size();
            for(int i=0; i<len; ++i){
                for(int j=i+1; j<len; ++j){
                    if(_gcd(A[i], A[j]) < 2)continue;
                    _union(A[i], A[j]);
                }
            }
            return *std::max_element(begin(_n), end(_n));
        }
//685. 冗余连接 II
        std::vector<int> findRedunDantDirectedConnection(std::vector<std::vector<int>> &edges){
            int n = edges.size();
            std::vector<int> in(n), in2, _f(n);
            for(auto &e : edges)++in[e[1]-1];
            for(int i=n-1; i>=0; --i){
                if(in[edges[i][1]-1] == 2)in2.push_back(i);
            }
            std::function<int(int)> _find = [&](int i){
                return _f[i] == i ? i : _f[i] = _find(_f[i]); };
            std::function<bool(int)> _del_in2_ok = [&](int t){
                int k = n;
                std::iota(begin(_f), end(_f), 0);
                for(int i=0; i<n; ++i){
                    if(i == t)continue;
                    int pa = _find(edges[i][0]-1), pb = _find(edges[i][1]-1);
                    if(pa == pb)return false;
                    _f[pa] = pb;
                    --k;
                }
                return k==1;
            };
            if(in2.size()){
                if(_del_in2_ok(in2[0])){
                    return edges[in2[0]];
                }else{
                    return edges[in2[1]];
               }
            }
            std::iota(begin(_f), end(_f), 0);
            for(auto &e : edges){
                int pa = _find(e[0]-1), pb = _find(e[1]-1);
                if(pa == pb)return e;
                _f[pa] = pb;
            }
            return {-1, -1};
        }
//684. 冗余连接
        std::vector<int> findRedunantConnection(std::vector<std::vector<int>> &edges){
            std::vector<int> _f(1001);
            std::iota(begin(_f), end(_f), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i] == i ? i : _f[i] = _find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                _f[_find(a)] = _f[_find(b)]; };
            for(auto &p : edges){
                if(_find(p[0]) == _find(p[1]))return p;
                _union(p[0], p[1]);
            }
            return {};
        }
//990. 等式方程的可满足性
        bool equationsPossible(std::vector<std::string> &equations){
            std::vector<int> _f(26);
            std::iota(begin(_f), end(_f), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i] == i ? i : _f[i] = _find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                _f[_find(a)] = _f[_find(b)]; };
            for(auto &e : equations){
                if(e[1] == '!')continue;
                _union(e[0]-'a', e[3]-'a');
            }
            for(auto &e : equations){
                if(e[1] != '!')continue;
                if(_find(e[0]-'a') == _find(e[3]-'a'))return false;
            }
            return true;
        }
};
void debug(std::vector<int> &ans){
    for(auto &x : ans)std::cout<<x<<"  ";
}
int main(int argc,const char *argv[]){
    Solution te;
    //std::vector<std::vector<int>> c {{1, 2, 3}, {3, 4, 4}};
    //int n = 4;
    //std::vector<std::vector<int>> c = {{1, 2, 5}, {1, 3, 6}, {2, 3, 1}};
    //int n = 3;
    //std::cout<<te.minimumCost_kru(n, c)<<std::endl;
    //std::cout<<te.minimumCost_prim(n, c)<<std::endl;
    //std::vector<std::vector<int>> e {{0, 1}, {1, 2}, {2, 3}, {1, 4}, {1, 3}};
    //int n = 5;
    //std::vector<std::vector<int>> e {{0, 1}, {0, 2}, {0, 3}, {1, 4}};
    //int n = 5;
    //std::cout<<te.validTree(n, e)<<std::endl;
    //std::vector<std::string> w1 {"great", "acting", "skills"};
    //std::vector<std::string> w2 {"fine", "drama", "tal"};
    //std::vector<std::vector<std::string>> ps {{"great", "fine"}, {"acting","drama"}, {"skills","talent"}};
    //std::cout<<te.areSenrencesSimilarTwo(w1, w2, ps)<<std::endl;
    //std::vector<std::vector<int>> logs
    //{ { 20190101,0,1 },{ 20190104,3,4 },{ 20190107,2,3 },{ 20190211,1,5 },
        //{ 20190224,2,4 },{ 20190301,0,3 },{ 20190312,1,2 },{ 20190322,4,5 } };
    //int N = 6;
    //std::cout<<te.earliestAcq(logs, N)<<std::endl;
    //std::string s1 = "leetcode", s2 = "programs", s3 = "sourcecode";
    //std::string s1 = "hello", s2 = "world", s3 = "hold";
    //std::string s1 = "parker", s2 = "morris", s3 = "parser";
    //std::cout<<te.smallestEquivalentString(s1, s2, s3)<<std::endl;
    //std::vector<std::vector<int>> e {{0, 1}, {1, 2}, {3, 4}, {2, 3}};
    //int n = 5;
    //std::cout<<te.countComponents(n, e)<<std::endl;
    //std::vector<std::vector<int>> pipes {{1,2,1},{2,3,1}};
    //std::vector<int> wells {1,2,2};
    //int n = 3;
    //std::cout<<te.minCostToSubpplyWatter(n, wells, pipes)<<std::endl;
    //std::vector<std::vector<int>> pos {{0,0}, {0, 1}, {1, 2}, {2, 1}};
    //int m = 3, n = 3;
    //auto ans = te.numIslandsII(m, n, pos);
    //debug(ans);
    return 0;
}
