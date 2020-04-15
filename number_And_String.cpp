/*********************************************
*     ------------------------
*     ------------------------
*     file name: number_And_String.cpp
*     author   : @ JY
*     date     : 2020--04--08
**********************************************/
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        string int_To_String(char *chs, int size, int num){
            if(!size || num<1){
                return "";
            }
            string __res = "";
            int len      = 0;
            int cur      = 1;
            while(num >= cur){
                num = num - cur;
                cur = cur * size;
                ++len;
            }
            while(len--){
                cur   = cur/size;
                //__res = __res + string(1,chs[num/cur]);
                __res = __res + string(1,'A'+num/cur);
                num   = num % cur;
            }
            return __res;
        }
        int string_To_Int(int size, string num){
            if(!size || !num.length()){
                return 0;
            }
            int __res = 0;
            int len   = num.length();
            for(char i : num){
                __res = __res + (i-'A'+1)*addN(size,--len);
            }
            return __res;
        }
        int addN(int i,int n){
            return (int)pow(i,n);
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    char chs[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    int size = *(&chs+1)-chs;
    cout<<te.int_To_String(chs,size,701)<<endl;
    //cout<<te.string_To_Int(chs,size,"BAEC")<<endl;
    return 0;
}
