/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_jumpGame_pro.cpp
*     author   : @ JY
*     date     : 2020--08--04
**********************************************/
#include <iostream>
#include <stack>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <stdlib.h>
class Solution{
    public:
        bool canJump(std::vector<int>& nums){
            int size = nums.size();
            if(size<=1)return true;
            std::vector<bool> dp(size, 0);
            if(!nums[0])return false;
            dp[0] = 1;
            for(int i=1; i<size; ++i){
                for(int j=i-1; j>=0; --j){
                    if((dp[i] = dp[j]&&nums[j]>=i-j))break;
                }
            }
            return dp[size-1];
        }
//给定一个非负整数数组，你最初位于数组的第一个位置。 数组中的每个元素代表你在该位置可以跳跃的最大长度。 你的目标是使用最少的跳跃次数到达数组的最后一个位置。
        int jump(std::vector<int>& nums){
            int size = nums.size();
            if(size<2)return 0;
            std::priority_queue<int> q;
            int res  = 1;
            int dis  = nums[0];
            for(int i=0; i<size; ++i){
                if(dis<i){
                    dis = q.top();
                    ++res;
                }
                q.push(i+nums[i]);
            }
            return res;
        }
        int jump_fuck(std::vector<int>& nums){
            int size = nums.size();
            std::vector<int> dp(size, size<<1);
            dp[0] = 0;
            for(int i=1; i<size; ++i){
                for(int j=i-1; j>=0; --j){
                    if(dp[j]!=size<<1 && nums[j]>=i-j){
                        dp[i] = std::min(dp[i], dp[j]+1);
                    }
                }
            }
            return dp[size-1];
        }
//这里有一个非负整数数组 arr，你最开始位于该数组的起始下标 start 处。当你位于下标 i 处时，你可以跳到 i + arr[i] 或者 i - arr[i]。 请你判断自己是否能够跳到对应元素值为 0 的 任一 下标处。 注意，不管是什么情况下，你都无法跳到数组之外。
        bool canReach(std::vector<int>& arr, int start){
            int size = arr.size();
            std::stack<int> st;
            std::vector<int> mp(size, 0);
            st.push(start);
            mp[start] = 1;
            while(st.size()){
                int m = st.top();
                st.pop();
                int r = m + arr[m];
                int l = m - arr[m];
                if((r<size && !arr[r]) || (l>=0 && !arr[l]))return true;
                if(r<size && !mp[r])st.push(r), mp[r]=1;
                if(l>=0   && !mp[l])st.push(l), mp[l]=1;
            }
            return false;
        }
//给你一个整数数组 arr ，你一开始在数组的第一个元素处（下标为 0）。
//每一步，你可以从下标 i 跳到下标：
//i + 1 满足：i + 1 < arr.length
//i - 1 满足：i - 1 >= 0
//j 满足：arr[i] == arr[j] 且 i != j
//请你返回到达数组最后一个元素的下标处所需的 最少操作次数 。
        int minJumps(std::vector<int>& arr){
            int size = arr.size();
            std::vector<int> dp(size, size<<1);
            std::queue<int>st;
            std::unordered_map<int,std::vector<int>> mp;
            st.push(0);
            for(int i=0; i<size; ++i) mp[arr[i]].push_back(i);
            dp[0]   = 0;
            while(st.size()){
                int m = st.front();
                st.pop();
                int l = m - 1;
                int r = m + 1;
                if(r<size && dp[m]+1 < dp[r])dp[r] = dp[m] + 1, st.push(r);
                if(l>=0   && dp[m]+1 < dp[l])dp[l] = dp[m] + 1, st.push(l);
                for(auto d : mp[arr[m]]){
                    if(dp[d] > dp[m] + 1)dp[d] = dp[m] + 1, st.push(d);
                }
                mp.erase(arr[m]);
            }
            return dp[size-1];
        }
//给你一个整数数组 arr 和一个整数 d 。每一步你可以从下标 i 跳到：
//i + x ，其中 i + x < arr.length 且 0 < x <= d 。
//i - x ，其中 i - x >= 0 且 0 < x <= d 。
//除此以外，你从下标 i 跳到下标 j 需要满足：arr[i] > arr[j] 且 arr[i] > arr[k] ，其中下标 k 是所有 i 到 j 之间的数字（更正式的，min(i, j) < k < max(i, j)）。
//你可以选择数组的任意下标开始跳跃。请你返回你 最多 可以访问多少个下标。
        int maxJumps(std::vector<int>& arr, int d){
            int size = arr.size();
            std::vector<int> dp(size+1, -1);
            for(int i=0; i<size; ++i){
                dfs(arr, dp, i, d);
            }
            return *max_element(dp.begin(), dp.end());
        }
        void dfs(std::vector<int>& arr, std::vector<int>& dp, int index, int d){
            if(dp[index] != -1)return;
            dp[index] = 1;
            int size = arr.size();
            for(int i=index-1; i+d>=index && i>=0 && arr[index]>arr[i]; --i){
                dfs(arr, dp, i, d);
                dp[index] = std::max(dp[index], dp[i]+1);
            }
            for(int i=index+1; i-d<=index && i<size && arr[index]>arr[i]; ++i){
                dfs(arr, dp, i, d);
                dp[index] = std::max(dp[index], dp[i]+1);
            }
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    int d = 0;
    std::vector<int> arr = {6, 4, 14, 6, 8, 13, 9, 7, 10, 6, 12};
    te.maxJumps(arr, d);
    return 0;
}

