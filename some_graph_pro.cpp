/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_graph_pro.cpp
*     author   : @ JY
*     date     : 2020--10--30
**********************************************/
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <climits>
#include <queue>
#include <numeric>
#include <functional>
#include <stdlib.h>
class Node {
public:
    int val;
    std::vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = std::vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = std::vector<Node*>();
    }
    Node(int _val, std::vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
class Solution{
    public:
//Leetcode 1136：平行课程
//已知有 N 门课程，它们以 1 到 N 进行编号。
//给你一份课程关系表 relations[i] = [X, Y]，用以表示课程 X 和课程 Y 之间的先修关系：课程 X 必须在课程 Y 之前修完。 假设在一个学期里，你可以学习任何数量的课程，但前提是你已经学习了将要学习的这些课程的所有先修课程。 请你返回学完全部课程所需的最少学期数。 如果没有办法做到学完全部这些课程的话，就返回 -1。
        int miniumuSemesters(int N, std::vector<std::vector<int>> relations){
            std::vector<int> in(N);
            std::unordered_map<int, std::vector<int>> e;
            for(auto &r : relations){
                ++in[r[1]-1];
                e[r[0]-1].emplace_back(r[1]-1);
            }
            std::queue<int> q;
            for(int i=0; i<N; ++i){
                if(!in[i])q.push(i);
            }
            int res = 0;
            while(q.size()){
                int size = q.size();
                ++res;
                while(size--){
                    --N;
                    int cur = q.front();q.pop();
                    for(auto &t : e[cur]){
                        if(!--in[t])q.push(t);
                    }
                }
            }
            return N ? -1 : res;
        }
//LeetCode 1548
        std::vector<int> mostSimilar(int n, std::vector<std::vector<int>> &roads,
                                     std::vector<std::string> &names,
                                     std::vector<std::string> &targetPath){
            std::vector<std::vector<int>> e(n);
            for(auto &r : roads){
                e[r[0]].emplace_back(r[1]);
                e[r[1]].emplace_back(r[0]);
            }
            std::vector<int> dp_0(n, INT_MAX), dp_1(n, INT_MAX);
            std::vector<std::vector<int>> path0(n), path1(n);
            for(int i=0; i<n; ++i){
                dp_0[i] = (names[i] != targetPath[0]);
                path0[i].push_back(i);
            }
            int len = targetPath.size();
            for(int i=1; i<len; ++i){
                for(int j=0; j<n; ++j){
                    if(dp_0[j] == INT_MAX)continue;
                    for(auto &t : e[j]){
                        if(dp_1[t] > dp_0[t] + (names[t] != targetPath[i])){
                            dp_1[t] = dp_0[t] + (names[t] != targetPath[i]);
                            path1[t] = path0[i];
                            path1[t].push_back(t);
                        }
                    }
                }
                dp_0 = dp_1;
                std::fill(begin(dp_1), end(dp_1), INT_MAX);
                swap(path0, path1);
            }
            int min_ = INT_MAX, res = -1;
            for(int i=0; i<n; ++i){
                if(min_ > dp_0[i]){
                    min_ = dp_0[i];
                    res = i;
                }
            }
            return path0[res];
        }
//1361. 验证二叉树
        bool validateBinaryTreeNodes(int n, std::vector<int> &leftChild,
                std::vector<int> &rightChild){
                std::vector<int> in(n);
                for(int i=0; i<n; ++i){
                    if(leftChild[i]!=-1)++in[leftChild[i]];
                    if(rightChild[i]!=-1)++in[rightChild[i]];
                }
                int root = -1;
                for(int i=0; i<n; ++i){
                    if(!in[i] && root != -1)return false;
                    if(in[i] > 1)return false;
                    if(!in[i])root = i;
                }
                std::vector<int> vi(n);
                std::function<bool(int)> _dfs = [&](int i){
                    if(i==-1)return true;
                    if(vi[i])return false;
                    vi[i] = 1;
                    return _dfs(leftChild[i]) && _dfs(rightChild[i]);
                };
                return _dfs(root) && *std::min_element(begin(vi), end(vi));
        }
//[leetcode] 269
//有一种新的外来语言使用拉丁字母。但是，你不知道字母之间的顺序。您将从字典中收到一个单词列表，其中的单词是按照这种新语言的规则按字典顺序排序的。推导出这种语言中字母的顺序。
        std::string alienOrder(std::vector<std::string> &words){
            std::unordered_map<char, int> in;
            std::unordered_map<char, std::unordered_set<char>> mp2;
            int len = words.size();
            for(auto &s : words){
                for(auto &c : s)in[c] = 0;
            }
            for(int i=1,j=0; i<len; ++i){
                int s1 = words[i-1].size();
                int s2 = words[i].size();
                int s = std::min(s1, s2);
                for(j=0; j<s; ++j){
                    if(words[i-1][j] != words[i][j]){
                        if(mp2[words[i-1][j]].insert(words[i][j]).second){
                            ++in[words[i][j]];
                        }
                        break;
                    }
                }
                if(j==s && s1 > s2)return "";
            }
            std::queue<int> q;
            for(auto &[c, n] : in){
                if(!n)q.push(c);
            }
            int n = in.size();
            std::string res = "";
            while(q.size()){
                char c = q.front();q.pop();
                res += c;
                for(auto &t : mp2[c]){
                    if(!--in[t])q.push(t);
                }
            }
            return res.size() == n ? res : "";
        }
//1042. 不邻接植花
        std::vector<int> gardenNoAdj_better(int n, std::vector<std::vector<int>> &paths){
            std::vector<std::vector<int>> e(n);
            std::vector<int> res(n);
            for(auto &p : paths){
                e[p[0]-1].emplace_back(p[1]-1);
                e[p[1]-1].emplace_back(p[0]-1);
            }
            for(int i=0, j=1; i<n; ++i){
                std::vector<int> c(5);
                for(auto &t : e[i])++c[res[t]];
                for(j=1; j<=4 && c[j]; ++j);
                res[i] = j;
            }
            return res;
        }
        std::vector<int> gardenNoAdj(int n, std::vector<std::vector<int>> &paths){
            std::unordered_map<int, std::vector<int>> e;
            for(auto &x : paths){
                e[x[0]-1].emplace_back(x[1]-1);
                e[x[1]-1].emplace_back(x[0]-1);
            }
            std::vector<int> res(n), vi(n+1);
            std::function<void(int)> _dfs = [&](int i){
                if(vi[i])return;
                vi[i] = 1;
                std::vector<int> c(5);
                for(auto t : e[i])++c[res[t]];
                int j = 1;
                for(; j<5 && c[j]; ++j);
                res[i] = j;
                for(auto &t : e[i]) _dfs(t);
            };
            for(int i=0; i<n; ++i) _dfs(i);
            return res;
        }
//Leetcode 1153：字符串转化
        bool canConvert(std::string str1, std::string str2){
            if(!str1.compare(str2))return true;
            std::unordered_set<char> cnt(begin(str1), end(str1));
            int size1 = cnt.size();
            cnt = {begin(str2), end(str2)};
            int size2 = cnt.size();
            if(size2 == 26 || size1 < size2)return false;
            std::unordered_map<char, int> s1;
            std::unordered_map<char, int> s2;
            int mp = 0, len = str1.size();
            for(int i=0; i<len; ++i){
                char c1 = str1[i];
                char c2 = str2[i];
                if(!s2.count(c2)){
                    if(s1.count(c1))return false;
                    s1[c1] = s2[c2] = mp++;
                }
                if(!s1.count(c1)){
                    s1[c1] = s2[c2];
                }
                if(s1[c1] != s2[c2])return false;
            }
            return true;
        }
//1334. 阈值距离内邻居最少的城市
        int findTheCity_spfa(int n, std::vector<std::vector<int>> &edges, int distanceThreshold){
            using pii = std::pair<int, int>;
            int INF = 0x3f3f3f3f;
            std::unordered_map<int, std::vector<pii>> e;
            for(auto &x : edges){
                e[x[0]].emplace_back(x[2], x[1]);
                e[x[1]].emplace_back(x[2], x[0]);
            }
            std::function<int(int)> _spfa = [&](int start){
                std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
                std::vector<int> dis(n, INF), vi(n);
                dis[start] = 0;
                q.emplace(0, start);
                while(q.size()){
                    auto [d, cur] = q.top();q.pop();
                    vi[cur] = 0;
                    for(auto &[d1, next] : e[cur]){
                        if(dis[next] > dis[cur] + d1){
                            dis[next] = dis[cur] + d1;
                            if(!vi[next])q.emplace(dis[next], next), vi[next] = 1;
                        }
                    }
                }
                int ans = 0;
                for(int i=0; i<n; ++i)ans += dis[i] <= distanceThreshold;
                return ans;
            };
            int res, max_ = INT_MAX;
            for(int i=n-1; i>=0; --i){
                int t = _spfa(i);
                if(t < max_)max_ = t, res = i;
            }
            return res;
        }
        int findTheCity_dij(int n, std::vector<std::vector<int>> &edges, int distanceThreshold){
            int INF = 0x3f3f3f3f;
            std::vector<std::vector<int>> e(n, std::vector<int>(n, INF));
            for(auto &x : edges){
                e[x[0]][x[1]] = x[2];
                e[x[1]][x[0]] = x[2];
                e[x[0]][x[0]] = 0;
                e[x[1]][x[1]] = 0;
            }
            std::function<int(int)> _dijkstra = [&](int start){
                using pii = std::pair<int, int>;
                std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
                std::vector<int> dis(n, INF), vi(n);
                dis[start] = 0;
                q.push({0, start});
                while(q.size()){
                    auto [d, cur] = q.top();q.pop();
                    if(vi[cur])continue;
                    vi[cur] = 1;
                    for(int i=0; i<n; ++i){
                        if(vi[cur])continue;
                        if(dis[i] > d + e[cur][i]){
                            dis[i] = d + e[cur][i];
                            q.push({dis[i], i});
                        }
                    }
                }
                int ans = 0;
                for(int i=0; i<n; ++i)ans += dis[i] <= distanceThreshold;
                return ans;
            };
            int res, max_ = INT_MAX;
            for(int i=n-1; i>=0; --i){
                int t = _dijkstra(i);
                if(t < max_)max_ = t, res = i;
            }
            return res;
        }
        int findTheCity_floyd(int n, std::vector<std::vector<int>> &edges, int distanceThreshold){
            std::vector<std::vector<long>> e(n, std::vector<long>(n, INT_MAX));
            for(auto &x : edges){
                e[x[0]][x[1]] = x[2];
                e[x[1]][x[0]] = x[2];
            }
            int res, max_ = INT_MAX;
            for(int i=0; i<n; ++i){
                for(int j=0; j<n; ++j){
                    for(int k=0; k<n; ++k){
                        e[j][k] = std::min(e[j][k], e[j][i] + e[i][k]);
                    }
                }
            }
            for(int i=0; i<n; ++i){
                int cnt = 0;
                for(int j=0; j<n; ++j){
                    if(i!=j && e[i][j] <= distanceThreshold)++cnt;
                }
                if(cnt <= max_)max_ = cnt, res = i;
            }
            return res;
        }
//47. 全排列 II
        std::vector<std::vector<int>> permueII(std::vector<int> &nums){
            std::sort(begin(nums), end(nums));
            int len = nums.size();
            std::vector<int> vi(len), arr;
            std::vector<std::vector<int>> res;
            std::function<void(void)> _dfs = [&](void){
                if(arr.size() == len){
                    res.emplace_back(arr);
                    return;
                }
                for(int i=0; i<len; ++i){
                    if(i && !vi[i-1] && nums[i] == nums[i-1]){
                        continue;
                    }
                    if(vi[i])continue;
                    vi[i] = 1;
                    arr.emplace_back(nums[i]);
                    _dfs();
                    vi[i] = 0;
                    arr.pop_back();
                }
            };
            _dfs();
            return res;
        }
//46. 全排列
        std::vector<std::vector<int>> permute_better(std::vector<int>& nums) {
            int len = nums.size();
            std::vector<int> vi(len), arr;
            std::vector<std::vector<int>> res;
            std::function<void(void)> _dfs = [&](void){
                if(arr.size() == len){
                    res.emplace_back(arr);
                    return;
                }
                for(int j=0; j<len; ++j){
                    if(vi[j])continue;
                    vi[j] = 1;
                    arr.emplace_back(nums[j]);
                    _dfs();
                    vi[j] = 0;
                    arr.pop_back();
                }
            };
            _dfs();
            return res;
        }
        std::vector<std::vector<int>> permute(std::vector<int>& nums) {
            std::vector<std::vector<int>> res;
            int len = nums.size();
            std::function<void(int)> _dfs = [&](int i){
                if(i == len){
                    res.push_back(nums);
                    return;
                }
                for(int j=i; j<len; ++j){
                    std::swap(nums[i], nums[j]);
                    _dfs(i+1);
                    std::swap(nums[i], nums[j]);
                }
            };
            _dfs(0);
            return res;
        }
//996. 正方形数组的数目
        int numSquarefulPerms(std::vector<int> &A){
            int len = A.size();
            std::vector<int> vi(len);
            std::sort(begin(A), end(A));
            int res = 0;
            std::function<bool(int, int)> _ok = [&](int a, int b){
                return (int)sqrt(a+b) == sqrt(a+b); };
            std::function<void(int, int)> _dfs = [&](int c, int p){
                if(c==len){
                    ++res;
                    return;
                }
                for(int i=0; i<len; ++i){
                    if(i && !vi[i-1] && A[i] == A[i-1])continue;
                    if(!vi[i] && (p == -1 || _ok(p, A[i]))){
                        vi[i] = 1;
                        _dfs(c+1, A[i]);
                        vi[i] = 0;
                    }
                }
            };
            _dfs(0, -1);
            return res;
        }
        int numSquarefulPerms_fuck(std::vector<int> &A){
            int n = A.size();
            std::vector<std::vector<int>> e(n);
            for(int i=0; i<n; ++i){
                for(int j=i+1; j<n; ++j){
                    if((int)(sqrt(A[i]+A[j])) == (sqrt(A[i]+A[j]))){
                        e[i].emplace_back(j);
                        e[j].emplace_back(i);
                    }
                }
            }
            std::set<std::vector<int>> mp;
            std::vector<int> vi(n);
            std::function<void(int, int, std::vector<int> &)> _dfs = [&](int i, int k, std::vector<int> &arr){
                if(vi[i])return;
                if(k == n){
                    mp.insert(arr);
                    return;
                }
                vi[i] = 1;
                std::sort(begin(e[i]), end(e[i]));
                do{
                    for(auto &t : e[i]){
                        arr.emplace_back(A[t]);
                        _dfs(t, k+1, arr);
                        arr.pop_back();
                    }
                }while(std::next_permutation(begin(e[i]), end(e[i])));
                vi[i] = 0;
            };
            std::vector<int> arr;
            for(int i=0; i<n; ++i){
                std::fill(begin(vi), end(vi), 0);
                arr.push_back(A[i]);
                _dfs(i, 1, arr);
                arr = {};
            }
            return mp.size();
        }
//LeetCode 1059. 从始点到终点的所有路径
//给定有向图的边 edges，以及该图的始点 source 和目标终点 destination，确定从始点 source 出发的所有路径是否最终结束于目标终点 destination，即： 从始点 source 到目标终点 destination 存在至少一条路径 如果存在从始点 source 到没有出边的节点的路径，则该节点就是路径终点。 从始点source到目标终点 destination 可能路径数是有限数字
        bool leadsToDestination(int n, std::vector<std::vector<int>> &edges, int source, int destination){
            std::vector<std::vector<int>> e(n);
            for(auto &ed : edges)e[ed[0]].emplace_back(ed[1]);
            std::vector<int> vi(n);
            std::function<bool(int)> _dfs = [&](int i){
                if(i == destination)return true;
                if(!e[i].size())return false;
                if(vi[i])return false;
                vi[i] = 1;
                for(auto &t : e[i]){
                    if(!_dfs(t))return false;
                }
                vi[i] = 0;
                return true;
            };
            return !e[n-1].size() && _dfs(source);
        }
//97. 所有可能的路径
        std::vector<std::vector<int>> allPathsSourceTaeget(
                std::vector<std::vector<int>> &graph){
            int n = graph.size();
            std::set<std::vector<int>> mp;
            std::set<std::pair<int, std::vector<int>>> vi;
            std::function<void(int, std::vector<int> &)> _dfs = [&](int i, std::vector<int> &arr){
                if(i == n-1){
                    mp.insert(arr);
                    return;
                }
                if(vi.count({i, arr}))return;
                for(auto &x : graph[i]){
                    arr.push_back(x);
                    _dfs(x, arr);
                    arr.pop_back();
                }
                vi.insert({i, arr});
            };
            std::vector<int> arr {0} ;
            _dfs(0, arr);
            std::vector<std::vector<int>> res(mp.begin(), mp.end());
            return res;
        }
        std::vector<std::vector<int>> allPathsSourceTaeget_fuck(
                std::vector<std::vector<int>> &graph){
            int n = graph.size();
            std::vector<std::vector<int>> e(n, std::vector<int>(n));
            for(int i=0; i<n; ++i){
                for(auto &x : graph[i]){
                    e[i][x] = 1;
                }
            }
            std::vector<std::vector<int>> res;
            std::function<bool(int, int)> _dfs = [&](int state, int i){
                state = state & (state - 1);
                if(!state)return true;
                int t = __builtin_ctz(state);
                if(!e[i][t] || !_dfs(state, t))return false;
                return true;
            };
            std::function<void(int)> _deal = [&](int state){
                std::vector<int> ans;
                int p = 0;
                while(state){
                    ans.emplace_back(p);
                    state = state & (state - 1);
                    if(!state)break;
                    p = __builtin_ctz(state);
                }
                res.emplace_back(ans);
            };
            for(int i=0; i<(1<<n); ++i){
                if(!(1&i) || !((1<<(n-1))&i))continue;
                if(!_dfs(i, 0))continue;
                _deal(i);
            }
            return res;
        }
//997. 找到小镇的法官
        int findJudge(int N, std::vector<std::vector<int>> &trust){
            std::vector<int> in(N), out(N);
            for(auto &t : trust)++in[t[1]-1], ++out[t[0]-1];
            for(int i=0; i<N; ++i){
                if(in[i] == N-1 && out[i] == 0){
                    return i + 1;
                }
            }
            return -1;
        }
        Node * cloneGraph(Node *node){
            std::unordered_map<int, Node*> mp;
            std::function<Node *(Node *)> _dfs = [&](Node *cur){
                if(!cur)return (Node*) (NULL);
                if(mp.count(cur->val))return mp[cur->val];
                Node *root = new Node (cur->val);
                mp[root->val] = root;
                for(auto node : cur->neighbors){
                    root->neighbors.emplace_back(_dfs(node));
                }
                return root;
            };
            return _dfs(node);
        }
//面试题 04.01. 节点间通路
        bool findWhetherExistsPath(int n,
                std::vector<std::vector<int>> &graph,
                int start, int target){
            std::vector<int> vi(n);
            std::vector<std::vector<int>> e(n);
            for(auto &g : graph)e[g[0]].emplace_back(g[1]);
            std::function<bool(int)> _dfs = [&](int i){
                if(i == target)return true;
                vi[i] = 1;
                for(auto &to : e[i]){
                    if(vi[to])continue;
                    if(_dfs(to))return true;
                }
                return false;
            };
            return _dfs(start);
       }
};
int main(int argc,const char *argv[]){
    Solution te;
    //std::vector<std::vector<int>> ra {{1, 2}, {2, 3}, {3, 1}};
    std::vector<std::vector<int>> ra {{1, 3}, {2, 3}};
    int N = 3;
    std::cout<<te.miniumuSemesters(N, ra)<<std::endl;
    //std::vector<std::string> wd { "wrt", "wrf", "er", "ett", "rftt"};
    //std::vector<std::string> wd { "z", "x"};
    //std::cout<<te.alienOrder(wd)<<std::endl;
    //std::vector<std::vector<int>> e {{0, 1}, {0, 3}, {1, 2}, {2, 1}};
    //int n = 4, s = 0, d = 3;
    //std::vector<std::vector<int>> e {{0, 1}, {0, 3}, {1, 3}, {2, 3}};
    //int n = 4, s = 0, d = 3;
    //std::vector<std::vector<int>> e {{0, 1}, {1, 1}, {1, 2}};
    //int n = 3, s = 0, d = 2;
    //std::vector<std::vector<int>> e {{0, 1}, {1, 1}};
    //int n = 2, s = 0, d = 1;
    //std::vector<std::vector<int>> e {{0, 1}, {0, 2}, {2, 3}, {1, 5}, {4,1}, {3, 4}};
    //int n = 6, s = 0, d = 5;
    //std::cout<<te.leadsToDestination(n, e, s, d)<<std::endl;
    return 0;
}
