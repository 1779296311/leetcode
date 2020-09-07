/*********************************************
*     ------------------------
*     ------------------------
*     file name: DoubleWeek33.cpp
*     author   : @ JY
*     date     : 2020--08--23
**********************************************/
#include <iostream>
#include <vector>
#include <functional> 
#include <algorithm>
#include <unordered_set>
#include <stdlib.h>

class Solution{
    public:
//5479. 千位分隔数
        std::string thousnadSeparator(int n){
            std::vector<int> t;
            while(n){
                t.push_back(n%10);
                n /= 10;
            }
            std::string res = "";
            for(int i=0; i<t.size(); ++i){
                if(i && !(i%3))res += '.';
                res += std::to_string(t[i]);
            }
            reverse(res.begin(), res.end());
            return res;
        }
//5480. 可以到达所有点的最少点数目
        std::vector<int> findSmallestSetOfVertices(int n, std::vector<std::vector<int>> edgs){
            std::unordered_set<int> from;
            std::unordered_set<int> to;
            std::vector<int> res;
            for(auto &e : edgs)from.insert(e[0]), to.insert(e[1]);
            for(auto &f : from){
                if(!to.count(f))res.push_back(f);
            }
            return res;
        }
//5481. 得到目标数组的最少函数调用次数
        int minOperations(std::vector<int>& nums){
            int res = 0;
            while(1){
                int zero = 0;
                for(auto &n : nums){
                    if(n&1)++res;
                    zero += !(n >>= 1);
                }
                if(zero==nums.size())break;
                ++res;
            }
            return res;
        }
//5482. 二维网格图中探测环
        bool containsCycle(std::vector<std::vector<int>>& grid){
            int m = grid.size();
            int n = grid[0].size();
            std::vector<std::vector<int>> fun = {{1, 0},{-1, 0},{0, 1},{0, -1}};
            std::vector<std::vector<int>>vi(m, std::vector<int>(n, 0));
            std::function<bool(char, int, int, int, int)> dfs = [&](char c, int x, int y, int pre_x, int pre_y){
                if(x<0 || y<0 || x>=m || y>=n)return false;
                if(grid[x][y] != c)return false;
                if(vi[x][y])return true;
                vi[x][y] = 1;
                for(auto &f : fun){
                    int x1 = x + f[0];
                    int y1 = y + f[1];
                    if(x1==pre_x && y1==pre_y)continue;
                    if(dfs(c, x1, y1, x, y))return true;
                }
                vi[x][y]   = 0;
                grid[x][y] = '^';
                return false;
            };
            std::function<bool(void)> calc = [&](){
                for(int i=0; i<m; ++i){
                    for(int j=0; j<n; ++j){
                        if(grid[i][j]=='^')continue;
                        if(dfs(grid[i][j], i, j, -1, -1))return true;
                    }
                }
                return false;
            };
            return calc();
        }
};
