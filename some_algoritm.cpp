/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_algoritm.cpp
*     author   : @ JY
*     date     : 2020--11--14
**********************************************/
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <climits>
#include <cmath>
#include <stdlib.h>

class Solution{
    public:
        int _quick_select(std::vector<int> &nums, int n){
            std::function<int(int, int, int)> _quickSelect
                = [&](int L, int R, int n){
                    if(L == R)return nums[L];
                    int x = nums[R-1];
                    int cur = L, l = L-1, r = R;
                    while(cur < r){
                        if(nums[cur] < x){
                            std::swap(nums[cur++], nums[++l]);
                        }else if(nums[cur] > x){
                            std::swap(nums[cur], nums[--r]);
                        }else{
                            ++cur;
                        }
                    }
                    if(n>l && n<cur)return nums[l+1];
                    if(l>=n)return _quickSelect(L, l + 1, n);
                    return _quickSelect(cur, R, n);
            };
            return _quickSelect(0, nums.size(), std::min(n, (int)nums.size()-1));
        }
        void qpartition1(std::vector<int> &nums, int x){
            int l = -1, r = nums.size(), cur = -1;
            while(++cur < r){
                if(nums[cur] <= x){
                    std::swap(nums[cur], nums[++l]);
                }
            }
            for(auto &x : nums)std::cout<<x<<"   ";
            std::cout<<std::endl;
            std::cout<<l<<std::endl;
        }
        void qpartition(std::vector<int> &nums, int x){
            int l = -1, r = nums.size(), cur = 0;
            while(cur < r){
                if(nums[cur] < x){
                    std::swap(nums[cur++], nums[++l]);
                }else if(nums[cur] > x){
                    std::swap(nums[cur], nums[--r]);
                }else{
                    ++cur;
                }
            }
            for(auto &x : nums)std::cout<<x<<"    ";
            std::cout<<std::endl;
            std::cout<<l<<"    "<<cur<<std::endl;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    //std::vector<int> nums {2, 4, 1, 3, 5};
    //int n = 3;
    std::vector<int> nums {3,2,1,5,5,5,6,4,23,12,3,-1,230123,25,-1,23,34,556,71,223,456,567,-123};
    //te.qpartition1(nums, 5);
    //std::cout<<te._quick_select(nums, 2)<<std::endl;
    for(int i=0; i<nums.size(); ++i){
        std::cout<<te._quick_select(nums, i)<<"  "<<nums[i]<<std::endl;
    }
    //te.qpartition(nums, 5);
    return 0;
}
