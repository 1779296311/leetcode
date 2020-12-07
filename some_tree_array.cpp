/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_tree_array.cpp
*     author   : @ JY
*     date     : 2020--11--08
**********************************************/
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <string>
#include <algorithm>
#include <stack>
#include <map>
#include <cmath>
#include <climits>
#include <vector>
#include <queue>
#include <cstring>
#include <numeric>
#include <set>
#include <bitset>
#include <stdlib.h>


class Fancy{
    using ll = long long;
    private:
        int index = 0, size, MOD = 1e9 + 7;
        std::vector<ll> segnodes, lazya, lazym;
        void _push_down(int l, int m, int r, int node){
            if(!lazya[node] && lazym[node]==1)return;

            ll lc = node << 1 | 1, rc = (node + 1) << 1;

            lazya[lc] = (lazya[lc] * lazym[node]) % MOD;
            lazya[lc] = (lazya[lc] + lazya[node]) % MOD;
            lazym[lc] = (lazym[lc] * lazym[node]) % MOD;

            lazya[rc] = (lazya[rc] * lazym[node]) % MOD;
            lazya[rc] = (lazya[rc] + lazya[node]) % MOD;
            lazym[rc] = (lazym[rc] * lazym[node]) % MOD;

            segnodes[lc] = (segnodes[lc] * lazym[node] + (m - l + 1) * lazya[node]) % MOD;
            segnodes[rc] = (segnodes[rc] * lazym[node] + (r - m + 0) * lazya[node]) % MOD;

            lazya[node] = 0;
            lazym[node] = 1;
        }
        void _update(int l, int r, int node, int L, int R, int add, int mul){
            if(l > R || r < L)return ;
            if(L<=l && r<=R){
                lazya[node] = (lazya[node] * mul) % MOD;
                lazya[node] = (lazya[node] + add) % MOD;

                lazym[node] = (lazym[node] * mul) % MOD;

                segnodes[node] = (segnodes[node]*mul + (r-l+1)*add) % MOD;
                return ;
            }
            int m = l + ((r - l) >> 1);
            _push_down(l, m, r, node);
            if(m >= L)_update(l, m, node << 1 | 1, L, R, add, mul);
            if(m <  R)_update(m+1, r, (node+1) << 1, L, R, add, mul);
            segnodes[node] = (segnodes[node << 1 | 1] + segnodes[(node+1) << 1]) % MOD;
        }
        ll _query(int l, int r, int node, int index){
            if(l == r)return segnodes[node];
            int m = l + ((r - l) >> 1);
            _push_down(l, m, r, node);
            if(m >= index)return _query(l, m, node << 1 | 1, index);
            return _query(m+1, r, (node + 1) << 1, index);
        }
    public:
        Fancy() : size(1e5 + 1), lazya(size<<2), lazym(size<<2, 1LL), segnodes(size<<2){}

        void append(int val){
            _update(0, size-1, 0, index, index, val, 1);
            ++index;
        }
        void addAll(int inc){
            _update(0, size-1, 0, 0, index-1, inc, 1);
        }
        void multAll(int mul){
            _update(0, size-1, 0, 0, index-1, 0, mul);
        }
        int getIndex(int idx){
            if(idx<0 || idx>=index)return -1;
            return _query(0, size-1, 0, idx);
        }
};
class Segtree{
    int max_size;
    std::vector<int> segnodes, lazy;
    public:
        Segtree(int size) : max_size((size<<2)+1), segnodes(max_size), lazy(max_size){};
        void _build(int node, int l, int r){}
        void _push_down(int l, int m, int r, int node){
            if(!lazy[node])return;
            lazy[node << 1 | 1] += lazy[node];
            lazy[(node+1) << 1] += lazy[node];

            segnodes[node << 1 | 1] += (m - l + 1) * lazy[node];
            segnodes[(node+1) << 1] += (r - m) * lazy[node];

            lazy[node] = 0;
        }
        void _update_point(int v, int l, int r, int node){
            if(l == r){
                segnodes[node] = v;
                return;
            }
            int m = l + ((r - l) >> 1);
            _push_down(l, m, r, node);
            if(m >= node){
                _update_point(v, l, m, node<<1|1);
            }else{
                _update_point(v, m+1, r, (node+1)<<1);
            }
            segnodes[node] = segnodes[node<<1|1] + segnodes[(node+11)<<1];
        }
        void _update_range(int v, int l, int r, int node, int L, int R){
            if(L<=l && r<=R){
                lazy[node] += v;
                segnodes[node] += (r - l + 1) * v;
                return ;
            }
            if(l > R || r < L)return;
            int m = l + ((r - l) >> 1);
            _push_down(l, m, r, node);
            if(m >= L)_update_range(v, l, m, node << 1 | 1, L, R);
            if(m <  R)_update_range(v, m+1, r, (node + 1) << 1, L, R);
            segnodes[node] = segnodes[node << 1 | 1] + segnodes[(node + 1) << 1];
        }
        int _query(int l, int r, int node, int L, int R){
            if(L<=l && r<=R)return segnodes[node];
            int m = l + ((r - l) >> 1), ans = 0;
            _push_down(l, m, r, node);
            if(L <= m)ans += _query(l, m, node << 1 | 1,  L, R);
            if(m < R)ans += _query(m+1, r, (node + 1) << 1, L, R);
            return ans;
        }
};
//715. Range 模块
class RangeModule{
    std::map<int, int> rl;
    std::queue<std::map<int, int>::const_iterator>q;
    public:
        RangeModule(){}
        void addRange(int left, int right){
            for(auto it=rl.lower_bound(left); it!=end(rl) && it->second<=right; ++it){
                q.emplace(it);
            }
            while(q.size()){
                auto it = q.front();q.pop();
                auto [r, l] = *it;
                left = std::min(left, l);
                right = std::max(right, r);
                rl.erase(it);
            }
            rl.emplace(right, left);
        }
        bool queryRange(int left, int right){
            auto it = rl.lower_bound(right);
            return it!=end(rl) && it->second <= left;
        }
        void removeRange(int left, int right){
            for(auto it=rl.upper_bound(left); it!=end(rl) && it->second<right; ++it){
                q.emplace(it);
            }
            while(q.size()){
                auto it = q.front();q.pop();
                auto [r, l] = *it;
                rl.erase(it);
                if(left > l)rl.emplace(left, l);
                if(right < r)rl.emplace(r, right);
            }
        }
};

class NumArray_arr_tree{
    std::vector<int> tree, data;
    int n;
    NumArray_arr_tree(std::vector<int> &nums) : data(nums),
        tree(nums.size() + 2), n(nums.size() + 2){
            for(int i=0; i<nums.size(); ++i)_update(i+1, nums[i]);
    }
    int _lowbit(int x){return x & -x;};
    int _query(int x){
        int ans = 0;
        for(; x ; x-=_lowbit(x))ans += tree[x];
        return ans;
    }
    void _update(int x, int val){
        for(; x<n; x+=_lowbit(x))tree[x] += val;
    }
    void update(int i, int val){
        _update(i+1, val-data[i]);
        data[i] = val;
    }
    int sumRange(int i, int j){
        return _query(j+1) - _query(i);
    }
};
class NumArray{
    std::vector<int> tree;
    int len;
    NumArray(std::vector<int> &nums) : tree(nums.size() << 2), len(nums.size()){
        std::function<void(int, int, int)> _build = [&](int l, int r, int node){
            if(l == r){
                tree[node] = nums[l];
                return;
            }
            int m = l + ((r - l) >> 1);
            _build(l, m, node << 1 | 1);
            _build(m+1, r, (node+1) << 1);
            tree[node] = tree[node << 1| 1] + tree[(node + 1) << 1];
        };
        if(len)_build(0, len-1, 0);
    }
    void update(int i, int val){
        std::function<void(int, int, int, int, int)> _update =
            [&](int l, int r, int node, int index, int val){
                if(l == r){
                    tree[node] = val;
                    return;
                }
                int m = l + ((r - l) >> 1);
                if(m >= index)_update(l, m, node << 1 | 1, index, val);
                if(m <  index)_update(m+1, r, (node + 1) << 1, index, val);
                tree[node] = tree[node << 1 | 1] + tree[(node + 1) << 1];
            };
        if(len)_update(0, len-1, 0, i, val);
    }
    int sumRange(int i, int j){
        std::function<int(int, int, int, int, int)> _query
            = [&](int l, int r, int node, int L, int R){
                if(l > R || r < L)return 0;
                if(L<=l && r<=R)return tree[node];
                int m = l + ((r - l) >> 1);
                int ans = 0;
                if(m >= L)ans += _query(l, m, node << 1 | 1, L, R);
                if(m <  R)ans += _query(m+1, r, (node + 1) << 1, L, R);
                return ans;
            };
        return len ? _query(0, len-1, 0, i, j) : 0;
    }
};
class Solution{
//699. 掉落的方块
    std::vector<int> fallingSquares(std::vector<std::vector<int>> &positions){
        std::set<int> mp1;
        for(auto &p : positions)mp1.insert(p[0]), mp1.insert(p[0]+p[1]-1);
        int code = 0;
        std::unordered_map<int, int> mp;
        for(auto &x : mp1)mp[x] = code++;
        std::vector<int> tree((code<<2) + 1), lazy((code<<2) + 1);
        std::function<void(int, int, int, int)> _push_down
            = [&](int l, int m, int r, int node){
                if(!lazy[node])return;
                lazy[node << 1 | 1] = lazy[node];
                lazy[(node + 1) << 1] = lazy[node];

                tree[node << 1 | 1] = lazy[node];
                tree[(node + 1) << 1] = lazy[node];

                lazy[node] = 0;
            };
        std::function<void(int, int, int ,int , int, int)> _update
            = [&](int l, int r, int node, int L, int R, int val){
                if(l > R || r < L)return;
                if(L<=l && r<=R){
                    lazy[node] = val;
                    tree[node] = val;
                    return;
                }
                int m = l + ((r-l) >> 1);
                _push_down(l, m, r, node);
                if(m >= L)_update(l, m, node << 1| 1, L, R, val);
                if(m < R)_update(m+1, r, (node+1) << 1, L, R, val);
                tree[node] = std::max(tree[node << 1 | 1], tree[(node+1) << 1]);
            };
        std::function<int(int, int, int, int, int)> _query
            = [&](int l, int r, int node, int L, int R){
                if(l > R || r < L)return 0;
                if(L<=l && r<=R)return tree[node];
                int m = l + ((r - l) >> 1);
                _push_down(l, m, r, node);
                int ans = 0;
                if(m >= L)ans = std::max(ans, _query(l, m, node << 1 | 1, L, R));
                if(m <  R)ans = std::max(ans, _query(m+1, r, (node+1) << 1, L, R));
                return ans;
            };
        std::vector<int> res;
        for(auto &p : positions){
            int h = _query(0, code-1, 0, mp[p[0]], mp[p[0]+p[1]-1]) + p[1];
            _update(0, code-1, 0, mp[p[0]], mp[p[0]+p[1]-1], h);
            res.emplace_back(tree[0]);
        }
        return res;
    }
//850. 矩形面积 II
    int rectangleArea(std::vector<std::vector<int>> &rectangles){
        long long MOD = 1e9 + 7, res = 0;
        std::set<int> xs, ys;
        for(auto &p : rectangles){
            xs.insert(p[0]), xs.insert(p[2]);
            ys.insert(p[1]), ys.insert(p[3]);
        }
        std::vector<int> mp1(begin(xs), end(xs)), mp2(begin(ys), end(ys));
        int codex = 0, codey = 0;
        std::unordered_map<int, int>mpx, mpy;
        for(auto &x : xs)mpx[x] = codex++;
        for(auto &y : ys)mpy[y] = codey++;
        std::vector<std::vector<int>> e(codex, std::vector<int>(codey));
        for(auto &p : rectangles){
            for(int i = mpx[p[0]]; i<mpx[p[2]]; ++i){
                for(int j = mpy[p[1]]; j<mpy[p[3]]; ++j)e[i][j] = 1;
            }
        }
        for(int i=0; i<codex; ++i){
            for(int j=0; j<codey; ++j){
                if(!e[i][j])continue;
                res = (res + (long long)(mp1[i+1] - mp1[i]) * (long long)(mp2[j+1] - mp2[j])) % MOD;
            }
        }
        return res;
    }
    public:
//计算右侧小于当前元素的个数
        std::vector<int> countSmaller(std::vector<int> &nums){
            std::unordered_map<int, int> mp;
            std::set<int> st(begin(nums), end(nums));
            int code = 0;
            for(auto &x : st)mp[x] = ++code;
            std::vector<int> tree(code+1);
            std::function<int(int)> _lowbit = [&](int x){
                return x & -x; };
            std::function<void(int, int)> _update = [&](int x, int v){
                for(; x<=code; x+=_lowbit(x))tree[x] += v; };
            std::function<int(int)> _query = [&](int x){
                int ans = 0;
                for(; x ; x-=_lowbit(x))ans += tree[x];
                return ans;
            };
            std::vector<int> res(nums.size());
            for(int i=nums.size()-1; i>=0; --i){
                res[i] = _query(mp[nums[i]]-1);
                _update(mp[nums[i]], 1);
            }
            return res;
        }
//翻转对
        int reversePairs(std::vector<int> &nums){
            using ll = long long;
            std::set<ll> temp;
            for(auto &x : nums)temp.insert(x), temp.insert((ll)x * 2);
            std::unordered_map<ll, int> values;
            int code = 0;
            for(auto &x : temp)values[x] = ++code;
            int n = values.size();
            std::vector<int> tree(n+1);
            std::function<int(ll)> _lowbit = [&](ll x){
                return x & -x; };
            std::function<void(ll, int)> _update = [&](ll x, int v){
                for(; x<=n; x+=_lowbit(x))tree[x] += v; };
            std::function<ll(ll)> _query = [&](ll x){
                ll res = 0;
                for(; x ; x-=_lowbit(x))res += tree[x];
                return res;
            };
            int res = 0;
            for(auto &x : nums){
                res += _query(code) - _query(values[(ll)x* 2]);
                _update(values[x], 1);
            }
            return res;
        }
//327. 区间和的个数
        int countRangeSum(std::vector<int> &nums, int lower, int upper){
            using ll = long long;
            ll sum = 0;
            std::vector<ll> pre_sum {0};
            for(auto &x : nums)pre_sum.emplace_back(sum += x);
            std::set<ll> mp;
            for(auto &x : pre_sum){
                mp.insert(x), mp.insert(x-lower), mp.insert(x-upper);
            }
            int code = 0;
            std::unordered_map<ll, int> values;
            for(auto &x : mp)values[x] = ++code;
            ll n = values.size(), res = 0;
            std::vector<int> tree(n+1);
            std::function<int(int)> _lowbit = [&](int x){
                return x & -x; };
            std::function<void(int, int)> _update = [&](int x, int v){
                for(; x<=n; x+=_lowbit(x))tree[x] += v; };
            std::function<int(int)> _query = [&](int x){
                int res = 0;
                for(; x; x-=_lowbit(x))res += tree[x];
                return res;
            };
            for(int i=0; i<pre_sum.size(); ++i){
                int l = values[pre_sum[i] - upper];
                int r = values[pre_sum[i] - lower];
                res  += _query(r) - _query(l-1);
                _update(values[pre_sum[i]], 1);
            }
            return res;
        }
//5564. 通过指令创建有序数组
        int createSortedArray_seg_tree(std::vector<int> &instructions){
            using ll = long long;
            const int n = *std::max_element(begin(instructions), end(instructions));
            std::vector<int> segnode(n << 2);
            std::function<void(int, int, int, int, int)> _update
                = [&](int v, int x, int node, int l, int r){
                    if(l > x || r < x)return;
                    segnode[node] += v;
                    if(l == r)return ;
                    int m = l + ((r - l) >> 1);
                    _update(v, x, node<<1|1, l, m);
                    _update(v, x, (node+1)<<1, m+1, r);
                };
            std::function<ll(int, int, int, int, int)> _query
                = [&](int L, int R, int node, int l, int r){
                    if(l > R || r < L)return (ll)0;
                    if(L<=l && r<=R)return (ll)segnode[node];
                    int m = l + ((r - l) >> 1);
                    return _query(L, R, node<<1|1, l, m) +
                           _query(L, R, (node+1)<<1, m+1, r);
                };
            ll res = 0, MOD = 1e9 + 7;
            for(auto &x : instructions){
                int lower = _query(1, x-1, 0, 1, n);
                int upper = _query(x+1, n, 0, 1, n);
                res = (res + std::min(lower, upper)) % MOD;
                _update(1, x, 0, 1, n);
            }
            return res;
        }
        int createSortedArray_tree_array(std::vector<int> &instructions){
            using ll = long long;
            int max_ = *std::max_element(begin(instructions), end(instructions));
            int MOD = 1e9 + 7;
            std::vector<int> tree(max_+1);
            std::function<int(int)> _lowbit = [&](int x){
                return x & - x; };
            std::function<void(ll, ll)> _update = [&](ll x, ll v){
                for(;x<=max_; x+=_lowbit(x))tree[x] += v; };
            std::function<ll(ll)> _query = [&](ll x){
                ll res = 0;
                for(; x ; x-=_lowbit(x))res = (res + tree[x]) % MOD;
                return res;
            };
            ll res = 0, len = instructions.size();
            for(int i=0; i<len; ++i){
                int x = instructions[i];
                res  += std::min(_query(x-1), i-_query(x));
                res  %= MOD;
                _update(x, 1);
            }
            return res % MOD;
        }
};
