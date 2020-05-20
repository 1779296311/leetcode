/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ40.cpp
*     author   : @ JY
*     date     : 2020--05--11
**********************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    vector<int>getLeastNumbers1(vector<int>& arr, int k){
        if(!k){
            return vector<int>{};
        }
        if(k>=arr.size()){
            return arr;
        }
        vector<int>heap(k,0);
        dealTopK(heap,arr,k);
        sort(heap.begin(), heap.end());
        return heap;
    }
    void dealTopK(vector<int>& heap, vector<int>& arr, int k){
        for(int i=0; i<k; ++i){
            heapInsert(heap,arr[i],i);
        }
        for(int i=k; i<arr.size(); ++i){
            if(arr[i] < heap[0]){
                debug(heap);
                cout<<arr[i]<<endl;
                heap[0] = arr[i];
                heapfy(heap,k,0);
            }
        }
    }
    void heapInsert(vector<int>& heap, int num, int size){
        if(!size){
            heap[0] = num;
        }else{
            int parent = (size-1)/2;
            int index  = size;
            while(index && heap[parent]<num){
                heap[index] = heap[parent];
                index       = parent;
                parent      = (index-1)/2;
            }
            heap[index] = num;
        }
    }
    void heapfy(vector<int>&heap, int size, int index){
        int left = (index<<1)+1;
        int cur  = heap[index];
        while(left<size){
            left = (left+1<size && heap[left+1] > heap[left])?left+1:left;
            left = cur > heap[left]?index:left;
            if(left == index){
                break;;
            }
            heap[index] = heap[left];
            index       = left;
            left        = (index<<1)+1;
        }
        heap[index] = cur;
    }
     void checkHeap(vector<int>& nums){
         int right,left;
         for(int i=0; (i*2+2)<nums.size(); ++i){
             if(nums[i]<nums[i*2+1] || nums[i]<nums[i*2+2]){
                 cout<<"index-----"<<i;
                 cout<<"---"<<nums[i]<<"----"<<nums[i*2+1]<<"-------"<<nums[i*2+2]<<endl;
             }
         }
    }
    void debug(vector<int>& nums){
        for(int i=0; i<nums.size(); ++i){
            cout<<nums[i]<<" ";
        }
        cout<<endl;
    }
    /////////----------------------------time------------------------limit
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> res;
        for(int i=0; i<k; ++i){
            res.push_back(this->bfprt(arr,0,arr.size()-1,i));
        }
        return res;
    }
    int bfprt(vector<int>& nums, int begin, int end, int k){
        if(begin == end){
            return nums[begin];
        }
        int midNum = getNumsMid(nums,begin,end);
        int l = begin;
        int r = end;
        partition(nums, &l, &r, midNum);
        if(k<=r && k>=l){
            return nums[k];
        }else if(k<l){
            return bfprt(nums,begin,l-1,k);
        }else{
            return bfprt(nums,r+1,end,k);
        }
    }
    int getNumsMid(vector<int>& nums, int begin, int end){
        int size = end - begin + 1;
        int midN = (size/5) + ((size%5)?1:0);
        vector<int> midNums(midN,0);
        int s;
        int e;
        for(int i=0; i<midN; ++i){
            s = begin + i*5;
            e = s     + 4;
            midNums[i] = getMidFrom5Nums(nums,s,min(e,end));
        }
        return bfprt(midNums,0,midN-1,(midN>>1));
    }
    int getMidFrom5Nums(vector<int>& nums, int start, int end){
        sort(nums.begin()+start, nums.begin()+end+1);
        return nums[(start+end)>>1];
    }
    void partition(vector<int>& nums, int *l, int *r, int midNum){
        int left  = *l-1;
        int right = *r+1;
        int cur   = *l;
        while(cur<right){
            if(nums[cur]<midNum){
                swap(nums,cur++,++left);
            }else if(nums[cur]>midNum){
                swap(nums,cur,--right);
            }else{
                ++cur;
            }
        }
        *l = left  + 1;
        *r = right - 1;
    }
    void swap(vector<int>& nums, int a, int b){
        if(nums[a] == nums[b]){
            return ;
        }
        nums[a] = nums[a] ^ nums[b];
        nums[b] = nums[a] ^ nums[b];
        nums[a] = nums[a] ^ nums[b];
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    vector<int> nums = {0,1,1,1,4,5,3,7,7,8,10,2,7,8,0,5,2,16,12,1,19,15,5,18,2,2,22,15,8,22,17,6,22,6,22,26,32,8,10,11,2,26,9,12,9,7,28,33,20,7,2,17,44,3,52,27,2,23,19,56,56,58,36,31,1,19,19,6,65,49,27,63,29,1,69,47,56,61,40,43,10,71,60,66,42,44,10,12,83,69,73,2,65,93,92,47,35,39,13,75};
    te.getLeastNumbers1(nums,75);
    sort(nums.begin(), nums.end());
    te.debug(nums);
    //cout<<te.bfprt(nums,0,nums.size()-1,2)<<endl;
    return 0;
}
