/*********************************************
*     ------------------------
*     ------------------------
*     file name: rectangAreaStack.cpp
*     author   : @ JY
*     date     : 2020--03--27
**********************************************/
#include <iostream>
#include <vector>
#include <stack>
#include <stdlib.h>

#define peek() ({ \
            auto t = st.top(); \
            st.pop(); \
            t;})

using  namespace  std;
//设置一个单调递减的栈
class Solution{
    public:
        int maxArea_by_Stack(int *nums, int size){
            int __res = 0;
            stack<int> st;
            int index = 0;
            while(index<size){
                while(!st.empty() && nums[st.top()] >=nums[index] ){
                    int i    = peek();
                    int left = (st.empty())?-1:st.top();
                    __res    = max(__res,(index-left-1)*nums[i]);
                }
                st.push(index++);
            }
            while(!st.empty()){
                int i    = peek();
                int left = (st.empty())?-1:st.top();
                __res    = max(__res,(size-left-1)*nums[i]);
            }
            return __res;
        }
        int maxRect_by_stacK(vector<vector<int>>& nums){
            int sizeh      = nums.size();
            int sizel      = nums[0].size();
            int tmp[sizel] = {0};
            int __res      = 0;
            for(int i=0; i<sizeh; ++i){
                for(int j=0; j<sizel; ++j){
                    tmp[j] += nums[i][j]?nums[i][j]:-tmp[j];
                }
                __res = max(__res,maxArea_by_Stack(tmp,sizel));
            }
            return __res;
        }
        int howMany_can_seeEacher(int *nums, int size){
            int maxIndex = 0;
            int __res    = 0;
            for(int i=0; i<size; ++i){
                maxIndex = nums[maxIndex]>nums[i]?maxIndex:i;
            }
            stack<pair<int,int>> st;
            st.push(pair<int,int>(nums[maxIndex],1));
            int mnext    = getNumsNext(size,maxIndex);
            while(mnext != maxIndex){
                while(!st.empty() && st.top().first<nums[mnext]){
                    auto  tmp = peek();
                    __res     = __res + get_Cn2(tmp.second) + (tmp.second)*2;
                }
                if(st.top().first == nums[mnext]){
                    ++st.top().second;
                }else{
                    st.push(pair<int,int>(nums[mnext],1));
                }
                mnext = getNumsNext(size,mnext);
            }
            while(!st.empty()){
                auto tmp = peek();
                __res = __res + get_Cn2(tmp.second);
                if(!st.empty()){
                    __res = __res + tmp.second;
                    if(st.size()>1){
                        __res = __res + tmp.second;
                    }
                }
            }
            return __res;
        }
        int getNumsNext(int size, int index){
            return ++index==size?0:index;
        }
        int get_Cn2(int n){
            return n==1?0:int(long(n)*long(n-1)/2);
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    //int numss[] = {1,2,2,2,4};
    //int numss[] = {1,3,5,7,2};
    int numss[] = {2,2,2};
    cout<<te.howMany_can_seeEacher(numss,*(&numss+1)-numss)<<endl;
    //vector<vector<int>> nums = {{1,1,0,1,1},{0,1,1,1,1},{1,0,1,1,0},{1,1,1,1,0}};
    //cout<<te.maxRect_by_stacK(nums)<<endl;
    //cout<<te.maxArea_by_Stack(numss,*(&numss+1)-numss)<<endl;
    //int llong = 5;
    //int nums[][llong] = {{1,1,0,1,1},{0,1,1,0,1},{1,0,1,1,0},{1,1,1,0,0}};
    //int hhigh = *(&nums+1)-nums;

    return 0;
}
