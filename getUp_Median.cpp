/*********************************************
*     ------------------------
*     ------------------------
*     file name: getUp_Median.cpp
*     author   : @ JY
*     date     : 2020--04--07
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        int getUp_Median(int *a, int as, int ae, int *b, int bs, int be){
            int mida;
            int midb;
            int offset;
            while(as<ae){
                mida   = as+((ae-as)>>1);
                midb   = bs+((be-bs)>>1);
                offset = (ae-as)&1;
                if(a[mida] > b[midb]){
                    ae = mida;
                    bs = midb + offset;
                }else if(a[mida]<b[midb]){
                    be = midb;
                    as = mida + offset;
                }else{
                    return a[mida];
                }
            }
            return min(a[as],b[bs]);
        }
        int getK_Num(int *a, int sizea, int *b, int sizeb, int k){
            int sizeL;
            int sizeS;
            int *Long  = sizea>=sizeb?({sizeL=sizea;a;}):({sizeL=sizeb;b;});
            int *Short = sizea<sizeb?({sizeS=sizea;a;}):({sizeS=sizeb;b;});
            if(k<=sizeS){
                return this->getUp_Median(Short,0,k-1,Long,0,k-1);
            }else if(k>sizeL){
                if(Short[k-sizeL-1] >= Long[sizeL-1]){
                    return Short[k-sizeL-1];
                }
                if(Long[k-sizeS-1] >= Short[sizeS-1]){
                    return Long[k-sizeS-1];
                }
                return this->getUp_Median(Short,k-sizeL,sizeS-1,Long,k-sizeS,sizeL-1);
            }else{
                if(Long[k-sizeS-1] >= Short[sizeS-1]){
                    return Long[k-sizeS-1];
                }
                return this->getUp_Median(Short,0,sizeS-1,Long,k-sizeS,k-1);
            }
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    int a[] = {1,7,8,10};
    int b[] = {3,6,7,8,10,18,19,21};
    int size1 = *(&a+1)-a;
    int size2 = *(&b+1)-b;
    cout<<te.getK_Num(a,size1,b,size2,size2+3)<<endl;
    //cout<<te.getUp_Median(a,0,size,b,0,size)<<endl;
    //cout<<te.getUp_Median(a,0,size-1,b,0,size-1)<<endl;
    return 0;
}
