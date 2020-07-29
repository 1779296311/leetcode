/*********************************************
*     ------------------------
*     ------------------------
*     file name: 838.cpp
*     author   : @ JY
*     date     : 2020--07--24
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
class Solution{
   public:
       std::string pushDominoes(std::string d){
           int size = d.length();
           std::vector<int> p(size, 0);
           int f = 0;
           for(int i=0; i<size; ++i){
               if(d[i]=='R'){
                   f = size;
               }else if(d[i]=='L'){
                   f = 0;
               }else{
                   f = std::max(f-1,0);
               }
               p[i] = f;
           }
           f = 0;
           for(int i=size-1; i>=0; --i){
               if(d[i]=='R'){
                   f = 0;
               }else if(d[i]=='L'){
                   f = size;
               }else{
                   f = std::max(f-1,0);
               }
               p[i] -= f;
           }
           std::string res = "";
           for(int i=0; i<size; ++i)res += p[i]>0?'R':(p[i]<0?'L':'.');
           return res;
       }
};
