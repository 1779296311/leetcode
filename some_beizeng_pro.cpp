/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_beizeng_pro.cpp
*     author   : @ JY
*     date     : 2020--06--16
**********************************************/
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
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
                st.pop();
                ::std::cout<<h<<::std::endl;
                vis[h] = true;
                for(int i=head[h]; ~i; i=edgs[i].next){
                    if(!vis[edgs[i].to]){
                        st.push(edgs[i].to);
                    }
                }
            }
        }
};
class LCA{
//即最近公共祖先，是指这样一个问题：在有根树中，找出某两个结点u和v最近的公共祖先
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
                ++vis[p];
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

            if(a==b)return a;

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
/*---------------------给定一个整数 M，对于任意一个整数集合 S，定义“校验值”如下:
从集合 S 中取出 M 对数(即 2∗M 个数，不能重复使用集合中的数，如果 S 中的整 数不够 M 对，则取到不能取为止)，使得“每对数的差的平方”之和最大，这个最大值 就称为集合 S 的“校验值”。
现在给定一个长度为 N 的数列 A 以及一个整数 T。我们要把 A 分成若干段，使得 每一段的“校验值”都不超过 T。求最少需要分成几段*/
class Solution{
    public:
        ::std::vector<int> b;
        ::std::vector<int> c;

        Solution(){
            b = ::std::vector<int>(200);
            c = ::std::vector<int>(200);
        }
        int getK(::std::vector<int>& nums, int T, int M){
            int p   = 1;
            int res = 0;
            int m   = 0;
            int l   = 0;
            int n   = nums.size();
            b[l]    = nums[l];
            while(l<n){
                p    = 1;
                while(p){
                    if(p+m<n && calc(nums,l,m,m+p,M)<=T){
                        m += p;
                        p <<= 1;
                        for(int i=l; i<=m+p; ++i)b[i] = c[i];
                    }else{
                        p >>= 1;
                    }
                }
                ++res;
                m = m + 1;
                l = m;
            }
            return res;
        }
        int calc(::std::vector<int>& nums, int l, int m, int r, int M){
            int N = ::std::min(M,(r-l+1)>>1);

            //      quick sort
            //for(int i=0; i<=r; ++i)b[i] = nums[i];
            //::std::sort(b.begin()+l, b.begin()+r+1);
            //for(int i=0; i<=r; ++i){
                //::std::cout<<b[i]<<" ";
            //}

            //merge sort
            for(int i=m+1; i<=r; ++i)b[i] = nums[i];
            ::std::sort(b.begin()+m+1, b.begin()+r+1);
            merge_sort(b,l,m,r);

            int res = 0;
            for(int i=0; i<N; ++i){
                res += (c[l+i]-c[r-i]) * (c[l+i]-c[r-i]);
                //res += (b[l+i]-b[r-i]) * (b[l+i]-b[r-i]);
            }
            return res;
        }

        void merge_sort(::std::vector<int>& nums, int l, int m, int r){
            int i = l;
            int j = m+1;
            int p = l;
            while(i<=m && j<=r){
                c[p++] = nums[i]>nums[j]?nums[j++]:nums[i++];
            }
            while(i<=m){
                c[p++] = nums[i++];
            }
            while(j<=r){
                c[p++] = nums[j++];
            }
        }
};
// 给定一个长度为n的数列A，有m个询问，每次给定一个整数T，求出最大的k，满足a[1]，a[2]……a[k]的和小于等于T（-
class AskK{
    public:
        int askK(::std::vector<int>& nums, int T){
            for(int i=1; i<nums.size(); ++i){
                nums[i] = nums[i-1] + nums[i];
            }
            int p = 1;
            int c = 0;
            int k = -1;
            while(p){
                if(c+p<nums.size() && nums[c+p] <= T){
                    c += p;
                    p <<= 1;
                }else{
                    p >>= 1;
                }
            }
            return c;
        }
};
//---------------------倍增算法的应用：RMQ 问题（ST表
class RMQ{
    private:
        ::std::vector<::std::vector<int>> f1;
    public:
        void init1(::std::vector<int>& nums, int n){
            f1 = ::std::vector<::std::vector<int>>(n+2,::std::vector<int>(21));

            for(int i=1; i<=n; ++i)f1[i][0] = nums[i-1];

            for(int j=1; (1<<j)<=n; ++j){
                for(int i=1; i+(1<<j)-1<=n; ++i){
                    f1[i][j] = ::std::max(f1[i][j-1], f1[i+(1<<(j-1))][j-1]);
                }
            }
        }
        int check(int l, int r){
            for(int i=1; i<f1.size(); ++i){
                for(int j=0; j<21; ++j){
                    ::std::cout<<f1[i][j]<<" ";
                }
                ::std::cout<<::std::endl;
            }

            int m = trunc(log2(r-l+1));

            //::std::cout<<l<<"--"<<m<<::std::endl;
            //::std::cout<<r-(1<<m)+1<<"--"<<m<<::std::endl;

            return ::std::max(f1[l][m], f1[r-(1<<m)+1][m]);
        }
    public:
        RMQ(::std::vector<int>& nums){
            init1(nums, nums.size());
        }
};

int main(int argc,const char *argv[]){
    ::std::vector<int> nums = {0,1,2,3,4,5,123,23,53,4564,57,5678,56,7,24,1234};
    RMQ rmq(nums);
    ::std::cout<<rmq.check(5,7)<<::std::endl;
    //AskK ask;
    //::std::cout<<ask.askK(nums,10)<<::std::endl;
    //Solution te;
    //::std::vector<int> nums = {8,2,-100,7,9};
    //int T = 64;
    //int M = 1;
    //::std::cout<<te.getK(nums,T,M)<<::std::endl;
    //::std::cout<<te.getK(nums,T,64)<<::std::endl;
    //::std::cout<<te.getK(nums,T,4)<<::std::endl;
    return 0;
}
