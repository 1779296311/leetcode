/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_bit_pro.cpp
*     author   : @ JY
*     date     : 2020--04--29
**********************************************/
#include <iostream>
#include <climits>
#include <vector>
#include <stdlib.h>
using  namespace  std;
/*
去掉最后一位          | (101101->10110)           | x shr 1             x >> 1
在最后加一个0         | (101101->1011010)         | x shl 1             x << 1
在最后加一个1         | (101101->1011011)         | x shl 1+1
把最后一位变成1       | (101100->101101)          | x or 1
把最后一位变成0       | (101101->101100)          | x or 1-1
最后一位取反          | (101101->101100)          | x xor 1
把右数第k位变成1      | (101001->101101,k=3)      | x or (1 shl (k-1))
把右数第k位变成0      | (101101->101001,k=3)      | x and not(1 shl (k-1))
右数第k位取反         | (101001->101101,k=3)      | x xor (1 shl (k-1))
取末三位              | (1101101->101)            | x and 7
取末k位               | (1101101->1101,k=5)       | x and (1 shl k-1)
取右数第k位           | (1101101->1,k=4)          | x shr (k-1) and 1
把末k位变成1          | (101001->101111,k=4)      | x or (1 shl k-1)
末k位取反             | (101001->100110,k=4)      | x xor (1 shl k-1)
把右边连续的1变成0    | (100101111->100100000)    | x and (x+1)
把右起第一个0变成1    | (100101111->100111111)    | x or (x+1)
把右边连续的0变成1    | (11011000->11011111)      | x or (x-1)
取右边连续的1         | (100101111->1111)         | (x xor (x+1)) shr 1
*/
class Solution{
    public:
        /*----------------------------------------use bit (+,-,*,/)-----------------------------------------------------------*/
        int add(int a, int b){
            int tmp = 0;
            while(b){
                tmp = a;
                a   = a ^ b;
                b   = (tmp&b)<<1;
            }
            return a;
        }
        int sub(int a, int b){
            return add(a,add(~b,1));
        }
        int mul(int a, int b){
            int res = 0;
            while(b){
                if(b&1){
                    res = add(res,a);
                }
                a = a<<1;
                b = (unsigned)b>>1;
            }
            return res;
        }
        int abs(int a){
            if(a<0){
                return add(~a,1);
            }
            return a;
        }
        int divReal(int a, int b){
            int flag = 0;
            if((a<0 && b<0) ||(a>0 && b>0)){
                flag = 1;
            }
            int x = abs(a);
            int y = abs(b);
            int res = 0;
            for(int i=31; i>=0; i=sub(i,1)){
                if((x>>i)>=y){
                    res = res | (1<<i);
                    x   = sub(x,(y<<i));
                }
            }
            return !flag?add(~res,1):res;
        }
        int div(int a, int b){
            if(!b){
                cout<<"b is zero"<<endl;
                return -1;
            }
            if(a == INT_MIN && b==INT_MIN){
                return 1;
            }else if(a == INT_MIN){
                int res = divReal(add(a,1),b);
                return add(res,divReal(sub(a,mul(res,b)),b));
            }else if(b == INT_MIN){
                return 0;
            }else{
                return divReal(a,b);
            }
        }
        /*---------------------------------------Cow num------------------------------------------------------------*/
        int cowNum(int n){
            if(n<=4){
                return n;
            }
            vector<vector<int>> ori = {{3,2,1}};
            vector<vector<int>> res = {{1,1,0},{0,0,1},{1,0,0}};
            res = quickPow(res,n-3);
            res = matrixMul(ori,res);
            //debug(res);
            return res[0][0];
        }
        /*---------------------------------------Fibonacci------------------------------------------------------------*/
        int Fibonacci(int n){
            if(n<=0 || n==1 || n==2){
                return 1;
            }
            vector<vector<int>>ori = {{1,1}};
            vector<vector<int>>res = {{1,1},{1,0}};
            res = quickPow(res,n-2);
            res = matrixMul(ori,res);
            return res[0][0];
        }
        vector<vector<int>> quickPow(vector<vector<int>>& matrix, int n){
            int sizeI = matrix.size();
            int sizeJ = matrix[0].size();
            if(sizeI != sizeJ){
                cout<<"Can't pow!!!"<<endl;
                return vector<vector<int>>{};
            }
            vector<vector<int>> res(sizeI,vector<int>(sizeI,0));
            for(int i=0; i<sizeI; ++i){
                res[i][i] = 1;
            }
            while(n>0){
                if(n&1){
                    res = matrixMul(res,matrix);
                }
                matrix = matrixMul(matrix,matrix);
                n = n >> 1;
            }
            return res;
        }
        vector<vector<int>> matrixMul(vector<vector<int>>& a, vector<vector<int>>& b){
            int sizeAI = a[0].size();
            int sizeBJ = b.size();
            if(sizeAI != sizeBJ){
                cout<<"Can't mul!!!"<<endl;
                return vector<vector<int>>{};
            }
            int sizea = a.size();
            int sizeb = b[0].size();
            vector<vector<int>> res(sizea,vector<int>(sizeb,0));
            for(int i=0; i<sizea; ++i){
                for(int j=0; j<sizeb; ++j){
                    for(int k=0; k<sizeAI; ++k){
                        res[i][j] = res[i][j] + a[i][k]*b[k][j];
                    }
                }
            }
            return res;
        }
        void debug(vector<vector<int>>& res){
            if(res.empty()){
                cout<<"Empty cout??"<<endl;
                return;
            }
            for(int i=0; i<res.size(); ++i){
                for(int j=0; j<res[0].size(); ++j){
                    cout<<" "<<res[i][j]<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    cout<<te.div(10,-5)<<endl;
    cout<<te.div(INT_MIN,-1)<<endl;
    cout<<te.div(12345,-5)<<endl;
    cout<<endl;
    //cout<<te.Fibonacci(6)<<endl;
    //cout<<te.Fibonacci(7)<<endl;
    //cout<<te.Fibonacci(8)<<endl;
    //vector<vector<int>> a = {{1,3,2},{1,0,0},{1,2,2}};
    //vector<vector<int>> b = {{0,0,2},{7,5,0},{2,1,1}};
    //vector<vector<int>> a = {{5,2,4},{3,8,2},{6,0,4}};
    //vector<vector<int>> b = {{2,2},{2,2},{3,3}};
    //vector<vector<int>> res = te.quickPow(b,2);
    //te.debug(res);
    //vector<vector<int>> b = {{2,4},{1,3},{3,2}};
    //vector<vector<int>> res = te.matrixMul(a,b);
    //te.debug(res);
    return 0;
}
