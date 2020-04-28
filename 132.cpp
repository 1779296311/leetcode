/*********************************************
*     file name: 132.cpp
*     author   : @ JY
*     data     : 2019--09--15
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <climits>
#include <vector>
using  namespace  std;

class Solution{
    public:
        int minCutPalindrome(string s){
            int size = s.size();
            if(size == 1 || size == 0){
                return size;
            }
            vector<vector<bool>> memo(size, vector<bool>(size, false));
            Palindrome(memo, size, s);
            vector<int> fd(size+1, INT_MAX);
            fd[0] = 0;
            for(int i=1; i<=size; i++){
                for(int j=0; j<i; j++){
                    if(memo[j][i-1]){
                        fd[i] = min(fd[i], fd[j] + 1);
                    }
                }
            }
            return (fd[size] - 1);
        }
    private:
        void Palindrome(vector<vector<bool>>& memo, int size, string s){
            for(int i=0; i<size; i++){
                memo[i][i] = true;
            }
            for(int i=1; i<size; i++){
                for(int j=0; j<i; j++){
                    if(s[i] == s[j] && (j+1 == i || memo[j+1][i-1])){
                        memo[j][i]  = true;
                    }
                }
            }
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    string  s = "aslasalab";
    //string  s = "ab";
    //cout <<te.minCutPalindrome(s) <<endl;
    return 0;
}
            //for(int i=0; i<size; i++){
            //    for(int j=0; j<size; j++){
            //        cout <<memo[i][j] <<"-- ";
            //    }
            //    cout <<endl;
            //}
