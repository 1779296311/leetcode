/*********************************************
*     ------------------------
*     ------------------------
*     file name: 628.cpp
*     author   : @ JY
*     date     : 2019--09--24
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        int maximumProduct(vector<int>& nums){ 
            int size = nums.size();
            for(int i=0; i<2; i++){
                for(int j=i+1; j<3; j++){
                    if(nums[i] > nums[j]){
                        nums[i] = nums[j] ^ nums[i];
                        nums[j] = nums[j] ^ nums[i];
                        nums[i] = nums[j] ^ nums[i];
                    }
                }
            }
            int max1 = nums[2];
            int max2 = nums[1];
            int max3 = nums[0];
            int min1 = nums[0];
            int min2 = nums[1];
            int min3 = nums[2];
            for(int i=1; i<size; i++){
                if(nums[i] > max1){
                    max3 = max2;
                    max2 = max1;
                    max1 = nums[i];
                }else if(nums[i] <=max1 && nums[i] > max2){
                    max3 = max2;
                    max2 = nums[i];
                }else if(nums[i] <= max2 && nums[i] > max3){
                    max3 = nums[i];
                }
                if(nums[i] < min1){
                    min3 = min2;
                    min2 = min1;
                    min1 = nums[i];
                }else if(nums[i] >=min1 && nums[i] < min2){
                    min3 = min2;
                    min2 = nums[i];
                }else if(nums[i] >= min2 && nums[i] < min3){
                    min3 = nums[i];
                }
            }
            return max(max((max3*max1*max2),(min1*min2*max3)),(min1*min2*max1));
        }
};
