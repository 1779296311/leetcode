/*********************************************
*     ------------------------
*     ------------------------
*     file name: hnt.cpp
*     author   : @ JY
*     date     : 2020--03--14
**********************************************/
#include <iostream>
#include <climits>
#include <stack>
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
        /*-------------------------------------------------*-----------------*-----------------*-----------------*-----------------*-----------------*-----------------*-----------------*/
        int hnt2(int num, string left, string mid, string right, string from, string to){
            if(num == 1){
                if(from==mid || to==mid){
                    cout<<"move "<<num<<" from "<<from<<" -> "<<to<<endl;
                    return 1;
                }else{
                    cout<<"move "<<num<<" from "<<from<<" -> "<<mid<<endl;
                    cout<<"move "<<num<<" from "<<mid<<"  -> "<<to<<endl;
                    return 2;
                }
            }
            if(from==mid || to==mid){
                string other = (from==left||to==right)?right:left;
                int sp1 = hnt2(num-1,left,mid,right,from,other);
                cout<<"move "<<num<<" from "<<from<<" -> "<<to<<endl;
                int sp2 = hnt2(num-1,left,mid,right,other,to);
                return sp1+sp2+1;
            }else{
                int sp1 = hnt2(num-1,left,mid,right,from,to);
                cout<<"move "<<num<<" from "<<from<<" -> "<<mid<<endl;
                int sp2 = hnt2(num-1,left,mid,right,to,from);
                cout<<"move "<<num<<" from "<<mid<<" -> "<<to<<endl;
                int sp3 = hnt2(num-1,left,mid,right,from,to);
                return sp1+sp2+sp3+2;
                /*-----------------------------------------------*/
                //int sp1 = hnt2(num-1,left,mid,right,from,mid);
                //int sp2 = hnt2(num-1,left,mid,right,mid,to);
                //cout<<"move "<<num<<" from "<<from<<" -> "<<mid<<endl;
                //int sp3 = hnt2(num-1,left,mid,right,to,from);
                //cout<<"move "<<num<<" from "<<mid<<" -> "<<to<<endl;
                //int sp4 = hnt2(num-1,left,mid,right,from,to);
                //return sp1+sp2+sp3+sp4+2;
            }
        }
        int hnt2(int num, string left, string mid, string right){
            stack<int> L;
            stack<int> M;
            stack<int> R;
            L.push(INT_MAX);
            R.push(INT_MAX);
            M.push(INT_MAX);
            for(int i=num; i>0; --i){
                L.push(i);
            }
            int step    = 0;
            int opPre   = 0;
            /*
             * l->m 1
             * m->l 2
             * m->r 3
             * r->m 4
             * */
            while(R.size() != num+1){
                step  += tryMove(opPre,2,1,L,M,left,mid);
                step  += tryMove(opPre,1,2,M,L,mid,left);
                step  += tryMove(opPre,4,3,M,R,mid,right);
                step  += tryMove(opPre,3,4,R,M,right,mid);
            }
            return step;
        }
        int tryMove(int& opPre,int opP,int opNow, stack<int>& F, stack<int>& T, string from, string to){
            if(opPre != opP && F.top()<T.top()){
                T.push(F.top());
                F.pop();
                opPre = opNow;
                cout<<"move "<<T.top()<<" from "<<from<<" -> "<<to<<endl;
                return 1;
            }
            return 0;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    cout<<te.hnt2(5,"left","mid","right")<<endl;
    cout<<"______________________________________--"<<endl;
    cout<<te.hnt2(5,"left","mid","right","left","right")<<endl;
    //vector<int> p = {3,3,1,2};
    //vector<int> p = {3,1,1};
    //cout<<te.is_bestPath(p)<<endl;
    return 0;
}
