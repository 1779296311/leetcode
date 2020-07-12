/*********************************************
*     ------------------------
*     ------------------------
*     file name: WEEK195.cpp
*     author   : @ JY
*     date     : 2020--06--28
**********************************************/
#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <list>
#include <queue>
#include <unordered_set>
#include <stdlib.h>
class Solution{
    public:
//给你一个字符串 path，其中 path[i] 的值可以是 'N'、'S'、'E' 或者 'W'，分别表示向北、向南、向东、向西移动一个单位。
//机器人从二维平面上的原点 (0, 0) 处开始出发，按 path 所指示的路径行走。
//如果路径在任何位置上出现相交的情况，也就是走到之前已经走过的位置，请返回 True ；否则，返回 False 。
        bool isPathCrossing(::std::string path){
            ::std::unordered_map<int,::std::unordered_set<int>> hp;
            int size = path.length();
            int i = 0;
            int j = 0;
            hp[0].insert(0);
            for(auto &c : path){
                switch(c){
                    case 'N':
                        --i;
                        break;
                    case 'S':
                        ++i;
                        break;
                    case 'E':
                        ++j;
                        break;
                    case 'W':
                        --j;
                        break;
                }
                if(hp.count(i) && hp[i].count(j))return true;
                hp[i].insert(j);
            }
            return false;
        }
//你一个整数数组 arr 和一个整数 k ，其中数组长度是偶数，值为 n 。
//现在需要把数组恰好分成 n / 2 对，以使每对数字的和都能够被 k 整除。
//如果存在这样的分法，请返回 True ；否则，返回 False 
        bool canArrange(::std::vector<int>& arr, int k){
            ::std::vector<int> tmp(k,0);
            for(auto &n : arr)++tmp[((n%k)+k)%k];
            for(int i=1; i<k; ++i)if(tmp[i] != tmp[k-i])return false;
            return !(tmp[0]&1);//{6,6,6,3} 6
        }

//给你一个整数数组 nums 和一个整数 target 。
//请你统计并返回 nums 中能满足其最小元素与最大元素的 和 小于或等于 target 的 非空 子序列的数目。
//由于答案可能很大，请将结果对 10^9 + 7 取余后返回。
        int mod = 1e9+7;
        int numSubseq(::std::vector<int>& nums, int t){
            long long res = 0;
            ::std::sort(nums.begin(), nums.end());
            for(int i=0; i<nums.size(); ++i){
                if(nums[i]>t/2)break;
                //auto it = upper_bound(nums.begin()+i+1, nums.end(), t-nums[i]);
                res = (res+my_pow2((upper_bound(nums.begin()+i+1, nums.end(), t-nums[i])-(nums.begin()+i)-1)))%mod;
            }
            return res;
        }
        int my_pow2(int n){
            long long p = 1;
            long long s = 2;
            while(n){
                if(n&1)p = (p * s)%mod;
                s = (s * s)%mod;
                n >>=1;
            }
            return p;
        }
        int fuck_numSubseq(::std::vector<int>& nums, int target){
            int l = 0;
            int r = 0;
            long long res = 0;
            int size = nums.size();
            ::std::list<int> mi;
            ::std::list<int> ma;
            while(l<size){
                while(r<size){
                    while(mi.size() && nums[mi.back()]>=nums[r])mi.pop_back();
                    mi.push_back(r);
                    while(ma.size() && nums[ma.back()]<=nums[r])ma.pop_back();
                    ma.push_back(r);
                    if(nums[mi.front()] + nums[ma.front()] > target)break;
                    ++r;
                }
                if(mi.front()==l)mi.pop_front();
                if(ma.front()==l)ma.pop_front();
                res += r - l;
                ++l;
            }
            return res%(int)(1e9+7);
        }

//给你一个数组 points 和一个整数 k 。数组中每个元素都表示二维平面上的点的坐标，并按照横坐标 x 的值从小到大排序。也就是说 points[i] = [xi, yi] ，并且在 1 <= i < j <= points.length 的前提下， xi < xj 总成立。
//请你找出 yi + yj + |xi - xj| 的 最大值，其中 |xi - xj| <= k 且 1 <= i < j <= points.length。
//题目测试数据保证至少存在一对能够满足 |xi - xj| <= k 的点。
        int findMaxValueOfEquation(::std::vector<::std::vector<int>>& points, int k){
            ::std::list<::std::pair<int,int>> q;
            int i    = 0;
            int size = points.size();
            int res  = INT_MIN;
            while(i<size){
                while(q.size() && q.front().first<points[i][0]-k)q.pop_front();
                if(q.size()) res = ::std::max(res,q.front().second+points[i][0]+points[i][1]);
                while(q.size() && q.back().second<=points[i][1]-points[i][0])q.pop_back();
                q.push_back({points[i][0],points[i][1]-points[i][0]});
                ++i;
            }
            return res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;;
    ::std::vector<int> nums = {2,3,3,4,6,7};
    int k = 12;
    te.numSubseq(nums, k);
    //::std::cout<<te.my_pow(0)<<::std::endl;
    //::std::vector<int> arr = {-4,-7,5,2,9,1,10,4,-8,-3};
    ::std::vector<int> arr = {6,6,6,3};
    //int k = 6;
    //te.canArrange(arr, k);
    return 0;
}
