/********************************************* 
*     ------------------------
*     ------------------------
*     file name: findMedian.cpp
*     author   : @JY
*     data     : 2019--09--05
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <climits> 
using  namespace  std;

class Solution{
    public:
        double  findMedianSortedArray(vector<int> &nums1, vector<int> &nums2){
            for(int i=0; i<nums2.size(); i++){
                nums1.push_back(nums2[i]);
            }
            sort(nums1.begin(), nums1.end());
            if(nums1.size() % 2 == 0){
                return (nums1[nums1.size()/2] + nums1[nums1.size()/2+1])/2.0;
            }else{
                return nums1[nums1.size()/2+1]/1.0;
            }

        }
        double findMedianTwice(vector<int> &nums1, vector<int> &nums2){
            int n = nums1.size();
            int m = nums2.size();
            if(n > m){
                return findMedianTwice(nums2, nums1);
            }
            int lo = 0;
            int ro = 2 * n;
            int L_max1, R_min1, L_max2, R_min2;
            int cut_1 , cut_2;

            while(lo <= ro){
                cut_1   = (lo + ro)/2;
                cut_2   = (n + m) - cut_1;

                L_max1  = (cut_1 == 0)   ? INT_MIN   : nums1[(cut_1 - 1)/2];
                R_min1  = (cut_1 == 2*n) ? INT_MAX   : nums1[cut_1/2];
                L_max2  = (cut_2 == 0)   ? INT_MIN   : nums2[(cut_2 - 1)/2];
                R_min2  = (cut_2 == 2*m) ? INT_MAX   : nums2[cut_2/2];

                if(L_max1 > R_min2){
                    ro = cut_1 - 1;
                }else if(R_min1 < L_max2){
                    lo = cut_1 + 1;
                }else{
                    break;
                }
            }
            if(L_max2 > L_max1){
                L_max1   = L_max2;
            }
            if(R_min2 < R_min1){
                R_min1   = R_min2;
            }
            return (R_min1 + L_max1)/2.0;
        }

};


int main(int argc,const char *argv[]){
    vector<int> nums1 = {1,2,3,4};
    vector<int> nums2 = {1,2,3,4};
    class Solution tt;

    cout <<tt.findMedianTwice(nums1, nums2)<<endl;

    return 0;
} 
