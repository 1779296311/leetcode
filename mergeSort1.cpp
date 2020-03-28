/*********************************************
*     ------------------------
*     ------------------------
*     file name: mergeSort1.cpp
*     author   : @ JY
*     date     : 2020--03--06
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
int merge(int *nums, int l, int m, int r){
    int left  = l;
    int right = m+1;
    int index = 0;
    int __res = 0;
    int __tmp[r-l+1];
    while(left<=m && right<=r){
        __tmp[index++] = nums[left]<nums[right]?({__res+=(r-right+1)*nums[left],nums[left++];}):nums[right++];
    }
    while(left<=m){
        __tmp[index++] = nums[left++];
    }
    while(right<=r){
        __tmp[index++] = nums[right++];
    }
    for(int i=0; i<r-l+1; ++i){
        nums[i+l] = __tmp[i];
    }
    return __res;
}
int msort(int *nums, int l, int r){
    if(l == r){
        return 0;
    }
    int mid = l+((r-l)>>1);
    return msort(nums,l,mid) + msort(nums,mid+1,r) + merge(nums,l,mid,r);
}
int main(int argc,const char *argv[]){
    int nums[6] = {1,2,7,8,6,10};
    cout<<msort(nums,0,5)<<endl;
    return 0;
}
