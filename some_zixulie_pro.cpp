/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_zixulie_pro.cpp
*     author   : @ JY
*     date     : 2020--05--27
**********************************************/
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <climits>
#include <stdlib.h>
class Solution{
    public:

//给定一个未经排序的整数数组，找到最长且连续的的递增序列，并返回该序列的长度。
        int findLengthOfLCIS(::std::vector<int>& nums) {
            int size = nums.size();
            if(size<=1)return size;
            ::std::vector<int> dp(size,1);
            int res = 0;
            for(int i=1; i<size; ++i){
                if(nums[i-1] < nums[i])dp[i] = dp[i-1] + 1;
                res = ::std::max(res, dp[i]);
            }
            return res;
        }
        ///
        int longestIncreasingSubsequence(::std::vector<int>& nums){
            int size = nums.size();
            int res  = 0;
            ::std::vector<int> dp(size,0);
            //dp[0] = 1;
            for(int i=1; i<size; ++i){
                for(int j=0; j<i; ++j){
                    if(nums[i]>nums[j]){
                        dp[i] = ::std::max(dp[i],dp[j]+1);
                    }
                }
                res = ::std::max(res,dp[i]);
            }
            return ++res;
        }
        int longestCommenSubsequence(::std::vector<int>& nums1, ::std::vector<int>& nums2){
            int old;
            int tmp;
            int res = INT_MIN;
            ::std::vector<int>dp(nums2.size()+1,0);
            for(int i=1; i<=nums1.size(); ++i){
                old = 0;
                for(int j=1; j<=nums2.size(); ++j){
                    tmp = dp[j];
                    dp[j] = ::std::max(dp[j],dp[j-1]);
                    if(nums1[i-1] == nums2[j-1]){
                        dp[j] = ::std::max(dp[j], old+1);
                    }
                    old = tmp;
                    res = ::std::max(res,dp[j]);
                }
            }
            return res;
        }
        //dp[i][j] j结尾的公共上升子序列的集合
        int longestCommenIncreasingSubsequence(::std::vector<int>& nums1, ::std::vector<int>& nums2){
            int size1 = nums1.size();
            int size2 = nums2.size();
            ::std::vector<::std::vector<int>> dp(size1+1,::std::vector<int>(size2+1,0));
            for(int i=1; i<=size1; ++i){
                for(int j=1; j<=size2; ++j){
                    dp[i][j] = dp[i-1][j];
                    if(nums1[i-1] == nums2[j-1]){
                        int M = 1;
                        for(int k=1; k<j; ++k){
                            if(nums1[i-1] > nums2[k-1]) M = ::std::max(M,dp[i-1][k]+1);
                        }
                        dp[i][j] = ::std::max(dp[i][j], M);
                    }
                }
            }
            int res = INT_MIN;
            for(int i=1; i<=size2; ++i)res = ::std::max(res,dp[size1][i]);
            return res;
        }
        int LCIS(::std::vector<int>& nums1, ::std::vector<int>& nums2){
            int size1 = nums1.size();
            int size2 = nums2.size();
            int maxv  = 1;
            ::std::vector<::std::vector<int>> dp(size1+1,::std::vector<int>(size2+1, 0));
            for(int i=1; i<=size1; ++i){
                maxv = 1;
                for(int j=1; j<=size2; ++j){
                    dp[i][j] = dp[i-1][j];
                    if(nums1[i-1] == nums2[j-1])dp[i][j] = ::std::max(dp[i][j], maxv);
                    if(nums1[i-1] > nums2[j-1])maxv = ::std::max(maxv,dp[i-1][j]+1);
                }
            }
            maxv = 0;
            for(int i=1; i<=size2; ++i)maxv = ::std::max(maxv, dp[size1][i]);
            return maxv;
        }
        int LCIS2(::std::vector<int>& nums1, ::std::vector<int>& nums2){
            int size1 = nums1.size();
            int size2 = nums2.size();
            int maxv  = 1;
            int res   = 0;
            ::std::vector<int> dp(size2+1,0);
            for(int i=1; i<=size1; ++i){
                maxv = 1;
                for(int j=1; j<=size2; ++j){
                    if(nums1[i-1] == nums2[j-1])dp[j] = ::std::max(dp[j], maxv);
                    if(nums1[i-1] > nums2[j-1])maxv = ::std::max(maxv, dp[j]+1);
                    res = ::std::max(res,dp[j]);
                }
            }
            return res;
            maxv = 0;
            for(int i=1; i<=size2; ++i)maxv = ::std::max(maxv, dp[i]);
            return maxv;
        }
        int tmp(::std::vector<int>& n1, ::std::vector<int>& n2){
            int size1 = n1.size();
            int size2 = n2.size();
            ::std::vector<int>dp(size2+1,0);
            int M = INT_MIN;
            for(int i=1; i<=size1; ++i){
                M = 1;
                for(int j=1; j<=size2; ++j){
                    if(n1[i-1] == n2[j-1])dp[j] = ::std::max(dp[j], M);
                    if(n1[i-1] > n2[j-1])M = ::std::max(M, dp[j]+1);
                }
            }
            int res = 0;
            for(int i=1; i<=size2; ++i)res = ::std::max(res, dp[i]);
            return res;
        }
        /******************************************最长连续不重复子序列(chuan)*********************************************/
        int longestUnequalSubsquence(::std::string& a){
            int res = 1;
            ::std::vector<int> N(256,0);
            for(int i=0,j=0; i<a.length(); ++i){
                ++N[a[i]];
                while(j<=i && N[a[i]]>1){N[a[j++]]--;}
                res = ::std::max(res,i-j+1);
            }
            return res;
        }
        /******************************************最长不重复子序列*********************************************/
        int longestUnequalSubsquence1(::std::string& s){
            int all  = s.length();
            int size = all;
            ::std::vector<int> M(256,0);
            int i    = 0;
            while(i<size){
                if(++M[s[i++]-'a'] > 1)--all;
            }
            return all;
        }
        /**************************************判断子序列***************************************************************/
        bool isSubsquence(::std::string a, ::std::string b){
            ::std::vector<::std::vector<int>> M(26,::std::vector<int>(a.length()+2, -1));
            ::std::vector<int>val(26,-1);
            for(int i=a.length()-1; i>=0; --i){
                val[a[i]-'a'] = i;
                for(int j=0; j<26; ++j){
                    M[j][i] = val[j];
                }
            }
            for(int i=0; i<26; ++i){
                for(int j=0; j<a.length(); ++j){
                    ::std::cout<<M[i][j]<<" ";
                }
                ::std::cout<<::std::endl;
            }
            int next = 0;
            for(int i=0; i<b.length(); ++i){
                if(M[b[i]-'a'][next] == -1){
                    return false;
                }else{
                    next = M[b[i]-'a'][next] + 1;
                }
            }
            return true;
        }
        /**************************************最大的矩阵和***************************************************************/
        int maxSumR(::std::vector<::std::vector<int>>& r){
            ::std::vector<::std::vector<int>> R(r.size()+1,::std::vector<int>(r[0].size()+1,0));
            for(int i=1; i<R.size(); ++i){
                for(int j=1; j<R[0].size(); ++j){
                    R[i][j] = R[i][j-1] + r[i-1][j-1];
                }
            }
            int res = INT_MIN;
            int tmp;
            for(int j=1; j<R[0].size(); ++j){
                for(int k=0; k<j; ++k){
                    tmp = 0;
                    for(int i=1; i<R.size(); ++i){
                        tmp = (tmp+R[i][j]-R[i][k]>0)?(tmp+R[i][j]-R[i][k]):0;
                        res = ::std::max(res,tmp);
                    }
                }
            }
            return res;
        }
        /***************************************带限制的子序列和**************************************************************/
        int constrainedSubsetSum(::std::vector<int>& nums, int k) {
            ::std::priority_queue<::std::pair<int,int>>q;
            ::std::vector<int> dp(nums.size(),0);
            int res = INT_MIN;
            int i   = 0;
            while(i<nums.size()){
                dp[i] = nums[i];
                while(!q.empty() && q.top().second<(i-k)){q.pop();}
                dp[i] = q.empty()?dp[i]:(::std::max(dp[i], dp[i]+q.top().first));
                res   = ::std::max(dp[i],res);
                q.push(::std::make_pair(dp[i],i));
                ++i;
            }
            return res;
        }
        int consttainedSubset_sum(::std::vector<int>& nums, int k){
            int size = nums.size();
            int res  = INT_MIN;
            ::std::priority_queue<int> heap;
            ::std::vector<int> dp(size,0);
            for(int i=0; i<size; ++i){
                while(heap.size() && heap.top()<i-k)heap.pop();
                dp[i] = (heap.size()?(::std::max(0, nums[heap.top()])):0)+nums[i];
                heap.push(i);
                res = ::std::max(res, dp[i]);
            }
            return res;
        }
        /***********************************************最长定差子序列*******************************************************/
        int longestSubsequence(::std::vector<int>& arr, int difference) {
            ::std::vector<int>dp(arr.size(), 1);
            int res = 1;
            for(int i=0; i<arr.size(); ++i){
                for(int j=i-1; j>=0; --j){
                    if(arr[i]-arr[j]==difference)dp[i] = ::std::max(dp[i],dp[j]+1);
                }
                res = ::std::max(dp[i], res);
            }
            return res;
        }
        int longestSubsequence1(::std::vector<int>& arr, int difference){
            int res = 1;
            ::std::unordered_map<int,int> m;
            for(auto x : arr )res = ::std::max(res,m[x] = m[x-difference]+1);
            return res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    ::std::string a  ="asdfaghjklzxcvbnm";
    ::std::string b  ="asnm";
    ::std::cout<<te.isSubsquence(a,b)<<::std::endl;
    //::std::vector<::std::vector<int>> R= {
            //{0, -2, -7,  0},
            //{9,  2,  -6,  2},
            //{-4, 1, -4,  1},
            //{-1, 8,  0, -2}
    //};
    //::std::cout<<te.maxSumR(R)<<::std::endl;
    //::std::string  s = "mmmmm";
    //::std::string  a = "pwwkiuew";
    //::std::string  b = "asdsdasdfg";
    //::std::cout<<te.longestUnequalSubsquence1(a)<<::std::endl;
    //::std::cout<<te.longestUnequalSubsquence(a)<<::std::endl;
    //::std::cout<<te.isSubsquence(b,a)<<::std::endl;
    //::std::vector<int>a({-1,2,3,4,1,0,8,9,10,11,2,4,12,34,56,78,90});
    //::std::vector<int>b({-1,1,3,4,8,123,8,79,9,12,12,22,33,11,12,34,45,67,10,234});
    //::std::cout<<te.longestCommenIncreasingSubsequence(a,b)<<std::endl;
    //::std::cout<<te.LCIS(a,b)<<std::endl;
    //::std::cout<<te.LCIS2(a,b)<<std::endl;
    return 0;
}
