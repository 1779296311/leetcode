/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_binary_search_pro.cpp
*     author   : @ JY
*     date     : 2020--08--12
**********************************************/
#include <iostream>
#include <functional>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <vector>
#include <stdlib.h>

class Solution{
    public:
//传送带上的包裹必须在 D 天内从一个港口运送到另一个港口。 传送带上的第 i 个包裹的重量为 weights[i]。每一天，我们都会按给出重量的顺序往传送带上装载包裹。我们装载的重量不会超过船的最大运载重量。 返回能在 D 天内将传送带上的所有包裹送达的船的最低运载能力。
        int shipWithinDays(std::vector<int>&weights, int D){
            int l = *max_element(weights.begin(), weights.end());
            int r = accumulate(weights.begin(), weights.end(), 0);
            int res = r;
            while(l<=r){
                int mid = l + ((r-l)>>1);
                int t   = 0;
                int d   = 0;
                for(auto &w : weights){
                    t += w;
                    if(t > mid)t=w,++d;
                }
                ++d>D?(l=mid+1):(res=std::min(res,mid), r=mid-1);
            }
            return res;
        }
//给你一个大小为 m x n 的矩阵 mat 和一个整数阈值 threshold。 请你返回元素总和小于或等于阈值的正方形区域的最大边长；如果没有这样的正方形区域，则返回 0 。
        int maxSideLength(std::vector<std::vector<int>>& mat, int threshold){
            int size_i = mat.size();
            int size_j = mat[0].size();
            std::vector<std::vector<int>> dp(size_i+1,std::vector<int>(size_j+1));
            for(int i=1; i<=size_i; ++i){
                for(int j=1; j<=size_j; ++j){
                    dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + mat[i-1][j-1];
                }
            }
            std::function<bool(int, int, int)> calc = [&](int i, int j, int l){
                return dp[i+l-1][j+l-1]-dp[i+l-1][j-1]-dp[i-1][j+l-1]+dp[i-1][j-1] <= threshold;
            };
            int l = 1;
            int r = std::min(size_i, size_j);
            int res = 0;
            while(l<=r){
                int mid = l + ((r-l)>>1);
                int f   = false;
                for(int i=1; i<=size_i-mid+1; ++i){
                    for(int j=1; j<=size_j-mid+1; ++j){
                        if(calc(i, j, mid)){
                            f = true;
                            break;
                        }
                    }
                }
                f?(res=mid, l=++mid):(r=--mid);
            }
            return res;
        }
//搜索旋转数组。给定一个排序后的数组，包含n个整数，但这个数组已被旋转过很多次了，次数不详。请编写代码找出数组中的某个元素，假设数组元素原先是按升序排列的。若有多个相同元素，返回索引值最小的一个。
        int search(std::vector<int>& arr, int target){
            int size = arr.size();
            if(!size)return -1;
            int l = 0;
            int r = size - 1;
            while(l < r){
                while(l<r && arr[l]==arr[r])--r;
                int mid = l + ((r-l)>>1);
                if(mid+1<=r){
                    int t   = arr[mid+1];
                    while(l<=mid && t==arr[mid])--mid;
                }
                if(arr[l] <= arr[mid]){
                    if(target >= arr[l] && target <= arr[mid]){
                        r = mid;
                    }else{
                        l = mid + 1;
                    }
                }else{
                    if(target>=arr[mid+1] && target<=arr[r]){
                        l = mid + 1;
                    }else{
                        r = mid;
                    }
                }
            }
            if(arr[l]==target)return l;
            return -1;
        }
//一个已排序好的表 A，其包含 1 和其他一些素数.  当列表中的每一个 p<q 时，我们可以构造一个分数 p/q 。 那么第 k 个最小的分数是多少呢?  以整数数组的形式返回你的答案, 这里 answer[0] = p 且 answer[1] = q.
        std::vector<int> kthSmallestPrimeFraction(std::vector<int>& A, int k){
            std::function<int(double)> calc = [&](double mid){
                int res = 0;
                for(int i=0; i<A.size(); ++i){
                    res += A.end() - std::upper_bound(A.begin()+i+1, A.end(), A[i]/mid);
                }
                return res;
            };
            double l = 0;
            double r = 1.0;
            while(l<r){
                double mid = l + ((r-l)/2);
                int c = calc(mid);
                if(c==k){
                    l = mid;
                    break;
                }else if(c<k){
                    l = mid;
                }else{
                    r = mid;
                }
            }
            int p = A[0];
            int q = A.back();
            for(int i=0; i<A.size(); ++i){
                auto pl = std::upper_bound(A.begin()+i+1, A.end(), A[i]/l);
                if(pl!=A.end()){
                    double t = 1.0 * A[i] / *pl;
                    if(t<l && (1.0*p/q)<t)p=A[i],q=*pl;
                }
            }
            return {p, q};
        }
//给定一个 n x n 矩阵，其中每行和每列元素均按升序排序，找到矩阵中第 k 小的元素。 请注意，它是排序后的第 k 小元素，而不是第 k 个不同的元素。
        int calc(std::vector<std::vector<int>>& m, int k, int mid){
            int size = m.size(); 
            int sum  = 0;
            int i = size - 1;
            int j = 0;
            while(j<size && i>=0){
                if(m[i][j] <= mid){
                    ++j;
                    sum += i + 1;
                }else{
                    --i;
                }
            }
            return sum>=k;
        }
        int kthSmallest(std::vector<std::vector<int>>& matrix, int k){
            int size = matrix.size();
            int l = matrix[0][0];
            int r = matrix[size-1][size-1];
            while(l<r){
                int mid = l + ((r-l)>>1);
                if(calc(matrix, k, mid)){
                    r = mid;
                }else{
                    l = mid + 1;
                }
            }
            return l;
        }
//给定一个数组 nums ，如果 i < j 且 nums[i] > 2*nums[j] 我们就将 (i, j) 称作一个重要翻转对。 你需要返回给定数组中的重要翻转对的数量。
        int merge(std::vector<int>& nums, int left, int mid, int right){
            int size = right - left + 1;
            std::vector<int> tmp(size);
            int l   = left;
            int r   = mid + 1;
            int i   = -1;
            int res = 0;
            while (l <= mid && r <= right) {
                if (nums[l] > 2LL * nums[r]) {
                    res += mid - l + 1;
                    ++r;
                }else{
                    ++l;
                }
            }
            l = left; r = mid + 1;
            while(l<=mid && r<=right)tmp[++i] = nums[l]>nums[r]?nums[r++]:nums[l++];
            while(l<=mid)tmp[++i] = nums[l++];
            while(r<=right)tmp[++i] = nums[r++];
            for(int i=0; i<size; ++i)nums[left+i] = tmp[i];
            return res;
        }
        int process(std::vector<int>& nums, int l, int r){
            if(l>=r)return 0;
            int m = l + ((r-l)>>1);
            return process(nums, l,   m) +
                   process(nums, m+1, r) +
                   merge(nums, l, m, r);
        }
        int reversePairs(std::vector<int>& nums){
            return process(nums, 0, nums.size()-1);
        }
//个马戏团正在设计叠罗汉的表演节目，一个人要站在另一人的肩膀上。出于实际和美观的考虑，在上面的人要比下面的人矮一点且轻一点。已知马戏团每个人的身高和体重，请编写代码计算叠罗汉最多能叠几个人。
        int bestSeqAIndex(std::vector<int>& height, std::vector<int>& weight){
            int size = height.size();
            std::vector<std::pair<int, int>> p;
            for(int i=0; i<size; ++i)p.push_back({height[i], weight[i]});
            std::sort(p.begin(), p.end(), [](auto &a, auto &b){
                    return a.first==b.first?a.second>b.second:a.first<b.first;
            });
            std::vector<int> dp;
            dp.push_back(p[0].second);
            for(int i=1; i<size; ++i){
                if(p[i].second > dp[dp.size()-1]){
                    dp.push_back(p[i].second);
                }else{
                    *lower_bound(dp.begin(), dp.end(), p[i].second) = p[i].second;
                }
            }
            for(auto &x : dp)std::cout<<x<<"    ";
            std::cout<<std::endl;
            return dp.size();
        }
        int bestSeqAtIndex_fuck(std::vector<int>& height, std::vector<int>& weight){
            int size = height.size();
            std::vector<std::pair<int, int>>p; 
            for(int i=0; i<size; ++i)p.push_back({height[i], weight[i]});
            std::sort(p.begin(), p.end());
            std::vector<int> dp(size, 1);
            for(int i=1; i<size; ++i){
                for(int j=i-1; j>=0; --j){
                    if(p[i].second > p[j].second && p[i].first > p[j].first){
                        dp[i] = std::max(dp[i], dp[j] + 1);
                    }
                }
            }
            return *max_element(dp.begin(), dp.end());
        }
};

class TopVotedCandidate {
//在选举中，第 i 张票是在时间为 times[i] 时投给 persons[i] 的。 现在，我们想要实现下面的查询函数： TopVotedCandidate.q(int t) 将返回在 t 时刻主导选举的候选人的编号。 在 t 时刻投出的选票也将被计入我们的查询之中。在平局的情况下，最近获得投票的候选人将会获胜
public:
    std::vector<int> res;
    std::vector<int> times;
    TopVotedCandidate(std::vector<int>& p, std::vector<int>& t) : times(t){
        int max_v = 0;
        int max_n = 0;
        std::vector<int> N(p.size(), 0);
        res = std::vector<int>(p.size(), 0);
        for(int i=0; i<p.size(); ++i){
            if(++N[p[i]] >= max_n){
                max_n  = N[p[i]];
                max_v  = p[i];
                res[i] = p[i];
            }else{
                res[i] = max_v;
            }
        }
    }
    int q(int t) {
        int i    = std::upper_bound(times.begin(), times.end(), t) - times.begin() - 1;
        return res[i];
    }
};


