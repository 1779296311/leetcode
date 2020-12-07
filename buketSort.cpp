/*********************************************
*     ------------------------
*     ------------------------
*     file name: buketSort.cpp
*     author   : @ JY
*     date     : 2020--10--13
**********************************************/
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <stdlib.h>
void _print(std::vector<int> &nums){
    for(auto &x : nums)std::cout<<x<<"  ";
    std::cout<<std::endl;
}
class Solution{
    public:
        void buk_sort(std::vector<int> &nums){
            int len  = nums.size();
            int min_ = *min_element(begin(nums), end(nums));
            int max_ = *max_element(begin(nums), end(nums));
            int dis  = (max_ - min_);
            int bukV = std::max(1, dis/(len-1));
            int bukS = dis / bukV + 1;
            std::vector<std::vector<int>> buk(bukS);
            std::function<void(int, int)> _insert_sort = [&](int i, int val){
                buk[i].insert(std::lower_bound(begin(buk[i]), end(buk[i]), val), val);
            };
            for(auto &x : nums){
                _insert_sort((x - min_) / bukV, x);
            }
            nums.clear();
            for(auto &v : buk)nums.insert(end(nums), begin(v), end(v));
        };
        void radix_sort(std::vector<int> &nums){
            int len = nums.size();
            int exp = 1;
            std::vector<int> temp(len), count(10);
            int max_ = *max_element(begin(nums), end(nums));
            while(max_ / exp){
                for(int i=0; i<10; ++i)count[i] = 0;
                for(auto &x : nums)++count[x / exp % 10];
                for(int i=1; i<10; ++i)count[i] += count[i-1];
                for(int i=len-1; i>=0; --i)temp[--count[nums[i]/exp%10]] = nums[i];
                for(int i=0; i<len; ++i)nums[i] = temp[i];
                exp *= 10;
            }
        }
        void shell_sort(std::vector<int> &nums){
            int len = nums.size();
            std::function<std::vector<int>(void)> _get_steps = [&](void){
                std::vector<int> steps;
                int l = len;
                while((l >>= 1) > 0)steps.push_back(l);
                return steps;
            };
            std::function<void(int)> _sort_by_step = [&](int step){
                for(int col=0; col<step; ++col){
                    for(int begin = col+step; begin < len; begin+=step){
                        int cur = begin;
                        while(cur>col && nums[cur] < nums[cur-step]){
                            std::swap(nums[cur], nums[cur-step]);
                            cur -= step;
                        }
                    }
                }
            };
            std::function<void(void)> _shell_sort = [&](void){
                auto steps = _get_steps();
                for(auto &step : steps)_sort_by_step(step);
            };
            _shell_sort();
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    //std::vector<int> nums = {5, 23, 534, 187, 49, 30, 0, 21, 1, -1, -2, -9, -123, 100,930,63,184,505,278,109,589,269,9154,2423,9458,113,4606,5933,3867,2307,3360,8093,1857,-5579,5735,-6827,8033,396,5564,1218,2323,1504};
    std::vector<int> nums = {5, 23, 534, 187, 49, 30, 0, 21, 1, 100,930,63,184,505,278,109,589,269,9154,2423,9458,113,4606,5933,3867,2307,3360,8093,1857,5735,8033,396,5564,1218,2323,1504};
    te.shell_sort(nums);
    //te.radix_sort(nums);
    //te.buk_sort(nums);
    _print(nums);
    return 0;
}
