/*********************************************
*     ------------------------
*     ------------------------
*     file name: hnt.cpp
*     author   : @ JY
*     date     : 2020--03--14
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        void hnt(int n, const char*from, const char *to, const char *help){
            if(n == 1){
                cout<<"move "<<from<<"->"<<to<<endl;
            }else{
                hnt(n-1,from,help,to);
                cout<<"move "<<from<<"->"<<to<<endl;
                hnt(n-1,help,to,from)
            }
        }
};
