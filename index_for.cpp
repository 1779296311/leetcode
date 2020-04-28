/*********************************************
*     ------------------------
*     ------------------------
*     file name: index_for.cpp
*     author   : @ JY
*     date     : 2020--04--18
**********************************************/
#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
using  namespace  std;
//下标循环怼
class Solution{
    public:
        void heapSort(int *nums, int size){
            for(int i=(size>>1)-1; i>=0; --i){
                heapfy(nums,size,i);
            }
            for(int i=size-1; i>=1; --i){
                swap(nums,0,i);
                heapfy(nums,i,0);
            }
        }
        void heapfy(int *nums, int size, int index){
            int left = (index<<1)+1;
            int cur  = 0;
            while(left < size){
                cur = (left+1<size&&nums[left]<nums[left+1])?left+1:left;
                cur = nums[cur]>nums[index]?cur:index;
                if(cur == index){
                    break;
                }
                swap(nums,cur,index);
                index = cur;
                left  = (index<<1)+1;
            }
        }
    public:
        void shuffle_1(int *nums,int size){
            heapSort(nums,size);
            int begin = 0;
            if(size&1){
                ++begin;
            }else{
                rorate(nums,begin,size>>1,size);
            }
            shuffle(nums,begin,size);
        }
        void shuffle(int *nums,int begin, int size){
            if((size-begin)&1){
                return;
            }
            int end   = size;
            int k     = 0;
            int mid   = 0;
            int tmp   = 0;
            while(begin<end){
                mid = begin+((end-begin)>>1)-1;
                k   = less_ThreeK(end-begin);
                tmp = ((int)(pow(3.0,k)-1)>>1);
                rorate(nums,begin+tmp,mid,mid+tmp+1);
                shuffle(nums,begin,begin+(tmp<<1),k);
                begin = begin + (tmp<<1);
            }
        }
        void shuffle(int *nums, int begin, int end, int k){
            int mid    = ((end-begin)>>1)-1;
            int tmp    = 0;
            int offset = 0;
            int head   = 0;
            int value  = 0;
            for(int i=0; i<k; ++i){
                head   = pow(3.0,i)-1;
                offset = head;
                value  = nums[begin+offset];
                do{
                    if(offset<=mid){
                        offset = (offset<<1)+1;
                    }else{
                        offset = ((offset-mid)<<1)-2;
                    }
                    tmp                = nums[begin+offset];
                    nums[begin+offset] = value;
                    value              = tmp;
                }while(offset != head);
            }
        }
        int less_ThreeK(int n){
            int i   = 0;
            int tmp = 0;
            while(n>=tmp){
                tmp = pow(3.0,i++)-1;
            }
            //cout<<pow(3.0,i-2)-1<<endl;
            return i>2?i-2:0;
        }
        void rorate(int *nums, int s, int m, int e){
            if(s>m || m>e || s>e){
                return;
            }
            if(e-s<2){
                swap(nums,s,e);
            }else if(!((e-s)&1) && (((e-s)>>1)+s==m)){
                while(m<e){
                    swap(nums,s++,m++);
                }
                cout<<"yes"<<endl;
            }else{
                int a = s;
                int b = m;
                while(a<b){
                    swap(nums,a++,b--);
                }
                a = m+1;
                b = e;
                while(a<b){
                    swap(nums,a++,--b);
                }
                a = s;
                b = e;
                while(a<b){
                    swap(nums,a++,--b);
                }
            }
        }
        void swap(int *nums, int a, int b){
            if(nums[a] == nums[b]){
                return ;
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
    //cout<<te.less_ThreeK(1)<<endl;
    //int  nums[] = {1,2,3,4,5,6,7,8,9,10};
    int  nums[] = {1,2,3,4,0,0,0,0};
    //int  nums[] = {2,4,6,8,1,3,5,7};
    //int  nums[] = {0,0,0,0,1,1,1,1,2,2,2,2};
    //int  nums[] = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
    //int  nums[] = {3,2};
    //int  nums[] = {2,2,2,3,1,4};
    int size = *(&nums+1)-nums;
    te.debug(nums,size);
    te.rorate(nums,1,4,7);
    te.debug(nums,size);
    return 0;
}
