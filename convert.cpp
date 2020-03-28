/********************************************* 
*     ------------------------                 
*     ------------------------                 
*     file name: convert.cpp
*     author   : @JY    
*     data     : 2019--09--06
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using  namespace  std;

class Solution {
public:
    string convert(string s, int num) {
    int size = s.size();
    int index= 0;
    int flag = 0;
    int y    = num ;
    int x    = 0;
    if(size ==0 || size == 1 || num ==1){
            return s;
        }

    if((size%(2*num -2)) == 0){
        x = size / (2*num -2) * (num -1);
    }else if((size%(2*num -2)) <= num){
        x = size / (2*num -2) * (num -1) + 1;
    }else{
        x= size / (2*num -2) * (num -1) + (size % (2*num -2) - num);
    }

        x++;
    char str[y][x];
     for(int i=0; i<y; i++){
        for(int j=0; j<x; j++){
            str[i][j] = NULL;
        }
     }

    for(int i=0; i<x; ){
        if(flag == 0){
            for(int j=0; j<y; j++){
                if( index < size ){
                    str[j][i] = s[index];
                    index ++ ;
                }else{
                    goto next;
                }
            }
            i++;
            flag ++;
        }else{
            for(int j=y -2 ; j>0 ; j--){
                if( index < size ){
                    str[j][i] = s[index];
                    index ++ ;
                }else{
                    break;
                }
                i++;
            }
            flag = 0;
        }
    }
        next:
    index   = 0;
    for(int i=0; i<y; i++){
        for(int j=0; j<x; j++){
            if(str[i][j] ){
                if(index >= size){
                    goto ret;
                }else{
                    s[index] = str[i][j];
                }
                index ++;
            }
        }
    }
ret:
    return s;       
    }

    string convert_2(string s, int num){
        int  size    = s.size();
        bool if_next = false;
        int  index   = 0;
        vector<string>  rows(min(num , size));

        for(char c: s){
            rows[index]   = rows[index] + c;
            if(index == 0 || index == num -1){
                if_next   = !if_next;
            }
            index         = index + (if_next ? 1 : -1);
        }

        string str;
        for(string row : rows){
            str    = str + row; 
        }

        return str;
    }
};
