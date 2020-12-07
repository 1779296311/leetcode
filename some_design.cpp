/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_design.cpp
*     author   : @ JY
*     date     : 2020--10--09
**********************************************/
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <functional>
#include <stdlib.h>
class NestedInteger {
  public:
    bool isInteger() const;
    int getInteger() const;
    const std::vector<NestedInteger> &getList() const;
};

class CombinationIterator{
    public:
        std::string word;
        std::vector<int> pos;
        int f = 1;
        CombinationIterator(std::string characters,
                int c) :word(characters){
            pos.resize(c);
            std::iota(begin(pos), end(pos), 0);
        }
        std::string next(){
            std::string res;
            for(auto &p : pos)res += word[p];
            int i = pos.size() - 1;
            for(; i>=0 && pos[i]==word.size()-pos.size()+i; --i);
            if(i < 0){
                f = 0;
                return res;
            }
            ++pos[i];
            for(int j=i+1; j<pos.size(); ++j)pos[j] = pos[j-1] + 1;
            return res;
        }
        bool hasNext(){
            return f;
        }
};

class WordDictionary{
    public:
        struct _node{
            std::vector<_node *> next;
            bool end = 0;
            _node () : next(26) {}
            ~_node(){
                for(auto x : next)if(x) delete x;
            }
        } *root = new _node();
        WordDictionary(){}
        ~WordDictionary(){delete root;}
        void addWord(std::string word){
            _node *cur = root;
            for(auto &c : word){
                if(!cur->next[c-'a'])cur->next[c-'a'] = new _node();
                cur = cur->next[c-'a'];
            }
            cur->end = 1;
        }
        bool search(std::string word){
            int len = word.size();
            std::function<bool(int, _node*)> _dfs= [&](int i, _node *cur){
                if(!cur)return false;
                if(i == len)return cur->end;
                if(word[i] == '.'){
                    for(int c=0; c<26; ++c){
                        if(_dfs(i+1, cur->next[c])) return true;
                    }
                    return false;
                }else{
                    cur = cur->next[word[i] - 'a'];
                    return _dfs(i+1, cur);
                }
            };
            return _dfs(0, root);
        }
};

//355. 设计推特
class Twitter{
    public:
        int time;
        Twitter() : time(0) {}
        std::unordered_map<int, std::unordered_set<int>> user_follow;
        std::unordered_map<int, std::unordered_map<int, int>> user_post;
        void postTweet(int userId, int tweetId){
            user_post[userId].insert({time++, tweetId});
        }
        std::vector<int> getNewsFeed(int userId){
            std::priority_queue<std::pair<int, int>> q;
            for(auto &p : user_post[userId])q.push(p);
            for(auto &follow_id : user_follow[userId]){
                if(userId == follow_id)continue;
                for(auto &p : user_post[follow_id]){
                    q.push(p);
                }
            }
            std::vector<int> res;
            int k = 10;
            while(k-- && q.size())res.push_back(q.top().second),q.pop();
            return res;
        }
        void follow(int followId, int followeeId){
            user_follow[followId].insert(followeeId);
        }
        void unfollow(int followId, int followeeId){
            user_follow[followId].erase(followeeId);
        }
};
//703. 数据流中的第K大元素
class KthLargest{
    public:
        std::priority_queue<int, std::vector<int>, std::greater<>> small;
        int K;
        KthLargest(int k, std::vector<int> &nums) : K(k){
            for(auto &x : nums){
                if(small.size() < k){
                    small.push(x);
                }else{
                    if(x > small.top()){
                        small.pop();
                        small.push(x);
                    }
                }
            }
        }
        int add(int val){
            if(small.size() < K){
                small.push(val);
            }else{
                if(val > small.top()){
                    small.pop();
                    small.push(val);
                }
            }
            return small.top();
        }
};
//面试题 17.20. 连续中值
class MedianFinder{
    public:
        MedianFinder(){ }
        std::priority_queue<int> big;
        std::priority_queue<int, std::vector<int>, std::greater<>> small;
        void addNum(int num){
            int diff = big.size() > small.size();
            if(big.size() && big.top() > num){
                big.push(num);
                ++diff;
            }else{
                small.push(num);
                --diff;
            }
            if(diff>1)small.push(big.top()), big.pop();
            if(diff<0)big.push(small.top()), small.pop();
        }
        double findMedian(){
            if((big.size() + small.size())&1)return big.top();
            return (big.top() + small.top()) / 2.;
        }
};
//1381. 设计一个支持增量操作的栈
class CustomStack{
    std::vector<int> st;
    int max_;
    CustomStack(int ms) : max_(ms){ }
    void push(int x){
        if(st.size()==max_)return;
        st.push_back(x);
    }
    int pop(){
        if(st.size()){
            int ans = st.back();
            st.pop_back();
            return ans;
        }
        return -1;
    }
    void increment(int k, int val){
        int size = std::min(k, (int)st.size());
        for(int i=0; i<size; ++i)st[i] += val;
    }
};
//341. 扁平化嵌套列表迭代器
class NestedIterator{
    std::vector<int> nums;
    int now = 0;
    NestedIterator(std::vector<NestedInteger> &nextedList){
        std::function<void(std::vector<NestedInteger> &)> _dfs
            = [&](std::vector<NestedInteger> &nl){
            for(auto &x : nl){
                if(x.isInteger()){
                    nums.emplace_back(x.getInteger());
                }else{
                    std::vector<NestedInteger> child = x.getList();
                    _dfs(const_cast<std::vector<NestedInteger> &>(child));
                }
            }
        };
        _dfs(nextedList);
    }
    int next(){
        return nums[now++];
    }
    bool hasNext(){
        return now < nums.size();
    }
};
//面试题 03.02. 栈的最小值
class MinStack {
public:
    std::vector<int> st1;
    std::vector<int> st2;
    MinStack() { st2.push_back(INT_MAX); }
    void push(int x) {
        st1.push_back(x);
        st2.push_back(std::min(x, st2.back()));
    }
    void pop() {
        st2.pop_back();
        st1.pop_back();
    }
    int top() {
        return st1.back();
    }
    int getMin() {
        return st2.back();
    }
};
//901. 股票价格跨度
class StockSpanner{
    StockSpanner(){}
    std::vector<std::pair<int, int>> st;
    int next(int price){
        if(!st.size() || price < st.back().first){
            st.emplace_back(price, 1);
            return 1;
        }
        int k = 1, i = st.size() - 1;
        for( ; i>=0; --i){
            if(st[i].first > price)break;
            ++k;
        }
        st.emplace_back(price, k+st[i+1].second);
        return k;
    }
};
//895. 最大频率栈
class FreqStack {
public:
    FreqStack() : max_(0) { }
    std::map<int, int> mp1;
    std::map<int, std::stack<int>> mp2;
    int max_;
    void push(int x) {
        max_ = std::max(max_, ++mp1[x]);
        mp2[mp1[x]].push(x);
    }
    int pop() {
        int ans = mp2[max_].top();
        --mp1[ans];
        mp2[max_].pop();
        if(!mp2[max_].size())--max_;
        return ans;
    }
};

class Solution{
    public:

};
