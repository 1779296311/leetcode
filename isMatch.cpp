/********************************************* 
*     ------------------------                 
*     ------------------------                 
*     file name: isMatch.cpp
*     author   : @JY    
*     data     : 2019--09--07
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;

class Solution {
public:
    bool isMatch(char *s, char *p){
        if(*p == 0){
            return *s == 0;
        }
        auto  is_match  = (*s == *p || *p == '.') && *s;

        if(*(p + 1) == '*'){
            return (is_match &&  isMatch(s, p+2) ) || isMatch(++s, p);
        }else{
            return is_match && isMatch(++s, ++p);
        }
    }



    bool isMatch(string s, string p) {
            int s_size  = s.size();
            int p_size  = p.size();
            int j;
            int i;
            int next[s_size + 1];
            get_next(next, s);

            if(s == p){
                return true;
            }
            if(p.find('.') == p.npos && p.find('*') == p.npos && p_size != s_size){
                return false;
            }

            i = 0;
            j = 0;
            while(i<p_size && j<s_size){
                if(j == -1 || p[i] == s[j] || p[i] == '.'){
                //if(p[i] == s[j] || p[i] == '.'){
                    i++;
                    j++;
                }else if(p[i] == '*'){
                    if(i != 0){
                        if(p[i-1] != '.'){
                            while(s[j] == p[i-1]  && j<s_size){                                
                                j++;
                            }                                           
                            i++;
                        }else if(p[i -1 ] == '.'){
                            if(i == p_size - 1){
                                return true;   
                            }else{
                                i++;
                                while(s[j] != p[i] && j < s_size){
                                    j++;
                                    if(j == s_size){
                                        return false;
                                    }
                                }
                            }
                        }
                }else { 
                    i++;
                    j++;
                }
            } else{
                    if(i < p_size - 1 && p[i+1] == '*'){
                        i = i+2;
                    }else{
                        j = next[j];   
                    }
                }

                if(j >= s_size ){
                    return true;
                }
            }
            return false;
        }
        void get_next(int *next, string s){
            int size   = s.size();
            int i         = 0;
            int j         = -1;
            next[0]    = -1;

            while(i < size){
                if(j == -1 || s[i] == s[j]){
                    i++;
                    j++;
                    next[i]  = j;
                }else{
                    j  = next[j];
                }
            }
        }
        
    };


int main(int argc,const char *argv[]){
    string s  = "aab";
    string p  = "c*a*b";
    Solution te;
    cout<<te.isMatch(s,p)<<endl;
    return 0;
} 
