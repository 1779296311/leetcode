/*********************************************
*     ------------------------
*     ------------------------
*     file name: WEEK205.cpp
*     author   : @ JY
*     date     : 2020--09--06
**********************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <functional>
#include <numeric>
#include <stdlib.h>

class Solution{
    public:
//507. 替换所有的问号
        std::string moditString(std::string s){
            int len = s.length();
            if(s[0]=='?' && len==1)return "a";
            if(len==1)return s;
            if(s[0]=='?')s[0]=s[1]=='?'?'a':(s[1]=='a'?s[1]+1:s[1]-1);
            for(int i=1; i<len-1; ++i){
                if(s[i] != '?')continue;
                s[i] =
                    (s[i+1]=='?')
                            ?
                    (s[i-1]=='a'?s[i-1]+1:s[i-1]-1)
                            :
                    (({char x='a';for(; x<='z'&&(x!=s[i-1] || x!=s[i+1]); ++x); x;}));

            }
            if(s[len-1]=='?')s[len-1] = s[len-2]=='a'?'b':s[len-2]-1;
            return s;
        }
//5508. 数的平方等于两数乘积的方法数
        int numTripletsstd(std::vector<int>& nums1, std::vector<int>& nums2){
            int m = nums1.size();
            int n = nums2.size();
            std::unordered_map<long long, int> mp;
            for(int i=0; i<m; ++i){
                for(int j=i+1; j<m; ++j){
                    ++mp[(static_cast<long long>(nums1[i])*static_cast<long long>(nums1[j]))];
                }
            }
            int res = 0;
            for(int i=0; i<n; ++i)res += mp[(static_cast<long long>(nums2[i])*static_cast<long long>(nums2[i]))];
            mp.clear();
            for(int i=0; i<n; ++i){
                for(int j=i+1; j<n; ++j){
                    ++mp[(static_cast<long long>(nums2[i])*static_cast<long long>(nums2[j]))];
                }
            }
            for(int i=0; i<m; ++i)res += mp[(static_cast<long long>(nums1[i])*static_cast<long long>(nums1[i]))];
            return res;
        }
//5509. 避免重复字母的最小删除成本
        int minCost(std::string s, std::vector<int>& cost){
            int res = 0;
            int i   = 0;
            int j   = 0;
            int l   = s.length();
            while(i < l){
                j = i + 1;
                int m = cost[i];
                int h = cost[i];
                while(j<l && s[i]==s[j])h+=cost[j],m=std::max(m, cost[j++]);
                if(i!=j+1)res += h - m;
                i = j;
            }
            return res;
        }
//5510. 保证图可完全遍历
        int maxNumEdgesToRemove(int n, std::vector<std::vector<int>>& edges){
            int res = 0;
            std::vector<int> _f(n+1);
            std::function<int(int)> _find = [&](int i){
                return _f[i]==i?i:_f[i]=_find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                _f[_find(a)] = _f[_find(b)]; };
            std::function<int(void)> _calc = [&](){
                int res = 0;
                for(int i=1; i<=n; ++i)res += i==_find(i);
                return res;
            };
            int c1=0, c2=0, c3=0;
            std::iota(_f.begin(), _f.end(), 0);
            for(auto &e : edges){
                if(e[0]==1 || e[0]==3)_union(e[1], e[2]), ++c1;
            }
            if(_calc() > 1)return -1;
            std::iota(_f.begin(), _f.end(), 0);
            for(auto &e : edges){
                if(e[0]==2 || e[0]==3)_union(e[1], e[2]), ++c2;
            }
            if(_calc() > 1)return -1;
            std::iota(_f.begin(), _f.end(), 0);
            for(auto &e : edges){
                if(e[0]==3)_union(e[1], e[2]), ++c3;
            }
            int c = _calc();
            c1 -= c3;
            c2 -= c3;

            res += (c3 - (n-c));
            res += c1-(c-1) + 2-(c-1);
            return res;
        }
};
