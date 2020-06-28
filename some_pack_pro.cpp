/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_pack_pro.cpp
*     author   : @ JY
*     date     : 2020--05--30
**********************************************/
#include <iostream>
#include <climits>
#include <vector>
#include <stdlib.h>
class Solution{
    public:
        void zero_one_pack(::std::vector<int>& dp, int v, int w, int V){
            for(int i=V; i>=v; --i){
                dp[i] = ::std::max(dp[i],dp[i-v]+w);
            }
        }
        void complete_pack(::std::vector<int>& dp, int v, int w, int V){
            for(int i=v; i<=V; ++i){
                dp[i] = ::std::max(dp[i],dp[i-v]+w);
            }
        }
        void multiple_pack(::std::vector<int>& dp, int v, int w, int n, int V){
            if(v*n>V){
                complete_pack(dp,v,w,V);
                return;
            }
            int k = 1;
            while(n>=k){
                zero_one_pack(dp,v*k,w*k,V);
                n = n - k;
                k = k << 1;
            }
            if(n)zero_one_pack(dp,n*v,n*w,V);
        }
        int mutiplePack(::std::vector<::std::vector<int>>& goods, int V){
            ::std::vector<int> dp(V+1,0);
            for(int i=0; i<goods.size(); ++i){
                multiple_pack(dp,goods[i][0],goods[i][1],goods[i][2],V);
            }
            return dp[V];
        }
        /*************************多重背包问题**************HE*****一些优化***********************8*/
        //yuanshi
        int mutiplePack1(::std::vector<::std::vector<int>>& goods, int V){
            ::std::vector<int> dp(V+1,0);
            for(int i=0; i<goods.size(); ++i){
                for(int j=V; j>=0; --j){
                    for(int k=0; k<=goods[i][2]; ++k){
                        if(j-goods[i][0]*k>=0)dp[j] = ::std::max(dp[j], dp[j-goods[i][0]*k]+goods[i][1]*k);
                    }
                }
            }
            return dp[V];
        }
        //单调队列优化
        struct node{
            int value;
            int index;
        };
        int mutiplePack2(::std::vector<::std::vector<int>>& goods, int V){
            ::std::vector<node> q(V+1,{0,0});
            ::std::vector<int> dp(V+1,0);
            for(int i=0; i<goods.size(); ++i){
                for(int j=0; j<goods[i][0]; ++j){
                    int l    = 0;
                    int r    = 0;
                    int stop = (V-j)/goods[i][0];
                    for(int k=0; k<=stop; ++k){
                        int val = dp[j+k*goods[i][0]] - k*goods[i][1];
                        while(l<r && q[r-1].value<=val){--r;}
                        q[r++]  = {val,k};
                        if(q[l].index+goods[i][2]<k)++l;
                        dp[j+k*goods[i][0]] = q[l].value + k*goods[i][1];
                    }
                }
            }
            return dp[V];
        }
        /***************************************************二维费用的背包问题*********/
        int towPack(::std::vector<::std::vector<int>>& goods, int V, int W){
            ::std::vector<::std::vector<int>> dp(W+1,::std::vector<int>(V+1,0)) ;
            for(int i=0; i<goods.size(); ++i){
                for(int w=W; w>=goods[i][1]; --w){
                    for(int v=V; v>=goods[i][0]; --v){
                        dp[w][v] = ::std::max(dp[w][v], dp[w-goods[i][1]][v-goods[i][0]] + goods[i][2]);
                    }
                }
            }
            return dp[W][V];
        }
        /*****************GROUP***************************背包问题*********/
        int gropPack(::std::vector<::std::vector<::std::vector<int>>>& goods, int V){
            ::std::vector<int> dp(V+1,0);
            for(int i=0; i<goods.size(); ++i){
                for(int j=V; j>=0; --j){
                    for(int k=0; k<goods[i].size(); ++k){
                        if(j-goods[i][k][0]>=0)dp[j] = ::std::max(dp[j], dp[j-goods[i][k][0]] + goods[i][k][1]);
                    }
                }
            }
            return dp[V];
        }
        /*************************方案数************************************/
        int zeroOnePackNum(::std::vector<::std::vector<int>>& goods, int V){
            ::std::vector<int> dp(V+1,INT_MIN);
            ::std::vector<int> N(V+1,0);
            dp[0] = 0;
            N[0]  = 1;
            for(int i=0; i<goods.size(); ++i){
                for(int j=V; j>=goods[i][0]; --j){
                    int tmp = ::std::max(dp[j], dp[j-goods[i][0]]+goods[i][1]);
                    if(tmp==dp[j-goods[i][0]]+goods[i][1])N[j] += N[j-goods[i][0]];
                    dp[j]   = tmp;
                }
            }
            int maxv = INT_MIN;
            int res  = 0;
            for(int i=0; i<dp.size(); ++i)maxv = ::std::max(maxv,dp[i]);
            for(int i=0; i<dp.size(); ++i){
                if(maxv==dp[i])res = res + N[i];
            }
            return res;
        }
        /*************************求方案************************************/
        void onePathPack(::std::vector<::std::vector<int>>& goods, int V){
            ::std::vector<::std::vector<int>> dp(goods.size()+4, ::std::vector<int>(V+4,0));
            for(int i=goods.size()-1; i>=0; --i){
                for(int j=0; j<=V; ++j){
                    dp[i][j] = dp[i+1][j];
                    if(j>=goods[i][0])dp[i][j] = ::std::max(dp[i][j], dp[i+1][j-goods[i][0]]+goods[i][1]);
                }
            }
            ::std::vector<int> res;
            int tmp = V;
            for(int i=0; i<goods.size(); ++i){
                if((tmp>=goods[i][0]) && (dp[i][tmp]==dp[i+1][tmp-goods[i][0]]+goods[i][1]) ){
                    res.push_back(i);
                    tmp = tmp - goods[i][0];
                }
            }
            ::std::cout<<"-----------------------------"<<::std::endl;
            for(int i=0; i<res.size(); ++i)::std::cout<<goods[res[i]][1]<<" ";
        }
        /********************有依赖的背包问题************************************************/
        void dfs(int index,::std::vector<::std::vector<int>>&goods, ::std::vector<::std::vector<int>>& dp,::std::vector<::std::vector<int>>& par, int V){
            for(int i=goods[index][0]; i<=V; ++i)dp[index][i] = goods[index][1];
            for(int i=0; i<par[index].size(); ++i){
                int y = par[index][i];
                dfs(y,goods,dp,par,V);
                for(int j=V; j>=goods[index][0]; --j){
                    for(int k=0; k<=j-goods[index][0]; ++k){
                        dp[index][j] = ::std::max(dp[index][j],dp[index][j-k]+dp[y][k]);
                    }
                }
            }
        }
        int YL_Pack(::std::vector<::std::vector<int>>& goods, int V){
            ::std::vector<::std::vector<int>> par(goods.size()+1,::std::vector<int>());
            ::std::vector<::std::vector<int>> dp(goods.size(),::std::vector<int>(V+1,0));
            int root;
            for(int i=0; i<goods.size(); ++i){
                if(goods[i][2] == -1){
                    root = i;
                }else{
                    par[goods[i][2]-1].push_back(i);
                }
            }
            dfs(root,goods,dp,par,V);
            return dp[root][V];
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    ::std::vector<::std::vector<int>> goods = {
        {2,3,-1},
        {2,2,1},
        {3,5,1},
        {4,7,2},
        {3,6,2}
    };
    ::std::cout<<te.YL_Pack(goods,7)<<::std::endl;
    //::std::vector<::std::vector<int>> goods = {
        //{1,2},
        //{2,4},
        //{3,4},
        //{4,6},
    //};
    //te.onePathPack(goods,5);
    //::std::vector<::std::vector<::std::vector<int>>> goods = {
        //{{1,2},{2,4}},
        //{{3,4}},
        //{{4,5}}
    //};
    //::std::cout<<te.gropPack(goods,5)<<::std::endl;
    //::std::vector<::std::vector<int>> goods = {
        //{1,2,3},
        //{2,4,4},
        //{3,4,5},
        //{4,5,6},
    //};
    //::std::cout<<te.towPack(goods,5,6)<<::std::endl;
    //::std::vector<::std::vector<int>> goods = {
        //{1,2,3},
        //{2,4,1},
        //{2,6,2},
        //{3,6,2},
        //{5,9,1},
        //{3,4,3},
        //{4,5,2}
    //};
    //::std::cout<<te.mutiplePack(goods,17)<<::std::endl;
    //::std::cout<<te.mutiplePack1(goods,17)<<::std::endl;
    //::std::cout<<te.mutiplePack2(goods,17)<<::std::endl;
    return 0;
}
