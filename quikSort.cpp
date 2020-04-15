/*********************************************
*     ------------------------
*     ------------------------
*     file name: quikSort.cpp
*     author   : @ JY
*     date     : 2020--03--08
**********************************************/
#include <iostream>
#include <stack>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
       void qpartition(int *nums, int *l, int *r){
           int left  = (*l)-1;
           int right = *r;
           int cur   = *l;
           while(cur<right){
               if(nums[cur]<nums[*r]){
                   qswap(nums,++left,cur++);
               }else if(nums[cur]>nums[*r]){
                   qswap(nums,--right,cur);
               }else{
                   ++cur;
               }
           }
           qswap(nums,cur,*r);
           *l = left;
           *r = right+1;
       }
       void quikSort(int *nums,int l, int r){
           if(l>=r){
               return;
           }
           int ml = l;
           int mr = r;
           qpartition(nums,&ml,&mr);
           quikSort(nums,l,ml);
           quikSort(nums,mr,r);
       }
       void quickSortNotR(int *nums, int l, int r){
           stack<int> st;
           int left;
           int right;
           st.push(r);
           st.push(l);
           while(!st.empty()){
               left  = l = st.top();
               st.pop();
               right = r = st.top();
               st.pop();
               qpartition(nums,&l,&r);
               if(l>left){
                   st.push(l);
                   st.push(left);
               }
               if(r<right){
                   st.push(right);
                   st.push(r);
               }
           }
       }
       void qswap(int *nums, int a, int b){
           if(nums[a] == nums[b]){
               return;
           }
           nums[a] = nums[a] ^ nums[b];
           nums[b] = nums[a] ^ nums[b];
           nums[a] = nums[a] ^ nums[b];
       }
       void qdebug(int *nums,int l, int r){
           int size = r;
           //qpartition(nums,&l,&r);
           for(int i=0; i<=size; ++i){
               cout<<nums[i]<<endl;
           }
       }
};
int main(int argc,const char *argv[]){
    Solution te;
    int nums[10] = {2,4,1,1,1,12,1,3,0,5467};
    te.quickSortNotR(nums,0,9);
    te.qdebug(nums,0,9);
    te.quikSort(nums,0,9);
    te.qdebug(nums,0,9);
    return 0;
}
