/********************************************* 
*     ------------------------                 
*     ------------------------                 
*     file name: maxArea.cpp
*     author   : @JY    
*     data     : 2019--09--08
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;

class Solution{

    public:
        int maxArea(vector<int> &height){
            int Max;
            for(int i=0; i<height.size(); i++){
                for(int j=i + 1; j<height.size(); i++){
                    int tmp_1 = min(height[i], height[j]);
                    Max = max(Max, height[j] * (j -i));
                }
            }
            return Max;
        }
        int max_area(vector<int> &height){
            int Max = 0;;
            int j = height.size() - 1;
            int i = 0;
            while(i<j){
                int tmp  = min(height[i], height[j]);
                Max      = max(Max, tmp * (j-i));
                if(height[i] > height[j]){
                    j--;
                }else{
                    i++;
                }
            }
            return Max;
        }
};
