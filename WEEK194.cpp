/*********************************************
*     ------------------------
*     ------------------------
*     file name: WEEK194.cpp
*     author   : @ JY
*     date     : 2020--06--21
**********************************************/
#include <iostream>
#include <algorithm>
#include <climits>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
class Solution{
    public:
        int xorOperation(int n, int start) {
            int i   = -1;
            int res = 0;
            while(n--){res ^= start+2*++i;}
            return res;
        }
        ::std::vector<::std::string> getFolderNames(::std::vector<::std::string>& names){
            ::std::unordered_map<::std::string,int> hs;
            ::std::unordered_set<::std::string> tmp;
            ::std::vector<::std::string> res;
            int size = names.size();
            for(int i=0; i<size; ++i){
                if(hs.find(names[i]) == hs.end()){
                    if(tmp.find(names[i]) != tmp.end()){
                        int t = 1;
                        ::std::string value = names[i];
                        while(tmp.find(value)!=tmp.end()){
                            value = names[i] + "(" + ::std::to_string(t++) +")";
                        }
                        tmp.insert(value);
                        res.push_back(value);
                        continue;
                    }
                    res.push_back(names[i]);
                    tmp.insert(names[i]);
                    hs[names[i]] = 0;
                }else{
                    ::std::string value = names[i];
                    int  k              = hs[names[i]];
                    while(tmp.find(value)!=tmp.end()){
                        value = names[i]+"(" + ::std::to_string(++k) +")";
                    }
                    res.push_back(value);
                    tmp.insert(value);
                    hs[names[i]] = k;
                }
            }
            return res;
        }
        struct Node{
            int val;
            int time;
        };
        struct cmp{
            bool operator()(Node &a, Node &b){
                return a.time > b.time;
            }
        };
        ::std::vector<int> avoidFlood(::std::vector<int>& rains){
            int size = rains.size();
            ::std::vector<int> res(size,1);
            ::std::unordered_map<int, int> hp;
            ::std::vector<int> mp(size, 0);
            ::std::priority_queue<Node,::std::vector<Node>,cmp> q;
            ::std::unordered_set<int> hset;

            for(int i=0; i<size; ++i){
                if(hp.count(rains[i]))mp[hp[rains[i]]] = i;
                hp[rains[i]] = i;
            }
            //::std::cout<<::std::endl;
            for(int i=0; i<size; ++i){
                if(rains[i] == 0){
                    if(q.size()){
                        res[i] = q.top().val;
                        q.pop();
                        hset.erase(res[i]);
                    }
                    continue;
                }else if(hset.count(rains[i])){
                    return {};
                }else if(mp[i]){
                    q.push({rains[i],mp[i]});
                    hset.insert(rains[i]);
                }
                res[i]  = -1;
            }
            return res;
        }
        //------------------------------------------
        ::std::vector<int> par;
        int find(int x){
            if(par[x] != x)par[x] = find(par[x]);
            return par[x];
        }
        int work1(int n, int k, ::std::vector<::std::vector<int>>& edges){
            for(int i=0; i<par.size(); ++i)par[i] = i;
            int res = 0;
            int t   = n;
            for(auto tmp : edges){
                if(tmp[3]==k)continue;
                int p1 = find(tmp[1]);
                int p2 = find(tmp[2]);
                if(p1 != p2){
                    par[p1] = p2;
                    --t;
                    res += tmp[0];
                }
            }
            return !--t?res:INT_MAX;
        }
        int work2(int n, int k, ::std::vector<::std::vector<int>>& edges){
            for(int i=0; i<par.size(); ++i)par[i] = i;
            int res = 0;
            int t   = n;
            for(auto tmp : edges){
                if(tmp[3] == k){
                    par[find(tmp[1])] =  find(tmp[2]);
                    --t;
                    res += tmp[0];
                    break;
                }
            }
            for(auto tmp : edges){
                int p1 = find(tmp[1]);
                int p2 = find(tmp[2]);
                if(p1 != p2){
                    par[p1] = p2;
                    --t;
                    res += tmp[0];
                }
            }
            return !--t?res:INT_MAX;
        }
        ::std::vector<::std::vector<int>> findCriticalAndPseudoCriticalEdges(int n, ::std::vector<::std::vector<int>>& edges){
            par = ::std::vector<int>(n);
            for(int i=0; i<edges.size(); ++i){
                auto& tmp = edges[i];
                ::std::swap(tmp[2], tmp[0]);
                tmp.push_back(i);
            }
            sort(edges.begin(), edges.end());
            int cost = work1(n,-1,edges);
            ::std::vector<::std::vector<int>> res(2);
            for(int i=0; i<edges.size(); ++i){
                if(cost != work1(n,i,edges)){
                    res[0].push_back(i);
                }else if(cost == work2(n,i,edges)){
                    res[1].push_back(i);
                }
            }
            return res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    ::std::vector<int> rains = {1,3,2,0,2,0,3,0,1,0,0,0};
    //::std::vector<int> rains = {1,3,2,,2,0,3,0,1,0,0,0};
    te.avoidFlood(rains);
    return 0;
}
