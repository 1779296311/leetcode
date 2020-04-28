/*********************************************
*     ------------------------
*     ------------------------
*     file name: forCout.cpp
*     author   : @ JY
*     date     : 2020--04--22
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        void forRorate(vector<vector<int>>& nums){
            int size = nums.size();
            if(size != nums[0].size()){
                cout<<"GNMD!!"<<endl;
                return;
            }
            int beginX = 0;
            int beginY = 0;
            int endX   = size-1;
            int endY   = size-1;
            while(beginX<endX && beginY<endY){
                rorateReal(nums,beginX++,beginY++,endX--,endY--);
            }
        }
        void rorateReal(vector<vector<int>>& nums,int x1, int y1, int x2, int y2){
            int tmp ;
            for(int i=0; i<x2-x1; ++i){
                tmp            = nums[x1][y1+i];
                nums[x1][y1+i] = nums[x2-i][y1];
                nums[x2-i][y1] = nums[x2][y2-i];
                nums[x2][y2-i] = nums[x1+i][y2];
                nums[x1+i][y2] = tmp;
            }
        }
        void forCout(vector<vector<int>>& nums){
            int size1 = nums.size();
            int size2 = nums[0].size();
            int beginX = 0;
            int beginY = 0;
            int endX   = size1-1;
            int endY   = size2-1;
            while(beginX<=endX && beginY<=endY){
                coutReal(nums,beginX++,beginY++,endX--,endY--);
            }
        }
        void coutReal(vector<vector<int>>& nums,int x1, int y1, int x2, int y2){
            for(int i=y1; i<=y2; ++i){
                cout<<nums[x1][i]<<" ";
            }
            for(int i=x1+1; i<=x2; ++i){
                cout<<nums[i][y2]<<" ";
            }
            for(int i=y2-1; i>=y1; --i){
                cout<<nums[x2][i]<<" ";
            }
            for(int i=x2-1; i>x1; --i){
                cout<<nums[i][y1]<<" ";
            }
            cout<<endl<<"-------------------"<<endl;
        }
        void debug(vector<vector<int>>& nums){
            int size1 = nums.size();
            int size2 = nums[0].size();
            for(int i=0; i<size1; ++i){
                for(int j=0; j<size2; ++j){
                    cout<<nums[i][j]<<" ";
                }
                cout<<endl;
            }
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    //vector<vector<int>> nums = {{1,1,1},{2,2,2},{3,3,3},{4,4,4}};
    vector<vector<int>> nums = {{1,1,1,1},{2,2,2,2},{3,3,3,3},{4,4,4,4}};
    te.debug(nums);
    te.forRorate(nums);
    te.debug(nums);
    return 0;
}
