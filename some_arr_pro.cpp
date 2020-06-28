/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_arr_pro.cpp
*     author   : @ JY
*     date     : 2020--06--24
**********************************************/
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <climits>
#include <stdlib.h>
#include <vector>
#include <queue>
class Solution{
    public:
//1343. 大小为 K 且平均值大于等于阈值的子数组数目
        int numOfSubarrays(::std::vector<int>& arr, int k, int t) {
            int res = 0;
            int sub = 0;
            int r   = 0;
            int size = arr.size();
            while(r < size){
                sub += arr[r] - t;
                if(r>=k)sub -= arr[r-k] - t;
                if(r>=k-1 && sub>=0)++res;
                ++r;
            }
            return res;
        }
//设计一个算法，判断玩家是否赢了井字游戏。输入是一个 N x N 的数组棋盘，由字符" "，"X"和"O"组成，其中字符" "代表一个空位。
//以下是井字游戏的规则：
//玩家轮流将字符放入空位（" "）中。
//第一个玩家总是放字符"O"，且第二个玩家总是放字符"X"。
//"X"和"O"只允许放置在空位中，不允许对已放有字符的位置进行填充。
//当有N个相同（且非空）的字符填充任何行、列或对角线时，游戏结束，对应该字符的玩家获胜。
//当所有位置非空时，也算为游戏结束。
//如果游戏结束，玩家不允许再放置字符。
//如果游戏存在获胜者，就返回该游戏的获胜者使用的字符（"X"或"O"）；如果游戏以平局结束，则返回 "Draw"；如果仍会有行动（游戏未结束），则返回 "Pending"。

    ::std::string tictactoe(::std::vector<::std::string>& board) {
        int size      = board.size();
        int null_flag = 0;
        ::std::string X(size,'X');
        ::std::string O(size,'O');
        for(int i=0; i<size; ++i){
            if(X == board[i])return "X";
            if(O == board[i])return "O";
        }
        ::std::string v1(""),v2("");
        int i=0,j=0,j1=size-1;
        while(i<size){
            v1 += board[i][j++];
            v2 += board[i++][j1--];
        }
        if(v1==X || v2==X)return "X";
        if(v1==O || v2==O)return "O";
        j = 0;
        while(j<size){
            ::std::string tmp("");
            for(int i=0; i<size; ++i){
                if(board[i][j] == ' ')null_flag = 1;
                tmp += board[i][j];
            }
            if(X == tmp)return "X";
            if(O == tmp)return "O";
            ++j;
        }
        return null_flag?"Pending":"Draw";
    }
//给你一个整数数组 nums，每次 操作 会从中选择一个元素并 将该元素的值减少 1。
//如果符合下列情况之一，则数组 A 就是 锯齿数组：
//每个偶数索引对应的元素都大于相邻的元素，即 A[0] > A[1] < A[2] > A[3] < A[4] > ...
//或者，每个奇数索引对应的元素都大于相邻的元素，即 A[0] < A[1] > A[2] < A[3] > A[4] < ...
//返回将数组 nums 转换为锯齿数组所需的最小操作次数
    int movesToMakeZigzag(::std::vector<int>& nums) {
        int size = nums.size();
        int res1 = 0;
        int res2 = 0;
        for(int i=0; i<size; ++i){
            int l = i?nums[i-1]:INT_MAX;
            int r = i==size-1?INT_MAX:nums[i+1];
            if(i&1){
                res1 += ::std::max(0, nums[i] - ::std::min(l,r) + 1);
            }else{
                res2 += ::std::max(0, nums[i] - ::std::min(l,r) + 1);
            }
        }
        return ::std::min(res1, res2);
    }
//学校在拍年度纪念照时，一般要求学生按照 非递减 的高度顺序排列。
//请你返回能让所有学生以 非递减 高度排列的最小必要移动人数。
//注意，当一组学生被选中时，他们之间可以以任何可能的方式重新排序，而未被选中的学生应该保持不动。
    int heightChecker(::std::vector<int>& h) {
        ::std::vector<int> tmp(h);
        ::std::sort(tmp.begin(), tmp.end());
        int res  = 0;
        int size = h.size();
        for(int i=0; i<size; ++i){
            if(tmp[i] != h[i])++res;
        }
        return res;
    }
//给你数字 k ，请你返回和为 k 的斐波那契数字的最少数目，其中，每个斐波那契数字都可以被使用多次。
//斐波那契数字定义为：
//F1 = 1
//F2 = 1
//Fn = Fn-1 + Fn-2 ， 其中 n > 2 。
//数据保证对于给定的 k ，一定能找到可行解。
    int findMinFibonacciNumbers(int k){
        ::std::vector<int> dp(2,1);
        int i = 0;
        int j = 1;
        while(1){
            int t = dp[i++] + dp[j++];
            dp.push_back(t);
            if(t ==k)return 1;
            if(t > k)break;
        }
        int res = 0;
        j       = dp.size();
        while(k && j){
            if(dp[--j]<=k)k -= dp[j],++res;
        }
        return res;
    }
//给定一个整数数组 prices，其中第 i 个元素代表了第 i 天的股票价格 ；非负整数 fee 代表了交易股票的手续费用。
//你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。
//返回获得利润的最大值。
//注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。
    int maxPoit(::std::vector<int>& prices, int fee){
        int n = prices.size();
        int dp_i_0 = 0, dp_i_1 = INT_MIN;
        for (int i = 0; i < n; i++) {
            int temp = dp_i_0;
            dp_i_0 = ::std::max(dp_i_0, dp_i_1 + prices[i]);
            dp_i_1 = ::std::max(dp_i_1, temp - prices[i] - fee);
        }
        return dp_i_0;
    }
//在老式手机上，用户通过数字键盘输入，手机将提供与这些数字相匹配的单词列表。每个数字映射到0至4个字母。给定一个数字序列，实现一个算法来返回匹配单词的列表。你会得到一张含有有效单词的列表。映射如下图所示：
    ::std::unordered_map<char,::std::pair<int,int>> hs = {
        {'2', ::std::make_pair('a','c')},
        {'3', ::std::make_pair('d','f')},
        {'4', ::std::make_pair('g','i')},
        {'5', ::std::make_pair('j','l')},
        {'6', ::std::make_pair('m','o')},
        {'7', ::std::make_pair('p','s')},
        {'8', ::std::make_pair('t','v')},
        {'9', ::std::make_pair('w','z')}
    };
    ::std::vector<::std::string> getValid9Words(::std::string sum, ::std::vector<::std::string>& words){
        ::std::vector<::std::string> res;
        int size = sum.length();
        int i    = 0;
        for(::std::string &s : words){
            if(size != s.length())continue;
            for(i=0;i<size; ++i){
                if(hs[sum[i]].first<=s[i]&&hs[sum[i]].second>=s[i])continue;
                break;
            }
            if(i==size)res.push_back(s);
        }
        return res;
    }
//绘制直线。有个单色屏幕存储在一个一维数组中，使得32个连续像素可以存放在一个 int 里。屏幕宽度为w，且w可被32整除（即一个 int 不会分布在两行上），屏幕高度可由数组长度及屏幕宽度推算得出。请实现一个函数，绘制从点(x1, y)到点(x2, y)的水平线。
//给出数组的长度 length，宽度 w（以比特为单位）、直线开始位置 x1（比特为单位）、直线结束位置 x2（比特为单位）、直线所在行数 y。返回绘制过后的数组。
    ::std::vector<int> drawLine(int length, int w, int x1, int x2, int y){
        ::std::vector<int>res(length,0);
        for(int i=x1; i<=x2; ++i){
            res[i/32 + y*w/32] |= (1<<(31-i%32));
        }
        return res;
    }

//给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的连续子数组，并返回其长度。如果不存在符合条件的连续子数组，返回 0。
//    O(n)
    int minSubArrayLen(int s, ::std::vector<int>& nums){
        int r    = 0;
        int l    = 0;
        int size = nums.size();
        int sum  = 0;
        int res  = size+1;
        while(r<size){
            if((sum += nums[r++])<s)continue;
            while(sum>=s && l<=r){
                sum -= nums[l++];
            }
            res = ::std::min(res, r-l+1);
        }
        return res==size+1?0:res;
    }
//    O(log(n))  ???????????
    int minSubArrayLen1(int s,::std::vector<int>& nums){
        int size = nums.size();
        int res = size + 1;
        ::std::vector<int>sums(nums);
        for(int i=1; i<size; ++i)sums[i] += sums[i-1];
        for(int i=0; i<size; ++i){
            int  found = s+sums[i];
            auto bound = ::std::lower_bound(sums.begin(), sums.end(), found);
            if(bound != sums.end()){
                res = ::std::min(res, static_cast<int>(bound-(sums.begin()+i)));
            }
        }
        return res==size+1?0:res;
    }

//给你一份『词汇表』（字符串数组） words 和一张『字母表』（字符串） chars。
//假如你可以用 chars 中的『字母』（字符）拼写出 words 中的某个『单词』（字符串），那么我们就认为你掌握了这个单词。
//注意：每次拼写（指拼写词汇表中的一个单词）时，chars 中的每个字母都只能用一次。
//返回词汇表 words 中你掌握的所有单词的 长度之和。
    int countCharacters(::std::vector<::std::string>& words, ::std::string chars) {
        ::std::vector<int>c(26,0);
        int size = chars.length();
        int res  = 0;
        for(int i=0; i<size; ++i)++c[chars[i]-'a'];
        for(::std::string &w : words){
            ::std::vector<int> tmp(c);
            int i = 0;
            for(; i<w.length(); ++i){
                if(--tmp[w[i]-'a']<0)break;
            }
            if(i == w.length())res += i;
        }
        return res;
    }
//给定一个非负整数，你至多可以交换一次数字中的任意两位。返回你能得到的最大值
    int maximumSwap(int num){
        ::std::string s = ::std::to_string(num);
        int i           = 1;
        int size        = s.length();
        while(i<size && s[i]<=s[i-1])++i;
        if(i==size)return num;
        int f = s[i];
        int j = i++;
        for(; i<size; ++i){
            if(f<=s[i]){
                f = s[i];
                j = i;
            }
        }
        i = 0;
        for(; i<size; ++i){
            if(s[i]<f)break;
        }
        ::std::swap(s[j], s[i]);
        return atoi(s.c_str());
    }
//给定一个整数数组和一个整数 k，你需要找到该数组中和为 k 的连续的子数组的个数。
    int subarraySum(::std::vector<int>& nums, int k){
        ::std::unordered_map<int,int> hp;
        hp[0]   = 1;
        int res = 0;
        int sum = 0;
        for(auto &n : nums){
            res += hp[(sum += n)-k];
            ++hp[sum];
        }
        for(auto &n : hp){
            ::std::cout<<n.first<<"--"<<n.second<<::std::endl;
        }
        return res;
    }
    int test(){
        ::std::unordered_map<int,int>hp;
        for(int i=0; i<20; ++i){
            ::std::cout<<hp[i]<<::std::endl;
        }
        return 0;
    }
//给定一个整数数组，返回所有数对之间的第 k 个最小距离。一对 (A, B) 的距离被定义为 A 和 B 之间的绝对差值。
    int smallestDistancePair(::std::vector<int>& nums, int k) {
        ::std::priority_queue<int> hp;
        int size = nums.size();
        for(int i=0; i<size; ++i){
            for(int j=i+1; j<size; ++j){
                int tmp = abs(nums[i]-nums[j]);
                if(hp.size()==k){
                    if(hp.top()>tmp){
                        hp.pop();
                        hp.push(tmp);
                    }
                }else{
                    hp.push(tmp);
                }
            }
        }
        return hp.top();
    }
    // 2--search
    int smallestDistancePair1(::std::vector<int>& nums, int k) {
        ::std::sort(nums.begin(), nums.end());
        int size  = nums.size();
        int left  = 0;
        int right = nums[size-1] - nums[0];
        while(left < right){
            int mid = left + ((right-left)>>1);
            if(calc(nums,mid)>=k){
                right = mid;
            }else{
                left  = mid + 1;
            }
        }
        return left;
    }
    int calc(::std::vector<int>& nums, int mid){
        int l=0,r=0;
        int size = nums.size();
        int res  = 0;
        while(r<size){
            while(nums[r]-nums[l] > mid)++l;
            res += r - l;
            ++r;
        }
        return res;
    }

//给你一个数组 arr ，请你将每个元素用它右边最大的元素替换，如果是最后一个元素，用 -1 替换。
//完成所有替换操作后，请你返回这个数组。
    ::std::vector<int> replaseElements(::std::vector<int>& nums){
        int size = nums.size();
        if(size==0)return nums;
        int m    = nums[size-1];
        int t    = INT_MIN;
        nums[size-1] = -1;
        for(int i=size-2; i>=0; --i){
            t = nums[i];
            nums[i] = m;
            m = ::std::max(m, t);
        }
        return nums;
    }

//给定一个放有字符和数字的数组，找到最长的子数组，且包含的字符和数字的个数相同。
//返回该子数组，若存在多个最长子数组，返回左端点最小的。若不存在这样的数组，返回一个空数组。
    ::std::vector<::std::string> findLongestSubarray(::std::vector<::std::string>& array){
        ::std::unordered_map<int,int> hp;
        int s = 0;
        int e = 0;
        int n = 0;
        int size = array.size();
        for(int i=0; i<size; ++i){
            if(::std::isdigit(array[i][0])){
                ++n;
            }else{
                --n;
            }
            if(n==0){
                s = 0;
                e = i;
            }else if(hp.count(n)==0){
                hp[n] = i;
            }else if(i-hp[n]-1 > e-s){
                s = hp[n] + 1;
                e = i;
            }
        }
        if(s==e)return {};
        return ::std::vector<::std::string>(array.begin()+s, array.begin()+e);
    }
//给定一个已按照升序排列 的有序数组，找到两个数使得它们相加之和等于目标数。
//函数应该返回这两个下标值 index1 和 index2，其中 index1 必须小于 index2。
    ::std::vector<int> twoSum(::std::vector<int>& nums, int target){
        int size = nums.size();
        int l = 0;
        int r = size - 1;
        while(l<r){
            int sum  = nums[l] + nums[r];
            if(sum < target){
                ++l;
            }else if(sum > target){
                --r;
            }else{
                return {++l,++r};
            }
        }
        return {};
    }
//给定一个数组，包含从 1 到 N 所有的整数，但其中缺了两个数字。你能在 O(N) 时间内只用 O(1) 的空间找到它们吗？
//以任意顺序返回这两个数字均可。
    ::std::vector<int> missTwo(::std::vector<int>& nums){
        int size = nums.size();
        int x    = 0;
        int p    = 0;
        for(int i=0; i<size+2; ++i)x ^= (i+1);
        for(int i=0; i<size; ++i)x ^= nums[i];
        int f = x & ~x+1;
        int t = 0;
        for(int i=0; i<size; ++i){
            if(nums[i]&f)t ^= nums[i];
        }
        for(int i=1; i<=size+2; ++i){
            if(i&f)t ^= i;
        }
        return {t, x^t};
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    ::std::vector<int>nums = {2,3,1,2,-2,-3,-4,4,5,1,2,3,4,5,6};
    te.subarraySum(nums, 3);
    //::std::cout<<te.findMinFibonacciNumbers(19)<<::std::endl;
    return 0;
}
