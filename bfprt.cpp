/*********************************************
*     ------------------------
*     ------------------------
*     file name: bfprt.cpp
*     author   : @ JY
*     date     : 2020--03--25
**********************************************/
#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution{
     public:
         int bfprt(int* nums,int begin,int end,int k){
             if(end == begin){
                 return nums[end];
             }
             int l      = begin;
             int r      = end;
             int midNum = get_mid_num(nums,begin,end);
             partion(nums,&l,&r,midNum);
             if(k>=l && k<=r){
                 return nums[k];
             }else if(k<l){
                 return bfprt(nums,begin,l-1,k);
             }else{
                 return bfprt(nums,r+1,end,k);
             }
         }
         int get_mid_num(int *nums,int b, int e){
             int N     = e - b + 1;
             int size  = (N/5) + ((N%5)?1:0);
             int tmp[size];
             for(int i=0; i<size; ++i){
                 int begin = b + i*5;
                 int end   = begin + 4;
                 tmp[i] = sort_mid_num(nums,begin,min(end,e));
             }
             return bfprt(tmp,0,size-1,size/2);
         }
         int sort_mid_num(int* nums, int begin, int end){
             sort(nums+begin,nums+end+1);
             return nums[((begin+end)/2+(begin+end)%2)];
         }
         void partion(int *nums, int* l,int* r, int midNum){
             int l1 = *l-1;
             int r1 = *r+1;
             int m  = *l;
             while(m<r1){
                 if(nums[m]<midNum){
                     swap(nums,++l1,m++);
                 }else if(nums[m]>midNum){
                     swap(nums,--r1,m);
                 }else{
                     ++m;
                 }
             }
             *l = l1+1;
             *r = r1-1;
         }
         void swap(int* nums, int a, int b){
             if(nums[a] == nums[b]){
                 return;
             }
             nums[a] = nums[a] ^ nums[b];
             nums[b] = nums[a] ^ nums[b];
             nums[a] = nums[a] ^ nums[b];
         }
         int get_K_num(int* nums,int size, int k){
             if(k>size || k<1){
                 cout<<"k is not reachable"<<endl;
                 return INT_MAX;
             }
             return bfprt(nums,0,size,k-1);
         }
};
int main(int argc,const char *argv[]){
    Solution te;
    int nums[] = {1,3,6,234,2354,34,563,4612,0,8,2};
    int size = *(&nums+1)-nums-1;
    //cout<<te.get_mid_num(nums,0,size)<<endl;
    cout<<te.get_K_num(nums,size,1)<<endl;
    //cout<<te.get_K_num(nums,13)<<endl;
    //cout<<te.get_K_num(nums,1)<<endl;
    //cout<<te.get_K_num(nums,7)<<endl;
    return 0;
}
