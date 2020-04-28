/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_str_pro.cpp
*     author   : @ JY
*     date     : 2020--04--27
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        int min_editDistanceDP(string a, string b, int del, int add, int rep){
            int sizea = a.size();
            int sizeb = b.size();
            vector<vector<int>> dp(sizea+1,vector<int>(sizeb+1,0));
            for(int i=0; i<=sizeb; ++i){
                dp[0][i] = i*add;
            }
            for(int i=0; i<=sizea; ++i){
                dp[i][0] = i*del;
            }
            for(int i=1; i<=sizea; ++i){
                for(int j=1; j<=sizeb; ++j){
                    if(a[i-1] == b[j-1]){
                        dp[i][j] = dp[i-1][j-1];
                    }else{
                        dp[i][j] = dp[i-1][j-1] + rep;
                    }
                    dp[i][j] = min(dp[i][j],min(dp[i-1][j]+del,dp[i][j-1]+add));
                }
            }
            return dp[sizea][sizeb];
        }
        int min_editDistance(string a, string b,int del, int add, int rep){
            return process1(a,b,a.length()-1,b.length()-1,del,add,rep);
        }
        int process1(string a, string b, int i, int j, int del, int add, int rep){
            if(!i){
                return j*add;
            }
            if(!j){
                return i*del;
            }
            int res = process1(a,b,i-1,j-1,del,add,rep);
            if(a[i] != b[j]){
                res = res + rep;
            }
            return
                min(res,min(process1(a,b,i-1,j,del,add,rep)+del,process1(a,b,i,j-1,del,add,rep)+add));
        }
        /*--------------字符串交叉-----------------------------------------------------------------------------------*/
        bool is_Cross(string a, string b, string c){
            int sizea = a.length();
            int sizeb = b.length();
            int sizec = c.length();
            if(sizea+sizeb != sizec){
                return false;
            }
            return process2(a,b,c,sizea-1,sizeb-1);
        }
        bool process2(string a, string b, string c, int i, int j){
            if(a[i] != c[i+j+1] && b[j] != c[i+j+1]){
                return false;
            }
            if(!i){
                a[i]==c[i+j+1] && process2(a,b,c,i,j);
            }
            if(!j){
            }
            bool res = false;
            if(a[i] == c[i+j+1]){
                res = res | process2(a,b,c,i-1,j);
            }
            if(b[j] == c[i+j+1]){
                res = res |  process2(a,b,c,i,j-1);
            }
            return res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    string a = "bqr";
    string b = "rqr";
    string c = "rbqrqr";
    string b1= "asdasdasd";
    string b2= "rsdasdasdasdasqwerqwer";
    string b3= "qwerasddddddddqwerqwer";
    string b4= "qsdasdwer";
    cout<<te.is_Cross(a,b,c)<<endl;
    //cout<<"-----------------------------"<<endl;
    //cout<<te.min_editDistanceDP(b1,b2,1,2,3)<<endl;
    //cout<<te.min_editDistance(b1,b2,1,2,3)<<endl;
    //cout<<te.min_editDistanceDP(a,b,1,2,3)<<endl;
    //cout<<te.min_editDistance(a,b,1,2,3)<<endl;
    //cout<<"-----------------------------"<<endl;
    //cout<<te.min_editDistanceDP(b2,b4,1,2,3)<<endl;
    //cout<<te.min_editDistance(b2,b4,1,2,3)<<endl;
    //cout<<"-----------------------------"<<endl;
    //cout<<te.min_editDistanceDP(a,b3,1,2,3)<<endl;
    //cout<<te.min_editDistance(a,b3,1,2,3)<<endl;
    //cout<<"-----------------------------"<<endl;
    //cout<<te.min_editDistanceDP(a,b4,1,2,3)<<endl;
    //cout<<te.min_editDistance(a,b4,1,2,3)<<endl;
    //cout<<"-----------------------------"<<endl;
    return 0;
}
