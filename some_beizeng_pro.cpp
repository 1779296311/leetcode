/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_beizeng_pro.cpp
*     author   : @ JY
*     date     : 2020--06--16
**********************************************/
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <stdlib.h>
//-----------------------链式前向星+BFS：
class LIAN{
    private:
        int cur = 0;
        struct Node{
            int to;
            int next;
        }edgs[100];
        int  head[100];
        bool vis[100];
    public:
        void add(int from, int to){
            edgs[cur].to   = to;
            edgs[cur].next = head[from];
            head[from]     = cur++;
        }
        void DFS(::std::vector<int>& p){
            int root = -1;
            memset(head,-1,sizeof(head));
            memset(vis,false,sizeof(vis));
            for(int i=0; i<p.size(); ++i){
                if(p[i] == -1){
                    root = i;
                }else{
                    add(p[i],i);
                }
            }
            dfs(root);
        }
        void dfs(int root){
            ::std::cout<<root<<::std::endl;
            vis[root] = true;
            for(int i=head[root]; ~i; i=edgs[i].next){
                if(false == vis[edgs[i].to]){
                    dfs(edgs[i].to);
                }
            }
        }
        void BFS(::std::vector<int>& p){
            int root = -1;
            memset(head,-1,sizeof(head));
            for(int i=0; i<p.size(); ++i){
                if(p[i] == -1){
                    root = i;
                }else{
                    add(p[i],i);
                }
            }
            ::std::queue<int> st;
            st.push(root);
            while(!st.empty()){
                int h  = st.front();
                ::std::cout<<h<<::std::endl;
                vis[h] = true;
                st.pop();
                for(int i=head[h]; ~i; i=edgs[i].next){
                    if(!vis[edgs[i].to]){
                        st.push(edgs[i].to);
                    }
                }
            }
        }
};
class LCA{
    private:
        int head[100];
        int vis[100];
        int dep[100];
        struct{
            int to;
            int next;
        }edgs[100];
        int cur = 0;
        ::std::vector<::std::vector<int>> f;
    public:
        LCA(::std::vector<int>& p){
            f = ::std::vector<::std::vector<int>>(p.size(),::std::vector<int>(20,-1));
            memset(head,-1,sizeof(head));
            memset(vis,0,sizeof(vis));
            memset(dep,0,sizeof(dep));
            int root = init(p);

            ::std::queue<int> st;
            st.push(root);
            while(!st.empty()){
                int p = st.front();
                st.pop();
                vis[p]++;
                for(int i=head[p]; ~i; i = edgs[i].next){
                    int t   = edgs[i].to;
                    if(vis[t] != 0)continue;
                    f[t][0] = p;
                    dep[t]  = dep[p] + 1;
                    for(int j=1; j<(1<<dep[t]); ++j){
                        if(f[t][j-1] != -1){
                            f[t][j] = f[f[t][j-1]][j-1];
                        }
                    }
                    st.push(t);
                }
            }
        }

        int lca(int a, int b){
            if(dep[a] < dep[b]){
                ::std::swap(a,b);
            }
            for(int i=19; i>=0; --i){
                if(dep[a]-(1<<i) >= dep[b]){
                    a = f[a][i];
                }
            }
            for(int i=19; i>=0; --i){
                if(f[a][i] != f[b][i]){
                    a = f[a][i];
                    b = f[b][i];
                }
            }
            return f[a][0];
        }
        int init(::std::vector<int>& p){
            int root = -1;
            for(int i=0; i<p.size(); ++i){
                if(p[i] == -1){
                    root = i;
                }else{
                    add(p[i],i);
                }
            }
            return root;
        }
    private:
        void add(int from, int to){
            edgs[cur].to   = to;
            edgs[cur].next = head[from];
            head[from]     = cur++;
        }
};
//-------------------di-----K-------ge-------zu--------xian--------------------
class TreeAncestor{
public:
    ::std::vector<::std::vector<int>> p;
    ::std::vector<::std::vector<int>> f;
    TreeAncestor(int n, ::std::vector<int>& parent){
        f = ::std::vector<::std::vector<int>>(n, ::std::vector<int>(16,-1));
        p = ::std::vector<::std::vector<int>>(n);
        int root = -1;
        for(int i=0; i<parent.size(); ++i){
            if(parent[i] == -1){
                root = i;
            }else{
                p[parent[i]].push_back(i);
            }
        }
        ::std::queue<int> st;
        st.push(root);
        while(!st.empty()){
            int par = st.front();
            st.pop();
            for(int c : p[par]){
                f[c][0] = par;
                for(int i=1; i<16; ++i){
                    if(f[c][i-1] != -1){
                        f[c][i] = f[f[c][i-1]][i-1];
                    }
                }
                st.push(c);
            }
        }
    }

    int getKthAncestor(int node, int k){
        for(int i=0; i<16; ++i){
            if(k>>i&1){
                node = f[node][i];
                if(node==-1)return node;
            }
        }
        return node;
    }
};
int main(int argc,const char *argv[]){
    ::std::vector<int> p = {-1,0,0,1,1,2,2};
    LCA l(p);
    ::std::cout<<l.lca(0,4)<<::std::endl;
    return 0;
}
