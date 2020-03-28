/*********************************************
*     ------------------------
*     ------------------------
*     file name: 292.cpp
*     author   : @ JY
*     date     : 2019--09--16
**********************************************//*
你和你的朋友，两个人一起玩 Nim 游戏：桌子上有一堆石头，每次你们轮流拿掉 1 - 3 块石头。 拿掉最后一块石头的人就是获胜者。你作为先手。
你们是聪明人，每一步都是最优解。 编写一个函数，来判断你是否可以在给定石头数量的情况下赢得游戏。
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/nim-game
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/
#include <iostream>
#include <stdlib.h>
using  namespace  std;

class Solution{
    public:
        bool canWinNim(int n){
            if(n==0){
                return false;
            }else if(n<3){
                return true;
            }
            vector<bool> memo(n+1,false);
            memo[0] = false;
            memo[1] = true;
            memo[2] = true;
            memo[3] = true;
            for(int i=4; i<=n; i++){
                memo[i] = memo[i-1] || memo[i-2] || memo[i-3];
            }
            return memo[n];
        }
        bool canWinNim(int n){
           //return n%4;
           int k = n>>2;
           return k<<2 != n;
           //bitset<32> b(n);
           //return (b[0]==1||b[1]==1);
        }
};
