/********************************************* 
*     ------------------------                 
*     ------------------------                 
*     file name: myAtoi.cpp
*     author   : @JY    
*     data     : 2019--09--07
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <climits>
using  namespace  std;

class Solution{
    public:
        int myAtoi(string s){

            int index = 0;
            int flag  = 0;
            int ret   = 0;
            int e     = 1;
            int size  = s.size();
            int right = 0;
            int left  = 0;
            int has_change = 0;
            int has_zero;
        
            if(size == 0 || s == " " ){
                return 0;
            }
        
            if(s[index] == '-' || s[index] == '+'){
                if(s[index] == '-'){
                    flag     = 1;
                }
                has_change = 1;
                index ++;
            }
        
            while(s[index] == ' ' ){
                if(has_change){     // "+      -"
                    return 0;
                }
                index ++;
            }
        if((s[index]=='-' || s[index]=='+') && flag ==0){
            if(has_change ){
                return 0;
            }
            if(s[index]=='-'){
                flag = 1;   
            }
            index++;
        }
        while(s[index] == '0'){ //"0000000000000000-1"
            has_zero = 1;       //"-000000000000"
            index ++;
        }
        if((s[index]=='-' || s[index]=='+') && flag ==0){
            if(has_zero){
                return 0;
            }
            if(s[index]=='-'){
                     flag = 1;   
            }
            index++;
        }

            if(s[index] > '9' || s[index] < '0'){
                return 0;
            }

            left      = index;
            right     = left;
            while(index < size){
                if(s[index] <= '9' && s[index] >= '0'){
                    right ++;
                    index ++;
                    continue;
                }else{
                    break;
                }
          }

            index = right - left;
            if((index) > 10 || (index == 10 && s[left] > '2' )){
                 return (flag==1) ? INT_MIN : INT_MAX;
            }
            string cmp = "2147483648";
            if((index == 10 && s[left] == '2' )){
                int i =0;
                for(i=0;i<10;i++){
                    if(s[left + i] > cmp[i]){
                        return (flag==1) ? INT_MIN : INT_MAX;
                    }
                }
                if(i == 10  &&  s[left + i -1 ] == '8'){
                   return (flag==1) ? INT_MIN : INT_MAX;
                }
            }

            ret   = (int)(s[right - 1] - '0');
            for(int i=right -2; i>=left; i--){
                e   = e   * 10;
                ret = ret + e*(int)(s[i] - '0');
            }

           return ret * ((flag==1) ? -1 : 1);
    }
        int my_atoi(string s){
            int size  = s.size();
            int index = 0;
            int flag  = 0;
            int ret   = 0;

            while(s[index] == ' '){
                index++;
            }

            if(s[index] >= '0' && s[index] <= '9'){
                ret   = s[index] - '0';
            }else if(s[index] == '+' || s[index] == '-' ){
                if(s[index] == '-'){
                    flag = 1;
                }
            }else{
                return 0;
            }

            index++;
            while(index < size && s[index] >= '0' && s[index] <= '9'){
                int num  = s[index] - '0';
                if(flag == 0){
                    if(ret >= (INT_MAX - num)/10 + ((INT_MAX -num )%10 != 0)){
                        return INT_MAX;
                    }
                    ret   = ret*10 + num;
                }else{
                    if(ret <= (INT_MIN + num)/10 - ((INT_MIN + num)%10 != 0)){
                        return INT_MIN;
                    }
                    ret   = ret*10 + num;
                }
                index++;
           }
           return ret *(flag==1 ? -1 : 1);
        }

};

int main(int argc,const char *argv[]){
    //string s = "4193 with words";
    //string s = "words and 987";
    string s = "283648";
    Solution te;
    cout <<te.my_atoi(s) <<endl;

    return 0;
} 
