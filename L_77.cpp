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
        //zi xulie
        int longestCommonSubsequence(string s1, string s2){
            int size_1 = s1.size();
            int size_2 = s2.size();
            if(size_1 == 0 || size_2 == 0){
                return 0;
            }
            vector<vector<int>> memo(size_1+1, vector<int>(size_2+1, 0));
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
        int longestCommonSubsequence_2(string s1, string s2){
            int size_1 = s1.size();
            int size_2 = s2.size();
            if(size_1 == 0 || size_2 == 0){
                return 0;
            }
            int oldP = 0;
            int newP = 0;
            vector<int> memo(size_2+1,0);
            for(int i=1; i<=size_1; i++){
                for(int j=1; j<=size_2; j++){
                    newP    = memo[j];
                    memo[j] = max(memo[j-1], memo[j]);
                    if(s1[i-1] == s2[j-1]){
                        memo[j] = oldP + 1;
                    }
                    oldP    = newP;
                }
                oldP = 0;
            }
            return memo[size_2];
        }
        // zi chuan
        int longestCommonSon(string s1, string s2){
            int len1 = s1.length();
            int len2 = s2.length();
            int row  = 0;
            int col  = len2-1;
            int len  = 0 ;
            int maxL = 0 ;
            int end  = 0 ;
            while(row < len1){
                int i = row;
                int j = col;
                while(i<len1 && j<len2){
                    if(s1[i] == s2[j]){
                        ++len;
                    }else{
                        len = 0;
                    }
                    if(maxL < len){
                        maxL = len;
                        end  = i;
                    }
                    ++i;
                    ++j;
                }
                if(col > 0){
                    --col;
                }else{
                    ++row;
                }
            }
            return maxL;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    string b = "jassj";
    string a = "ssjss";
    cout<<te.longestCommonSon(a,b)<<endl;
    string   s1 = "abbbbbasdbdasdng";
    string   s2 = "abbsssbbbdasdng";
    string   s3 = "abbbdasdng";
    string   s4 = "abbbbbbdasdassdngsd";
    string   s5 = "bnasdjbbbbbbbsdasdiangll";
    //cout <<te.longestCommonSubsequence(s3, s2)<<endl;
    //cout <<te.longestCommonSubsequence_2(s3, s2)<<endl;
    //cout<<"_____________________-"<<endl;
    //cout <<te.longestCommonSubsequence(s1, s3)<<endl;
    //cout <<te.longestCommonSubsequence_2(s1, s3)<<endl;
    //cout<<"_____________________-"<<endl;
    //cout <<te.longestCommonSubsequence(s4, s2)<<endl;
    //cout <<te.longestCommonSubsequence_2(s4, s2)<<endl;
    //cout<<"_____________________-"<<endl;
    //cout <<te.longestCommonSubsequence(s3, s3)<<endl;
    //cout <<te.longestCommonSubsequence_2(s3, s3)<<endl;
    //cout<<"_____________________-"<<endl;
    //cout <<te.longestCommonSubsequence(s5, s4)<<endl;
    //cout <<te.longestCommonSubsequence_2(s5, s4)<<endl;
    //cout<<"_____________________-"<<endl;
    //cout<<te.longestCommonSon(s1,s2)<<endl;
    return 0;
}
