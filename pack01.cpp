/********************************************* 
*     ------------------------
*     ------------------------
*     file name: pack01.cpp
*     author   : @ JY
*     data     : 2019--09--11
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;

class Solution{
    public:
        int pack01(vector<int>& w, vector<int>& v, int c){
            int len = w.size();
            vector<vector<int>> memo(len+1, vector<int>(c+1, 0));
            for(int i=0; i<=c; i++){
                if(i >= w[0]){
                    memo[0][i] = v[0];
                }
            }
            for(int i=1; i<len; i++){
                for(int j=1; j<=c; j++){
                    memo[i][j] = memo[i-1][j];
                    if(j>=w[i]){
                        memo[i][j] = max(memo[i][j],v[i]+memo[i-1][j-w[i]]);
                    }
                }
            }
            return memo[len -1][c];
        }
        int pack_better(vector<int>& w, vector<int>& v, int c){
            int len  = w.size();
            vector<int> memo(c+1, -1);
            for(int i=0; i<=c; i++){
                memo[i] = (i>=w[0]) ? v[0] : 0;
            }

            for(int i=1; i<len; i++){
                for(int j=c; j>=w[i]; --j){
                    memo[j] = max(memo[j], v[i] + memo[j-w[i]]);
                }
            }
            return memo[c];
        }
        int pack_3(vector<int>& w, vector<int>& v, int c){
            int len  = w.size();
            vector<int> memo(c+1, -1);
            for(int i=0; i<=c; i++){
                memo[i] = (i>=w[0]) ? v[0] : 0;
            }

            for(int i=1; i<len; i++){
                for(int j=1; j<=c; ++j){
                    if(j>=w[i]){
                        memo[j] = max(memo[j], v[i] + memo[j-w[i]]);
                    }
                }
            }
            return memo[c];
        }
        int pack_2(vector<int>& w, vector<int>& v, int c){
            int len  = w.size();
            vector<int> memo(c+1, -1);
            for(int i=0; i<=c; i++){
                memo[i] = (i>=w[0]) ? v[0] : 0;
            }

            for(int j=1; j<=c; ++j){
                for(int i=1; i<len; i++){
                    if(j>=w[i]){
                        memo[j] = max(memo[j], v[i] + memo[j-w[i]]);
                    }
                }
            }
            return memo[c];
        }

        //int find_best_01(vector<vector<int>>& memo, int i, int j, vector<int>& best,vector<int>& w,vector<int>& v){
            //if(i>0){
                //if(memo[i][j] == memo[i-1][j]){
                    //best[i] = 0;
                    //find_best_01(memo, i-1, j, best, w, v);
                //}else if(j-w[i]>=0 && memo[i][j] == memo[i][j-w[i]] + v[i]){
                    //best[i] = 1;
                    //find_best_01(memo, i-1, j-w[i], best, w, v);
                //}
            //}
        //}
};
int main(int argc,const char *argv[]){
    vector<int> packW = {2,4,5,6,8,13};
    vector<int> packM = {1,3,5,6,7,14};
    Solution te;
    cout<<te.pack01(packW,packM,30)<<endl;
    cout<<te.pack_better(packW,packM,30)<<endl;
    cout<<te.pack_2(packW,packM,30)<<endl;
    cout<<te.pack_3(packW,packM,30)<<endl;
    return 0;
}
