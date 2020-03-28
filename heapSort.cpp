/*********************************************
*     ------------------------
*     ------------------------
*     file name: heapSort.cpp
*     author   : @ JY
*     date     : 2020--03--07
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution{
   public:
   void adjust(int *nums, int size, int index){
        int leftC  = index*2 + 1;
        int rightC = index*2 + 2;
        int now    = index;
        if(leftC<size && nums[leftC]>nums[now]){
            now = leftC;
        }
        if(rightC<size && nums[rightC]>nums[now]){
            now = rightC;
        }
        if(now != index){
            nums[now]   = nums[now] ^ nums[index];
            nums[index] = nums[now] ^ nums[index];
            nums[now]   = nums[now] ^ nums[index];
            adjust(nums,size,now);
        }
    }
   void  heapfi(int *nums, int size, int index){
       int left = index*2+1;
       int now;
       while(left<size){
           now  = (left+1<size&&nums[left+1]>nums[left])?left+1:left;
           now  = (nums[index]>nums[now])?index:now;
           if(now == index){
               break;
           }
           swap(nums,now,index);
           index       = now;
           left        = index*2+1;
       }
   }
   void heapaux(int *nums, int size, int index, int value){
       int parent = ((index-1)>>1);
       while(index>0&&nums[parent]<value){
           nums[index] = nums[parent];
           index       = parent;
           parent      = ((index-1)>>1);
       }
       nums[index] = value;
   }
    void heapSort(int *nums, int size){
        //for(int i=size-1; i>=0; --i){
        for(int i=(size/2)-1; i>=0; --i){
            //adjust(nums,size,i);
            heapfi(nums,size,i);
        }
        for(int i=size-1; i>=1; --i){
            nums[0] = nums[0] ^ nums[i];
            nums[i] = nums[0] ^ nums[i];
            nums[0] = nums[0] ^ nums[i];
            //adjust(nums,i,0);
            heapfi(nums,i,0);
        }
    }
    void swap(int *nums, int a,int b){
        if(nums[a] == nums[b]){
            return;
        }
        nums[a] = nums[a] ^ nums[b];
        nums[b] = nums[a] ^ nums[b];
        nums[a] = nums[a] ^ nums[b];
    }
    void debug(int nums[], int size){
        for(int i=0; i<=size; ++i){
            cout<<nums[i]<<endl;
        }
    }
};
void test(int *nums){
    int num[10] = {2,1,234,11,234,56785678,122,-2,4,87};
    cout<<(*(&nums+1)-nums)<<endl;
    cout<<(*(&num+1)-num)<<endl;
}
int main(int argc,const char *argv[]){
    int nums[10] = {2,1,234,11,234,56785678,122,-2,4,87};
    int a = 9;
    int *k = &a;
    int *p = nums;
    cout<<*(&p+1)-p<<endl;
    test(nums);
    //Solution te;
    //te.heapSort(nums,10);
    //te.debug(nums,10);
    return 0;
}
