/*********************************************
*     ------------------------
*     ------------------------
*     file name: WEEK198.cpp
*     author   : @ JY
*     date     : 2020--07--20
**********************************************/
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <stdlib.h>
class Solution{
    public:
//小区便利店正在促销，用 numExchange 个空酒瓶可以兑换一瓶新酒。你购入了 numBottles 瓶酒。 如果喝掉了酒瓶中的酒，那么酒瓶就会变成空的。
        int numerWaterBottles(int b, int e){
            int res  = 0;
            while(b>=e){
                b   -= e;
                ++b;
                res += e;
            }
            res += b;
            return res;
        }
//给你一棵树（即，一个连通的无环无向图），这棵树由编号从 0  到 n - 1 的 n 个节点组成，且恰好有 n - 1 条 edges 。树的根节点为节点 0 ，树上的每一个节点都有一个标签，也就是字符串 labels 中的一个小写字符（编号为 i 的 节点的标签就是 labels[i] ） 边数组 edges 以 edges[i] = [ai, bi] 的形式给出，该格式表示节点 ai 和 bi 之间存在一条边。 返回一个大小为 n 的数组，其中 ans[i] 表示第 i 个节点的子树中与节点 i 标签相同的节点数。 树 T 中的子树是由 T 中的某个节点及其所有后代节点组成的树。
        std::vector<int> f;
        std::vector<int> countSubTrees(int n, std::vector<std::vector<int>>& ed, std::string l){
            std::vector<int> res(n, 0);

            std::vector<std::vector<int>> e(n);
            for(int i=0; i<ed.size(); ++i){
                e[ed[i][0]].push_back(ed[i][1]);
                e[ed[i][1]].push_back(ed[i][0]);
            }
            for(int i=0; i<n; ++i){
                for(auto & n : e[i]){
                    std::cout<<n<<"--";
                }
                std::cout<<std::endl;
            }
            f = std::vector<int> (n);
            dfs(res, e, l, 0);
            for(int i=0; i<n; ++i)std::cout<<res[i]<<"--";
            return res;
        }
        std::vector<int> dfs(std::vector<int>& res, std::vector<std::vector<int>>& e,
                             std::string l, int root){
            std::vector<int> c(26, 0);
            if(f[root])return c;
            ++f[root];
            ++c[l[root]-'a'];
            std::vector<int> t;
            for(int i=0; i<e[root].size(); ++i){
                t = dfs(res, e, l, e[root][i]);
                for(int i=0; i<26; ++i)c[i] += t[i];
            }
            res[root] += c[l[root]-'a'];
            return c;
        }
//给你一个只包含小写字母的字符串 s ，你需要找到 s 中最多数目的非空子字符串，满足如下条件： 这些字符串之间互不重叠，也就是说对于任意两个子字符串 s[i..j] 和 s[k..l] ，要么 j < k 要么 i > l 。 如果一个子字符串包含字符 c ，那么 s 中所有 c 字符都应该在这个子字符串中。 请你找到满足上述条件的最多子字符串数目。如果有多个解法有相同的子字符串数目，请返回这些子字符串总长度最小的一个解。可以证明最小总长度解是唯一的。 请注意，你可以以 任意 顺序返回最优解的子字符串。
        std::vector<std::string> maxNumOfSubstrings(std::string s){
            std::vector<int> f(26, -1);
            std::vector<int> e(26, -1);
            int size  = s.length();
            for(int i=0; i<size; ++i){
                if(f[s[i]-'a']==-1)f[s[i]-'a'] = i;
                e[s[i]-'a']   = i;
            }
            std::vector<int> r;
            for(auto &N : e) if(N!=-1){
                r.push_back(N);
            }
            std::vector<std::string> res;
            std::sort(r.begin(), r.end());
            int limit  = -1;
            for(int i=0; i<r.size(); ++i){
                int c   = s[r[i]] - 'a';
                int pre = f[c];
                int t   = r[i];
                while(t > pre){
                    if(r[i] < e[s[t]-'a'] || t <= limit)break;
                    pre = std::min(pre, f[s[t--]-'a']);
                }
                if(t==pre){
                    res.push_back(s.substr(pre, r[i]-pre+1));
                    limit = r[i];
                }
            }
            return res;
        }
        int closestToTarget(std::vector<int>& arr, int target){
            std::vector<int>  v = {arr[0]};
            int res = abs(arr[0] - target);
            int size = arr.size();
            for(int i=0; i<size; ++i){
                res = std::min(res, abs(arr[i]-target));
                std::vector<int> t = {arr[i]};
                for(auto &n : v){
                    t.push_back(n&arr[i]);
                    res = std::min(res, abs((n&arr[i])-target));
                }
                t.erase(std::unique(t.begin(), t.end()), t.end());
                v = t;
            }
            return res;
        }
        int closestToTarget_fuck(std::vector<int>& arr, int target){
            int size = arr.size();
            int res  = INT_MAX;
            std::vector<std::vector<int>> dp(size, std::vector<int> (size, -1e9));
            for(int i=0; i<size; ++i){
                for(int j=i; j<size; ++j){
                    if(i==j){
                        dp[i][j] = arr[i];
                        continue;
                    }
                    dp[i][j] = dp[i][j-1] & arr[j];
                    res = std::min(res, abs(dp[i][j] - target));
                }
            }
#ifdef debug
            for(int i=0; i<size; ++i){
                for(int j=0; j<size; ++j){
                    std::cout<<dp[i][j]<<"---";
                }
                std::cout<<std::endl;
            }
            std::cout<<std::endl;
#endif
            return res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    std::vector<int> arr = {9, 12, 3, 7, 15};
    int target = 5;
    ::std::cout<<te.closestToTarget(arr, target)<<::std::endl;
    //std::string s = "abba";
    //te.maxNumOfSubstrings(s);
    //int n = 4;
    //std::vector<std::vector<int>> e = {
        //{0, 2},
        //{0, 3},
        //{1, 2},
    //};
    //std::string  l = "aeed";
    //te.countSubTrees(n, e, l);
    return 0;
}
