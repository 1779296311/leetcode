/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_shorest+path.cpp
*     author   : @ JY
*     date     : 2020--09--17
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
 
class Sulotion{
    public:
//882. 细分图中的可到达结点
        int reachableNodes(std::vector<std::vector<int>> &edges, int M, int N){
            using pii  = std::pair<int, int>;
            using vpii = std::vector<pii>;
            int INF = 0x3f3f3f3f;
            std::unordered_map<int, vpii> mp;
            for(auto &p : edges){
                mp[p[0]].emplace_back(p[1], p[2] + 1);
                mp[p[1]].emplace_back(p[0], p[2] + 1);
            }
            std::vector<int> dist(N, INF);
            std::priority_queue<pii, vpii, std::greater<pii>> q;
            q.push({0, 0});
            dist[0] = 0;
            while(q.size()){
                auto [d, cur] = q.top();q.pop();
                if(d != dist[cur])continue;
                for(auto &&[next, d1] : mp[cur]){
                    if(dist[next] > d + d1){
                        q.push({dist[next]=d+d1, next});
                    }
                }
            }
            int res = 0;
            for(auto &e : edges){
                int i = e[0], j = e[1], d = e[2];
                res += std::min(std::max(0, M-dist[i])+std::max(0, M-dist[j]), d);
            }
            for(int i=0; i<N; ++i)res += M>=dist[i];
            return res;
        }

//743. 网络延迟时间
    //单源最短路
///朴素的dijkstra算法/所有边权都是正
        int networkDelay_dij(std::vector<std::vector<int>> &times, int N, int K){
            int INF = 0x3f3f3f3f;
            std::vector<int> di(N+1, INF);
            std::vector<int> vi(N+1);
            std::vector<std::vector<int>> e(N+1, std::vector<int>(N+1, INF));
            for(auto &t : times)e[t[0]][t[1]] = t[2];
            di[K] = 0;
            for(int i=0; i<N-1; ++i){
                int t = -1;
                for(int j=1; j<=N; ++j){
                    if(!vi[j] &&(t==-1 || di[t]>di[j])){
                        t = j;
                    }
                }
                vi[t] = 1;
                for(int j=1; j<=N; ++j){
                    di[j] = std::min(di[j], di[t]+e[t][j]);
                }
            }
            int res = *max_element(di.begin()+1, di.end());
            return res==INF?-1:res;
        }
//堆优化版的Dijkstra算法
        int networkDelay_dij_h(std::vector<std::vector<int>> &times, int N, int K){
            typedef std::pair<int, int> pii;
            int INF = 0x3f3f3f3f;
            std::vector<int> vi(N+1);
            std::vector<int> di(N+1, INF);
            std::unordered_map<int, std::vector<pii>> e;
            for(auto &t : times)e[t[0]].push_back({t[2], t[1]});
            std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
            di[K] = 0;
            q.push({0, K});
            while(q.size()){
                auto [d, t] = q.top();q.pop();
                if(vi[t])continue;
                vi[t] = 1;
                for(auto [d1, t1] : e[t]){
                    if(di[t1] > d+d1){
                        di[t1] = d + d1;
                        q.push({di[t1],t1});
                    }
                }
            }
            int res = *max_element(di.begin()+1, di.end());
            return res==INF?-1:res;
        }
//存在负权边 Bellman-Ford O(nm) 
        int networkDelay_bell_f(std::vector<std::vector<int>> &times, int N, int K){
            int INF = 0x3f3f3f3f;
            std::vector<int> di(N+1, INF);
            di[K] = 0;
            for(int i=0; i<N; ++i){
                for(auto &t : times){
                    di[t[1]] = std::min(di[t[1]], di[t[0]] + t[2]);
                }
            }
            int res = *max_element(di.begin()+1, di.end());
            return res>INF/2?-1:res;
        }
//spfa 一般O(m),最坏O(nm) 
        int networkDealy_spf(std::vector<std::vector<int>> &times, int N, int K){
            typedef std::pair<int, int> pii;
            int INF = 0x3f3f3f3f;
            std::vector<int> vi(N+1);
            std::vector<int> di(N+1, INF);
            std::unordered_map<int, std::vector<pii>> e;
            for(auto &t : times)e[t[0]].push_back({t[2], t[1]});
            std::queue<pii> q;
            q.push({0, K});
            di[K] = 0;
            vi[K] = 1;
            while(q.size()){
                auto [d, cur] = q.front(); q.pop();
                vi[cur] = 0;
                for(auto [d1, t] : e[cur]){
                    if(di[t] > di[cur] + d1){
                        di[t] = di[cur] + d1;
                        if(!vi[t])q.push({d1, t}),vi[t]=1;
                    }
                }
            }
            int res = *max_element(di.begin()+1, di.end());
            return res==INF?-1:res;
        }

    //多源汇最短路 Floyd算法 O(n^3)
        //floyd算法
        int networkDealy_floyd(std::vector<std::vector<int>> &times, int N, int K){
            int INF = 0x3f3f3f3f;
            std::vector<std::vector<int>> di(N+1, std::vector<int>(N+1, INF));
            for(auto &t : times)di[t[0]][t[1]] = std::min(di[t[0]][t[1]], t[2]);
            for(int i=0; i<N; ++i)di[i][i] = 0;
            for(int i=1; i<=N; ++i){
                for(int j=1; j<=N; ++j){
                    for(int k=1; k<=N; ++k){
                        di[j][k] = std::min(di[j][k], di[j][i] + di[i][k]);
                    }
                }
            }
            int res = *max_element(di[K].begin()+1, di[K].end());
            return res>INF/2?-1:res;
       }
};
