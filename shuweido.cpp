/*********************************************
*     ------------------------
*     ------------------------
*     file name: shuweido.cpp
*     author   : @ JY
*     date     : 2020--05--25
**********************************************/

#include <bits/stdc++.h>
 
//using namespace std;
//typedef long long ll;
 
//const int key = 9 * 18 * 18;
//ll dp[20][20][key*2+10];
//int dight[20];
 
//ll dfs(int pos, int mid, int det, bool limit)
//{
    //if(!pos) return det == key;
    //if(!limit && ~dp[pos][mid][det]) return dp[pos][mid][det];
    //int up = limit ? dight[pos] : 9;
    //ll res = 0;
    //for(int i = 0;i <= up;i ++) {
        //res += dfs(pos-1, mid, det + (pos-mid) * i, limit && i == dight[pos]);
    //}
    //if(!limit) dp[pos][mid][det] = res;
    //return res;
//}
 
//ll solve(ll n)
//{
    //if(n == -1) return 0;
    //int cnt = 0;
    //while(n) {
        //dight[++cnt] = n % 10;
        //n /= 10;
    //}
    //ll res = 0;
    //for(int i = cnt;i >= 1;i --) {
        //res += dfs(cnt, i, key, 1);
    //}
    //return res - cnt + 1; //0多加了cnt-1次
//}
//int main()
//{
    //memset(dp, -1, sizeof(dp));
    //int T;
    //ll L = 7604;
    //ll R = 24324;
        //printf("%lld\n", solve(R) - solve(L-1) );
        //printf("%lld\n", solve(R));
        //printf("%lld\n", solve(L-1));
    //return 0;
//}
//o
typedef long long ll;
const int key = 9 * 18 * 18;
long long DP3[20][20][2000];
int ndigs[20];
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
//long long solve3(long long n)
//{
    //if(n == -1) return 0;
    //int cnt = 0;
    //while(n) {
        //ndigs[cnt++] = n % 10;
        //n /= 10;
    //}
    //ll res = 0;
    //for(int i=0; i<cnt; i++){
        //res += dfs3(cnt-1, i, 0, 1);
    //}
    //return res - cnt + 1;
//}
        int solve3(int n){
            if(0>=n)return 1;
    int cnt = 0;
    while(n) {
        ndigs[cnt++] = n % 10;
        n /= 10;
    }
            int res = 0;
            for(int i=0; i<cnt; ++i){
                res = res + dfs3(cnt-1,i,0,1);
            }
            return res - cnt + 1;
        }
int main(int argc,const char *argv[]){
    int a = 7604;
    int b = 24324;
    memset(DP3, -1, sizeof(DP3));
    ::std::cout<<solve3(b)<<::std::endl;
    ::std::cout<<solve3(a-1)<<::std::endl;
    return 0;
}
