/*********************************************
*     file name: 87.cpp
*     author   : @ JY
*     date     : 2019--09--18
**********************************************/
/*
给定一个字符串 s1，我们可以把它递归地分割成两个非空子字符串，从而将其表示为二叉树。
下图是字符串 s1 = "great" 的一种可能的表示形式。
    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t
在扰乱这个字符串的过程中，我们可以挑选任何一个非叶节点，然后交换它的两个子节点。
例如，如果我们挑选非叶节点 "gr" ，交换它的两个子节点，将会产生扰乱字符串 "rgeat" 。
    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t
我们将 "rgeat” 称作 "great" 的一个扰乱字符串。
同样地，如果我们继续交换节点 "eat" 和 "at" 的子节点，将会产生另一个新的扰乱字符串 "rgtae" 。
    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a
我们将 "rgtae” 称作 "great" 的一个扰乱字符串。
给出两个长度相等的字符串 s1 和 s2，判断 s2 是否是 s1 的扰乱字符串。
*/
#include <iostream>
#include <stdlib.h>
#include <string>
using  namespace  std;
class Solution{
    public:
        bool isScramble(string s1, string s2){
            int size = s1.size();
            if(size != s2.size()){
                return false;
            }
            vector<vector<vector<bool>>> memo(size, vector<vector<bool>>(size, vector<bool>(size+1, false)));
            for(int i=0; i<szie; i++){
                for(int j=0; j<size; j++){
                    memo[i][j][1] = s1[i] == s2[j];
                }
            }
            for(int length=2; length<=size; length++){
                for(int i=0; i<=size - length; i++){
                    for(int j=0; j<=size - length; j++){
                        for(int k=1; k<length; k++){
                            if((memo[i][j][k] && memo[i+k][j+k][length-k]) || (memo[i+k][j][length-k] && memo[i][j+length-k][k])){
                                memo[i][j][length] = true;
                            }
                        }
                    }
                }
            }
            return memo[0][0][size];
        }
};

