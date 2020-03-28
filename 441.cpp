/*********************************************
*     ------------------------
*     file name: 441.cpp
*     author   : @ JY
*     date     : 2019--09--18
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;

class Solution{
    public:
        int arrangeCoins(int n){
            if(n<1){
                return 0;
            }
            int line = 1;
            while(n>0){
                n = n - line;
                if(n > line){
                    line++;
                }else{
                    break;
                }
            }
            return line;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    cout <<te.arrangeCoins(10)<<endl;
        return 0;
}
