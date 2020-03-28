/********************************************* 
*     ------------------------                 
*     ------------------------                 
*     file name: revice.cpp
*     author   : @JY    
*     data     : 2019--09--06
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <algorithm>
using  namespace  std;

class Solution{

    public:
        int revice(int num){
            string str =  to_string(num);
            reverse(str.begin(),str.end());

            long long n       =  stol(str);

            if(n < -4294967296 || n >4294967295){
                return 0;
            }else{
                return (int)n ;
            }

        }

};

int main(int argc,const char *argv[]){
    int num = atoi(argv[1]);
    Solution s;
    cout <<s.revice(num) <<endl;

    return 0;
} 

