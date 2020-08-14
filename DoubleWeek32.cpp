/*********************************************
*     ------------------------
*     ------------------------
*     file name: DoubleWeek32.cpp
*     author   : @ JY
*     date     : 2020--08--09
**********************************************/
#include <vector>
#include <iostream>
#include <unordered_map>
#include <climits>
#include <stdlib.h>
class Solution{
    public:
        int findKthPositive(std::vector<int>& nums, int k){
            int size = nums.size();
            int s    = 1;
            for(int i=0; i<size; ){
                while(s<nums[i] && k--)++s;
                if(0>=k)return s-1;
                ++i, ++s;
            }
            return nums[size-1]+k;
        }
//给你两个字符串 s 和 t ，你的目标是在 k 次操作以内把字符串 s 转变成 t 。 在第 i 次操作时（1 <= i <= k），你可以选择进行如下操作： 选择字符串 s 中满足 1 <= j <= s.length 且之前未被选过的任意下标 j （下标从 1 开始），并将此位置的字符切换 i 次。 不进行任何操作。 切换 1 次字符的意思是用字母表中该字母的下一个字母替换它（字母表环状接起来，所以 'z' 切换后会变成 'a'）。 请记住任意一个下标 j 最多只能被操作 1 次。 如果在不超过 k 次操作内可以把字符串 s 转变成 t ，那么请你返回 true ，否则请你返回 false 。
////
        bool canConverString(std::string& s, std::string& t, int k){
            if(s.length() != t.length())return false;
            int res = 0;
            int size = s.length();
            std::vector<int> mp(26, 0);
            for(int i=0; i<size; ++i)res = std::max(res, calc(s[i], t[i], mp));
            return res <= k;
        }
        int calc(char a, char b, std::vector<int>&mp){
            if(a==b)return 0;
            int d = (b-a+26) % 26;
            return d+mp[d]++*26;
        }
//给你一个括号字符串 s ，它只包含字符 '(' 和 ')' 。一个括号字符串被称为平衡的当它满足： 任何左括号 '(' 必须对应两个连续的右括号 '))' 。 左括号 '(' 必须在对应的连续两个右括号 '))' 之前。 比方说 "())"， "())(())))" 和 "(())())))" 都是平衡的， ")()"， "()))" 和 "(()))" 都是不平衡的。 你可以在任意位置插入字符 '(' 和 ')' 使字符串平衡。
        int minInsertions(std::string& s){
            int size = s.length();
            int R = 0;
            int L = 0;
            int res = 0;
            for(int i=0; i<size; ++i){
                if(s[i]=='('){
                    ++L;
                }else{
                    if(i+1>size || s[i+1] != ')'){
                        ++res;
                    }else{
                        ++i;
                    }
                    R += 2;
                }
                if(L*2 < R){
                    ++res;
                    ++L;
                }
            }
            return res + (L*2-R);
        }
        void get_arr(std::string& s, std::vector<std::vector<int>>& arr){
            int size = s.length();
            for(int j=0; j<size; ++j){
                for(int i=j; i>=0; --i){
                    if(j-i<2){
                        arr[i][j] = false;
                        continue;
                    }
                    if(s[i]=='(' && s[j]==')' && s[j-1]==')' && (arr[i+1][j-2] || j-i==2)){
                        arr[i][j] = true;
                    }
                }
            }
        }
//给你一个字符串 s 。请返回 s 中最长的 超赞子字符串 的长度。 「超赞子字符串」需满足满足下述两个条件： 该字符串是 s 的一个非空子字符串 进行任意次数的字符交换重新排序后，该字符串可以变成一个回文字符串
        int longestAwesome(std::string& s){
            int size = s.length();
            std::vector<int> pre(1025, size);
            int xoR = 0;
            int res = 0;
            pre[0]  = -1;
            for(int i=0; i<size; ++i){
                xoR ^= (1<<(s[i]-'0'));
                res = std::max(res, i-pre[xoR]);
                for(int s=0; s<10; ++s){
                    res = std::max(res, i-pre[xoR^(1<<s)]);
                }
                pre[xoR] = std::min(pre[xoR], i);
            }
            return res;
        }
};
