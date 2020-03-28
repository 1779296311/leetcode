/*********************************************
*     ------------------------
*     ------------------------
*     file name: 48.cpp
*     author   : @ JY
*     date     : 2019--10--18
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        void rotate(vector<vector<int>>& matrix){
            if(!matrix.size()){
                return;
            }
            int size  = matrix.size();
            for(int i=0; i<size; i++){
                for(int j=0; j<i; j++){
                    matrix[i][j] = matrix[i][j] ^ matrix[j][i];
                    matrix[j][i] = matrix[i][j] ^ matrix[j][i];
                    matrix[i][j] = matrix[i][j] ^ matrix[j][i];
                }
            }
            for( auto x: matrix ){
                for(auto p:x){
                    cout<<p<<"--";
                }
                cout<<endl;
            }
            for(int i=0; i<size; i++){
                int left  = 0;
                int right = size-1;
                while(left<right){
                    matrix[i][left]  = matrix[i][left] ^ matrix[i][right];
                    matrix[i][right] = matrix[i][left] ^ matrix[i][right];
                    matrix[i][left]  = matrix[i][left] ^ matrix[i][right];
                    left++;
                    right--;
                }
            }
            for( auto x: matrix ){
                for(auto p:x){
                    cout<<p<<"--";
                }
                cout<<endl;
            }
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    vector<int> tmp =  {5,1,9,11};
    vector<int> tmp1 = {2,4,8,10};
    vector<int> tmp2 = {13,3,6,7};
    vector<int> tmp3 = {15,14,12,16};
    //vector<int> tmp =  {1,2,3,0};
    //vector<int> tmp1 = {4,5,6,0};
    //vector<int> tmp2 = {7,8,9,0};
    //vector<int> tmp3 = {17,18,19,0};
    vector<vector<int>> matrix;
    matrix.push_back(tmp);
    matrix.push_back(tmp1);
    matrix.push_back(tmp2);
    matrix.push_back(tmp3);
    te.rotate(matrix);
    return 0;
}
