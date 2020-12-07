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
#include <unordered_set>
#include <algorithm>
#include <climits>
#include <deque>
#include <numeric>
#include <vector>
#include <random>
#include <map>
#include <set>
#include <cmath>
#include <stack>
#include <stdlib.h>
#include <queue>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {
    }
};
class MountainArray {
  public:
    int get(int index);
    int length();
};

class SummaryRanges {
//给定一个非负整数的数据流输入 a1，a2，…，an，…，将到目前为止看到的数字总结为不相交的区间列表352. 将数据流变为多个不相交区间
public:

    std::vector<int> inv;
    SummaryRanges() {}
    void addNum(int val) {
        int index = std::upper_bound(inv.begin(), inv.end(), val) - inv.begin();
        if(index&1)return;
        if(index < inv.size() && inv[index]==val+1){
            inv[index] = val;
        }else{
            inv.insert(inv.begin()+index, val);
            inv.insert(inv.begin()+index+1, val);
        }
        if(index && inv[index]<=inv[index-1]+1){
            inv.erase(inv.begin()+index);
            inv.erase(inv.begin()+index-1);
        }
    }

    std::vector<std::vector<int>> getIntervals() {
        int size = inv.size();
        std::vector<std::vector<int>> res;
        for(int i=0; i<size; ++i)res.push_back({inv[i], inv[++i]});
        return res;
    }
};

class Solution_1 {
public:
//给定一个包含 [0，n ) 中独特的整数的黑名单 B，写一个函数从 [ 0，n ) 中返回一个不在 B 中的随机整数。 对它进行优化使其尽量少调用系统方法 Math.random() 。
    std::vector<int> b;
    int n;
    int b_size;
    Solution_1(int N, std::vector<int>& blacklist) : n(N), b(blacklist){
        std::sort(b.begin(), b.end());
        b_size = b.size();
    }
    int pick() {
        int k = rand() % (n - b_size);
        int l = 0;
        int r = b_size - 1;
        while(l < r){
            int mid = (l + r + 1)/2;
            if(b[mid] - mid > k){
                r = mid - 1;
            }else{
                l = mid;
            }
        }
        return l==r && b[l]-l<=k?l+k+1:k;
    }
};

class TimeMap {
public:
        //81. 基于时间的键值存储
    std::map<std::string, std::vector<int>> kmp;
    std::map<std::pair<std::string, int>, std::string> ktmp;

    TimeMap(){}

    void set(std::string k, std::string v, int t) {
        ktmp[{k, t}] = v;
        kmp[k].push_back(t);
    }

    std::string get(std::string k, int t) {
        auto it = lower_bound(kmp[k].rbegin(), kmp[k].rend(), t, std::greater<int>());
        return it==kmp[k].rend()?"":ktmp[{k, *it}];
    }
};

//528. 按权重随机选择
class Solution_2 {
public:
    std::vector<int> sums;
    std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<int> uni;

    Solution_2(std::vector<int>& w) {
        sums = w;
        for(int i=1; i<sums.size(); ++i)sums[i] += sums[i-1];
        uni = std::uniform_int_distribution<int>{0, sums.back()-1};
    }
    int pickIndex() {
        int t = uni(gen);
        int l = 0;
        int r = sums.size()-1;
        while(l <= r){
            int mid = l + ((r - l)>>1);
            if(sums[mid] <= t){
                l = mid + 1;
            }else{
                r = mid;
            }
        }
        return l;
    }
};
class CustomFunction {
public:
    // Returns f(x, y) for any given positive integers x and y.
    // Note that f(x, y) is increasing with respect to both x and y.
    // i.e. f(x, y) < f(x + 1, y), f(x, y) < f(x, y + 1)
    int f(int x, int y);
};
/*
["MajorityChecker","query"]
[[[2,3,3,2,2,2,2,2,2,3,2,3,3,3,2,1,1,2,1,2,2]],[0,8,5]]
*/
class MajorityChecker {
//1157. 子数组中占绝大多数的元素
public:
    MajorityChecker(std::vector<int>& arr) : A(arr){}
    struct Hash_Cmp{
        size_t operator()(const std::pair<int, int>& p) const{
            return p.first ^ p.second;
        }
    };
    std::vector<int> A;
    std::unordered_map<std::pair<int, int>, std::pair<int, int>, Hash_Cmp> mp;

    int query(int left, int right, int threshold) {
        if(mp.count({left, right})){
            auto [res, n] = mp[{left, right}];
            return n>=threshold?res:-1;
        }
        int res = A[left];
        int n   = 1;
        for(int i=left+1; i<=right; ++i){
            res==A[i]?++n:--n;
            !n?res=A[i],++n:0;
        }
        n = 0;
        for(int i=left; i<=right; ++i)n += res==A[i];
        mp[{left, right}] = {res, n};
        return n>=threshold?res:-1;
    }
};

class Solution_3{
//497. 非重叠矩形中的随机点
public:
    std::mt19937 rg{std::random_device{}()};
    std::uniform_int_distribution<int> uni;
    std::vector<std::vector<int>> rects;
    std::vector<int> q;
    int total;
    Solution_3(std::vector<std::vector<int>>& r):rects(r){
        for(auto &n : rects){
            total += (n[2]-n[0]+1) * (n[3]-n[1]+1);
            q.push_back(total);
        }
        uni = std::uniform_int_distribution<int>{0, total-1};
    }
    std::vector<int> pick() {
        int t1 = uni(rg);
        int l  = 0;
        int r  = rects.size() - 1;
        while(l < r){
            int m = l + ((r-l)>>1);
            if(t1 >= q[m]){
                l = m + 1;
            }else{
                r = m;
            }
        }
        const auto &x = rects[l];
        int  wi = x[2] - x[0] + 1;
        int  hi = x[3] - x[1] + 1;
        int  ba = q[l] - wi*hi;
        return {x[0]+(t1-ba)%wi, x[1]+(t1-ba)%hi};
    }
};

bool isBadVersion(int version);

class Solution{
        int guess(int n);
    public:
//1201. 丑数 III
        int nthUglyNumber(int n, int a, int b, int c){
            std::function<int(int, int)> gcd = [&](int a, int b){
                return a?gcd(b%a, a):b;
            };
        }

//面试题 10.05. 稀疏数组搜索
        int findString(std::vector<std::string>& words, std::string s){
            int l = 0;
            int r = words.size() - 1;
            while(l<=r){
                int m = l + ((r-l)>>1);
                while(m<=r && words[m]=="")++m;
                if(m>r){
                    r = l + ((r-l)>>1) - 1;
                    continue;
                }
                if(words[m]==s){
                    return m;
                }else if(words[m] < s){
                    l = m + 1;
                }else{
                    r = m - 1;
                }
            }
            return -1;
        }

//面试题 10.09. 排序矩阵查找
        bool searchMatrix(std::vector<std::vector<int>>& matrix, int t){
            if(!matrix.size())return false;
            int i = 0;
            int j = matrix[0].size() - 1;
            while(i<matrix.size() && j>=0){
                if(matrix[i][j]>t){
                    --j;
                }else if(matrix[i][j]<t){
                    ++i;
                }else{
                    return true;
                }
            }
            return false;
        }

//862. 和至少为 K 的最短子数组
        int shorestSubarray(std::vector<int>& A, int K){
            int size = A.size();
            std::deque<int> dq(size, 0);
            std::vector<int> sums(size+1, 0);
            dq.push_back(0);
            int res = INT_MAX;
            for(int i=0; i<size; ++i){
                sums[i+1] = sums[i] + A[i];
                while(dq.size() && sums[dq.back()]>=sums[i+1])dq.pop_back();
                while(dq.size() && (sums[i+1]-sums[dq.front()]>=K))res = std::min(res, i+1-dq.front()), dq.pop_front();
                dq.push_back(i+1);
            }
            return res==INT_MAX?-1:res;
        }
        int shorestSubarray_fuck(std::vector<int>& A, int K){
            int size = A.size();
            std::function<bool(int)> calc = [&](int m){
                int sum = 0;
                for(int i=0; i<size; ++i){
                    sum += A[i];
                    if(i>=m)sum -= A[i-m];
                    if(i>=m-1 && sum>=K)return true;
                }
                return false;
            };
            for(int i=1; i<=size; ++i){
                if(calc(i))return i;
            }
            return -1;
        }

//154. 寻找旋转排序数组中的最小值 II
        int findMin(std::vector<int>& nums){
            int l = 0;
            int r = nums.size() - 1;
            while(l < r){
                int m = l + ((r-l)>>1);
                if(nums[m] > nums[r]){
                    l = m + 1;
                }else if(nums[m] < nums[r]){
                    r = m;
                }else{
                    r = r - 1;
                }
            }
            return l;
        }

//剑指 Offer 53 - I. 在排序数组中查找数字 I
        int search(std::vector<int>& nums, int t){
            if(!nums.size())return 0;
            int l = 0;
            int r = nums.size()-1;
            int res = 0;
            while(l <= r){
                int m = l + ((r-l)>>1);
                if(nums[m]==t){
                    ++res;
                    for(int i=m+1;i<nums.size()&&nums[i]==t; ++i)++res;
                    for(int i=m-1;i>=0&&nums[i]==t; --i)++res;
                    return res;
                }else if(nums[m] > t){
                    r = m - 1;
                }else{
                    l = m + 1;
                }
            }
            return res;
        }

//483. 最小好进制
        std::string smallestGoodBest(std::string n){
            long long N = std::stoll(n);
            for(int m=59; m>1; --m){
                long long k = std::pow(N, 1.0/m);
                if(k<=1)continue;
                long long r = 0;
                for(int i=0; i<=m; ++i)r = r*k + 1;
                if(r==N)return std::to_string(k);
            }
            return std::to_string(N-1);
        }
//875. 爱吃香蕉的珂珂
        int minEatingSpeed(std::vector<int>& piles, int H){
            std::function<int(int)> calc = [&](int m){
                int res = 0;
                for(auto &p : piles)res += (p%m?1:0) + p/m;
                return res;
            };
            int l = 0;
            int r = *max_element(piles.begin(), piles.end());
            while(l < r){
                int m = l + ((r-l)>>1);
                if(calc(m) > H){
                    l = m + 1;
                }else{
                    r = m;
                }
            }
            return l;
        }

//74. 搜索二维矩阵
        bool searchMatrix(std::vector<std::vector<int>>& matrix, int t){
            int m = matrix.size();
            if(!m)return false;
            int n = matrix[0].size();
            int l = 0;
            int r = m*n - 1;
            while(l <= r){
                int m = l + ((r-l)>>1);
                int i = m/n;
                int j = m%n;
                if(matrix[i][j]==t){
                    return true;
                }else if(matrix[i][j]>t){
                    r = m - 1;
                }else{
                    l = m + 1;
                }
            }
            return false;
        }

//374. 猜数字大小
        int guessNumber(int n){
            int l = 1;
            int r = n;
            while(l <= r){
                int m = l + ((r-l)>>1);
                int t = guess(m);
                if(!t){
                    return m;
                }else if(t==1){
                    l = m + 1;
                }else{
                    r = m - 1;
                }
            }
            return l;
        }
//454. 四数相加 II
        int fourSumCount(std::vector<int>&A, std::vector<int>&B, std::vector<int>&C, std::vector<int>&D){
            int res = 0;
            std::unordered_map<int, int> mp;
            for(auto &a : A){
                for(auto &b : B){
                    ++mp[a+b];
                }
            }
            for(auto &c : C){
                for(auto &d : D){
                    if(mp.count(-(c+d)))res += mp[-(c+d)];
                }
            }
            return res;
        }

//315. 计算右侧小于当前元素的个数
        std::vector<int> countSmaller(std::vector<int>& nums){
            int n = nums.size();
            std::vector<int> res(n), index(n);
            std::vector<int> tmp_nums(n), tmp_index(n);
            std::iota(index.begin(), index.end(), 0);

            std::function<void (int, int, int)> merge = [&](int l, int m, int r){
                int size = r - l + 1;
                int L    = l;
                int R    = m + 1;
                int i    = 0;
                while(L<=m && R<=r)tmp_nums[i++] = nums[L]>nums[R]?({tmp_index[i]=index[R];nums[R++];}):({res[index[L]]+=R-m-1;tmp_index[i]=index[L]; nums[L++];});
                while(L<=m)tmp_nums[i++] = ({res[index[L]]+=R-m-1;tmp_index[i]=index[L];nums[L++];});
                while(R<=r)tmp_nums[i++] = ({tmp_index[i]=index[R]; nums[R++];});
                while(size--)index[l+size] = tmp_index[size], nums[l+size] = tmp_nums[size];
            };
            std::function<void(int , int)> calc = [&](int l, int r){
                if(l>=r)return;
                int m = l + ((r-l)>>1);
                calc(l, m);
                calc(m+1, r);
                merge(l, m, r);
            };
            calc(0, n-1);
            return res;
        }
//668. 乘法表中第k小的数
        int findKthNumber(int m, int n, int k){
            std::function<int(int)> calc = [&](int mid){
                int res = 0;
                for(int i=1; i<=m; ++i)res += std::min(mid/i, n);
                return res < k;
            };
            int l = 1;
            int r = m * n;
            while(l < r){
                int m = l + ((r-l)>>1);
                if(calc(m)){
                    l = m + 1;
                }else{
                    r = m;
                }
            }
            return l;
        }

//878. 第 N 个神奇数字
        int nthMagicalNumber(int N, int A, int B){
            std::function<int(int, int)> gcd = [&](int a, int b){
                return a?gcd(b%a, a):b;
            };
            int M = 1e9 + 7;
            int L = A/gcd(A, B)*B;
            long long l = 0;
            long long r = std::min(A, B)*(long long)N + 1;
            while(l < r){
                long long m = l + ((r-l)>>1);
                if(m/A + m/B - m/L < N){
                    l = m + 1;
                }else{
                    r = m;
                }
            }
            return l%M;
        }

//367. 有效的完全平方数
        bool idPrefectSquare(int num){
            long long l = 0;
            long long r = num;
            while(l <= r){
                long long m = l + ((r-l)>>1);
                if(m*m == num){
                    return true;
                }else if(m*m < num){
                    l = m + 1;
                }else{
                    r = m - 1;
                }
            }
            return false;
        }
//1300. 转变数组后最接近目标值的数组和
        int findBestvalue(std::vector<int>& arr, int target){
            int size = arr.size();
            std::sort(arr.begin(), arr.end());
            std::vector<long long> sums(size+1, 0);
            for(int i=1; i<=size; ++i)sums[i] += sums[i-1] + arr[i-1];
            std::function<int(int)> calc = [&](int m){
                auto it = lower_bound(arr.begin(), arr.end(), m);
                return sums[it-arr.begin()] + (arr.end()-it)*m;
            };
            int l = 0;
            int r = arr[size-1];
            int res;
            while(l<=r){
                int m = l + ((r-l)>>1);
                int s = calc(m);
                if(s <= target){
                    res = m;
                    l   = m + 1;
                }else{
                    r   = m - 1;
                }
            }
            return abs(calc(res)-target) > abs(calc(res+1)-target)?res+1:res;
        }
//927. 三等分
        std::vector<int> threeEqualParts(std::vector<int>& A){
            int ones = std::accumulate(A.begin(), A.end(), 0);
            if(ones%3)return {-1,-1};
            if(!ones)return {0, 2};

            ones /= 3;
            std::vector<int> mp(6);
            int size = A.size();
            int c    = 0;
            for(int i=0; i<size; ++i){
                if(!A[i])continue;
                if(++c==1)      mp[0] = i;
                if(c==ones)     mp[1] = i;
                if(c==ones+1)   mp[2] = i;
                if(c==ones*2)   mp[3] = i;
                if(c==ones*2+1) mp[4] = i;
                if(c==ones*3)   mp[5] = i;
            }
            int zero = size - mp[5] - 1;
            if(mp[1]+zero>=mp[2] || mp[3]+zero>=mp[4])return {-1, -1};
            std::string s;
            for(int i=0; i<size; ++i)s += A[i]+'0';
            std::string s1 = s.substr(mp[0], mp[1] - mp[0] + 1 + zero);
            std::string s2 = s.substr(mp[2], mp[3] - mp[2] + 1 + zero);
            std::string s3 = s.substr(mp[4]);
            if(s1!=s2 || s2!=s3)return {-1, -1};
            return {mp[1]+zero, mp[3]+zero+1};
        }

        std::vector<int> threeEqualParts_fuck(std::vector<int>& A){
            int size = A.size();
            if(!*max_element(A.begin(), A.end()))return {0, size-1};
            std::function<int(int, int&, int&)> calc = [&](int m, int& left, int &right){
                int i = 0;
                int p = 0;
                for(; i<size && p<m; ++i)p = (p<<1) + A[i];
                if(p<m)return 1;
                left = i-1;
                for(p=0; i<size && p<m; ++i)p = (p<<1) + A[i];
                if(p<m)return 1;
                right = i;
                for(p=0; i<size; ++i)p = (p<<1) + A[i];
                if(p<m)return  1;
                if(p>m)return -1;
                return 0;
            };
            int l = 0;
            int r = (1<<size)/3;
            int left,right;
            while(l <= r){
                int m = l + ((r-l)>>1);
                int t = calc(m, left, right);
                if(!t){
                    return {left, right};
                }else if(t>0){
                    r = m - 1;
                }else if(t<0){
                    l = m + 1;
                }
            }
            return {-1, -1};
        }

//1283. 使结果不超过阈值的最小除数
        int smallestDivisor(std::vector<int>& nums, int th){
            std::function<long long(int)> calc = [&](int m){
                long long res = 0;
                for(auto &n : nums)res += (long long)(n%m?1:0) + (long long)n/m;
                return res;
            };
            long long l = 1;
            long long r = calc(th)*th;
            while(l < r){
                long long m = l + ((r-l)>>1);
                long long t = calc(m);
                if(t > th){
                    l = m + 1;
                }else{
                    r = m;
                }
            }
            return l;
        }

//778. 水位上升的泳池中游泳
        int swimInWater(std::vector<std::vector<int>>& grid){
            int m = grid.size();
            struct Node{
                int i; int j; int d;
                Node(int i1, int j1,  int d1) : i(i1), j(j1), d(d1) {}
                bool operator<(const Node &node) const{ return d > node.d; }
            };
            std::priority_queue<Node> q;q.push({0, 0, 0});
            std::vector<std::vector<int>> fun = {{0, 1},{0, -1},{1, 0},{-1, 0}};
            std::vector<std::vector<int>> mp(m, std::vector<int>(m));mp[0][0] = 1;
            int res = INT_MIN;
            while(q.size()){
                auto [i, j, d] = q.top();q.pop();
                res = std::max(res, grid[i][j]);
                if(i==m-1 && j==m-1)return res;
                for(auto &f : fun){
                    int i1 = i + f[0];
                    int j1 = j + f[1];
                    if(i1>=0 && i1<m && j1>=0 && j1<m && !mp[i1][j1]){
                        mp[i1][j1]++;
                        q.push({i1, j1, grid[i1][j1]});
                    }
                }
            }
            return res;
        }

//436. 寻找右区间
        std::vector<int> findRightINterval(std::vector<std::vector<int>>& intervals){
            std::map<int, int> mp;
            std::vector<int> res;
            for(int i=0; i<intervals.size(); ++i)mp[intervals[i][0]] = i;
            for(auto &v : intervals){
                auto it = mp.lower_bound(v[1]);
                it==mp.end()?res.push_back(-1):res.push_back((*it).second);
            }
            return res;
        }

//1237. 找出给定方程的正整数解
        std::vector<std::vector<int>> findSolution(CustomFunction& c, int z) {
            std::vector<std::vector<int>> res;
            int r = 1000;
            for(int i=1; i<=1000; ++i){
                int l = 1;
                while(l <= r){
                    int m = l + ((r-l)>>1);
                    int t = c.f(i, m);
                    if(t==z){
                        res.push_back({i, m});
                        r = m - 1;
                        break;
                    }else if(t > z){
                        r = m - 1;
                    }else{
                        l = m + 1;
                    }
                }
            }
            return res;
        }

//面试题 08.03. 魔术索引
        int findMagicIndex(std::vector<int>& nums){
            std::function<int(int, int)> calc = [&](int l, int r){
                if(l > r)return -1;
                int m    = l + ((r-l)>>1);

                int res1 = calc(l, m-1);
                if(res1 != -1)return res1;

                if(nums[m]==m)return m;

                return calc(m+1, r);
            };
            return calc(0, nums.size()-1);
        }

//69. x 的平方根
        int mySqrt(int x){
            if(x<=1)return x;
            long long l = 0;
            long long r = x;
            while(l < r){
                long long mid = l + ((r-l)>>1);
                if(mid*mid <= x){
                    l = mid + 1;
                }else{
                    r = mid;
                }
            }
            return l;
        }

//33. 搜索旋转排序数组
        int search(std::vector<int>& arr, int target){
            int l = 0;
            int r = arr.size() - 1;
            while(l < r){
                int mid = l + ((r - l)>>1);
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

//1351. 统计有序矩阵中的负数
        int countNegatives(std::vector<std::vector<int>>& grid){
            int res = 0;
            int m   = grid.size();
            if(!m || !grid[0].size())return res;
            for(int i=0; i<m; ++i)res += lower_bound(grid[i].rbegin(), grid[i].rend(), 0) - grid[i].rbegin();
            return res;
        }
//363. 矩形区域不超过 K 的最大数值和
        int maxSumSubmatrix(std::vector<std::vector<int>>& matrix, int k){
            int size_i  = matrix.size();
            int size_j;
            int res = INT_MIN;
            if(!size_i || !(size_j=matrix[0].size()))return 0;
            for(int t=0; t<size_j; ++t){
                std::vector<int> sums(size_i);
                for(int j=t; j<size_j; ++j){
                    int sum  = 0;
                    std::set<int> st;st.insert(0);
                    for(int i=0; i<size_i; ++i){
                        sums[i] += matrix[i][j];
                        sum += sums[i];
                        auto it = st.lower_bound(sum-k);
                        if(it != st.end())res = std::max(res, sum-*it);
                        st.insert(sum);
                    }
                }
            }
            return res;
        }

//793. 阶乘函数后K个零
        int preimageSizeFZF(int k){
            if(!k)return 5;
            std::function<long long(long long)> calc = [](long long mid){
                int res = 0;
                while(mid){
                    res += mid / 5;
                    mid /= 5;
                }
                return res;
            };
            long long l = 0;
            long long r = (long long)k*5 + 1;
            long long t;
            while(l < r){
                long long mid  = l + ((r - l)>>1);
                if((t=calc(mid))==k){
                    return 5;
                }else if(t > k){
                    r = mid;
                }else{
                    l = mid + 1;
                }
            }
            return 0;
        }
//327. 区间和的个数
        int countRangeSum(std::vector<int>& nums, int lower, int upper){
            int size = nums.size();
            std::vector<long long> sums(size+1);
            for(int i=1;i<=size;i++)sums[i] = sums[i-1] + nums[i-1];
            std::function<int(int, int, int)> merge = [&](int l, int m, int r){
                int size = r - l + 1;
                int res  = 0;
                int left = l;
                int lo   = m + 1;
                int up   = m + 1;
                while(left<=m){
                    while(lo<=r && sums[lo]-sums[left] <  lower)++lo;
                    while(up<=r && sums[up]-sums[left] <= upper)++up;
                    res += up - lo;
                    ++left;
                }
                left = l;
                up   = m+1;
                lo   = 0;
                std::vector<int> tmp(size);
                while(left<=m && up<=r)tmp[lo++] = sums[left]>sums[up]?sums[up++]:sums[left++];
                while(left<=m)tmp[lo++] = sums[left++];
                while(up<=r)tmp[lo++]   = sums[up++];
                while(size--)sums[l+size] = tmp[size];
                return res;
            };
            std::function<int(int,int)> calc = [&](int l, int r){
                if(l >= r)return 0;
                int m = l + ((r - l)>>1);
                return calc(l, m) + calc(m+1, r) + merge(l, m, r);
            };

            return calc(0, size);
        }

//658. 找到 K 个最接近的元素
        std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x){
            auto it = lower_bound(arr.begin(), arr.end(),x);
            int r   = std::min(int(it-arr.begin()+k), (int)arr.size()-1);
            int l   = std::max(int(it-arr.begin()-k), 0);
            while(r-l+1 > k)x-arr[l]>arr[r]-x?++l:--r;
            return {arr.begin()+l, arr.begin()+r+1};
        }

//278. 第一个错误的版本
        int firstBagVersion(int n){
            int l = 0;
            int r = n;
            while(l < r){
                int mid = l + ((r - l)>>1);
                if(isBadVersion(mid)){
                    r = mid;
                }else{
                    l = ++mid;
                }
            }
            return r;
        }

//349. 两个数组的交集
        std::vector<int> intersetion(std::vector<int>& nums1, std::vector<int>& nums2){
            if(!nums1.size() || !nums2.size())return {};
            int max_ = *max_element(nums1.begin(), nums1.end());
            int min_ = *min_element(nums1.begin(), nums1.end());
            std::unordered_set<int> mp1(nums1.begin(), nums1.end());
            std::unordered_set<int> mp2;
            for(auto &x : nums2){
                if(x>=min_ && x<=max_ && mp1.count(x))mp2.insert(x);
            }
            return std::vector<int>(mp2.begin(), mp2.end());
        }
//744. 寻找比目标字母大的最小字母
        char nextGreateestLetter(std::vector<char>& letters, int target){
            auto it = upper_bound(letters.begin(), letters.end(), target);
            return it != letters.end()?*it:letters[0];
        }

//475. 供暖器
        int findRadius(std::vector<int>& ho, std::vector<int>& he){
            int size_o = ho.size();
            int size_e = he.size();
            std::sort(he.begin(), he.end());
            int res = 0;
            for(auto &h : ho){
                int index = lower_bound(he.begin(), he.end(), h) - he.begin();
                int d1    = !index?INT_MAX:abs(h - he[index-1]);
                int d2    = index==size_e?INT_MAX:abs(h - he[index]);
                res       = std::max(res, std::min(d1, d2));
            }
            return res;
        }

//1111. 有效括号的嵌套深度
        std::vector<int> maxDepthAfterSplit(std::string seq){
            std::vector<int> res;
            int d = 0;
            for(auto &c : seq) res.push_back((c=='('?++d:d--)&1^1);
            return res;
        }

//给定两个整数，被除数 dividend 和除数 divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。 返回被除数 dividend 除以除数 divisor 得到的商。 整数除法的结果应当截去（truncate）其小数部分，例如：truncate(8.345) = 8 以及 truncate(-2.7335) = -2
        int div(int a, int b){
            if(a < b)return 0;
            int res = 1;
            int b1  = b;
            while(a-b1 >= b1){
                b1  += b1;
                res += res;
            }
            return res + div(a-b1, b);
        }
        int divide(int dd, int dr){
            if(!dd)return dd;
            if(dr==1)return dd;
            if(dr==-1)return dd==INT_MIN?INT_MAX:-dd;
            if(dr==INT_MIN)return dd==INT_MIN?1:0;
            bool flag = (dd>0) ^ (dr>0);
            int  res  = 0;
            if(dd==INT_MIN) dd = flag?dd+dr:dd-dr, ++res;
            res += div(dd>0?dd:-dd, dr>0?dr:-dr);
            return flag?-res:res;
        }

//给你一个大小为 m * n 的方阵 mat，方阵由若干军人和平民组成，分别用 1 和 0 表示。 请你返回方阵中战斗力最弱的 k 行的索引，按从最弱到最强排序。 如果第 i 行的军人数量少于第 j 行，或者两行军人数量相同但 i 小于 j，那么我们认为第 i 行的战斗力比第 j 行弱。 军人 总是 排在一行中的靠前位置，也就是说 1 总是出现在 0 之前。
        std::vector<int> kWeakestRows(std::vector<std::vector<int>>& mat, int k){
            int size_i = mat.size();
            int size_j = mat[0].size();
            std::priority_queue<std::pair<int, int>> q;
            for(int i=0; i<size_i; ++i){
                int l = 0;
                for(int j=0; j<size_j&&mat[i][j++]; ++l);
                if(q.size()==k){
                    if(q.top().second > l)q.pop(), q.push({l, i});
                }
                if(q.size() < k)q.push({l, i});
            }
            std::vector<int> res;
            while(q.size())res.push_back(q.top().second), q.pop();
            std::reverse(res.begin(), res.end());
            return res;
        }

//1095. 山脉数组中查找目标值
        int findInMountainArray_11_15(int t, MountainArray& m){
            int size = m.length();
            std::function<int(int, int, std::function<bool(int)>)> _bsearch
                = [&](int l, int r, std::function<bool(int)> _cmp){
                    while(l < r){
                        int m = l + ((r - l) >> 1);
                        if(_cmp(m)){
                            r = m;
                        }else{
                            l = m + 1;
                        }
                    }
                    return r;
                };
            int p = _bsearch(0, size-1, [&](int i) -> bool {
                    return m.get(i) > m.get(i+1); });
            if(m.get(p) == t) return p;
            int l = _bsearch(0, p - 1, [&](int i) -> bool {
                    return m.get(i) >= t; });
            if(m.get(l) == t) return l;
            int r = _bsearch(p+1, size - 1, [&](int i) -> bool {
                    return m.get(i) <= t; });
            return m.get(r) == t ? r : -1;
        }
        int findInMountainArray(int t, MountainArray& m){
            int size = m.length();
            int M    = 0;
            int l    = 0;
            int r    = size-1;
            std::function<int(int,int,int(int))> b_search = [&](int l, int r, int op(int)){
                t = op(t);
                while(l < r){
                    int mid = l + ((r-l)>>1);
                    int tmp = op(m.get(mid));
                    if(tmp==t){
                         return mid;
                    }else if(tmp > t){
                        r = mid - 1;
                    }else{
                        l = mid + 1;
                    }
                }
                return -1;
            };
            while(l<r){
                int mid = l + ((r-l)>>1);
                if(m.get(mid)<m.get(mid+1)){
                    l = mid + 1;
                }else{
                    r = mid;
                }
            }
            M = l;
            int tmp = m.get(M);
            if(tmp==t)return M;
            if(tmp<t)return -1;
            if(-1 != (tmp=b_search(0, M-1, [](int x){return x;})))return tmp;
            if(-1 != (tmp=b_search(M+1, size-1,[](int x){return -x;})))return tmp;
            return -1;
        }

//81. 搜索旋转排序数组 II
        bool search(std::vector<int>&nums, int t){
            int l = 0;
            int r = nums.size() - 1;
            while(l<r){
                while(l<r && nums[l]==nums[r])--r;
                int mid = l + ((r-l)>>1);
                if(t==nums[mid] || t==nums[r] || t==nums[l])return true;
                if(nums[l]<=nums[mid]){
                    if(nums[l]<t && nums[mid]>t){
                        r = --mid;
                        ++l;
                    }else{
                        l = ++mid;
                        --r;
                    }
                }else{
                    if(nums[mid]<t && nums[r]>t){
                        --r;
                        l = ++mid;
                    }else{
                        r = --mid;
                        ++l;
                    }
                }
            }
            return false;
        }
//给出一个字符串 S，考虑其所有重复子串（S 的连续子串，出现两次或多次，可能会有重叠）。 返回任何具有最长可能长度的重复子串。（如果 S 不含重复子串，那么答案为 ""。）
        std::string longestDupSubstring(std::string& S){
            int A    = 26;
            long MOD = pow(2, 32);
            int size = S.length();
            std::vector<int> dig(size);
            for(int i=0; i<size; ++i)dig[i] = S[i] - 'a';
            std::function<int(int)> calc = [&](int len){
                std::unordered_set<long long> mp;
                long long dp = 0;
                long long x  = 1;
                for(int i=0; i<len; ++i){
                    dp = (dp * A + dig[i]) % MOD;
                    x  = (x * A) % MOD;
                }
                mp.insert(dp);
                for(int i=1; i<=size-len; ++i){
                    dp = (dp*A - dig[i-1]*x % MOD + MOD )% MOD;
                    dp = (dp + dig[i+len-1]) % MOD;
                    if(mp.count(dp))return i;
                    mp.insert(dp);
                }
                return -1;
            };
            int l = 1;
            int r = size;
            while(l<r){
                int mid = l + ((r-l)>>1);
                if(calc(mid) !=-1){
                    l = ++mid;
                }else{
                    r = mid;
                }
            }
            int s = calc(l-1);
            return s==-1?"":S.substr(s, l-1);
        }
//230. 二叉搜索树中第K小的元素
        int kthSmallest(TreeNode* root, int k){
            std::stack<TreeNode*> st;
            while(root || st.size()){
                while(root)st.push(root),root=root->left;
                if(st.size()){
                    root = st.top();st.pop();
                    if(!--k)return root->val;
                    root = root->right;
                }
            }
            return -1;
        }
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
                    if((t+=w) > mid)t=w,++d;
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


