/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_dp_pro.cpp
*     author   : @ JY
*     date     : 2020--07--05
**********************************************/
#include <iostream>
#include <queue>
#include <unordered_map>
#include <list>
#include <set>
#include <unordered_set>
#include <vector>
#include <climits>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <stdlib.h>
class Solution{
    public:
//给定一个整数 n，求以 1 ... n 为节点组成的二叉搜索树有多少种？
        int numTree(int n){
            ::std::vector<int> dp(n+1, 0);
            dp[0] = 1;
            for(int i=1; i<=n; ++i){
                for(int j=i; j>=1; --j){
                    dp[i] += dp[j-1] * dp[i-j];
                }
            }
            return dp[n];
        }

//给你一个由若干 0 和 1 组成的二维网格 grid，请你找出边界全部由 1 组成的最大 正方形 子网格，并返回该子网格中的元素数量。如果不存在，则返回 0。
        int largestBorderSquare(::std::vector<::std::vector<int>>& grid){
            int n = grid.size();
            int m = grid[0].size();
            ::std::vector<::std::vector<int>> top(grid);
            ::std::vector<::std::vector<int>> left(grid);
            for(int i=0; i<n; ++i){
                for(int j=0; j<m; ++j){
                    if(!grid[i][j])continue;
                    if(i) top[i][j]   += top[i-1][j];
                    if(j) left[i][j]  += left[i][j-1];
                }
            }
            int res = 0;
            ::std::vector<::std::vector<int>> dp(n, ::std::vector<int>(m, 0));
            for(int i=0; i<n; ++i){
                for(int j=0; j<m; ++j){
                    int len = ::std::min(left[i][j], top[i][j]);
                    while(len < res){
                        if(left[i-len+1][j]>=len && top[i][j-len+1]>=len){
                            res = ::std::max(res, len);
                            break;
                        }
                        --len;
                    }
                }
            }
            return res*res;
        }

//给出一些不同颜色的盒子，盒子的颜色由数字表示，即不同的数字表示不同的颜色。
//你将经过若干轮操作去去掉盒子，直到所有的盒子都去掉为止。每一轮你可以移除具有相同颜色的连续 k 个盒子（k >= 1），这样一轮之后你将得到 k*k 个积分。
//当你将所有盒子都去掉之后，求你能获得的最大积分和
#define ve   ::std::vector<int>
#define vve  ::std::vector<ve>
#define vvve ::std::vector<vve>
        int removeBoxes(::std::vector<int>& boxs){
            int size = boxs.size();
            vvve dp(size, vve(size, ve(size, 0)));
            return dfs(boxs, dp, 0, size-1, 0);
        }
        int dfs(ve& boxs, vvve&dp, int l, int r, int n){
            if(l>r)return 0;
            if(dp[l][r][n])return dp[l][r][n];
            while(r>l && boxs[r]==boxs[r-1]){
                --r;
                ++n;
            }
            dp[l][r][n] = dfs(boxs, dp, l, r-1, 0) + (n+1)*(n+1);
            for(int i=l; i<r; ++i){
                if(boxs[i]==boxs[r]){
                    dp[l][r][n] = ::std::max(dp[l][r][n], dfs(boxs, dp, l, i, n+1)+dfs(boxs, dp, i+1, r-1, 0));
                }
            }
            return dp[l][r][n];
        }

//给定一个整数数组 nums ，你可以对它进行一些操作。
//每次操作中，选择任意一个 nums[i] ，删除它并获得 nums[i] 的点数。之后，你必须删除每个等于 nums[i] - 1 或 nums[i] + 1 的元素。
//开始你拥有 0 个点数。返回你能通过这些操作获得的最大点数。
        int deleteAndEarn(::std::vector<int>& nums){
            if(!nums.size())return 0;
            //int maxv = -1;
            //for(auto &n : nums)maxv = ::std::max(maxv, n);
            int maxv   = *(::std::max_element(nums.begin(), nums.end()));
            ::std::vector<int> index(maxv+1, 0);
            ::std::vector<int> dp(maxv+1, 0);
            for(auto &n : nums)++index[n];

            dp[1] = index[1];
            for(int i=2; i<=maxv; ++i){
                dp[i] = ::std::max(dp[i-1], dp[i-2]+i*index[i]);
            }
            return dp[maxv];
        }

//硬币。给定数量不限的硬币，币值为25分、10分、5分和1分，编写代码计算n分有几种表示法。(结果可能会很大，你需要将结果模上1000000007)
        int wayToChange(int n){
            ::std::vector<int> dp(n+1, 1);
            ::std::vector<int> coins = {1,5,10,25};
            for(int i=2; i<coins.size(); ++i){
                for(int j=coins[i]; j<=n; ++j){
                    dp[i] += (dp[j-coins[i]] % 1000000007);
                }
            }
            return dp[n] % 1000000007;
        }

//在 "100 game" 这个游戏中，两名玩家轮流选择从 1 到 10 的任意整数，累计整数和，先使得累计整数和达到 100 的玩家，即为胜者。
//如果我们将游戏规则改为 “玩家不能重复使用整数” 呢？
//例如，两个玩家可以轮流从公共整数池中抽取从 1 到 15 的整数（不放回），直到累计整数和 >= 100。
//给定一个整数 c（整数池中可选择的最大数）和另一个整数 d（累计和），判断先出手的玩家是否能稳赢（假设两位玩家游戏时都表现最佳）？
//你可以假设 c 不会大于 20， d 不会大于 300。
        bool canIWin(int c, int d){
            if(c>=d)return true;
            if(((1+c)*c)/2 < d)return false;
            ::std::vector<int> dp((1<<(c+1)), -1);
            return dfs(c, d, 0, dp);
        }
        bool dfs(int c, int d, int state, ::std::vector<int>& dp){
            if(d<=0)return false;
            if(dp[state]!=-1)return dp[state];
            for(int i=c; i>=1; --i){
                if(state&(1<<i))continue;
                if(dfs(c, d-i, state|(1<<i), dp))continue;
                return dp[state]=true;
            }
            return dp[state]=false;
        }

//一个厨师收集了他 n 道菜的满意程度 satisfaction ，这个厨师做出每道菜的时间都是 1 单位时间。
//一道菜的 「喜爱时间」系数定义为烹饪这道菜以及之前每道菜所花费的时间乘以这道菜的满意程度，也就是 time[i]*sf[i] 。
//请你返回做完所有菜 「喜爱时间」总和的最大值为多少。
//你可以按 任意 顺序安排做菜的顺序，你也可以选择放弃做某些菜来获得更大的总和。
        int maxStatisfaction(::std::vector<int>& sf){
            ::std::sort(sf.begin(), sf.end());
            int size  = sf.size();
            int index = 0;
            int sum   = 0;
            int sum1  = 0;
            while(size>index && sf[index]<0)++index;
            if(index==size)return 0;
            for(int i=index,j=1; i<size; ++i,++j){
                sum1 += sf[i];
                sum  += (j*sf[i]);
            }
            for(int i=index-1,j=1; i>=0; --i,++j){
                if(abs(sum1)<abs(sf[i]))break;
                sum1 += sf[i];
                sum  += sum1;
            }
            return sum;
        }
        int maxStatisfaction_better(::std::vector<int>& sf){
            int sum1  = 0;
            int sum   = 0;
            int res   = 0;
            for(int i=sf.size()-1; i>=0;--i){
                sum  += sum + sf[i];
                res   = ::std::max(res, sum);
                sum1 += sf[i];
            }
            return res;
        }
        int maxStatisfaction_dp(::std::vector<int>& sf){
            int size = sf.size();
            int res  = 0;
            ::std::sort(sf.begin(), sf.end());
            ::std::vector<int> dp(size, -1e6);
            dp[0] = 0;
            for(int i=0; i<size; ++i){
                for(int j=i; j>=0; --j){
                    dp[j+1] = ::std::max(dp[j+1], dp[j]+((j+1)*sf[i]));
                    res     = ::std::max(res, dp[j+1]);
                }
            }
            return res;
        }

//给定一个包含 非负数 的数组和一个目标 整数 k，编写一个函数来判断该数组是否含有连续的子数组，其大小至少为 2，且总和为 k 的倍数，即总和为 n*k，其中 n 也是一个整数。
        bool checkSubarraySum(::std::vector<int>& nums, int k){
            int size = nums.size();
            ::std::unordered_map<int, int> hp;
            int sum = 0;
            for(int i=0; i<size; ++i){
                sum += nums[i];
                if(k){
                    sum = sum % k;
                }
                if(hp.count(sum)){
                    if(i-hp[sum]>1)return true;
                }else{
                    hp[sum] = i;
                }
            }
            return false;
        }
        
//你正在安装一个广告牌，并希望它高度最大。这块广告牌将有两个钢制支架，两边各一个。每个钢支架的高度必须相等。
//你有一堆可以焊接在一起的钢筋 rods。举个例子，如果钢筋的长度为 1、2 和 3，则可以将它们焊接在一起形成长度为 6 的支架。
//返回广告牌的最大可能安装高度。如果没法安装广告牌，请返回 0。
        int tallestBillboard(::std::vector<int>& rods){
            int res  = 0;
            int size = rods.size();
            int maxv = ::std::accumulate(rods.begin(), rods.end(), 0);
            ::std::vector<int> dp(maxv+1, 0);
            for(int i=1; i<=size; ++i){
                auto tmp = dp;
                for(int j=0; j<=maxv; ++j){
                    if(dp[j]<j)continue;

                    int k  = j + rods[i-1];
                    tmp[k] = ::std::max(tmp[k], dp[j] + rods[i-1]);
                    k      = abs(j - rods[i-1]);
                    tmp[k] = ::std::max(tmp[k], dp[j] + rods[i-1]);
                }
                ::std::swap(tmp, dp);
            }
            return dp[0]>>1;
        }
        int tallestBillboard_fuck(::std::vector<int>& rods){
            int res = 0;
            int size = rods.size();
            if(size<2)return 0;
            for(int i=0; i<(1<<size); ++i){
                for(int j=0; j<(1<<size); ++j){
                    if(i&j)continue;
                    int a = calc(i, rods);
                    int b = calc(j, rods);
#ifdef debug
     if(i==14 && j==1){
         ::std::cout<<a<<"--"<<b<<::std::endl;
         ::std::cout<<i<<"--"<<j<<::std::endl;
     }
#endif
                    if(a==b){
                        res = ::std::max(res, a);
                    }
                }
            }
            return res;
        }
        int calc(int n, ::std::vector<int>& rods){
            int res = 0;
            int k   = 0;
            while(k<32){
                if(n&(1<<k++))res += rods[rods.size()-k];
            }
            return res;
        }

///矩阵链乘法
//相似的题目有 887鸡蛋掉落 312戳气球 132分割回文串

//我们正在玩一个猜数游戏，游戏规则如下：
//我从 1 到 n 之间选择一个数字，你来猜我选了哪个数字。
//每次你猜错了，我都会告诉你，我选的数字比你的大了或者小了。
//然而，当你猜了数字 x 并且猜错了的时候，你需要支付金额为 x 的现金。直到你猜到我选的数字，你才算赢得了这个游戏。
        int getMoneyAmount(int n){
            ::std::vector<::std::vector<int>> dp(n+1, ::std::vector<int>(n+1, INT_MAX));
            for(int i=0; i<=n; ++i)dp[i][i] = 0;
            for(int j=1; j<=n; ++j){
                for(int i=j; i>=1; --i){
                    if(i==j-1){
                        dp[i][j] = i;
                        continue;
                    }
                    for(int k=i+1; k<j; ++k){
                        dp[i][j] = ::std::min(dp[i][j], ::std::max(dp[i][k-1], dp[k+1][j])+k);
                    }
                }
            }
        //for(int l=1;l<=n;l++){
            //for(int i=1;i+l<=n;i++){
                //int j = i+l;
                //if(i==j-1){
                    //dp[i][j] = i;
                    //continue;
                //}
                //for(int k=i+1;k<j;k++){
                    //dp[i][j] = ::std::min(dp[i][j],::std::max(dp[i][k-1],dp[k+1][j])+k);
                    
                //}
            //}
        //}
        //return dp[1][n];
#ifdef debug
  for(int i=0; i<=n; ++i){
      for(int j=0; j<=n; ++j){
          if(dp[i][j]>(INT_MAX/2) || dp[i][j]<0){
            ::std::cout<<"M"<<"--";
          }else{
            ::std::cout<<dp[i][j]<<"--";
          }
      }
      ::std::cout<<::std::endl;
  }
::std::cout<<"------"<<dp[1][n]<<::std::endl;
#endif
            return dp[1][n];
        }
//你将获得 K 个鸡蛋，并可以使用一栋从 1 到 N  共有 N 层楼的建筑。
//每个蛋的功能都是一样的，如果一个蛋碎了，你就不能再把它掉下去。
//你知道存在楼层 F ，满足 0 <= F <= N 任何从高于 F 的楼层落下的鸡蛋都会碎，从 F 楼层或比它低的楼层落下的鸡蛋都不会破。
//每次移动，你可以取一个鸡蛋（如果你有完整的鸡蛋）并把它从任一楼层 X 扔下（满足 1 <= X <= N）。
//你的目标是确切地知道 F 的值是多少。
//无论 F 的初始值如何，你确定 F 的值的最小移动次数是多少？
        int superEggDrop(int K, int N){
//令f[i][j]表示当前有i个鸡蛋且最多可测j次时能测量最多多高的楼层
//按照第一次测量时 碎还是不碎来划分
            ::std::vector<::std::vector<int>> dp(K+1, ::std::vector<int>(N+1, 0));
            for(int j=1; j<=N; ++j){
                for(int i=1; i<=K; ++i){
                    dp[i][j] = dp[i-1][j-1] + dp[i][j-1] + 1;
                }
                if(dp[K][j]>=N)return j;
            }
            return 0;
        }
        int superEggDrop_fuck(int K, int N){
// 记dp[i][k]表示有k个鸡蛋，i层楼中确定F的具体值的最小搜索次数
            ::std::vector<::std::vector<int>> dp(N+1, ::std::vector<int>(K+1, INT_MAX));
            for(int i=0; i<=N; ++i)dp[i][0] = dp[i][1] = i;
            for(int i=0; i<=K; ++i)dp[0][i] = dp[1][i] = 1;

            for(int i=2; i<=N; ++i){
                for(int j=2; j<=K; ++j){
                    for(int t=1; t<=i; ++t){
                        dp[i][j] = ::std::min(dp[i][j], ::std::max(dp[t-1][j-1], dp[i-t][j])+1);
                    }
                }
            }

            return dp[N][K];
        }
//有 n 个气球，编号为0 到 n-1，每个气球上都标有一个数字，这些数字存在数组 nums 中。
//现在要求你戳破所有的气球。如果你戳破气球 i ，就可以获得 nums[left] * nums[i] * nums[right] 个硬币。 这里的 left 和 right 代表和 i 相邻的两个气球的序号。注意当你戳破了气球 i 后，气球 left 和气球 right 就变成了相邻的气球。
//求所能获得硬币的最大数量。
//说明:
//你可以假设 nums[-1] = nums[n] = 1，但注意它们不是真实存在的所以并不能被戳破。
//0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
        int maxCoins(::std::vector<int>& nums){
// memo[begin][end]  ~~ (begin+1 -- end-1)
            nums.insert(nums.begin(), 1);
            nums.push_back(1);
            int size = nums.size();
#ifdef debug
   for(int i=0; i<size; ++i){
       ::std::cout<<nums[i]<<"---";
   }
   ::std::cout<<::std::endl;
#endif
            ::std::vector<::std::vector<int>>  dp(size+1, ::std::vector<int>(size+1, 0));
            for(int j=1; j<size; ++j){
                for(int i=j; i>=0; --i){
                    for(int k=i+1; k<j; ++k){
                        dp[i][j] = ::std::max(dp[i][j], dp[i][k]+dp[k][j]+nums[i]*nums[k]*nums[j]);
                    }
                }
            }
#ifdef debug
   for(int i=0; i<=size; ++i){
       for(int j=0; j<=size; ++j){
           ::std::cout<<dp[i][j]<<"--";
       }
       ::std::cout<<::std::endl;
   }
#endif

            return dp[0][size-1];
        }

//给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。
//返回符合要求的最少分割次数。
        int minCut(::std::string s){
            int size = s.length();
            ::std::vector<int> dp(size, 0);
            ::std::iota(dp.begin(), dp.end(), 0);
#ifdef debug
  for(int i=0; i<size; ++i){
      ::std::cout<<dp[i]<<"--";
  }
  ::std::cout<<::std::endl;
#endif
            ::std::vector<::std::vector<int>> is_p(size, ::std::vector<int>(size, 0));
            is_palindrome(is_p, s);
            for(int i=0; i<size; ++i){
                if(is_p[0][i]){
                    dp[i] = 0;
                    continue;
                }
                for(int j=0; j<i; ++j){
                    if(is_p[j+1][i]){
                        dp[i] = ::std::min(dp[i], dp[j]+1);
                    }
                }
            }
            return dp[size-1];
        }
        int minCut_fuck(::std::string s){
            int size = s.length();
            ::std::vector<::std::vector<int>> dp(size, ::std::vector<int>(size, 0));
            ::std::vector<::std::vector<int>> is_p(size, ::std::vector<int>(size, 0));
            is_palindrome(is_p, s);
            for(int j=0; j<size; ++j){
                for(int i=j; i>=0; --i){
                    if(is_p[i][j]){
                        dp[i][j] = 1;
                        continue;
                    }
                    dp[i][j] = j - i + 1;
                    for(int k=i; k<=j; ++k){
                        if(is_p[i][k]){
                            dp[i][j] = ::std::min(dp[i][j], dp[k+1][j]+1);
                        }
                    }
                }
            }
            return --dp[0][size-1];
        }
        void is_palindrome(vve& is_p, ::std::string s){
            int size = s.length();
            for(int j=0; j<size; ++j){
                for(int i=j; i>=0; --i){
                    if((i==j) || ((is_p[i+1][j-1] || i+1==j) && s[i]==s[j])){
                        is_p[i][j] = 1;
                    }
                }
            }
//#ifdef debug
   //for(int i=0; i<size; ++i){
       //for(int j=0; j<size; ++j){
           //::std::cout<<is_p[i][j]<<"--";
       //}
       //::std::cout<<::std::endl;
   //}
//#endif
      }

//--------------------------------leetcode 1320-----------------------------------------
        int minimumDistance(::std::string word){
            int size = word.length();
            vvve dp(size, vve(26, ve(26, INT_MAX>>1)));
            for(int i=0; i<26; ++i)dp[0][i][word[0]-'A'] = dp[0][word[0]-'A'][i] = 0;

            for(int i=1; i<size; ++i){
                int cur = word[i]   - 'A';
                int pre = word[i-1] - 'A';
                int d   = dis(cur, pre);
                for(int j=0; j<26; ++j){
                    dp[i][cur][j] = ::std::min(dp[i][cur][j], dp[i-1][pre][j]+d);
                    dp[i][j][cur] = ::std::min(dp[i][j][cur], dp[i-1][j][pre]+d);
                    if(pre==j){
                        for(int k=0; k<26; ++k){
                            int t = dis(k, cur);
                            dp[i][cur][j] = ::std::min(dp[i][cur][j], dp[i-1][k][j] + t);
                            dp[i][j][cur] = ::std::min(dp[i][j][cur], dp[i-1][j][k] + t);
                        }
                    }
                }
            }
            int res = INT_MAX;
            for(int i=0; i<26; ++i){
                res = ::std::min(res, *min_element(dp[size-1][i].begin(), dp[size-1][i].end()));
            }
            return res;
        }
        int minimumDistance_better(::std::string word){
//在方法一中，状态转移方程具有高度对称性，那么我们可以断定，dp[i][op = 0][rest] 和 dp[i][op = 1][rest] 的值一定是相等的
//因此我们可以直接使用 dp[i][rest] 进行状态转移，其表示一只手在 word[i] 的位置，另一只手在 rest 的位置的最小移动距离
            int size = word.length();
            ::std::vector<::std::vector<int>> dp(size, ::std::vector<int>(26, INT_MAX>>1));
            ::std::fill(dp[0].begin(), dp[0].end(), 0);
            for(int i=1; i<size; ++i){
                int cur = word[i]   - 'A';
                int pre = word[i-1] - 'A';
                int d   = dis(pre, cur);
                for(int j=0; j<26; ++j){
                    dp[i][j] = ::std::min(dp[i][j], dp[i-1][j] + d);
                    if(j==pre){
                        for(int k=0; k<26; ++k){
                            dp[i][j] = ::std::min(dp[i][j], dp[i-1][k] + dis(k, cur));
                        }
                    }
                }
            }
            return *min_element(dp[size-1].begin(), dp[size-1].end());
        }
        int dis(int index1, int index2){
            int x1 = index1/6, y1 = index1%6;
            int x2 = index2/6, y2 = index2%6;
            return abs(x1-x2) + abs(y1-y2);
        }
//给定一个正整数 x，我们将会写出一个形如 x (op1) x (op2) x (op3) x ... 的表达式，其中每个运算符 op1，op2，… 可以是加、减、乘、除（+，-，*，或是 /）之一。例如，对于 x = 3，我们可以写出表达式 3 * 3 / 3 + 3 - 3，该式的值为 3 。
//在写这样的表达式时，我们需要遵守下面的惯例：
//除运算符（/）返回有理数。
//任何地方都没有括号。
//我们使用通常的操作顺序：乘法和除法发生在加法和减法之前。
//不允许使用一元否定运算符（-）。例如，“x - x” 是一个有效的表达式，因为它只使用减法，但是 “-x + x” 不是，因为它使用了否定运算符。 
//我们希望编写一个能使表达式等于给定的目标值 target 且运算符最少的表达式。返回所用运算符的最少数量。
        int leastOpsExpressTarget(int x, int target){
            ::std::priority_queue< ::std::pair<int, int>, 
                                   ::std::vector<::std::pair<int, int>>, 
                                   ::std::greater<::std::pair<int, int>> >q;
            ::std::unordered_set<int> mp;
            q.push({0, target});
            while(q.size()){
                int c = q.top().first;
                int t = q.top().second;
                q.pop();
                if(!t)return c - 1;
                if(mp.count(t))continue;
                mp.insert(t);

                int k = log(t)/log(x);
                int l = t - pow(x, k);
                int r = pow(x, k+1) - t;

                if(!mp.count(l)) q.push({c+(k?k:2), l});
                if(!mp.count(r)) q.push({c+k+1, r});
            }
            return -100;
        }
        int leastOpsExpressTarget1(int x, int target){
            ::std::unordered_map<int, int>  mp;
            return process1(x, target, mp);
        }
        int process1(int x, int target, ::std::unordered_map<int, int>& mp){
            if(x==target)return 0;
            if(x>target)return ::std::min((target<<1)-1, (x-target)<<1);
            if(mp.count(target))return mp[target];

            long long k   = log(target) / log(x);
            long long l   = target - pow(x, k);
            if(!l)return --k;
            long long r   = pow(x, k+1) - target;
            long long res = process1(x, l, mp) + k++;
            if(target>r)res = ::std::min(res, process1(x, r, mp) + k);

            return mp[target] = res;
        }
//你的赛车起始停留在位置 0，速度为 +1，正行驶在一个无限长的数轴上。（车也可以向负数方向行驶你的车会根据一系列由 A（加速）和 R（倒车）组成的指令进行自动驾驶。当车得到指令 "A" 时, 将会做出以下操作： position += speed, speed *= 2当车得到指令 "R" 时, 将会做出以下操作：如果当前速度是正数，则将车速调整为 speed = -1 ；否则将车速调整为 speed = 1。  (当前所处位置不变。) 例如，当得到一系列指令 "AAR" 后, 你的车将会走过位置 0->1->3->3，并且速度变化为 1->2->4->-1。 现在给定一个目标位置，请给出能够到达目标位置的最短指令列表的长度。
        int racecar(int target){
            ::std::vector<int> dp(target+1, 0);
            return process1(target, dp);
        }
        int process1(int target, ::std::vector<int>& dp){
            if(target<0)return 0;
            if(dp[target])return dp[target];

            int k = ceil(log2(target+1));
            int r = (1<<k) - target-1;
            if(!r)return dp[target] = k;
            dp[target] = k + 1 + process1(r, dp);

            for(int j = 0; j<k-1; ++j){
                dp[target] = ::std::min(dp[target], k+j+1+process1(target-((1<<(k-1))-(1<<j)), dp));
            }
            return dp[target];
        }
//亚历克斯和李用几堆石子在做游戏。偶数堆石子排成一行，每堆都有正整数颗石子 piles[i] 。
//游戏以谁手中的石子最多来决出胜负。石子的总数是奇数，所以没有平局。
//亚历克斯和李轮流进行，亚历克斯先开始。 每回合，玩家从行的开始或结束处取走整堆石头。 这种情况一直持续到没有更多的石子堆为止，此时手中石子最多的玩家获胜。
//假设亚历克斯和李都发挥出最佳水平，当亚历克斯赢得比赛时返回 true ，当李赢得比赛时返回 false 。
        bool storeGameI(::std::vector<int>& piles){
            int size = piles.size();
            ::std::vector<::std::vector<int>> dp(size, ::std::vector<int>(size, 0));
            for(int j=0; j<size; ++j){
                for(int i=j; i>=0; --i){
                    if(i==j){
                        dp[i][j] = piles[i];
                        continue;
                    }
                    dp[i][j] = ::std::max(piles[i]-dp[i+1][j], piles[j]-dp[i][j-1]);
                }
            }
            return dp[0][size-1] > 0;
        }
//历克斯和李继续他们的石子游戏。许多堆石子 排成一行，每堆都有正整数颗石子 piles[i]。游戏以谁手中的石子最多来决出胜负。 亚历克斯和李轮流进行，亚历克斯先开始。最初，M = 1。 在每个玩家的回合中，该玩家可以拿走剩下的 前 X 堆的所有石子，其中 1 <= X <= 2M。然后，令 M = max(M, X)。 游戏一直持续到所有石子都被拿走。 假设亚历克斯和李都发挥出最佳水平，返回亚历克斯可以得到的最大数量的石头。
        int storeGameII(::std::vector<int>& piles){
            int size = piles.size();
            int sum  = 0;
            ::std::vector<::std::vector<int>> dp(size, ::std::vector<int>(size+1, 0));
            for(int i=size-1; i>=0; --i){
                sum += piles[i];
                for(int k=1; k<size+1; ++k){
                    if(i + (k<<1) >= size){
                        dp[i][k] = sum;
                    }else{
                        for(int s=1; s<=(k<<1); ++s){
                            dp[i][k] = ::std::max(dp[i][k], sum - dp[i+s][::std::max(k, s)]);
                        }
                    }
                }
            }
            return dp[0][1];
        }
//Alice 和 Bob 两个人轮流玩一个游戏，Alice 先手。 一开始，有 n 个石子堆在一起。每个人轮流操作，正在操作的玩家可以从石子堆里拿走 任意 非零 平方数 个石子。 如果石子堆里没有石子了，则无法操作的玩家输掉游戏。
//给你正整数 n ，且已知两个人都采取最优策略。如果 Alice 会赢得比赛，那么返回 True ，否则返回 False 。
        bool stroeGameIV(int n){
            ::std::vector<int> dp(n+1, false);
            for(int i=n; i>=0; --i){
                for(int j=1; n>=i+j*j; ++j){
                    if((dp[i] = !dp[i+j*j]))break;
                }
            }
            return dp[0];
        }
//Alice 和 Bob 用几堆石子在做游戏。几堆石子排成一行，每堆石子都对应一个得分，由数组 stoneValue 给出。 Alice 和 Bob 轮流取石子，Alice 总是先开始。在每个玩家的回合中，该玩家可以拿走剩下石子中的的前 1、2 或 3 堆石子 。比赛一直持续到所有石头都被拿走。 每个玩家的最终得分为他所拿到的每堆石子的对应得分之和。每个玩家的初始分数都是 0 。比赛的目标是决出最高分，得分最高的选手将会赢得比赛，比赛也可能会出现平局。
//假设 Alice 和 Bob 都采取 最优策略 。如果 Alice 赢了就返回 "Alice" ，Bob 赢了就返回 "Bob"，平局（分数相同）返回 "Tie"
        ::std::string storeGameIII(::std::vector<int>& piles){
            int size = piles.size();
            int sum  = 0;
            ::std::vector<int> dp(size+4, 0);
            for(int i=size-1; i>=0; --i){
                dp[i] = INT_MIN/2;
                sum += piles[i];
                dp[i] = ::std::max(dp[i], sum-dp[i+1]);
                dp[i] = ::std::max(dp[i], sum-dp[i+2]);
                dp[i] = ::std::max(dp[i], sum-dp[i+3]);
            }
            if(sum-dp[0] == dp[0])return "Tie";
            if(sum-dp[0] > dp[0])return "Bob";
            return "Alice";
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
};
int main(int argc,const char *argv[]){
    Solution te;
    ::std::vector<::std::vector<int>> h = {
{ 1,2,3,4 },{ 1,2,3,4 },{ 1,2,3,4 },{ 1,2,3,4 }
        //{3,5,1},
        //{3,5},
        //{3,4},
        //{4,5},
        //{5},
    };
    te.numberWays(h);
    //int x      = 3;
    //int target = 19;
    //::std::cout<<te.leastOpsExpressTarget(x, 1452)<<::std::endl;
    //::std::cout<<te.leastOpsExpressTarget1(x, 1452)<<::std::endl;
    //::std::string s = "aaa";
    //::std::string s = "aaa s d l j a d Z X C B i a s i d u b";
    //::std::cout<<te.minCut(s)<<::std::endl;
    //::std::vector<int> coins = {3, 1, 5, 8};
    //::std::cout<<te.maxCoins(coins)<<::std::endl;
    //::std::cout<<te.superEggDrop_fuck(3, 14)<<::std::endl;
    //::std::cout<<te.superEggDrop(3, 14)<<::std::endl;
    //::std::vector<int> nums = {1,2,3,6};
    //::std::cout<<te.tallestBillboard(nums)<<::std::endl;
    //::std::vector<int> sf = {5};
    //::std::vector<int> sf = {-2, 5, -1, 0, -3, 3};
    //::std::vector<int> sf = {-1, -8, 0, 5, -9};
    //::std::cout<<te.maxStatisfaction(sf)<<::std::endl;
    //::std::cout<<te.maxStatisfaction_dp(sf)<<::std::endl;
    return 0;
}
