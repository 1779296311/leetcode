/********************************************* 
*     ------------------------                 
*     ------------------------                 
*     file name: longestPalindrome.cpp
*     author   : @JY    
*     data     : 2019--09--05
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

#define MAX(a,b)   ((a>b) ? (a) : (b))

using  namespace  std;

class Solution{
    public:
        string longestPalindrome(string s){
            int len   = s.length();
            int start = 0;
            int end   = 0;
            if(len ==0 || len == 1 ){
                return s;
            }
            //vector<vector<int>> obj(len , vector<int>(len));
            int obj[len][len];
            for(int i=0; i<len; i++){
                obj[i][i]   = 1;
            }
            for(int i=1; i<len; i++){
                for(int j=0; j<i; j++){
                    if(s[i] == s[j] && (i -1 == j || obj[j+1][i-1] == 1)){
                        obj[j][i] = 1;
                        if(i -j > end - start){
                            start = j;
                            end   = i;
                        }
                    }else{
                            obj[j][i] = 0;
                    }
                }
            }
            return s.substr(start, end - start +1) ;
    }
        string longestPalindrome_1(string s){

            int size   = s.size();
            int max    = 1;
            int start  = 0;
            int end    = 0;
            for(int i=0; i< size; i++){
                int max_1 = findmax(s, i, i);
                int max_2 = findmax(s, i, i + 1);
                max       = MAX(MAX(max_1, max_2),max);

                if(max > end - start + 1){
                    end   = i + max/2;
                    start = i - (max -1)/2;
                }
            }
            return s.substr(start, max);
        }
    private:
        int findmax(string s, int i, int j){
            int k = i;
            int m = j;
            int size = s.size();
            while(s[k] == s[m] && k >=0 && m <size){
                k--;
                m++;
            }
            return (m  - k - 1);
            //退出的位置 k m   是会文 两边的位置
        }
};
int main(int argc,const char *argv[]){
    string s ="asdfghgfdasd";
    class Solution tt;

    //cout <<tt.longestPalindrome(s) <<endl;
    cout <<tt.longestPalindrome_1(s) <<endl;

    return 0;
} 




