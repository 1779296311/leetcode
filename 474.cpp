/*********************************************
*     file name: 474.cpp
*     author   : @ JY
*     date     : 2019--09--22
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        int findMaxFrom(vector<string>& strs, int m, int n){
            int size = strs.size();
            vector<int> one(size,0);
            vector<int> zero(size,0);
            for(int j=0; j<size; j++){
                string str = strs[j];
                for(int i=0; i<str.size(); i++){
                    if(str[i] == '0'){
                        zero[j]++;
                    }
                    if(str[i] == '1'){
                        one[j]++;
                    }
                }
            }
            vector<vector<vector<int>>> memo(size+1,vector<vector<int>>(m+1, vector<int>(n+1)));
            for(int i=0; i<=m; i++){
                for(int j=0; j<=n; j++){
                    memo[0][i][j] = 0;;
                }
            }
            for(int i=1; i<=size; i++){
                for(int j=0; j<=m; j++){
                    for(int k=0; k<=n; k++){
                        memo[i][j][k] = memo[i-1][j][k];
                        if(j>zero[i-1] && k>one[i-1]){
                            memo[i][j][k] = max(memo[i][j][k], memo[i-1][j-zero[i-1]][k-one[i-1]]+1);
                        }
                    }
                }
            }
            return memo[size][m][n];
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    //te.findMaxFrom(strs,m,n);
    return 0;
}
