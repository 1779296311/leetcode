/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_zhuangyaDP.cpp
*     author   : @ JY
*     date     : 2020--06--30
**********************************************/
#include <climits>
#include <unordered_set>
#include <iostream>
#include <functional>
#include <list>
#include <numeric>
#include <climits>
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <vector>

class Solution {
public:
//LCP 04. 覆盖
    int domino(int n, int m,  std::vector<std::vector<int>> &broken){
        int all = (1 << m);
        std::vector<int> bro(n+1);
        std::vector<std::vector<int>> dp(n+1, std::vector<int>(all));
        for(auto &p : broken)bro[p[0]] |= 1 << p[1];
        std::function<int(int)> _calc = [&](int x){
            int res = 0;
            while(x){
                int r = x & (-x);
                if(x & (r << 1))++res;
                x &= ~(r);
                x &= ~(r << 1);
            }
            return res;
        };
        bro[n] = all - 1;
        for(int i=n-1; i>=0; --i){
            for(int cur=(~bro[i]) & (all-1); ;  cur = (cur-1)&(~bro[i])){
                int S = cur & (~bro[i+1]), ans = 0;
                for(int k=S; ; k=(k-1) & S){
                    ans = std::max(ans,
                            __builtin_popcount(k) + _calc(cur & (~k)) + dp[i+1][bro[i+1] | k]);
                    if(!k)break;
                }
                dp[i][~cur & (all-1)] = ans;
                if(!cur)break;
            }
        }
        return *std::max_element(begin(dp[0]), end(dp[0]));
    }

 //不需要回到原点
//dp[i][j]表示当前已经走过点的集合为i，移动到j
    int TSP(int n, ::std::vector<::std::vector<int>>& p){
        ::std::vector<::std::vector<int>> dp((1 << n), ::std::vector<int>(n + 1, 1e9));
        dp[1][0] = 0;
        for (int i = 0; i < (1 << n); ++i) {
            //for (int j = 0; j < n; ++j) {
                //if(!(i&(1<<j)))continue;
                //for (int k = 0; k < n; ++k) { //i
                    //if (!(i^(1<<j)&(1<<k)) || p[k][j]==-1)continue;
                    //dp[i][j] = ::std::min(dp[i][j], dp[i ^ (1 << j)][k] + p[k][j]);
                //}
            //}
            for(int j=0; j<n; ++j){
                if(i&(1<<j))continue;
                for(int k=0; k<n; ++k){
                    if(!(i&(1<<k)) || p[k][j]==-1)continue;
                    dp[i|(1<<j)][j] = ::std::min(dp[i|(1<<j)][j], dp[i][k] + p[k][j]);
                }
            }
        }
#ifdef debug
        for (int i = 0; i < n; ++i) {
            ::std::cout << dp[(1 << n) - 1][i]<< "--";
        }
        ::std::cout << std::endl;
        for (int j = 0; j < n; ++j) {
            if (p[j][0] == 1e9 || p[j][0]<=0) {
                ::std::cout << (1000000000) << "--";
            } else {
                ::std::cout << dp[(1 << n) - 1][j] + p[j][0] << "--";
            }
        }
        ::std::cout << std::endl;
#endif
        return dp[(1 << n) - 1][n-1]>=1e9?-1:dp[(1<<n)-1][n-1];
    }

#define ve   ::std::vector<int>
#define vve  ::std::vector<ve>
#define vvve ::std::vector<vve>

//有了连接这些岛屿的岛屿和桥梁的地图，众所周知，汉密尔顿路径是沿着桥梁的路径，因此它只能一次访问每个岛屿。在我们的地图上，每个岛都有一个正整数值。如果将以下所述的值最大化，我们将汉密尔顿路径称为最佳三角汉密尔顿路径。
//假设有n个岛。汉密尔顿路径C1C2 ... Cn的值计算为三部分之和。令Vi为岛Ci的值。作为第一部分，我们对路径中每个岛的所有Vi值求和。对于第二部分，对于路径中的每个边缘CiC i + 1，我们将乘积Vi * V i + 1相加。对于第三部分，每当三个连续的岛CiC i + 1 C i + 2在路径上，在地图上形成一个三角形，即Ci与C i + 2之间有一座桥，我们将乘积Vi * V i + 1 * V i + 2相加。
//您将要找到的最佳汉密尔顿三角形最佳路径（但不一定）包含许多三角形。很有可能会有不止一种最佳的三角形汉密尔顿路径；您的第二个任务是找到此类路径的数量
    void max_V_and_N(::std::vector<int>& v, ::std::vector<::std::vector<int>>& mp){
        int n = v.size();
        ::std::vector<::std::vector<int>> d(n, ::std::vector<int>(n, -1));
        vvve dp((1<<n), vve(n, ve(n, -1)));
        vvve s((1<<n),  vve(n, ve(n, 0)));
        for(int i=0; i<mp.size(); ++i){
            int i1 = mp[i][0];
            int j1 = mp[i][1];
            int st = (1<<i1) | (1<<j1);
            d[i1][j1]      = d[j1][i1]      = 1;
            dp[st][i1][j1] = dp[st][j1][i1] = v[i1] + v[j1] + v[i1] * v[j1];
            s[st][i1][j1]  = s[st][j1][i1]  = 1;
        }
        for(int state=0; state<(1<<n); ++state){
            for(int i=0; i<n; ++i){
                if(state&(1<<i))continue;
                for(int j=0; j<n; ++j){
                    if(d[i][j] == -1)continue;
                    if(!(state&(1<<j)))continue;
                    for(int k=0; k<n; ++k){
                        if(!(state&(1<<k)))continue;
                        if(d[k][j]==-1)continue;
                        if(dp[state][j][k]==-1)continue;
                        if(k==j)continue;
                        int tmp  = v[i] + v[j]*v[i] + dp[state][j][k];
                        if(d[i][k])tmp += v[i] * v[j] * v[k];
                        if(tmp>dp[state|(1<<i)][i][j]){
                            dp[state|(1<<i)][i][j] = tmp;
                            s[state|(1<<i)][i][j]  = s[state][j][k];
                        }else if(tmp==dp[state|(1<<i)][i][j]){
                            s[state|(1<<i)][i][j] += s[state][j][k];
                        }
                    }
                }
            }
        }
        //for(int state=0; state<(1<<n); ++state){
            //for(int i=0; i<n; ++i){
                //if((state&(1<<i))==0)continue;
                //for(int j=0; j<n; ++j){
                    //if(d[i][j]==-1)continue;
                    //if((state&(1<<j))==0)continue;
                    //if(i==j)continue;
                    //for(int k=0; k<n; ++k){
                        //if((state&(1<<k))==0 || i==k || i==j || j==k)continue;
                        //if(dp[state^(1<<i)][j][k]==-1)continue;
                        //if(d[j][k]==-1)continue;
                        //int tmp  = v[i] + v[j]*v[i] + dp[state^(1<<i)][j][k];
                        //if(d[i][k])tmp += v[i] * v[j] * v[k];
                        //if(tmp>dp[state][i][j]){
                            //dp[state][i][j] = tmp;
                            //s[state][i][j]  = s[state^(1<<i)][j][k];
                        //}else if(tmp==dp[state][i][j]){
                            //s[state][i][j] += s[state^(1<<i)][j][k];
                        //}
                    //}
                //}
            //}
        //}
        int res1 = -1;
        int res2 = 0;
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                if(i==j)continue;
                if(dp[(1<<n)-1][i][j] > res1){
                    res1 = dp[(1<<n)-1][i][j];
                    res2 = s[(1<<n)-1][i][j];
                }else if(dp[(1<<n)-1][i][j] == res1){
                    res2 += s[(1<<n)-1][i][j];
                }
            }
        }
        ::std::cout<<res1<<::std::endl;
        ::std::cout<<res2<<::std::endl;
    }


//有一个人要去旅游，他想要逛遍所有的城市，但是同一个城市又不想逛超过2次。现在给出城市之间的来往路费，他可以选择任意一个点为起点。问逛遍所有城市的最低路费是多少？
    int threenum[11] = {1,3,9,27,81,243,729,2187,6561,19683,59049};
    void get_three_n(int n, ::std::vector<::std::vector<int>>& three){
        int tmp = 0;
        for(int i=0; i<threenum[n]; ++i){
            tmp = i;
            for(int j=0; j<three[0].size() && tmp; ++j){
                three[i][j] = tmp%3;
                tmp /= 3;
            }
        }
    }
    int min_2_trvale(::std::vector<::std::vector<int>>& d){
        int n  = d.size();
        ::std::vector<::std::vector<int>> dp(threenum[n],    ::std::vector<int>(n+1, 1e9));
        ::std::vector<::std::vector<int>> three(threenum[n], ::std::vector<int>(n+1, 0));
        for(int i=0; i<n; ++i){
            dp[threenum[i]][i] = 0;
        }
        get_three_n(n, three);
        int  res = 1e9;
        bool f   = false;
        for(int state=0; state<threenum[n]; ++state){
            f = true;
            for(int i=0; i<n; ++i){
                if(three[state][i])continue;
                if(dp[state][i]==1e9)f = false;
                for(int j=0; j<n; ++j){
                    if(three[state][j]!=1)continue;
                    dp[state+threenum[i]][i] = ::std::min(dp[state+threenum[i]][i], dp[state][j]+d[j][i]);
                }
            }
            if(f){
                for(int k=0; k<n; ++k){
                    res = ::std::min(res, dp[state][k]);
                }
            }
        }
        //for(int i=0; i<threenum[n]; ++i){
            //f = true;
            //for(int j=0; j<n; ++j){
                //if(three[i][j]==0){
                    //f = false;
                    //continue;
                //}
                //if(i==j)continue;
                //for(int k=0; k<n; ++k){
                    //if(three[i][k]==0)continue;
                    //dp[i][j] = ::std::min(dp[i][j], dp[i-threenum[j]][k]+d[k][j]);
//#ifdef debug
    //::std::cout<<dp[i][j]<<"*";
//#endif
                //}
            //}
            //if(f){
                //for(int t=0; t<n; ++t){
                    //res = ::std::min(res, dp[i][t]);
                //}
            //}
        //}
        return res>=1e9?-1:res;
    }
                                                                //需要回到原点
//其中1≤ ñ ≤10.在此之后将是Ñ + 1行，每行含有Ñ + 1点的整数表示该次比萨饼之间的行程（编号0）和n个位置（数字1到n）。该Ĵ在上个值我个线路表示时间直接从位置去我到位置Ĵ无需访问沿途的任何其他地点。请注意，从i到j可能会有更快的方法由于速度限制，交通信号灯等的不同，也会通过其他位置。另外，时间值可能不是对称的，即直接从位置i到j的时间可能与直接从位置i的时间不同Ĵ给我。输入值n = 0将终止输入
    void floyd(::std::vector<::std::vector<int>>& p){
        int n = p.size();

        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                for(int k=0; k<n; ++k){
                    p[j][k] = ::std::min(p[j][k], p[j][i]+p[i][k]);
                }
            }
        }
    }
    int send_pizzas(::std::vector<::std::vector<int>>& pizzas){
        floyd(pizzas);
        int n = pizzas.size();
        ::std::vector<::std::vector<int>> dp((1<<n), ::std::vector<int>(n+1, 1e9));
        dp[1][0] = 0;
        for(int state=0; state<(1<<n); ++state){
            state |= 1;
            for(int i=0; i<n; ++i){
                for(int j=0; j<n; ++j){
                    if(!(state&(1<<j)))continue;
                    dp[state|1<<i][i] = ::std::min(dp[state|1<<i][i], dp[state][j] + pizzas[j][i]);
                }
            }
        }
#ifdef debug
        for(int i=0; i<n; ++i){
            ::std::cout<<dp[(1<<n)-1][i]<<"---";
        }
#endif
        return dp[(1<<n)-1][0]>=1e9?-1:dp[(1<<n)-1][0];
    }

//只走一次
    int tsp(int n, ::std::vector<::std::vector<int>>& p){
        ::std::vector<::std::vector<int>> dp((1 << n), ::std::vector<int>(n + 1, 1e9));
        dp[0][0] = 0;
        for (int i = 0; i < (1 << n); ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) { //i
                    if ((i>>k&1)==0 || p[k][j]==-1)continue;
                    dp[i][j] = ::std::min(dp[i][j], dp[i ^ (1 << k)][k] + p[k][j]);
                }
            }
        }
#ifdef debug
    for(int j=0; j<=n; ++j){
        ::std::cout<<dp[(1<<n)-1][j]<<"--";
    }
    ::std::cout<<std::endl;
#endif
        return dp[(1 << n) - 1][0]>=1e9?-1:dp[(1<<n)-1][0];
    }

    //农夫约翰的土地由M*N个小方格组成，现在他要在土地里种植玉米。
    //非常遗憾，部分土地是不育的，无法种植。
    //而且，相邻的土地不能同时种植玉米，也就是说种植玉米的所有方格之间都不会有公共边缘。
    //现在给定土地的大小，请你求出共有多少种种植方法。
    //土地上什么都不种也算一种方法。
    int plant_corn(::std::vector<::std::vector<int>>& land){
        int m = land.size();
        int n = land[0].size();
        ::std::vector<int> L;
        for (int i = 0; i < m; ++i) {
            L.push_back(0);
            for (int j = 0; j < n; ++j) {
                L[i] |= (land[i][j] << (n - j - 1));
            }
#ifdef debug
    ::std::cout << L[i] << ::std::endl;
#endif
        }
        ::std::vector<::std::vector<int>> dp((m + 1), ::std::vector<int>((1 << n), 0));
        for (int i = 0; i < (1 << n); ++i) {
            dp[1][i] = (L[0] & i)==i && !(i&(i<<1));
        }
        for (int i = 2; i <= m; ++i) {
            for (int j = 0; j < (1 << n); ++j) {
                if (j&(j>>1) || (j&L[i-1])!=j)continue;
                for (int k = 0; k < (1 << n); ++k) {
                    if (k&(k>>1) || k&j || (k&L[i-2])!=k)continue;
                    dp[i][j] += dp[i - 1][k];
                }
            }
        }
#ifdef debug
        for(int i=0; i<=m; ++i){
            for(int j=0; j<(1<<n); ++j){
                ::std::cout<<dp[i][j]<<"---";
            }
            ::std::cout<<::std::endl;
        }
#endif
        int res = 0;
        for(int i=0; i<(1<<n); ++i)res += dp[m][i];
        return res;
    }

//司令部的将军们打算在N*M的网格地图上部署他们的炮兵部队。一个N*M的地图由N行M列组成，地图的每一格可能是山地（用"H" 表示），也可能是平原（用"P"表示），如下图。在每一格平原地形上最多可以布置一支炮兵部队（山地上不能够部署炮兵部队）；一支炮兵部队在地图上的攻击范围如图中黑色区域所示：
//                                                                                *
//                                                                                *
//                                                                            * * @ * *
//                                                                                *
//                                                                                *
//如果在地图中的灰色所标识的平原上部署一支炮兵部队，则图中的黑色的网格表示它能够攻击到的区域：沿横向左右各两格，沿纵向上下各两格。图上其它白色网格均攻击不到。从图上可见炮兵的攻击范围不受地形的影响。
//现在，将军们规划如何部署炮兵部队，在防止误伤的前提下（保证任何两支炮兵部队之间不能互相攻击，即任何一支炮兵部队都不在其他支炮兵部队的攻击范围内），在整个地图区域内最多能够摆放多少我军的炮兵部队。
    int max_artillery(::std::vector<::std::vector<char>>& land){
        int n = land.size();
        int m = land[0].size();
        ::std::vector<int>L(n+1, 0);
        for(int i=0; i<n; ++i){
            for(int j=0; j<m; ++j){
                L[i+1] = (L[i+1]<<1) | (land[i][j]=='P');
            }
        }
#ifdef debug
    for(int i=0; i<n; ++i){
        ::std::cout<<L[i+1]<<::std::endl;
    }
    ::std::cout<<::std::endl;
#endif
        ::std::vector<int>ok;
        vvve dp(n+1, vve((1<<m), ve((1<<m), 0)));
        for(int i=1; i<(1<<m); ++i){
            if(((i>>1)&i) || ((i>>2)&i))continue;
            if((L[1]&i)==i)dp[1][i][1] = __builtin_popcount(i);
            ok.push_back(i);
        }
        for(int i=2; i<=n; ++i){
            for(auto &now : ok){
                if((now&L[i]) != now)continue;
                for(auto &pre : ok){
                    if(now&pre || (pre&L[i-1])!=pre)continue;
                    for(auto &ppre : ok){
                        if(now&ppre || ppre&pre )continue;
                        dp[i][now][pre] = ::std::max(dp[i][now][pre], dp[i-1][pre][ppre] + __builtin_popcount(now));
                    }
                }
            }
        }
        int res = 0;
        for(int k=1;k<=n; ++k){
            for(int i=0; i<(1<<m); ++i){
                for(int j=0; j<(1<<m); ++j){
                    ::std::cout<<dp[k][i][j]<<"--";
                    res = ::std::max(res, dp[k][i][j]);
                }
                ::std::cout<<::std::endl;
            }
        }
        ::std::cout<<::std::endl;
        return res;
    }

//给你一个整数 n 表示某所大学里课程的数目，编号为 1 到 n ，数组 dependencies 中， dependencies[i] = [xi, yi]  表示一个先修课的关系，也就是课程 xi 必须在课程 yi 之前上。同时你还有一个整数 k 。
//在一个学期中，你 最多 可以同时上 k 门课，前提是这些课的先修课在之前的学期里已经上过了。
//请你返回上完所有课最少需要多少个学期。题目保证一定存在一种上完所有课的方式。
    int minDay(int n, int k, vve& d){
        ::std::vector<int> dp((1<<n), 0);
        ::std::vector<int> pre((1<<n), 0);
        for(auto &n : d){
            pre[(1<<(n[1]-1))] |= (1<<(n[0]-1));
        }
        for(int i=1; i<(1<<n); ++i){
            pre[i] = pre[i^(i&-i)] | pre[i&-i];
        }
        for(int i=1; i<(1<<n); ++i){
            for(int j=i; j; j=(j-1)&i){
                if(__builtin_popcount(j) > k)continue;
                if((pre[j]&(i^j)) != pre[j])continue;
                dp[i] = ::std::min(dp[i], dp[i^j]+1);
            }
        }
        return dp[(1<<n)-1];
    }

//大矩形的高度h和宽度w。1 <= h，w <= 11。
//输出给定矩形可以用大小为2的小矩形填充的不同方式的数量。假设给定的大矩形是定向的，即多次计数对称平铺
    bool judge(int li, int lj, int W){
        int i = 0;
        while(i<W){
            int p = lj&(1<<i);
            int c = li&(1<<i);
            if(!c){
                if(!p)return false;
                ++i;
            }else{
                if(!p){
                    ++i;
                    continue;
                }else if(i==(W-1) || !(lj&(1<<++i)) || !(li&(1<<i++))){
                    return false;
                }
            }
        }
	    return true;
    }
    int judge1(int li, int W){
        int i = 0;
        while(i<W){
            if(li&(1<<i)){
                if(i==W-1 || !(li&(1<<++i)))return false;
            }
            ++i;
        }
        return true;
    }
    int ran_n(int h, int w){
        if(w>h)::std::swap(h, w);
        ::std::vector<::std::vector<int>> dp(h+1, ::std::vector<int>((1<<w), 0));
        for(int i=0; i<(1<<w); ++i)dp[0][i] = judge1(i, w);
        for(int i=1; i<h; ++i){
            for(int now=0; now<(1<<w); ++now){
                for(int pre=0; pre<(1<<w); ++pre){
                    if(judge(now, pre, w)) dp[i][now] += dp[i-1][pre];
                }
            }
        }
        return dp[h-1][(1<<w)-1];
    }

//在N×N的棋盘里面放K个国王，使他们互不攻击，共有多少种摆放方案。国王能攻击到它上下左右，以及左上
//左下右上右下八个方向上附近的各一个格子，共8个格子。
    int king_n(int n, int k){
        vvve dp(n+1,vve((1<<n),ve(k,0)));
        dp[0][0][0] = 1;
        ::std::vector<int> ok;
        for(int i=0; i<(1<<n); ++i){
            if(i&(i>>1))continue;
            ok.push_back(i);
        }
        for(int i=1; i<=n; ++i){
            for(auto &now : ok){
                for(auto &pre : ok){
                    if(pre&now || (now&(pre>>1)) || (pre&(now>>1)))continue;
                    int N = __builtin_popcount(now);
                    for(int pre_n=__builtin_popcount(pre); pre_n+N<=k; ++pre_n){
                            dp[i][now][pre_n+N] += dp[i-1][pre][pre_n];
                    }
                }
            }
        }
        long long res = 0;
        for(auto &i : ok)res += dp[n][i][k];
        return res;
    }
//已知镇海中学内共有n处景点。现在有n位该校的学生志愿承担导游和讲解任务。每个学生志愿者对各个景点的熟悉程度是不同的，如何将n位导游分配至n处景点，使得总的熟悉程度最大呢？要求每个景点处都有一个学生导游。(1≤n≤17)
    int visit_n(::std::vector<::std::vector<int>>& d){
        int n = d.size();
        ::std::vector<int> dp((1<<n), 0);
        for(int i=0; i<(1<<n); ++i){
            for(int j=0; j<n; ++j){
                if(i&(1<<j))dp[i] = ::std::max(dp[i], dp[i^(1<<j)] + d[j][__builtin_popcount(i^(1<<j))]);
            }
        }
#ifdef debug
        for(int i=0; i<(1<<n); ++i){
            ::std::cout<<dp[i]<<"--";
        }
        ::std::cout<<::std::endl;
#endif
        return dp[(1<<n)-1];
    }

//有n颗原子，给出一个n*n的矩阵map。map[i][j]=a，则代表第i个原子和第j个相撞，且第j个原子会消失，并且释放出a的能量，现在求释放能量的最大值是多少。
    int max_power(::std::vector<::std::vector<int>>& b){
        int n = b.size();
        ::std::vector<int> dp((1<<n), 0);
        for(int i=0; i<(1<<n); ++i){
            for(int j=0; j<n; ++j){
                if(i&(1<<j))continue;
                for(int k=0; k<n; ++k){
                    if(i&(1<<k))continue;
                    if(k==j)continue;
                    dp[i|(1<<k)] = ::std::max(dp[i|(1<<k)], dp[i]+b[j][k]);
                }
            }
        }
#ifdef debug
        for(int i=0; i<(1<<n); ++i){
            ::std::cout<<dp[i]<<"--";
        }
        ::std::cout<<::std::endl;
#endif
        int res = 0;
        return res;
    }

//总共有 n 个人和 40 种不同的帽子，帽子编号从 1 到 40 。 给你一个整数列表的列表 hats ，其中 hats[i] 是第 i 个人所有喜欢帽子的列表。 请你给每个人安排一顶他喜欢的帽子，确保每个人戴的帽子跟别人都不一样，并返回方案数。 由于答案可能很大，请返回它对 10^9 + 7 取余后的结果。
        int numberWays(::std::vector<::std::vector<int>> & hats){
            long long MOD = 1000000007;
            int size      = hats.size();
            ::std::vector<::std::vector<int>> dp((1<<size)+1, ::std::vector<int>(41, 0));
            ::std::vector<::std::vector<bool>> mp(41, ::std::vector<bool>(size, false));

            for(int i=0; i<size; ++i){
                for(auto &n : hats[i]){
                    mp[n][i] = true;
                }
            }

            dp[0][0] = 1;
            for(int i=1; i<41; ++i){
                for(int state=0; state<(1<<size); ++state){
                    dp[state][i] += dp[state][i-1];  // 不选第i顶帽子
                    dp[state][i] %= MOD ;
                    for(int k=0; k<size; ++k){
                        if(state&(1<<k))continue;
                        if(!mp[i][k])continue;
                        dp[state|(1<<k)][i] = (dp[state|(1<<k)][i] + dp[state][i-1]) % MOD;
                    }
                }
            }
#ifdef debug
   for(int i=0; i<(1<<size); ++i){
       for(int j=0; j<41; ++j){
           ::std::cout<<dp[i][j]<<"--";
       }
       ::std::cout<<::std::endl;
   }
#endif
            return dp[(1<<size)-1][40] % MOD;
        }
        int numberWay_better(::std::vector<::std::vector<int>> & hats){
            const int MOD = 1e9+7;
            int size = hats.size();
            ::std::vector<int> dp((1<<size), 0);
            ::std::vector<::std::unordered_set<int>> mp(41);
            for(int i=0; i<size; ++i){
                for(auto &h : hats[i]){
                    mp[h].insert(i);
                }
            }
            dp[0] = 1;
            for(int i=0; i<41; ++i){
                for(int state=(1<<size)-1; state>=0; --state){
                    for(auto &people : mp[i]){
                        if(state&(1<<people))continue;
                        dp[state|(1<<people)] = (dp[state|(1<<people)] + dp[state]) % MOD;
                    }
                }
            }
            return dp[(1<<size)-1] % MOD;
        }



//轮廓线DP-------or------------插头DP--------
};
int main(int argc, const char* argv[])
{
    Solution te;
    ::std::vector<int> v = {2,2,2};
    ::std::vector<::std::vector<int>> d = {
        {0,1},
        {1,2},
        {2,0},
    };
    te.max_V_and_N(v,d);
//1 2;
//2 3
//3 1
    //::std::vector<::std::vector<int>> d = {
        //{0,        40, (int)1e9},
        //{40,        0,       50},
        //{(int)1e9, 50,        0},
    //};
    //::std::vector<::std::vector<int>> d = {
        //{0,        3,         4},
        //{3,        0,       10},
        //{4, 10,        0},
    //};
//1 2 3
//1 3 4
//2 3 10
    //::std::cout<<te.min_2_trvale(d)<<::std::endl;
    //::std::vector<::std::vector<int>> p = {
            //{0,  1, 10, 10},
            //{1,  0,  1,  2},
            //{10, 1,  0, 10},
            //{10, 2, 10,  0},
        //{ 0,  5,  5, -1, -1},
        //{-1,  0,  6,  6, -1},
        //{-1, -1,  0,  6,  7},
        //{ 4, -1, -1,  0,  6},
        //{ -1,  4, -1, -1,  0}
    //};
    //::std::cout<<te.send_pizzas(p)<<::std::endl;
    //::std::cout<<te.tsp(5,p)<<::std::endl;
    //::std::cout<<te.TSP(5,p)<<::std::endl;
    //::std::vector<::std::vector<int>> d = {
           ////{0, 4},
           ////{1, 0},
            //{0, 20, 1},
            //{12, 0, 1},
            //{1, 10, 0}
    //};
    //te.max_power(d);
    //::std::vector<::std::vector<int>> d = {
           //{10, 6, 8},
           //{9,  2, 3},
           //{1,  7, 2},
    //};
    //::std::cout<<te.visit_n(d)<<::std::endl;
    //::std::cout<<te.ran_n(4,11)<<::std::endl;
    //::std::vector<::std::vector<char>> land = {
        //{'P','H','P','P'},
        //{'P','P','H','H'},
        //{'P','P','P','P'},
        //{'P','H','P','P'},
        //{'P','H','H','P'},
    //};
//[>
//*/

    //::std::vector<::std::vector<char>> land1 = {
        //{'P','H','H','P','P'},
        //{'H','P','P','H','P'},
        //{'P','P','H','P','P'},
        //{'P','P','P','P','P'},
        //{'P','P','P','P','P'},
        //{'P','P','H','P','P'},
        //{'P','P','H','P','P'},
        //{'H','P','P','P','H'},
        //{'H','P','H','H','H'},
        //{'H','P','H','P','H'}
    //};
    //::std::cout<<te.max_artillery(land1)<<::std::endl;
    //::std::cout<<te.max_artillery(land)<<::std::endl;
    //::std::vector<::std::vector<int>> land = {
        //{ 1, 1, 1 },
        //{ 0, 1, 0 },
    //};
    //::std::cout << te.plant_corn(land) << ::std::endl;
    //::std::vector<::std::vector<int>> graph1 = {
        //{ 0, 2, 1, 3 },
        //{ 2, 0, 1, 1 },
        //{ 1, 2, 0, 1 },
        //{ 1, 1, 1, 0 }
    //};
    //::std::vector<::std::vector<int>> g1 = {
        //{ 0,  5,  5, -1, -1},
        //{-1,  0,  6,  6, -1},
        //{-1, -1,  0,  6,  7},
        //{ 4, -1, -1,  0,  6},
        //{ 5,  4, -1, -1,  0}
    //};
    //::std::vector<::std::vector<int>> g2 = {
        //{ 0, 91,  32,-1},
        //{91,  0,  131,  124},
        //{32, 131,  0,  43},
        //{ -1, 124, 43,  0}
    //};
    //::std::vector<::std::vector<int>> graph = {
        //{ 0,  2, -1, 3},
        //{-1,  0,  6, 1},
        //{ 5,  2,  0, 4},
        //{ 5,  1,  3, 0}
    //};
    //::std::vector<::std::vector<int>> g = {
        //{0, 2, 4, 5, 1},
        //{2, 0, 6, 5, 3},
        //{4, 6, 0, 8, 3},
        //{5, 5, 8, 0, 5},
        //{1, 3, 3, 5, 0}
    //};
    //::std::vector<::std::vector<int>> g3 = {
        //{0, 1, 3},
        //{1, 0, 2},
        //{3, 2, 0}
    //};
    //::std::cout<<te.TSP(5,g1)<<::std::endl;
    //::std::cout<<te.tsp(5,g1)<<::std::endl;
    //::std::cout<<te.TSP(4,graph)<<::std::endl;
    //::std::cout<<te.TSP(5,g)<<::std::endl;
    return 0;
}
