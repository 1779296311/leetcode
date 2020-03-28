/*********************************************
*     ------------------------
*     ------------------------
*     file name: 16.cpp
*     author   : @ JY
*     date     : 2019--10--12
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using  namespace  std;
class Solution{
    public:
        int threeSumClosest(vector<int>& nums,int target){
            if(!nums.size() || nums.size() < 3 ){
                return 0;
            }
            sort(nums.begin(),nums.end());
            int size = nums.size();
            int sum  = nums[0]+nums[1]+nums[size-1];
            for(int i=0; i<size-2; i++){
                int right = i;
                int mid   = i+1;
                int left  = size-1;
                while(mid < left){
                    int tmp  = nums[right]+nums[mid]+nums[left];
                    if(tmp == target){
                        cout <<right<<"--"<<mid<<"--"<<left<<"--"<<endl;
                        return tmp;
                    }else if(tmp>target){
                        left--;
                    }else if(tmp<target){
                        mid++;
                    }
                    if(abs(tmp-target) < abs(sum-target)){
                        sum = tmp;
                    }
                }
            }
            return sum;
        }
};
int main(int argc,const char *argv[]){
    vector<int> nums = {1,2,-1,-4};
    Solution te;
    cout<<te.threeSumClosest(nums,1)<<endl;
    return 0;
}
