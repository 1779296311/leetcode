/*********************************************
*     ------------------------
*     ------------------------
*     file name: WEEK204.cpp
*     author   : @ JY
*     date     : 2020--08--31
**********************************************/
#include <functional>
#include <iostream>
#include <stdlib.h>
#include <vector>

class Solution{
    public:
        //1566. 重复至少 K 次且长度为 M 的模式
        bool containPattern(std::vector<int>& arr, int m, int k){
            int size = arr.size();
            if(m*k > size)return false;
            for(int i=0,j=i+m; i<=size-m*k; ++i){
                for(j=i+m; j<i+m*k; ++j){
                    if(arr[j] != arr[j-m])break;
                }
                if(j==i+m*k)return true;
            }
            return false;
        }
//1567. 乘积为正数的最长子数组长度
        int getMaxLen(std::vector<int>& nums){
            int a_len = nums[0]>0;
            int i_len = nums[0]<0;
            int res   = a_len;
            for(int i=1; i<nums.size(); ++i){
                if(nums[i] > 0){
                    a_len = a_len + 1;
                    i_len = i_len?i_len+1:0;
                }else if(nums[i] < 0){
                    int o_len = a_len;
                    a_len     = i_len?i_len+1:0;
                    i_len     = o_len + 1;
                }else{
                    a_len = 0;
                    i_len = 0;
                }
                res = std::max(res, a_len);
            }
            return res;
        }
//1568. 使陆地分离的最少天数
        int minDays(std::vector<std::vector<int>>& grid){
            int m  = grid.size();
            int n  = grid[0].size();
            std::vector<std::vector<int>> vi;
            std::vector<std::vector<int>> fun = {{1, 0},{-1, 0},{0, 1},{0, -1}};
            std::function<void(int x, int y)> dfs = [&](int x, int y){
                vi[x][y] = 1;
                for(int i=0; i<4; ++i){
                    int a = x + fun[i][0];
                    int b = y + fun[i][1];
                    if(a>=0 && b>=0 && a<m && b<n && !vi[a][b] && grid[a][b]){
                        dfs(a, b);
                    }
                }
            };
            std::function<bool(void)> check = [&](){
                int res = 0;
                vi = std::vector<std::vector<int>>(m, std::vector<int>(n));
                for(int i=0; i<m; ++i){
                    for(int j=0; j<n; ++j){
                        if(!vi[i][j] && grid[i][j]){
                            ++res;
                            dfs(i, j);
                        }
                    }
                }
                return res > 1;
            };
            if(check())return 0;
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    if(grid[i][j]){
                        grid[i][j] = 0;
                        if(check())return 1;
                        grid[i][j] = 1;
                    }
                }
            }
            return 2;
        }
//1569. 将子数组重新排序得到同一个二叉查找树的方案数
        int numsOfWays(std::vector<int>& nums){
            int m   = nums.size();
            int MOD = 1e9 + 7;
            std::vector<std::vector<int>> C(m+1, std::vector<int>(m+1, 1));
            for(int i=1; i<=m; ++i){
                for(int j=1; j<i; ++j){
                    C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
                }
            }
            std::function<int (std::vector<int>&)> calc = [&](const std::vector<int>& cs){
                int size = cs.size();
                if(size<=2)return 1;
                int H = cs[0];
                std::vector<int> left;
                std::vector<int> right;
                for(auto &x : cs){
                    if(x > H)right.push_back(x);
                    if(x < H)left.push_back(x);
                }
                long long res = (C[size-1][left.size()] * (long long)calc(left) % MOD * (long long)calc(right) % MOD) % MOD;
                return  static_cast<int>(res);
            };
            return calc(nums) - 1;
        }
};
