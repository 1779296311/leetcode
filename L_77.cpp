/*********************************************
*     ------------------------
*     file name: L_77.cpp
*     author   : @ JY
*     date     : 2019--09--20
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        int longestCommonSubsequence(string s1, string s2){
            int size_1 = s1.size();
            int size_2 = s2.size();
            if(size_1 == 0 || size_2 == 0){
                return 0;
            }
            vector<vector<int>> memo(size_1 + 1, vector<int>(size_2+1, 0));
            for(int i=1; i<=size_1; i++){
                for(int j=1; j<=size_2; j++){
                    memo[i][j] = max(memo[i][j-1], memo[i-1][j]);
                    if(s1[i-1] == s2[j-1]){
                        memo[i][j] = memo[i-1][j-1] + 1;
                    }
                }
            }
            return memo[size_1][size_2];
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    string   s1 = "jiasdasdng";
    string   s2 = "asdjiangll";
    cout <<te.longestCommonSubsequence(s1, s2)<<endl;
    return 0;
}
