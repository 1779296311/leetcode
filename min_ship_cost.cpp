/*********************************************
*     ------------------------
*     ------------------------
*     file name: min_ship_cost.cpp
*     author   : @ JY
*     date     : 2020--04--13
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        int min_ship_cost(int *nums, int size, int limit){
            quickSort(nums,0,size-1);
            if(nums[size-1] > limit){
                return -1;
            }
            int lessR = -1;
            for(int i=size-1; i>=0; --i){
                if(nums[i] <= limit/2){
                    lessR = i;
                    break;
                }
            }
            if(lessR == -1){
                return size;
            }
            int left  = lessR;
            int right = lessR+1;
            int b     = 0;
            while(left>=0){
                int solved = 0;
                while(right<size && nums[left]+nums[right] <= limit){
                    ++right;
                    ++solved;
                }
                if(!solved){
                    ++b;
                    --left;
                }else{
                    left = left - solved;
                }
            }
            int leftN = lessR + 1;
            int a     = leftN - b;
            int c     = size - leftN - a;
            return a+c+((b+1)>>1);
        }
        void partion(int *nums, int *l, int *r){
            int left  = (*l)-1;
            int right = (*r)+1;
            int cur   = *l;
            while(cur<right){
                if(nums[cur] < nums[*r]){
                    swap(nums,++left,cur++);
                }else if(nums[cur] > nums[*r]){
                    swap(nums,--right,cur);
                }else{
                    ++cur;
                }
            }
            *l = left;
            *r = right;
        }
        void quickSort(int *nums, int l, int r){
            if(l >= r){
                return;
            }
            int left  = l;
            int right = r;
            partion(nums, &left, &right);
            quickSort(nums,l,left);
            quickSort(nums,right,r);
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
                cout<<nums[i]<<"----";
            }
            cout<<endl;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    int nums[] = {1,1,3,5,16,18,19};
    int size = *(&nums+1)-nums;
    cout<<te.min_ship_cost(nums,size,20)<<endl;
    return 0;
}
