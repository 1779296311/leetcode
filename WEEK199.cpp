/*********************************************
*     ------------------------
*     ------------------------
*     file name: WEEK199.cpp
*     author   : @ JY
*     date     : 2020--07--27
**********************************************/
#include <iostream>
#include <climits>
#include <vector>
#include <stdlib.h>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution{
    public:
        std::string restoreString(std::string& s, std::vector<int>& indices){
            int size = s.length();
            std::string t = s;
            for(int i=0; i<size; ++i)t[indices[i]] = s[i];
            return t;
        }
        int minFlips(std::string target){
            int size = target.length();
            int res = 0;
            int i   = size - 1;
            int one = 0;
            while(i>=0 && target[i]=='1')one=1,--i;
            res += one;
            while(i>=0){
                while(i>=0 && target[i]=='1')one=1,--i;
                res += (one<<1);
                one  = 0;
                --i;
            }
            return res;
        }
        struct Info{
            std::vector<int> pairs;
            int res;
            Info(std::vector<int> p, int r=0): pairs(p), res(r) {}
        };
        int D;
        int countPairs(TreeNode* root, int d){
            D = d;
            return dfs(root, 1).res;
        }
        Info dfs(TreeNode* root, int d){
            if(!root)return {{},0};
            if(!root->left && !root->right) return {{d}, 0};

            Info l = dfs(root->left,  d+1);
            Info r = dfs(root->right, d+1);

            std::vector<int> pairs;
            for(auto &p : l.pairs)pairs.push_back(p);
            for(auto &p : r.pairs)pairs.push_back(p);

            int res = l.res + r.res;
            for(auto &p1 : l.pairs){
                for(auto &p2 : r.pairs){
                    if(p1 + p2 - (d<<1) <= D)++res;
                }
            }
            return {pairs, res};
        }
#define ve   ::std::vector<int>
#define vve  ::std::vector<ve>
#define vvve ::std::vector<vve>
        int calc(int n){
            if(n>9)return 3;
            if(n>1)return 2;
            return 1;
        }
        int getLongestOfOptimalCompression(std::string& s, int k){
            int size = s.length();
            std::vector<std::vector<int>> dp(size+1, std::vector<int>(k+2, INT_MAX>>1));
            dp[0][0] = 0;
            for(int i=1; i<=size; ++i){
                for(int n=0; n<=k; ++n){
                    dp[i][n+1] = std::min(dp[i][n+1], dp[i-1][n]);
                    int dif = 0, equ = 0;
                    for(int j=i; j<=size && n+dif<=k; ++j){
                        dif += s[i-1] != s[j-1];
                        equ += s[i-1] == s[j-1];
                        dp[j][n+dif] = std::min(dp[j][n+dif], dp[i-1][n] + calc(equ));
                    }
                }
            }
            return dp[size][k];
        }
        int getLongestOfOptimalCompression_fuck(std::string& s, int k){
            std::string t = "";
            int size      = s.length();
            int m=size, x=0;
            for(int i=0; i<size; ++i){
                int j = i;
                while(j<size && s[i]==s[j])++j;
                if(j-i==1)++x;
                m = std::min(m, j-i);
                t += s[i]+j-i;
                i  = j;
            }
            if(!k || k<m-1)return t.length() - x;
            if(k==m-1)return t.length() - ++x;

            vvve dp(size, vve(size, ve(k+1, INT_MAX>>1)));
            for(int j=0; j<size; j += 2){
                for(int i=j; i>=0; i -= 2){
                    if(i==j){
                        if(k>=t[i+1]-'0'){
                            dp[i][j][k-t[i+1]-'0'] = 0;
                        }else{
                            dp[i][j][k] = 2;
                        }
                        continue;
                    }
                    if(t[i]==t[j]){
                        int sum = 0;
                        for(int p=j-1; p>i+1; p -=2){
                            sum += t[p] - 'a';
                        }
                        if(sum <=k){
                            dp[i][j][k-sum] = 2;
                            int l = t[i+1] - 'a';
                            int r = t[j+1] - 'a';
                            if(k-sum-r-l >= 0)dp[i][j][k-sum-l-r] = 0;
                            if(k-sum-r-l == -1)dp[i][j][0] = 1;
                            continue;
                        }
                    }
                    int l = t[i+1] - 'a';
                    for(int n=0; n<=k; ++n){
                        if(n + l <= k){
                            dp[i][j][k-n-l] = std::min(dp[i][j][k-n-l], dp[i+2][j][n]);
                        }else{
                            dp[i][j][n] = std::min(dp[i][j][n], dp[i+2][j][n] + 2);
                        }
                    }
                    l = t[j+1] - 'a';
                    for(int n=0; n<=k; ++n){
                        if(n + l <= k){
                            dp[i][j][k-n-l] = std::min(dp[i][j][k-n-l], dp[i][j-2][n]);
                        }else{
                            dp[i][j][n] = std::min(dp[i][j][n], dp[i][j-2][n] + 2);
                        }
                    }
                }
            }
            for(int i=0; i<=k;++i)std::cout<<dp[0][size-1][i]<<"--";
            return 0;
        }
};
