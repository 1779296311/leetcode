/*********************************************
*     ------------------------
*     ------------------------
*     file name: 4.cpp
*     author   : @ JY
*     date     : 2020--09--03
**********************************************/
#include <iostream>
#include <climits>
#include <functional>
#include <vector>
#include <stdlib.h>

class Soution{
    public:
        double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2){
            int m = nums1.size();
            int n = nums2.size();
            if( m > n )return findMedianSortedArrays(nums2, nums1);
            int l = 0;
            int r = m * 2;
            int lmax1,lmax2,rmin1,rmin2;
            while(l <= r){
                int c_1 = l + ((r-l)>>1);
                int c_2 = (m+n) - c_1;

                lmax1 = c_1==0   ? INT_MIN : nums1[(c_1-1)/2];
                rmin1 = c_1==2*m ? INT_MAX : nums1[(c_1)/2];
                lmax2 = c_2==0   ? INT_MIN : nums2[(c_2-1)/2];
                rmin2 = c_2==2*n ? INT_MAX : nums2[(c_2)/2];

                if(lmax2 > rmin1){
                    l = c_1 + 1;
                }else if(lmax1 > rmin2){
                    r = c_1 - 1;
                }else{
                    break;
                }
            }
            return (std::max(lmax1, lmax2)+std::min(rmin1, rmin2))/2.0;
        }
        double findMedianSortedArrays_(std::vector<int>& nums1, std::vector<int>& nums2){
            int m    = nums1.size();
            int n    = nums2.size();
            int size = n + m;
            std::function<int(int k)> calc = [&](int k){
                int i = 0;
                int j = 0;
                while(1){
                    if(i==m)return nums2[j+k-1];
                    if(j==n)return nums1[i+k-1];
                    if(k==1)return std::min(nums1[i], nums2[j]);
                    int i1 = std::min(i+k/2-1, m-1);
                    int j1 = std::min(j+k/2-1, n-1);
                    if(nums1[i1] > nums2[j1]){
                        k = k - (j1-j+1);
                        j = j1 + 1;
                    }else{
                        k = k - (i1-i+1);
                        i = i1 + 1;
                    }
                }
                return -1;
            };
            if(size&1)return calc((size+1)/2);
            return (calc(size/2) + calc(size/2+1))/2.0;
        }
};
