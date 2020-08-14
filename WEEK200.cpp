/*********************************************
*     ------------------------
*     ------------------------
*     file name: WEEK200.cpp
*     author   : @ JY
*     date     : 2020--08--02
**********************************************/
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stdlib.h>
class Solution{
    public:
        int countGoodTriplets(std::vector<int>&arr, int a, int b, int c){
            int size = arr.size();
            int res  = 0;
            for(int i=0; i<size; ++i){
                for(int j=i+1; j<size; ++j){
                    if(abs(arr[i]-arr[j])>a)continue;
                    for(int k=j+1; k<size; ++k){
                        if(abs(arr[i]-arr[k])>c)continue;
                        if(abs(arr[j]-arr[k])>b)continue;
                        ++res;
                    }
                }
            }
            return res;
        }

        int getWinner(std::vector<int>&arr, int k){
            int size = arr.size();
            if(k>=size)return *max_element(arr.begin(), arr.end());
            int  q = arr[0];
            int  t = k;
            for(int i=1; i<size; ++i){
                if(q<arr[i]){
                    q = arr[i];
                    t = k;
                }
                if(!--t)return q;
            }
            return q;
        }
        int minSwap(std::vector<std::vector<int>>& grid){
            int size = grid.size();
            std::vector<int> zero(size, 0);
            for(int i=0; i<size; ++i){
                int count = 0;
                for(int j=size-1; j>=0&&!grid[i][j]&&++count; --j);
                zero[i]=count;
            }
            int res = 0;
            for(int i=0; i<size; ++i){
                if(size-i-1<=zero[i])continue;
                int j = i+1;
                for(;j<size && zero[j]<size-i-1; ++j);
                if(j==size)return -1;
                res += j-i;
                while(j>i)std::swap(zero[j], zero[--j]);
            }
            return res;
        }

        int maxSum(std::vector<int>& n1, std::vector<int>& n2) {
            int MOD        = 1e9 + 7;
            int size1      = n1.size();
            int size2      = n2.size();
            long long res  = 0;
            long long sum1 = 0;
            long long sum2 = 0;
            int i = 0, j = 0;
            while(i<size1 && j<size2){
                if(n1[i]==n2[j]){
                    res += std::max(sum1, sum2);
                    sum1 = sum2 = n1[i];
                    ++i,++j;
                }else if(n1[i] < n2[j]){
                    sum1 += n1[i++];
                }else{
                    sum2 += n2[j++];
                }
            }
            while(i<size1)sum1 += n1[i++];
            while(j<size2)sum2 += n2[j++];
            res +=std::max(sum1, sum2);
            return res % MOD;
        }
        std::unordered_map<int, int> hp1;
        std::unordered_map<int, int> hp2;
        std::vector<int> nums1;
        std::vector<int> nums2;
        std::vector<std::vector<int>> dp;
        int maxSum_fuck(std::vector<int>&n1, std::vector<int>& n2){
            nums1 = n1;
            nums2 = n2;
            int size1 = n1.size();
            int size2 = n2.size();
            for(int i=0; i<size1; ++i)hp1[nums1[i]] = i;
            for(int i=0; i<size2; ++i)hp2[nums2[i]] = i;

            dp = std::vector<std::vector<int>>(2, std::vector<int>(std::max(size1+1, size2+1), -1));

            int index1 = -1;
            int sum1   = 0;
            while(index1<size1-1 && !hp2.count(nums1[++index1]))sum1 += nums1[index1];
            int index2 = -1;
            int sum2   = 0;
            while(index2<size2-1 && !hp1.count(nums2[++index2]))sum2 += nums2[index2];
            if(index1==size1-1 && index2==size2-1)return std::max(sum1, sum2);

            int sum = std::max(sum1, sum2);
            int res1 = dfs(index1,0,sum);
            fill(dp[0].begin(), dp[0].end(), -1);
            fill(dp[1].begin(), dp[1].end(), -1);
            int res2 = dfs(index2,1,sum);

            for(int i=0; i<2; ++i){
                for(int j=0; j<dp[0].size(); ++j){
                    std::cout<<dp[i][j]<<"   ";
                }
                std::cout<<std::endl;
            }

            return std::max(res1, res2);
        }
        int dfs(int index, int func, int sum){
            //if(dp[func][index] != -1)return dp[func][index];
            if(func){
                if(index>=nums2.size()){
                    return dp[func][index] = std::max(dp[func][index], sum);
                }
                int t = -1;
                if(hp1.count(nums2[index])){
                    t  = dfs(hp1[nums2[index]]+1, !func, sum+nums2[index]);
                }
                return dp[func][index] = std::max(t, dfs(index+1, func, sum+nums2[index]));
            }else{
                if(index>=nums1.size()){
                    return dp[func][index] = std::max(dp[func][index], sum);
                }
                int t = -1;
                if(hp2.count(nums1[index])){
                    t  = dfs(hp2[nums1[index]]+1, !func, sum+nums1[index]);
                }
                return dp[func][index] = std::max(t, dfs(index+1, func, sum+nums1[index]));
            }
        }
};

int main(int argc,const char *argv[]){
    Solution te;
    std::vector<int> n1 = {10,11,19,31,43,45,52,54,62,68,80,81,90,93,96,102,111,114};
    std::vector<int> n2 = {5,8,11,23,24,34,43,53,63,73,76,78,80,85,93,94,106,117,123,135,145,154,165,173,185,196};
    te.maxSum(n1, n2);
    return 0;
}




















