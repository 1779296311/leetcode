/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_game_pro.cpp
*     author   : @ JY
*     date     : 2020--04--27
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        int num_gameDP(vector<int>& nums){
            int size = nums.size();
            if(!size){
                return 0;
            }
            vector<vector<int>> F(size,vector<int>(size,0));
            vector<vector<int>> S(size,vector<int>(size,0));
            for(int j=0; j<size; ++j){
                F[j][j] = nums[j];
                for(int i=j-1; i>=0; --i){
                    F[i][j] = max(nums[i]+S[i+1][j],nums[j]+S[i][j-1]);
                    S[i][j] = min(F[i+1][j],F[i][j-1]);
                }
            }
            return max(F[0][size-1],S[0][size-1]);
        }
        int num_game(vector<int>& nums){
            return max(F(nums,0,nums.size()-1),S(nums,0,nums.size()-1));
        }
        int F(vector<int>& nums,int l, int r){
            if(l==r){
                return nums[l];
            }
            return max(nums[l]+S(nums,l+1,r),nums[r]+S(nums,l,r-1));
        }
        int S(vector<int>& nums,int l, int r){
            if(l==r){
                return 0;
            }
            return min(F(nums,l+1,r),F(nums,l,r-1));
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    vector<int> nums  = {1,2,4,5,100};
    vector<int> nums1 = {1,222,4,5,100};
    vector<int> nums2 = {1,2,4,59,100};
    vector<int> nums3 = {1,2,49,0,5,0,100};
    vector<int> nums4 = {1,12,332,4534,9,2,4,5,100};
    cout<<te.num_game(nums)<<endl;
    cout<<te.num_gameDP(nums)<<endl;
    cout<<"--------"<<endl;
    cout<<te.num_game(nums1)<<endl;
    cout<<te.num_gameDP(nums1)<<endl;
    cout<<"--------"<<endl;
    cout<<te.num_game(nums2)<<endl;
    cout<<te.num_gameDP(nums2)<<endl;
    cout<<"--------"<<endl;
    cout<<te.num_game(nums3)<<endl;
    cout<<te.num_gameDP(nums3)<<endl;
    cout<<"--------"<<endl;
    cout<<te.num_game(nums4)<<endl;
    cout<<te.num_gameDP(nums4)<<endl;
    cout<<"--------"<<endl;
    return 0;
}
