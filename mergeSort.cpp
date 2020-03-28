/*********************************************
*     ------------------------
*     ------------------------
*     file name: mergeSort.cpp
*     author   : @ JY
*     date     : 2020--03--06
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
void merge(int *nums,int l, int m, int r){
    int __tmp[r-l+1];
    int l1 = l;
    int r1 = m+1;
    int i  = 0;
    while(l1<=m && r1<=r){
        __tmp[i++] = (nums[l1]<=nums[r1])?nums[l1++]:nums[r1++];
    }
    while(r1<=r){
        __tmp[i++] = nums[r1++];
    }
    while(l1<=m){
        __tmp[i++] = nums[l1++];
    }
    for(int i=0; i<(r-l+1); ++i){
        nums[i+l]  = __tmp[i];
    }
}
void msort(int *nums,int l, int r){
    if(l==r){
        return;
    }
    int mid = l+((r-l)>>1);
    msort(nums,l,mid);
    msort(nums,mid+1,r);
    merge(nums,l,mid,r);
}
int main(int argc,const char *argv[]){
    int nums[11] = {2,4,1,345,12,4356,689,123,2345,123123,12312412};
    int nums1[8] = {2,5,4,45,0,1,6,9};
    //merge(nums1,0,1,3);
    //for(int i=0; i<8; ++i){
        //cout<<nums1[i]<<endl;
    //}
    msort(nums,0,10);
    for(int i=0; i<11; ++i){
        cout<<nums[i]<<endl;
    }
    return 0;
}
