/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_tmp.cpp
*     author   : @ JY
*     date     : 2020--07--18
**********************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stdlib.h>
class Soluton{
    private:
        struct{
            int to;
            int next;
        }e[100];
        int cur = 0;
        std::vector<int> vis;
        std::vector<int> dep;
        std::vector<int> head;
        std::vector<std::vector<int>> par;
    private:
        void init(std::vector<int>& p){
            int size = p.size();
            fill(head.begin(), head.end(), -1);
            fill(vis.begin(), vis.end(), 0);
            fill(dep.begin(), dep.end(), 0);
            par = std::vector<std::vector<int>>(size, std::vector<int>(20, -1));
            int root = -1;
            for(int i=0; i<size; ++i){
                p[i]==-1?root=i:add(p[i],i);
                //if(p[i]==-1){
                    //root = i;
                //}else{
                    //add(p[i], i);
                //}
            }
            bfs(root);
        }
        int add(int from, int to){
            e[cur].to   = to;
            e[cur].next = head[from];
            head[from]  = cur++;
            return 0;
        }
        void bfs(int root){
            std::queue<int> q;
            q.push(root);
            while(q.size()){
                int p = q.front();
                q.pop();
                ++vis[p];
                for(int j=head[p]; ~j; j=e[j].next){
                    int to = e[j].to;
                    if(vis[to])continue;
                    dep[to]     = dep[p] + 1;
                    par[to][0]  = to;
                    for(int k=1; k<(1<<dep[to]); ++k){
                        if(par[to][k-1] != -1){
                            par[to][k] = par[par[to][k-1]][k-1];
                        }
                    }
                    q.push(to);
                }
            }
        }
    public:
        int LCA(int a, int b){
            if(a < b)std::swap(a, b);
            for(int i=19; i>=0; --i){
                if(dep[a] >= dep[b] + (1<<i)){
                    a = par[a][i];
                }
            }
            if(a==b)return a;
            for(int i=19; i>=0; --i){
                if(par[a][i] != par[b][i]){
                    a = par[a][i];
                    b = par[b][i];
                }
            }
            return par[a][0];
        }
};
