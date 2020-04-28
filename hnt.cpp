/*********************************************
*     ------------------------
*     ------------------------
*     file name: hnt.cpp
*     author   : @ JY
*     date     : 2020--03--14
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        void hnt(int n, const char*from, const char *to, const char *help){
            if(n == 1){
                cout<<"move "<<from<<"->"<<to<<endl;
            }else{
                hnt(n-1,from,help,to);
                hnt(1,from,to,help);
                hnt(n-1,help,to,from);
            }
        }
        int is_bestPath(vector<int>& p){
            return process1(p,p.size()-1,1,2,3);
        }
        int process1(vector<int>& p,int n, int A, int B, int C){
            if(n<0){
                return 0;
            }
            if(p[n] == B){
                return -1;
            }else if(p[n] == C){
                int tmp = process1(p,n-1,B,A,C);
                return tmp==-1?tmp:tmp+(1<<n);
            }else if(p[n] == A){
                return process1(p,n-1,A,C,B);
            }
            return -1;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    //vector<int> p = {3,3,1,2};
    vector<int> p = {3,1,1};
    cout<<te.is_bestPath(p)<<endl;
    return 0;
}
