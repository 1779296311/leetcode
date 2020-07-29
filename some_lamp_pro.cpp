/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_lamp_pro.cpp
*     author   : @ JY
*     date     : 2020--07--28
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdlib.h>
class Solution{
    public:
//初始时有 n 个灯泡关闭。 第 1 轮，你打开所有的灯泡。 第 2 轮，每两个灯泡你关闭一次。 第 3 轮，每三个灯泡切换一次开关（如果关闭则开启，如果开启则关闭）。第 i 轮，每 i 个灯泡切换一次开关。 对于第 n 轮，你只切换最后一个灯泡的开关。 找出 n 轮后有多少个亮着的灯泡。
        int bulbSwitch(int n){
            return sqrt(n);
        }

//现有一个房间，墙上挂有 n 只已经打开的灯泡和 4 个按钮。在进行了 m 次未知操作后，你需要返回这 n 只灯泡可能有多少种不同的状态。
//假设这 n 只灯泡被编号为 [1, 2, 3 ..., n]，这 4 个按钮的功能如下：
//将所有灯泡的状态反转（即开变为关，关变为开）
//将编号为偶数的灯泡的状态反转
//将编号为奇数的灯泡的状态反转
//将编号为 3k+1 的灯泡的状态反转（k = 0, 1, 2, ...)
        int flipLights(int n, int m){
            if(!n || !m)return 1;

            if(m==1){
                return n+m>=4?4:m+n;
            }

            if(n<=2)return n<<1;

            if(m==2){
                return 7;
            }
            return 8;
        }
        int numsTimesAllBule(std::vector<int>& lights){
            int size  = lights.size();
            int res   = 0;
            int sum_0 = 0;
            int sum_1 = 0;
            for(int i=1; i<=size; ++i){
                if( 
                    (sum_0 += i) 
                        == 
                    (sum_1 += lights[i-1]) )

                        ++res;
            }
            return res;
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
};
