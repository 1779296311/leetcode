/*********************************************
*     ------------------------
*     ------------------------
*     file name: buketSork.cpp
*     author   : @ JY
*     date     : 2020--03--09
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <cmath>
using  namespace  std;
class Solution{
    public:
        int getDigits(int num, int dig){
            return ((int)(num/pow(10,dig-1))%10);
        }
        int getNumMax(int *nums, int size){
            int m = nums[0];
            for(int i=0; i<size; ++i){
                if(nums[i]>m){
                    m = nums[i];
                }
            }
            return m;
        }
        int getNumBit(int num){
            int res = 0;
            while(num){
                num = num/10;
                ++res;
            }
            return res;
        }
        void buketSort(int *nums, int size){
            int maxN      = getNumMax(nums,size);
            int bit       = getNumBit(maxN);
            int tmp[size] = {0};
            for(int b=1; b<=bit; ++b){
                int digN[10]   = {0};
                for(int i=0; i<size; ++i){
                    ++digN[getDigits(nums[i],b)];
                }
                for(int i=1; i<10; ++i){
                    digN[i] = digN[i] + digN[i-1];
                }
                for(int i=size-1; i>=0; --i){
                    tmp[--digN[getDigits(nums[i],b)]] = nums[i];
                }
                for(int i=0; i<size; ++i){
                    nums[i] = tmp[i];
                }
            }
        }
        void debug(int *nums, int size){
            for(int i=0; i<size; ++i){
                cout<<nums[i]<<endl;
            }
        }
};
int main(int argc,const char *argv[]){
    int nums[] = {1,2345,12,678,2345,56,7254274,780,235,12423};
    Solution te;
    te.buketSort(nums,*(&nums+1)-nums);
    te.debug(nums,*(&nums+1)-nums);
    return 0;
}
