/*********************************************
*     ------------------------
*     ------------------------
*     file name: WEEK193.cpp
*     author   : @ JY
*     date     : 2020--06--14
**********************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <stdlib.h>

class Solution{
    public:

    ::std::vector<int> runningSum(::std::vector<int>& nums) {
        ::std::vector<int> res;
        int t = 0;
        for(int i=0; i<nums.size(); ++i){
            t = t + nums[i];
            res.push_back(t);
        }
        return res;
    }
    int findLeastNumOfUniqueInts(::std::vector<int>& arr, int k) {
        ::std::unordered_map<int,int> mp;
        for(int i=0; i<arr.size(); ++i){
            if(mp.find(arr[i]) != mp.end()){
                mp[arr[i]] += 1;
            }else{
                mp.insert(::std::make_pair(arr[i],1));
            }
        }
        ::std::vector<::std::pair<int,int>> tmp;
        for(auto p : mp){
            tmp.push_back(::std::make_pair(p.first,p.second));
        }
        sort(tmp.begin(),tmp.end(),[](::std::pair<int,int>&a, ::std::pair<int,int>& b){
                return a.second<b.second;
                });
        for(int i=0; i<tmp.size(); ++i){
            if(k<(tmp[i].second)){
                return tmp.size()-i;
            }else{
                k -= tmp[i].second;
            }
        }
        return 0;
    } 
    ///binary serach
    int minDaysBerSear(::std::vector<int>& by, int m, int k){
        int day = 0;
        int res = -1;
        int l   = 0;
        int r   = 1e9;
        while(l<r){
            day = l+((r-l)>>1);
            if(check(by,m,k,day)){
                res = day;
                r   = day - 1;
            }else{
                l = day + 1;
            }
        }
        return res;
    }
    int check(::std::vector<int>& by, int m, int k, int day){
        int res = 0;
        int len = 0;
        for(int i=0; i<by.size(); ++i){
            if(day>=by[i]){
                if(++len==k){
                    len = 0;
                    ++res;
                }
                if(res==m)return true;
            }else{
                len = 0;
            }
        }
        return false;
    }
    int get(int l, int r, int k){
        return (r-l+1)/k;
    }
    int minDays(::std::vector<int>& by, int m, int k) {
        if(by.size()<m*k)return -1;
        int n = by.size();
        ::std::vector<::std::pair<int,int>> h;
        for(int i=0; i<by.size(); ++i){
            h.push_back({by[i],i+1});
        }
        ::std::sort(h.begin(),h.end());
        ::std::vector<int> L(n+2,0);
        ::std::vector<int> R(n+2,0);
        int N = 0;
        for(auto H : h){
            int i = H.second;
            if(L[i-1] && R[i+1]){
                N         = N - get(L[i-1],i-1,k) - get(i+1,R[i+1],k) + get(L[i-1],R[i+1],k);
                R[L[i-1]] = R[i+1];
                L[R[i+1]] = L[i-1];
            }else if(L[i-1]){
                N         = N - get(L[i-1],i-1,k) + get(L[i-1],i,k);
                R[L[i-1]] = i;
                L[i]      = L[i-1];
            }else if(R[i+1]){
                N         = N - get(i+1,R[i+1],k) + get(i,R[i+1],k);
                L[R[i+1]] = i;
                R[i]      = R[i+1];
            }else{
                N = N + get(i,i,k);
                L[i] = i;
                R[i] = i;
            }
            if(N>=m)return H.first;
        }
        return -1;
    }
};
class TreeAncestor{
public:
    ::std::vector<::std::vector<int>> p;
    ::std::vector<::std::vector<int>> f;
    TreeAncestor(int n, ::std::vector<int>& parent){
        f = ::std::vector<::std::vector<int>>(n, ::std::vector<int>(16,-1));
        p = ::std::vector<::std::vector<int>>(n);
        int root = -1;
        for(int i=0; i<parent.size(); ++i){
            if(parent[i] == -1){
                root = i;
            }else{
                p[parent[i]].push_back(i);
            }
        }
        ::std::queue<int> st;
        st.push(root);
        while(!st.empty()){
            int par = st.front();
            st.pop();
            for(int c : p[par]){
                f[c][0] = par;
                for(int i=1; i<16; ++i){
                    if(f[c][i-1] != -1){
                        f[c][i] = f[f[c][i-1]][i-1];
                    }
                }
                st.push(c);
            }
        }
    }

    int getKthAncestor(int node, int k){
        for(int i=0; i<16; ++i){
            if(k>>i&1){
                node = f[node][i];
                if(node==-1)return node;
            }
        }
        return node;
    }
};
