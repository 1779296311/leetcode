/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_shuweiDP_pro.cpp
*     author   : @ JY
*     date     : 2020--05--25
**********************************************/
#include <iostream>
#include <cstring>
#include <vector>
#include <stdlib.h>
long long DP3[20][20][2000];
int ndigs[20];
class Solution{
    public:
        /*************************************62****************************88*/
        int init1(int n, ::std::vector<int>& nums){
            int len = 0;
            while(n){
                nums.push_back(n%10);
                n = n / 10;
                ++len;
            }
            return len;
        }
        ::std::vector<::std::vector<int>> DP;
        int dfs(int pos,int sta, int pre, int limit){
            if(pos==-1)return 1;
            if(!limit && DP[pos][sta]!=-1)return DP[pos][sta];
            int up  = limit?la[pos]:9;
            int res = 0;
            for(int i=0; i<=up; ++i){
                if(i==4)continue;
                if(i==2&&pre==6)continue;
                res = res + dfs(pos-1, i==6, i, limit&&i==la[pos]);
            }
            return limit?res:DP[pos][sta]=res;
        }
        ::std::vector<int> la;
        int solved(int a){
            int l = init1(a,la);
            DP.assign(20,::std::vector<int>(2,-1));
            return dfs(l-1,-1,-1,1);
        }
        /*************************************F(x)****************************88*/
        long long F(int x){
            int i         = 0;
            long long res = 0;
            while(x){
                res = res + (x%10*(1<<i++));
                x   = x/10;
            }
            return res;
        }
        ::std::vector<int> bdigs;
        ::std::vector<::std::vector<int>> DP1;
        int solved(int a, int b){
            int len = init1(b,bdigs);
            DP1.assign(12,::std::vector<int>(1e4+5,-1));
            return dfs(len-1,F(a),1);
        }
        int dfs(int pos, int sum, int limit){
            if(pos==-1)return sum>=0;
            if(sum<0)return 0;
            if(!limit && DP1[pos][sum] !=-1)return DP1[pos][sum];
            int up  = limit?bdigs[pos]:9;
            int res = 0;
            for(int i=0; i<=up; ++i){
                res = res + dfs(pos-1,sum-i*(1<<pos),limit&&i==bdigs[pos]);
            }
            return limit?res:DP1[pos][sum]=res;
        }
        /*********************************0N >= 1N********************************88*/
        ::std::vector<int> xdigs;
        ::std::vector<::std::vector<int>> DP2;
        int init2(int x){
            int len = 0;
            while(x){
                xdigs.push_back(x&1);
                x = x >> 1;
                ++len;
            }
            return len;
        }
        int dfs2(int pos, int sta, int zero, int limit){
            if(pos==-1)return sta>=32;
            if(!limit && !zero && DP2[pos][sta]!=-1)return DP2[pos][sta];
            int up  = limit?xdigs[pos]:1;
            int res = 0;
            for(int i=0; i<=up; ++i){
                if(zero && !i){
                    res = res + dfs2(pos-1,sta,1,limit&&i==xdigs[pos]);
                }else{
                    res = res + dfs2(pos-1,sta+(!i?1:-1),0,limit&&i==xdigs[pos]);
                }
            }
            return (!limit&&!zero)?DP2[pos][sta]=res:res;
        }
        int solved2(int x){
            int len = init2(x);
            DP2.assign(32,::std::vector<int>(66,-1));
            return dfs2(len-1,32,1,1);
        }
        /***********************************平衡号码*********************************************/
        //::std::vector<int> ndigs;
        int dfs3(int pos, int mid, int sum, int limit){
            if(pos==-1)return !sum;
            if(sum<0)return 0;
            if(!limit && DP3[pos][mid][sum]!=-1)return DP3[pos][mid][sum];
            int up  = limit?ndigs[pos]:9;
            int res = 0;
            for(int i=0; i<=up; ++i){
                res = res + dfs3(pos-1,mid,sum+(pos-mid)*i,limit&&i==ndigs[pos]);
            }
            return !limit?DP3[pos][mid][sum]=res:res;
        }
        int solve3(int n){
            if(0>=n)return 1;
            int cnt = 0;
            while(n) {
                ndigs[cnt++] = n % 10;
                n /= 10;
            }
            int res = 0;
            memset(DP3,-1,sizeof(DP3));
            for(int i=0; i<cnt; ++i){
                res = res + dfs3(cnt-1,i,0,1);
            }
            return res - cnt + 1;
        }

//我们有一组排序的数字 D，它是  {'1','2','3','4','5','6','7','8','9'} 的非空子集。（请注意，'0' 不包括在内。） 现在，我们用这些数字进行组合写数字，想用多少次就用多少次。例如 D = {'1','3','5'}，我们可以写出像 '13', '551', '1351315' 这样的数字。 返回可以用 D 中的数字写出的小于或等于 N 的正整数的数目。
        std::vector<int> dp, mp, digit;
    int atMostNGivenDigitSet(std::vector<std::string>& D, int N){
        digit.push_back(0);
        while(N>0){
            digit.push_back(N%10);
            N /= 10;
        }
        mp = std::vector<int>(10, 0);
        for(auto &d : D)mp[d[0]-'0'] = 1;
        int size = digit.size();
        dp = std::vector<int>(size+1, -1);
        return dfs(size-1, true, true);
    }
    int dfs(int index, bool limit, bool zero){
        if(!index)return !zero;
        if(!limit && !zero && dp[index]!=-1)return dp[index];
        int max_ = limit?digit[index]:9;
        int res_ = 0;
        for(int i=0; i<=max_; ++i){
            if(zero && !i){
                res_ += dfs(index-1, limit&&i==max_, true);
            }else if(mp[i]){
                res_ += dfs(index-1, limit&&i==max_, false);
            }
        }
        return (!zero && !limit)?dp[index]=res_:res_;
    }
    int atMostNGivenDigitSet_fuck(std::vector<std::string>& D, int N){
        int res = 0;
        std::vector<int> dp(N+5, -1);
        return dfs(0, dp, D, N);
    }
    int dfs(unsigned long long num, std::vector<int>& dp, std::vector<std::string>& D, int N){
        if(num>N)return 0;
        if(dp[num] != -1)dp[num];
        int res = 1;
        int size = D.size();
        for(int i=0; i<size; ++i){
            res += dfs(num*10+(D[i][0]-'0'), dp, D, N);
        }
        return res;
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    int a = 7604;
    int b = 24324;
    ::std::cout<<te.solve3(b)-te.solve3(a-1)<<::std::endl;
    ::std::cout<<te.solve3(b)<<::std::endl;
    ::std::cout<<te.solve3(a-1)<<::std::endl;
    return 0;
}
