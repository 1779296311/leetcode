/*********************************************
*     ------------------------
*     ------------------------
*     file name: WEEK196.cpp
*     author   : @ JY
*     date     : 2020--07--05
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>

class Solution{
    public:
//给你一个数字数组 arr 。
//如果一个数列中，任意相邻两项的差总等于同一个常数，那么这个数列就称为 等差数列 。
//如果可以重新排列数组形成等差数列，请返回 true ；否则，返回 false 。
        bool canMakeArithmeticProgression(::std::vector<int>& arr){
            if(arr.size() == 1)return true;
            ::std::sort(arr.begin(), arr.end());
            int q = arr[1] - arr[0];
            for(int i=2; i<arr.size(); ++i){
                if(arr[i]-arr[i-1]==q)continue;
                return false;
            }
            return true;
        }

//有一块木板，长度为 n 个 单位 。一些蚂蚁在木板上移动，每只蚂蚁都以 每秒一个单位 的速度移动。其中，一部分蚂蚁向 左 移动，其他蚂蚁向 右 移动。
//当两只向 不同 方向移动的蚂蚁在某个点相遇时，它们会同时改变移动方向并继续移动。假设更改方向不会花费任何额外时间。
//而当蚂蚁在某一时刻 t 到达木板的一端时，它立即从木板上掉下来。
//给你一个整数 n 和两个整数数组 left 以及 right 。两个数组分别标识向左或者向右移动的蚂蚁在 t = 0 时的位置。请你返回最后一只蚂蚁从木板上掉下来的时
        int getLastMoment(int n, ::std::vector<int>& left, ::std::vector<int>& right){
            int res1 = -1;
            int res2 = n;
            for(auto &x :  left)res1 = ::std::max(res1, x);
            for(auto &x : right)res2 = ::std::min(res2, x);
            return ::std::max(res1, res2);
        }

//给你一个只包含 0 和 1 的 rows * columns 矩阵 mat ，请你返回有多少个 子矩形 的元素全部都 1
        int numSubmat(::std::vector<::std::vector<int>>& mat){
            int n = mat.size();
            int m = mat[0].size();
            ::std::vector<::std::vector<int>> dp(n, ::std::vector<int> (m,0));
            for(int i=0; i<n; ++i){
                int one = 0;
                for(int j=0; j<m; ++j){
                    if(mat[i][j])++one;
                    if(!mat[i][j])one = 0;
                    dp[i][j] = one;
                }
            }
            int res = 0;
            for(int i=0; i<n; ++i){
                for(int j=0; j<m; ++j){
                    int tmp = 151;
                    for(int k=i; k>=0; --k){
                        tmp = ::std::min(tmp, dp[k][j]);
                        res += tmp;
                    }
                }
            }
            return res;
        }

//给你一个字符串 num 和一个整数 k 。其中，num 表示一个很大的整数，字符串中的每个字符依次对应整数上的各个 数位 。
//你可以交换这个整数相邻数位的数字 最多 k 次。
//请你返回你能得到的最小整数，并以字符串形式返回。
        ::std::string minInteger(::std::string num, int k){
            int size = num.length();
            if(size*size<=k){
                ::std::sort(num.begin(), num.end());
                return num;
            }
            for(int i=0; i<size; ++i){
                int mv    = num[i];
                int index = i;
                for(int j=i; j<size&&j<=k+i; ++j){
                    if(mv>num[j]){
                        mv    = num[j];
                        index = j;
                    }
                }
                k = k - index + i;
                for(int t=index; t>i; --t)num[t] = num[t-1];
                num[i] = mv;
                if(!k)return num;
            }
            return num;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    ::std::string s = "943895723478563540";
    int k = 23;
    ::std::cout<<te.minInteger(s,k)<<::std::endl;
    return 0;
}
