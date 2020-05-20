/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ13.cpp
*     author   : @ JY
*     date     : 2020--05--08
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        int movingCount(int i,int j, int k){
            vector<vector<int>> DFS(i,vector<int>(j,0));
            return dfs(0,0,k,DFS);
        }
        int dfs(int i, int j, int k, vector<vector<int>>& DFS){
            if(i<0||j<0||i>=DFS.size()||j>=DFS[0].size()||(i/10+i%10+j/10+j%10)>k||DFS[i][j]){
                return 0;
            }
            DFS[i][j] = 1;
            return 
                dfs(i+1,j,k,DFS)+
                dfs(i,j+1,k,DFS)+
                dfs(i-1,j,k,DFS)+
                dfs(i,j-1,k,DFS)+
                        1;
        }
        /////______________________fuck___________________fuck ____________fuck ____________fuck ____________fuck ____________fuck ____________fuck ____________fuck
        int movingCountFailed(int i, int j, int k){
            int t    = 0;
            int tmp  = 0;
            int maxI = i;
            int maxJ = j;
            while(t<=i){
                if(getNSum(t)>k){
                    maxI = t;
                    break;
                }
                ++t;
            }
            t = 0;
            while(t<=j){
                if(getNSum(t)>k){
                    maxJ = t;
                    break;
                }
                ++t;
            }
            if(getNSum(maxJ)+getNSum(maxI)<=k){
                cout<<"1"<<endl;
                return maxJ*maxI;
            }else if(maxJ == maxI){
                cout<<"2"<<endl;
                return (maxJ+((maxJ*(maxJ-1))>>1))>i*j?i*j:(maxJ+((maxJ*(maxJ-1))>>1));
            }else{
                cout<<maxI<<"--"<<maxJ<<endl;
                cout<<"3"<<endl;
                int maxN = max(maxI,maxJ);
                int minN = min(maxI,maxJ);
                int res  = minN*(maxN-minN);
                return res+(minN+((minN*(minN-1))>>1));
            }
        }
        int getNSum(int N){
            int res = 0;
            while(N){
                res = res + N%10;
                N   = N/10;
            }
            return res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    cout<<te.movingCount(38,15,9)<<endl;
    return 0;
}
