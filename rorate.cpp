/*********************************************
*     ------------------------
*     ------------------------
*     file name: rorate.cpp
*     author   : @ JY
*     date     : 2020--04--22
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        void rorate_1(int *nums,int b, int m, int e){
            if(b>e || b>m || m>e){
                return;
            }
            int leftN;
            int rightN;
            while(1){
                leftN  = m - b + 1;
                rightN = e - m - 1;
                if(leftN > rightN){
                    rorateReal(nums,b,m+1,rightN);
                    b = b + rightN;
                }else if(leftN < rightN){
                    rorateReal(nums,b,e-leftN,leftN);
                    e = e - leftN;
                }else{
                    rorateReal(nums,b,m+1,leftN);
                    break;
                }
                debug(nums,9);
            };
        }
        void rorate_2(int *nums, int b, int m, int e){
            if(b>e || b>m || m>e){
                return;
            }
            int leftN  = m - b + 1;
            int rightN = e - m - 1;
            if(leftN < rightN){
                rorateReal(nums,b,e-leftN,leftN);
                rorate_2(nums,b,m,e-leftN);
            }else if(leftN > rightN){
                rorateReal(nums,b,m+1,rightN);
                rorate_2(nums,b+rightN,m,e);
            }else{
                rorateReal(nums,b,m+1,rightN);
                return;
            }
        }
        void rorateReal(int *nums, int s1, int s2, int n){
            if(n<=0){
                return;
            }
            while(n){
                swap(nums, s1++, s2++);
                --n;
            }
        }
        void swap(int *nums, int a, int b){
            if(nums[a] == nums[b]){
                return;
            }
            nums[a] = nums[a] ^ nums[b];
            nums[b] = nums[a] ^ nums[b];
            nums[a] = nums[a] ^ nums[b];
        }
        void debug(int *nums, int size){
            for(int i=0; i<size; ++i){
                cout<<nums[i]<<"   ";
            }
            cout<<endl;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    int nums[] = {1,3,4,5,6,2,2,2,2};
    int size   = *(&nums+1) - nums;
    te.debug(nums,size);
    te.rorate_2(nums,0,4,size);
    te.debug(nums,size);
    return 0;
}
