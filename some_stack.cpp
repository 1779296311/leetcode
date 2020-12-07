/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_stack.cpp
*     author   : @ JY
*     date     : 2020--10--07
**********************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
#include <cmath>
#include <functional>
#include <sstream>
#include <cstring>
#include <numeric>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <stdlib.h>
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class NestedInteger{
    public:
     NestedInteger();
     NestedInteger(int value);
     bool isInteger() const;
     int getInteger() const;
     void setInteger(int value);
     void add(const NestedInteger &ni);
     const std::vector<NestedInteger> &getList() const;
};
class Solution{
    public:
//1410. HTML 实体解析器
        std::string entityParser(std::string text){
            std::string res;
            std::unordered_map<std::string, std::string> mp = {
                    {"&quot", "\""},{"&apos","\'"},{"&amp", "&"},
                    {"&gt", ">"},{"&lt", "<"},{"&frasl", "/"}
                };
            int len = text.size();
            for(int i=0; i<len; ++i){
                if(text[i]=='&'){
                    int index = text.find(';', i);
                    if(index!=std::string::npos){
                        auto str = text.substr(i, index-i);
                        if(mp.count(str)){
                            res += mp[str];
                            i = index;
                            continue;
                        }
                    }
                }
                res += text[i];
            }
            return res;
        }
//921. 使括号有效的最少添加
        int minAddToMakeValid(std::string S){
            int l = 0, res = 0;;
            for(auto &c : S){
                l += c=='(' ? 1 : -1;
                if(l<0)++res, ++l;
            }
            return res + l;
        }
//1441. 用栈操作构建数组
        std::vector<std::string> buildArray(std::vector<int> &target, int n){
            std::vector<std::string> res;
            int len = target.size();
            int j   = 0;
            for(int i=1; i<=n; ++i){
                res.push_back("Push");
                if(i==target[j]){
                    if(++j==len)break;
                }else{
                    res.push_back("Pop");
                }
            }
            return res;
        }
//591. 标签验证器
        bool isValid(std::string code) {
            std::stack<std::string> st;
            int len = code.size();
            if(len < 7 || code[0]!='<' || code.back()!='>')return false;
            for(int i=0; i<len; ++i){
                if(code[i]=='<'){
                    if(i==len-1){
                        return false;
                    }else if(code[i+1]=='!'){
                        if(!st.size() || i+15>=len)return false;
                        auto DATA = code.substr(i, 9);
                        if(DATA.compare("<![CDATA["))return false;
                        int end = code.find("]]>", i+9);
                        if(end == std::string::npos)return false;
                        i = end + 2;
                    }else{
                        bool _flag = code[i+1]=='/';
                        i += _flag;
                        std::string temp;
                        while(++i<len && code[i] != '>'){
                            if(!std::isupper(code[i])){
                                return false;
                            }else{
                                temp += code[i];
                            }
                        }
                        if(temp.size()<1 || temp.size()>9 || i==len)return false;
                        if(_flag){
                            if(!st.size())return false;
                            if(st.top().compare(temp))return false;
                            st.pop();
                            if(!st.size() && i!=len-1)return false;
                        }else{
                            st.push(temp);
                        }
                    }
                }
            }
            return !st.size();
        }
//1209. 删除字符串中的所有相邻重复项 II
        std::string removeDuplicatesII(std::string s, int k){
            std::string res;
            int len = s.size();
            for(int i=0; i<len; ++i){
                if(res.size()>=k-1 && s[i] ==res.back()){
                    int j = 0;
                    for( ; j<k-1 && res[j+res.size()-k+1]==s[i]; ++j);
                    if(j==k-1){
                        res.erase(res.size()-k+1);
                        continue;
                    }
                }
                res += s[i];
            }
            return res;
        }
//1047. 删除字符串中的所有相邻重复项
        std::string removeDuplicates(std::string S){
            std::string res;
            for(auto & c: S){
                int f = 1;
                while(res.size() && res.back() == c){
                    res.pop_back();
                    f = 0;
                }
                if(f)res += c;
            }
            return res;
        }
//496. 下一个更大元素 I
        std::vector<int> nextGreaterElementI(std::vector<int> &nums1,
                std::vector<int> &nums2){
            int len = nums2.size();
            std::unordered_map<int, int> mp;
            for(int i=0; i<len; ++i)mp[nums2[i]] = i;
            std::vector<int> ans(len, -1);
            std::stack<int> st;
            for(int i=0; i<len; ++i){
                while(st.size() && nums2[st.top()] < nums2[i]){
                    ans[st.top()] = nums2[i];
                    st.pop();
                }
                st.push(i);
            }
            std::vector<int> res;
            for(auto &x : nums1)res.push_back(ans[mp[x]]);
            return res;
        }
//503. 下一个更大元素 II
        std::vector<int> nextGreaterElementsII(std::vector<int> &nums){
            int len = nums.size();
            std::vector<int> res(len, -1);
            std::vector<int> st;
            for(int i=0; i<len*2-1; ++i){
                while(st.size() && nums[st.back()] < nums[i%len]){
                    res[st.back()] = nums[i%len];
                    st.pop_back();
                }
                st.push_back(i%len);
            }
            return res;
        }
//1081. 不同字符的最小子序列
        std::string smallestSubsequence(std::string s){
            std::string res;
            int len = s.size();
            for(int i=0; i<len; ++i){
                if(res.find(s[i]) != std::string::npos)continue;
                while(res.size() && res.back() > s[i]){
                    if(s.find(res.back(), i) == std::string::npos)break;
                    res.pop_back();
                }
                res += s[i];
            }
            return res;
        }
//735. 行星碰撞
        std::vector<int> asteroidCollision(std::vector<int> &asteroids){
            std::vector<int> st;
            for(auto &x : asteroids){
                if(!st.size() || !((x>0) ^ (st.back()>0))){
                    st.emplace_back(x);
                }else{
                    if(st.back() > 0 && x < 0){
                        int _flag = 1;
                        while(st.size() && st.back() > 0){
                            if(abs(st.back()) >= abs(x)){
                                _flag = 0;
                                if(abs(st.back()) == abs(x))st.pop_back();
                                break;
                            }
                            st.pop_back();
                        }
                        if(_flag)st.push_back(x);
                    }else{
                        st.push_back(x);
                    }
                }
            }
            return st;
        }
//316. 去除重复字母
        std::string removeDuplicateLetter(std::string s){
            std::string res;
            int len = s.size();
            for(int i=0; i<len; ++i){
                char c = s[i];
                if(res.find(c) != std::string::npos)continue;
                while(res.size() && res.back() > c){
                    if(s.find(res.back(), i) == std::string::npos)break;
                    res.pop_back();
                }
                res += c;
            }
            return res;
        }
//907. 子数组的最小值之和
        int sumSubarrayMins(std::vector<int> &A){
            A.push_back(0);
            int MOD = 1e9 + 7;
            int len = A.size();
            long long res = 0;
            std::stack<int> st;
            for(int i=0; i<len; ++i){
                while(st.size() && A[st.top()] >= A[i]){
                    int index = st.top();st.pop();
                    int l = index - (st.size() ? st.top() : -1);
                    int r = i - index;
                    res += A[index] * l * r;
                }
                st.push(i);
            }
            return res % MOD;
        }
//150. 逆波兰表达式求值
        int evallRON(std::vector<std::string> &tokens){
            std::stack<int> st;
            for(auto &s : tokens){
                if((s.size()==1 && std::isdigit(s[0])) || s.size()>1){
                    st.push(std::stoi(s));
                    continue;
                }
                int a1 = st.top(); st.pop();
                int a2 = st.top(); st.pop();
                if(s=="-"){
                    st.push(a2 - a1);
                }else if(s=="+"){
                    st.push(a2 + a1);
                }else if(s=="/"){
                    st.push(a2 / a1);
                }else{
                    st.push(a2 * a1);
                }
            }
            return st.top();
        }
//946. 验证栈序列
        bool validateStackSequences(std::vector<int> &pushed, std::vector<int> &popped){
            std::stack<int> st;
            int r = 0;
            for(auto &x : pushed){
                st.push(x);
                while(st.size() && st.top()==popped[r])st.pop(), ++r;
            }
            return !st.size();
        }
//385. 迷你语法分析器
        NestedInteger deserialize(std::string s){
            std::stringstream ss(s);
            std::function<NestedInteger(std::stringstream &)> _dfs = [&](std::stringstream &temp){
                int n;
                if(temp >> n)return NestedInteger(n);
                temp.clear();
                temp.get();
                NestedInteger ans;
                while(temp.peek() != ']'){
                    ans.add(_dfs(temp));
                    if(temp.peek() == ',')temp.get();
                }
                temp.get();
                return ans;
            };
            return _dfs(ss);
        }
        NestedInteger deserialize_stack(std::string s){
            std::function<int(std::string &)> _stoi = [&](std::string &num){
                int res = 0, i = 0, f = 1;
                if(num[0]=='-')++i, f = -1;
                for( ; i<num.size(); ++i)res = res * 10 + num[i] - '0';
                return res * f;
            };
            int len = s.size();
            if(!len)return NestedInteger();
            if(s[0] != '[')return NestedInteger(_stoi(s));
            std::string temp;
            std::stack<NestedInteger> st;
            for(auto &c : s){
                if(c=='['){
                    st.push(NestedInteger());
                }else if(c=='-' || std::isdigit(c)){
                    temp += c;
                }else if(c==',' && temp.size()){
                    st.top().add(NestedInteger(_stoi(temp)));
                    temp.clear();
                }else if(c==']'){
                    if(temp.size()){
                        st.top().add(NestedInteger(_stoi(temp)));
                        temp.clear();
                    }
                    if(st.size() > 1){
                        auto now = st.top();st.pop();
                        st.top().add(now);
                    }
                }
            }
            return st.top();
        }
//880. 索引处的解码字符串
        std::string decodeAtIndex(std::string S, int K){
            long long size = 0;
            int len  = S.size();
            for(auto &c: S){
                if(std::isdigit(c)){
                    size *= c - '0';
                }else{
                    ++size;
                }
            }
            for(int i=len-1; i>=0; --i){
                if(!(K%=size) && std::isalpha(S[i]))return {S[i]};
                if(std::isdigit(S[i]))size /= S[i] - '0';
                if(!std::isdigit(S[i]))--size;
            }
            return "";
        }
        std::string decodeAtIndex_fuck(std::string S, int K){
            std::string temp;
            int len = S.size();
            int num = 0;
            for(int i=0; i<len; ++i){
                if(std::isalpha(S[i])){
                    temp += S[i];
                }else{
                    int n  = S[i] - '0';
                    auto t = temp;
                    for(int i=1; i<n; ++i)temp += t;
                }
                if(temp.size() >= K)return {temp[K-1]};
            }
            return "";
        }
//71. 简化路径
        std::string simplifyPath(std::string path){
            std::string temp;
            std::stringstream ss(path);
            std::vector<std::string> st;
            while(std::getline(ss, temp, '/')){
                if(!temp.size())continue;
                if(temp==".")continue;
                if(temp==".."){
                    if(st.size())st.pop_back();
                }else{
                    st.emplace_back(temp+'/');
                }
            }
            std::string res = "/";
            for(auto &s : st)res += s;
            if(res.size()>1)res.pop_back();
            return res;
        }
//1249. 移除无效的括号
        std::string minRemoveToValid(std::string s){
            int l = 0, r = 0;
            std::vector<int> left;
            std::unordered_set<int> mp;
            int len = s.size();
            for(int i=0; i<len; ++i){
                if(s[i]=='(')++l, left.emplace_back(i);
                if(s[i]==')')++r;
                if(r > l)mp.insert(i),--r;
            }
            while(l-- > r){
                mp.insert(left.back());
                left.pop_back();
            }
            std::string res;
            for(int i=0; i<len; ++i){
                if(!mp.count(i))res += s[i];
            }
            return res;
        }
        int oddEvenJumps(std::vector<int> &A){
            int len = A.size();
            std::vector<int> a1(len);
            for(int i=0; i<len; ++i)a1[i] = i;
            std::function<void(std::vector<int> &)> _calc = [&](std::vector<int> &arr){
                std::stack<int> st;
                for(int i=0; i<len; ++i){
                    while(st.size() && st.top() < a1[i]){
                        arr[st.top()] = a1[i];
                        st.pop();
                    }
                    st.push(a1[i]);
                }
            };
            std::vector<int> bi(len, -1), sm(len, -1);
            std::sort(begin(a1), end(a1), [&](int i, int j){
                    return A[i] == A[j] ? i < j : A[i] < A[j]; });
            _calc(bi);
            std::sort(begin(a1), end(a1), [&](int i, int j){
                    return A[i] == A[j] ? i < j : A[i] > A[j]; });
            _calc(sm);
            std::vector<int> co(len), ce(len);
            co[len-1] = 1, ce[len-1] = 1 ;
            for(int i=len-2; i>=0; --i){
                int c1 = bi[i], c2 = sm[i];
                if(c1!=-1)ce[i] = co[c1];
                if(c2!=-1)co[i] = ce[c2];
            }
            int res = 0;
            for(int i=0; i<len; ++i)res += co[i];
            return res;
        }
        int oddEvenJumps_fuck(std::vector<int> &A){
            int len = A.size();
            std::vector<std::pair<int, int>> mp(len, {-1, -1});
            for(int i=0; i<len; ++i){
                for(int j=i+1; j<len; ++j){
                    if(A[j]>=A[i] && (mp[i].first==-1 || A[j] < A[mp[i].first])){
                        mp[i].first = j;
                    }
                    if(A[j]<=A[i] && (mp[i].second==-1 || A[j] > A[mp[i].second])){
                        mp[i].second = j;
                    }
                }
            }
            int res = 0, d = 0, next;
            for(int i=0; i<len; ++i){
                d = 1, next = i;
                while(1){
                    if(next==len-1){
                        ++res;
                        break;
                    }
                    if(next==-1)break;
                    d ? next = mp[next].first : next = mp[next].second;
                    d ^= 1;
                }
            }
            return res;
        }
//1021. 删除最外层的括号
        std::string removeOuterPartenthese(std::string S){
            std::string res;
            int len = S.length();
            int cnt = 0, left = 0;
            for(int i=0; i<len; ++i){
                char c = S[i];
                if(!cnt)left = i;
                if(c=='(')++cnt;
                if(c==')')--cnt;
                if(!cnt)res += S.substr(left+1, i-left-1);
            }
            return res;
        }
//1019. 链表中的下一个更大节点
        std::vector<int> nextLargerNodes(ListNode *head){
            std::stack<std::pair<int, int>> st;
            std::vector<int> res(100001);
            int size = 0;
            while(head){
                while(st.size() && st.top().first < head->val){
                    res[st.top().second] = (head->val);
                    st.pop();
                }
                st.push({head->val, size++});
                head = head->next;
            }
            return {res.begin(), res.begin()+size};
        }
//1190. 反转每对括号间的子串
        std::string reverseParentheses(std::string s){
            int len = s.size();
            std::string res;
            std::stack<int> st;
            for(int i=0; i<len; ++i){
                if(s[i]=='('){
                    st.push(i+1);
                }else if(s[i]==')'){
                    std::reverse(s.begin()+st.top(), s.begin() + i);
                    st.pop();
                }
            }
            for(auto &c : s){
                if(std::isalpha(c))res += c;
            }
            return res;
        }
        std::string reverseParentheses_better(std::string s){
            int len = s.size();
            std::vector<int> mp(len);
            std::stack<int> st;
            for(int i=0; i<len; ++i){
                if(s[i] == '('){
                    st.push(i);
                }else if(s[i] == ')'){
                    int l = st.top();st.pop();
                    mp[i] = l;
                    mp[l] = i;
                }
            }
            std::string res;
            for(int i=0, f=1; i<len; i+=f){
                if(!std::isalpha(s[i])){
                    i = mp[i];
                    f = -f;
                }else{
                    res += s[i];
                }
            }
            return res;
        }
//856. 括号的分数
        int scoreOfParentheses(std::string S){
            std::stack<int> st; st.push(0);
            for(auto &c : S){
                if(c=='('){
                    st.push(0);
                }else{
                    if(!st.top()){
                        st.pop();
                        st.push(1);
                    }else{
                        int t = 0;
                        while(st.top())t += st.top(), st.pop();
                        st.pop();
                        st.push(t<<1);
                    }
                }
            }
            int res = 0;
            while(st.size())res += st.top(), st.pop();
            return res;
        }
//636. 函数的独占时间
        std::vector<int> exclusiveTime(int n, std::vector<std::string> &logs){
            std::stack<int> st;
            std::stringstream ss;
            std::string cur0, cur1, cur2;
            int c0, c2;
            std::vector<int> res(n, 0);
            int pre = 0;
            for(auto &s : logs){
                ss.clear(); ss.str(s);
                std::getline(ss, cur0, ':');
                std::getline(ss, cur1, ':');
                std::getline(ss, cur2, ':');
                c0 = std::stoi(cur0), c2 = std::stoi(cur2);
                if(!st.size()){
                    st.push(c0);
                    pre = c2;
                    continue;
                }
                if(!cur1.compare("start")){
                    res[st.top()] += c2 - pre;
                    st.push(c0);
                    pre = c2;
                }else{
                    res[c0] += c2 - pre + 1;
                    st.pop();
                    pre = c2 + 1;
                }
            }
            return res;
        }
//331. 验证二叉树的前序序列化
        bool isValidSerialization(std::string preorder){
            std::stringstream ss(preorder);
            std::string temp;
            int solts = 1;
            while(std::getline(ss, temp, ',')){
                if(--solts < 0)return false;
                if(temp[0]!='#')++solts, ++solts;
            }
            return !solts;
        }
//456. 132模式
        bool find132pattern(std::vector<int> &nums){
            std::stack<int> st;
            int b   = INT_MIN;
            int len = nums.size();
            for(int i=len-1; i>=0; --i){
                if(b > nums[i])return true;
                while(st.size() && st.top() < nums[i]){
                    b = st.top();
                    st.pop();
                }
                st.push(nums[i]);
            }
            return false;
        }
//1130. 叶值的最小代价生成树
        int mcFromLeafValues(std::vector<int> &arr){
            int len = arr.size();
            std::vector<std::vector<int>> dp(len, std::vector<int>(len));
            for(int j=0; j<len; ++j){
                for(int i=j; i>=0; --i){
                    if(i==j)continue;
                    if(j-i==1){
                        dp[i][j] = arr[i] * arr[j];
                        continue;
                    }
                    dp[i][j] = INT_MAX;
                    for(int k=i; k<j; ++k){
                        int sum = *max_element(begin(arr)+i, begin(arr)+k+1) *
                                  *max_element(begin(arr)+k+1, begin(arr)+j+1);
                        dp[i][j] = std::min(dp[i][j], sum + dp[i][k] + dp[k+1][j]);
                    }
                }
            }
            return dp[0][len-1];
        }
//682. 棒球比赛
        int calPoints(std::vector<std::string> &ops){
            std::vector<int> st;
            for(auto &c : ops){
                int len = st.size();
                if(c=="+"){
                    st.emplace_back(st[len-1] + st[len-2]);
                }else if(c=="D"){
                    st.emplace_back(st[len-1] * 2);
                }else if(c=="C"){
                    st.pop_back();
                }else{
                    st.emplace_back(std::stoi(c));
                }
            }
            return std::accumulate(begin(st), end(st), 0);
        }
//84. 柱状图中最大的矩形
        int largestREctangleArea(std::vector<int> &heights){
            heights.emplace_back(0);
            int len = heights.size(), res = 0;
            std::stack<int> st;
            for(int i=0; i<len; ++i){
                while(st.size() && heights[st.top()] >= heights[i]){
                    int m = st.top();st.pop();
                    int l = st.size() ? st.top() : -1;
                    res   = std::max(res, heights[m] * (i-l-1));
                }
                st.push(i);
            }
            return res;
        }
//003. 检查替换后的词是否有效
        bool isValid(std::string s){
            if(s.size() % 3)return false;
            std::vector<char> st;
            st.emplace_back('*');
            st.emplace_back('*');
            int len;
            for(auto &c : s){
                len = st.size();
                if(c=='c'){
                    if(st[len-1]!='b' || st[len-2]!='a')return false;
                    st.pop_back();
                    st.pop_back();
                }else{
                    st.emplace_back(c);
                }
            }
            return st.size() == 2;
        }
//1124. 表现良好的最长时间段
        int longestWPI_better(std::vector<int> &hours){
            int len = hours.size(), res = 0;
            std::vector<int> sum(len+1);
            std::unordered_map<int, int> mp;
            for(int i=0; i<len; ++i){
                sum[i+1] = (hours[i] > 8 ? 1 : -1) + sum[i];
                if(sum[i+1] > 0){
                    res = i + 1;
                }else if(mp.count(sum[i+1] - 1)){
                    res = std::max(res, i - mp[sum[i+1]-1]);
                }
                if(!mp.count(sum[i+1]))mp[sum[i+1]] = i;
            }
            return res;
        }
        int longestWPI(std::vector<int> &hours){
            int len = hours.size();
            std::vector<int> sum(len+1, 0);
            std::stack<int> st;
            for(int i=0; i<len; ++i){
                sum[i+1] = (hours[i]>8?1:-1) + sum[i];
                if(!st.size() || sum[st.top()] > sum[i])st.push(i);
            }
            int res = 0;
            for(int i=len; i>=0; --i){
                while(st.size() && sum[i] > sum[st.top()]){
                    res = std::max(res, i - st.top());
                    st.pop();
                }
            }
            return res;
        }
};
