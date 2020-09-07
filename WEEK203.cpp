/*********************************************
*     ------------------------
*     ------------------------
*     file name: WEEK203.cpp
*     author   : @ JY
*     date     : 2020--08--24
**********************************************/
#include <iostream>
#include <numeric>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <functional>
#include <stdlib.h>

class Solution{
    public:
        std::vector<int> mostVisited(int n, std::vector<int>& round){
            std::vector<int> res;
            int start = round[0];
            int end   = round.back();
            while(start != end){
                res.push_back(start);
                start = ++start>n?1:start;
            }
            res.push_back(end);
            std::sort(res.begin(), res.end());
            return res;
        }
//5496. 你可以获得的最大硬币数目
        int maxCoins(std::vector<int>& piles){
            std::sort(piles.begin(), piles.end());
            int res = 0;
            int n   = piles.size() / 3;
            for(int i=piles.size()-2; i>=n; i-=2){
                res += piles[i];
            }
            return res;
        }
//5497. 查找大小为 M 的最新分组
        int findLastStep_better(std::vector<int>& arr, int m){
            int size = arr.size();
            int res  = -1;
            std::vector<int> len(size+2, 0);
            std::vector<int> cnt(size+2, 0);
            for(int i=0; i<size; ++i){
                int x = arr[i];
                if(len[x])continue;
                int l = len[x-1];
                int r = len[x+1];
                int t = l + r + 1;
                len[x] = len[x-l] = len[x+r] = t;
                --cnt[l];
                --cnt[r];
                ++cnt[t];
                if(cnt[m]>0)res = i + 1;
            }
            return res;
        }
        int findLastStep(std::vector<int>& arr, int m){
            std::vector<int> link(arr.size()+1, -1);
            int res = -1;
            int cnt = 0;
            for(int i=0; i<arr.size(); ++i){
                int pos   = arr[i] - 1;
                link[pos] = pos;
                int l     = pos;
                int r     = pos;
                if(l>0 && link[l-1]!=-1){
                    cnt -= (l-link[l-1]==m);
                    l    = link[l-1];
                }
                if(r+1<arr.size() && link[r+1]!=-1){
                    cnt -= (link[r+1]-r==m);
                    r    = link[r+1];
                }
                link[l]  = r;
                link[r]  = l;
                if(r-l+1==m)++cnt;
                if(cnt>0)res = i+1;
            }
            return res;
        }

};
