/*********************************************
*     ------------------------
*     ------------------------
*     file name: 29.cpp
*     author   : @ JY
*     date     : 2019--10--05
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        int add(int a, int b){
            int c;
            int p;
            while(b){
                c = a^b;
                p = (a&b)<<1;
                a = c;
                b = p;
            }
            return a;
        }
        int sub(int a, int b){
            return add(a,add(~b,1));
        }
        int check_sign(int a) const {
            return a>>31;
        }
        void change(int *a){
            if(check_sign(*a)){
                *a = (~*a + 1);
            }
        }
        int mul(int a, int b){
            bool flag = true;
            int res   = 0;
            if(check_sign(a) == check_sign(b)){
                flag = false;
            }
            change(&a);
            change(&b);
            while(b){
                res = add(res, a);
                b   = sub(b,1);
            }
            if(flag){
                res = ~res + 1;
            }
            return res;
        }
        int div(int a, int b){
            bool flag = true;
            int res   = 0;
            if(check_sign(a) == check_sign(b)){
                flag = false;
            }
            change(&a);
            change(&b);
            while(a>=b){
                res = add(res,1);
                a   = sub(a,b);
            }
            if(flag){
                res = (~res+1);
            }
            return res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    cout<<te.add(10,-3)<<endl;
    cout<<te.sub(3,8)<<endl;
    cout<<te.mul(-15,3)<<endl;
    cout<<te.div(10,4)<<endl;
    return 0;
}
