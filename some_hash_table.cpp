/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_hash_table.cpp
*     author   : @ JY
*     date     : 2020--09--24
**********************************************/
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <cmath>
#include <numeric>
#include <sstream>
#include <algorithm>
#include <functional>
#include <string_view>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <queue>
#include <sstream>
#include <cctype>
#include <cstring>
#include <stdlib.h>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
#define string_view string
class Solution{
//726. 原子的数量
    std::string countOfAtoms(std::string formula){
        struct _cmp{
            bool operator()(const std::string &a, const std::string &b) const{
                return a < b; }
        };
        int size = formula.size();
        using  mstr = std::map<std::string, long long, _cmp>;
        std::map<std::string, long long,_cmp> mp;
        std::function<void(int &, mstr &)> _calc = [&](int &i, mstr &ans){
                while(i < size){
                    if(formula[i]=='('){
                        mstr temp;
                        _calc(++i, temp);
                        ++i;
                        long long f = 0;
                        while(i<size && std::isdigit(formula[i])){
                            f = f * 10 + formula[i] - '0';
                            ++i;
                        }
                        if(!f)++f;
                        for(auto &[w, n] : temp)ans[w] += f * n;
                    }else if(formula[i]==')'){
                        break;
                    }else{
                        int be = i++;
                        while(i<size && std::isalpha(formula[i]) && std::islower(formula[i]))++i;
                        std::string wd = formula.substr(be, i-be);
                        long long f = 0;
                        while(i<size && std::isdigit(formula[i])){
                            f = f * 10 + formula[i] - '0';
                            ++i;
                        }
                        if(!f)++f;
                        ans[wd] += f;
                    }
                }
            };
        int i = 0;
        _calc(i, mp);
        std::string res;
        for(auto &&[wd, n] : mp){
            res += wd;
            if(n>1)res += std::to_string(n);
        }
        return res;
    }
//49. 字母异位词分组
    std::vector<std::vector<std::string>> groupAnagramsII(std::vector<std::string> &strs){
        std::unordered_map<double, std::vector<std::string>> mp;
        std::vector<int> a = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101};
        for(auto &w : strs){
            double temp = 1;
            for(auto &c : w)temp *= a[c-'a'];
            mp[temp].push_back(w);
        }
        std::vector<std::vector<std::string>> res;
        for(auto &[w, v] : mp)res.push_back(v);
        return res;
    }
//1189. “气球” 的最大数量
    int maxNumberOfBallboons(std::string text){
        std::vector<int> mp(26);
        for(auto &c : text)++mp[c-'a'];
        int res = INT_MAX;
        res = std::min(res, mp['a'-'a']);
        res = std::min(res, mp['b'-'a']);
        res = std::min(res, mp['n'-'a']);
        res = std::min(res, mp['l'-'a']/2);
        res = std::min(res, mp['o'-'a']/2);
        return res;
    }
//632. 最小区间
    std::vector<int> smallestRange_slip_window(std::vector<std::vector<int>> &nums){
        int size = nums.size();
        std::unordered_map<int, std::vector<int>> mp;
        int minl = INT_MAX, maxr = INT_MIN;
        for(int i=0; i<size; ++i){
            for(auto &x : nums[i]){
                mp[x].push_back(i);
                minl = std::min(minl, x);
                maxr = std::max(maxr, x);
            }
        }
        std::vector<int> hs(size);
        int resl = 0, resr = INT_MAX;
        int left = minl, right = minl - 1;
        while(right < maxr){
            if(mp.count(++right)){
                for(auto &x : mp[right]){
                    if(++hs[x] == 1)--size;
                }
                while(!size){
                    if(right-left < resr-resl){
                        resl = left;
                        resr = right;
                    }
                    if(mp.count(left)){
                        for(auto &x : mp[left]){
                            if(!--hs[x])++size;
                        }
                    }
                    while(left<right && !mp.count(++left));
                }
            }
        }
        return {resl, resr};
    }
    std::vector<int> smallestRange_priority_queue(std::vector<std::vector<int>> &nums){
        int n = nums.size();
        std::vector<int> next(n);
        auto _cmp = [&](const int a, const int b){
            return nums[a][next[a]] > nums[b][next[b]]; };
        std::priority_queue<int, std::vector<int>, decltype(_cmp)> q(_cmp);
        int maxr = 0;
        for(int i=0; i<n; ++i){
            q.push(i);
            maxr = std::max(maxr, nums[i][0]);
        }
        int resl = 0, resr = INT_MAX;
        while(1){
            int pos = q.top();q.pop();
            if(resr-resl < maxr-nums[pos][next[pos]]){
                resr = maxr;
                resl = nums[pos][next[pos]];
            }
            if(next[pos]==nums[pos].size()-1)break;
            maxr = std::max(maxr, nums[pos][++next[pos]]);
            q.push(pos);
        }
        return {resl, resr};
    }
//781. 森林中的兔子
    int numRabbits(std::vector<int> &answers){
        int res = 0;
        std::unordered_map<int, int> mp;
        for(auto &x : answers)++mp[x];
        for(auto &&[x, n] : mp){
            res += (x+n)/(x+1)*(x+1);
        }
        return res;
    }
//748. 最短补全词
    std::string shorestCompletingWord(std::string licensePlate, std::vector<std::string> &words){
        std::unordered_map<char, int> mp;
        int all = 0;
        for(auto c : licensePlate){
            if(!isalpha(c))continue;
            ++mp[tolower(c)];
            ++all;
        }
        std::string res;
        std::stable_sort(begin(words), end(words), [&](auto &a, auto &b){
                return a.size()<b.size(); });
        std::unordered_map<char, int> temp;
        int need = all;
        for(auto &w : words){
            temp = mp;
            need = all;
            for(auto &c : w){
                if(--temp[c] >= 0)--need;
                if(!need)return w;
            }
        }
        return "";
    }
//447. 回旋镖的数量
    int numOfBoomerangs(std::vector<std::vector<int>> &points){
        int res  = 0;
        int size = points.size();
        for(int i=0; i<size; ++i){
            int x = points[i][0];
            int y = points[i][1];
            std::unordered_map<long long, int> mp;
            for(int j=0; j<size; ++j){
                if(i==j)continue;
                long long d = pow(x-points[j][0], 2) + pow(y-points[j][1], 2);
                ++mp[d];
            }
            for(auto &[d, n] : mp)res += n*(n-1);
        }
        return res;
    }
//1418. 点菜展示表
    std::vector<std::vector<std::string>> displayTable(std::vector<std::vector<std::string>> &orders){
        struct _cmp{
            bool operator()(const std::string &a, const std::string &b) const {
                return stoi(a) > stoi(b); }
        };
        std::unordered_set<std::string> mp;
        std::map<std::string, std::unordered_map<std::string, int>, _cmp> ord;
        std::stringstream ss;
        for(auto &ta : orders){
            ++ord[ta[1]][ta[2]];
            mp.insert(ta[2]);
        }
        std::vector<std::vector<std::string>> res;
        std::vector<std::string> head;
        head.push_back("Table");
        for(auto &w : mp)head.push_back(w);
        std::sort(head.begin()+1, head.end());
        res.push_back(head);
        for(auto &[n, v] : ord){
            std::vector<std::string> temp;
            temp.push_back(n);
            for(int i=1; i<head.size(); ++i){
                temp.push_back(std::to_string(v[head[i]]));
            }
            res.push_back(temp);
        }
        return res;
    }
//575. 分糖果
    int distributeCandies(std::vector<int> &candies){
        return std::min(std::set<int>(begin(candies), end(candies)).size(), candies.size()/2);
    }
//166. 分数到小数
    std::string fractionToDecimal(int numerator, int denominator){
        if(!numerator || !denominator)return "0";
        std::string res;
        long long num = static_cast<long long>(numerator);
        long long den = static_cast<long long>(denominator);
        if((num>0) ^ (den>0))res.push_back('-');
        num = llabs(num);
        den = llabs(den);
        res.append(std::to_string(num/den));
        if(!(num %= den))return res;
        res.push_back('.');
        int i = res.size() - 1;
        std::unordered_map<int, int> mp;
        while(num && !mp.count(num)){
            mp[num] = ++i;
            num *= 10;
            res += std::to_string(num / den);
            num %= den;
        }
        if(mp.count(num)){
            res.insert(mp[num], "(");
            res.push_back(')');
        }
        return res;
    }
//438. 找到字符串中所有字母异位词
    std::vector<int> findAnagrams(std::string s, std::string p){
        int lens = s.size();
        int lenp = p.size();
        if(lens < lenp)return {};
        std::unordered_map<char, int> need;
        for(char c : p)++need[c];
        std::vector<int> res;
        int dif = lenp;
        for(int i=0; i<lenp; ++i){
            if(--need[s[i]] >=0)--dif;
        }
        for(int i=lenp; i<lens; ++i){
            if(!dif)res.push_back(i-lenp);
            if(--need[s[i]] >= 0)--dif;
            if(++need[s[i-lenp]] > 0)++dif;
        }
        if(!dif)res.push_back(lens-lenp);
        return res;
    }
//930. 和相同的二元子数组
    int numSubarrayWithSum(std::vector<int> &A, int S){
        int res = 0;
        int sum = 0;
        std::unordered_map<int, int> mp = {{0, 1}};
        for(auto &x : A){
            sum += x;
            res += mp[sum - S];
            ++mp[sum];
        }
        return res;
    }
//811. 子域名访问计数
    std::vector<std::string> subdomainVisits(std::vector<std::string> &cpdomains){
        using vs = std::vector<std::string>;
        std::function<vs(std::string &)> _calc
            = [&](std::string &s){
                std::vector<std::string> ans;
                int pos = s.find('.');
                std::string res2 = s.substr(pos+1);
                if(std::string::npos==(pos=res2.find('.')))return vs{s, res2};
                std::string res3 = res2.substr(pos+1);
                return vs{s, res2, res3};
        };
        std::unordered_map<std::string, int> mp;
        std::stringstream ss;
        std::string num;
        std::string cpd;
        for(auto &p : cpdomains){
            ss.clear();
            ss.str(p);
            ss >> num;
            ss >> cpd;
            auto _list = _calc(cpd);
            for(auto &w : _list)mp[w] += stoi(num);
        }
        vs res;
        for(auto &[w, n] : mp)res.push_back(std::to_string(n)+" "+w);
        return res;
    }
//36. 有效的数独
    bool isValidSudoku(std::vector<std::vector<char>> &board){
        std::vector<int> row(9);
        std::vector<int> col(9);
        std::vector<std::vector<int>> mat(3, std::vector<int>(3, 0));
        for(int i=0; i<9; ++i){
            for(int j=0; j<9; ++j){
                if(board[i][j]=='.')continue;
                int k = (1<<(board[i][j] - '0'));
                if(row[i] & k)return false;
                row[i] |= k;
                if(col[j] & k)return false;
                col[j] |= k;
                if(mat[i/3][j/3] & k)return false;
                mat[i/3][j/3] |= k;
            }
        }
        return true;
    }
//1138. 字母板上的路径
    std::string alphabetBoardPath(std::string target){
        std::string res;
        int cur_i = 0, cur_j = 0;
        int mov_i = 0, mov_j = 0;
        for(auto &c : target){
            int i = (c-'a') / 5;
            int j = (c-'a') % 5;
            mov_i = i - cur_i;
            mov_j = j - cur_j;
            cur_i = i;
            cur_j = j;
            if(c=='z' && cur_j!=0 && mov_i){
                res += std::string(mov_i-1, 'D');
                res += std::string(abs(mov_j), 'L');
                res += "D!";
                continue;
            }
            auto ud = std::string(abs(mov_i), mov_i>0?'D':'U');
            auto lr = std::string(abs(mov_j), mov_j>0?'R':'L');
            res += ud + lr + '!';
        }
        return res;
    }
//692. 前K个高频单词
    std::vector<std::string> topKFrequent(std::vector<std::string> &words, int k){
        std::vector<std::string> res;
        std::unordered_map<std::string, int> mp;
        for(auto &w : words)++mp[w];
        std::vector<std::pair<std::string, int>> temp(begin(mp), end(mp));
        std::sort(temp.begin(), temp.end(), [&](const auto &a, const auto &b){
                return a.second==b.second?a<b:a.second > b.second; });
        for(int i=0; i<k; ++i)res.push_back(temp[i].first);
        return res;
    }
//500. 键盘行
    std::vector<std::string> findWords(std::vector<std::string> &words){
        std::vector<std::string> res;
        std::unordered_set<char> mp1 = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'};
        std::unordered_set<char> mp2 = {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l'};
        std::unordered_set<char> mp3 = {'z', 'x', 'c', 'v', 'b', 'n', 'm'};
        for(auto &w : words){
            int state = 0;
            for(auto &c : w){
                if(mp1.count(c))state |= 1<<1;
                if(mp2.count(c))state |= 1<<2;
                if(mp3.count(c))state |= 1<<3;
                if(__builtin_popcount(state) > 1)break;
            }
            if(__builtin_popcount(state) > 1)continue;
            res.push_back(w);
        }
        return res;
    }
//1078. Bigram 分词
    std::vector<std::string> findOccurrences(std::string text, std::string first, std::string second){
        std::vector<std::string> res;
        std::stringstream ss(text);
        std::string pre, ppre, now;
        ss >> ppre;
        ss >> pre;
        while(ss >> now){
            if(!ppre.compare(first) && !pre.compare(second)){
                res.push_back(now);
            }
            ppre = pre;
            pre  = now;
        }
        return res;
    }
//1072. 按列翻转得到最大值等行数
    int amxEqualRowAfterFlips(std::vector<std::vector<int>> &matrix){
        std::unordered_map<std::string, int> mp;
        int res = 0;
        for(auto &s : matrix){
            int x = s[0] ^ 0;
            std::string temp;
            for(auto &c : s)temp += (c^x) + '0';
            res = std::max(res, ++mp[temp]);
        }
        return res;
    }
//299. 猜数字游戏
    std::string getHint(std::string secret, std::string guess){
        int a = 0;
        int b = 0;
        std::unordered_map<char, int> mp;
        for(auto &c : secret)++mp[c];
        int len = secret.size();
        for(int i=0; i<len; ++i){
            a += secret[i]==guess[i];
            b += --mp[guess[i]]>=0;
        }
        return std::to_string(a) + "A" + std::to_string(b-a) + "B";
    }
//970. 强整数
    std::vector<int> powerfulIntegers(int x, int y, int bound){
        std::unordered_set<int> mp;
        for(int i=0; i<20; ++i){
            int l = (int)pow(x, i);
            if(l > bound)break;
            for(int j=0; j<20; ++j){
                int r = (int)pow(y, j);
                if(l+r > bound)break;
                mp.insert(l+r);
            }
        }
        std::vector<int> res(begin(mp), end(mp));
        return res;
    }
//290. 单词规律
    bool wordPattert(std::string pattern, std::string s){
        std::stringstream ss(s);
        std::string temp;
        std::unordered_map<char, std::string> mp1;
        std::unordered_map<std::string, char> mp2;
        for(auto &c : pattern){
            if(!(ss>>temp))return false;
            if(mp1.count(c) && mp1[c]!=temp)return false;
            if(mp2.count(temp) && mp2[temp]!=c)return false;
            mp2[mp1[c]=temp] = c;
        }
        return (ss>>temp)?false:true;
    }
//1178. 猜字谜
    std::vector<int> findNumOfValidWords(std::vector<std::string> &words,
            std::vector<std::string> &puzzles){
        std::unordered_map<int, int> mp;
        int psize = puzzles.size();
        std::vector<int> bit(psize, 0);
        for(int i=0; i<psize; ++i){
            for(auto &c : puzzles[i]){
                bit[i] |= (1<<(c-'a'));
            }
        }
        int size = words.size();
        for(int i=0; i<size; ++i){
            int state = 0;
            for(auto &c : words[i]){
                state |= (1<<(c-'a'));
                if(state==(1<<26)-1)break;
            }
            ++mp[state];
        }
        std::vector<int> res(psize);
        for(int i=0; i<psize; ++i){
            for(int j=bit[i]; j; j=(j-1)&bit[i]){
                if(j&(1<<(puzzles[i][0]-'a'))){
                    res[i] += mp[j];
                }
            }
        }
        return res;
    }
//242. 有效的字母异位词
    bool isAnagram(std::string s, std::string t){
        if(s.size() != t.size())return false;
        std::unordered_map<char, int> mp;
        for(auto &c : t)++mp[c];
        for(auto &c : s)if(!mp[c]--)return false;
        return true;
    }
//1224. 最大相等频率
    int maxEqualFreq(std::vector<int> &nums){
        std::unordered_map<int, int> a;
        std::unordered_map<int, int> b;
        int max_ = 0;
        int res  = 0;
        int kind = 0;
        for(int i=0; i<nums.size(); ++i){
            auto x = nums[i];
            if(++a[x]==1)++kind;
            max_ = std::max(max_, a[x]);
            ++b[a[x]];
            if(a[x] > 1)--b[a[x]-1];
            if(max_==1 || b[1]==kind ||
              (b[max_]==1 && b[max_-1]==kind-1) ||
              (b[1]==1 && b[max_]==kind-1)){
                res = i + 1;
            }
        }
        return res;
    }
//957. N 天后的牢房
    std::vector<int> prisoAfterNDays(std::vector<int> &cells, int N){
        int state = 0;
        int loop  = 1;
        std::unordered_map<int, int> st_da;
        std::unordered_map<int, int> da_st;
        for(int i=0; i<8; ++i)state |= (cells[i]<<i);
        da_st[0] = state;
        st_da[state] = 0;
        for(int i=1; i<=N; ++i){
            int new_state = 0;
            for(int t=1; t<7; ++t){
                int l = (1&(state>>(t+1)));
                int r = (1&(state>>(t-1)));
                if(l==r)da_st[i] |= (1<<t);
            }
            state = new_state;
            if(st_da.count(da_st[i]=state)){
                loop = i - st_da[state];
                break;
            }
            st_da[state] = i;
        }
        state = da_st[N-(N-st_da[state])/loop*loop];
        std::vector<int> res(8, 0);
        for(int i=1; i<7; ++i)res[i] = state>>i&1;
        return res;
    }
//939. 最小面积矩形
    int minAreaRect(std::vector<std::vector<int>> &points){
        std::unordered_set<int> mp;
        for(auto &p : points)mp.insert(40001*p[0] + p[1]);
        int res  = INT_MAX;
        int size = points.size();
        for(int i=0; i<size; ++i){
            for(int j=i+1; j<size; ++j){
                int x1 = points[i][0];
                int y1 = points[i][1];
                int x2 = points[j][0];
                int y2 = points[j][1];
                if(x1!=x2 && y1!=y2 && mp.count(x1*40001+y2) && mp.count(x2*40001+y1)){
                    res = std::min(res, abs(x1-x2)*abs(y1-y2));
                }
            }
        }
        return res==INT_MAX?0:res;
    }
//961. 重复 N 次的元素
    int repeatNTimes(std::vector<int> &A){
        for(int i=1; i<A.size(); ++i){
            if(!(A[i] ^ A[i-1]))return A[i];
        }
        if(A[0]==A[2] || A[0]==A[3])return A[0];
        return A[1];
    }
//409. 最长回文串
    int longestOalidrome(std::string s){
        int res = 0;
        std::unordered_map<char, int> mp;
        for(auto &c : s)++mp[c];
        for(auto &[c, v] : mp){
            res += v / 2 * 2;
            if(v&1 && !(res&1))++res;
        }
        return res;
    }
//720. 词典中最长的单词
    std::string longestWord(std::vector<std::string> &words){
        std::sort(words.begin(), words.end(),[&](auto &a, auto &b){
            return a.size()==b.size()?a<b:a.size() > b.size(); });
        std::unordered_set<std::string> mp(words.begin(), words.end());
        std::function<bool(std::string &w, int)> _dfs
            = [&](std::string &word, int len){
                if(len==word.size())return true;
                return mp.count(word.substr(0, len)) && _dfs(word, len+1);
            };
        for(auto &wd : words)if(_dfs(wd, 1))return wd;
        return "";
    }
//面试题 01.04. 回文排列
    bool canPermutePalidrome(std::string s){
        std::unordered_map<char, int> mp;
        for(auto &c : s)++mp[c];
        int res = 0;
        for(auto &[c, n] : mp){
            if(!(n&1))continue;
            if(++res>1)return false;
        }
        return true;
    }
//1048. 最长字符串链
    int longestStrChain(std::vector<std::string> &words){
        std::sort(words.begin(), words.end(), [&](auto &a, auto&b){
                return a.size() < b.size(); });
        int wsize = words.size();
        std::unordered_map<std::string, int> mp;
        std::vector<int> dp(wsize, 1);
        std::string temp;
        int res = 1;
        for(int i=0; i<wsize-1; ++i){
            int j = i + 1;
            mp[words[i]] = i;
            if(words[j].size() - words[i].size() > 1)continue;
            for(int k=0; k<words[j].size(); ++k){
                temp = words[j].substr(0, k) + words[j].substr(k+1);
                if(!mp.count(temp))continue;
                dp[j] = std::max(dp[j], dp[mp[temp]] + 1);
                res   = std::max(res, dp[j]);
            }
        }
        return res;
    }
//336. 回文对
    std::vector<std::vector<int>> palidromePairs_tire(std::vector<std::string> &words){
        struct _node{
            int ch[26];
            int end;
            _node() : end(-1){
                memset(ch, 0, sizeof ch);
            }
        };
        std::vector<_node> tree = {_node()};
        std::function<void(std::string &, int)> _insert
            = [&](std::string &word, int id){
                int index = 0;
                for(auto &c : word){
                    int i = c - 'a';
                    if(!tree[index].ch[i]){
                        tree.emplace_back();
                        tree[index].ch[i] = tree.size() - 1;
                    }
                    index = tree[index].ch[i];
                }
                tree[index].end = id;
            };
        std::function<int(std::string &, int, int)> _find_rev
            = [&](std::string &word, int left, int right){
                int index = 0;
                for(int i=right; i>=left; --i){
                    int x = word[i] - 'a';
                    if(!tree[index].ch[x])return -1;
                    index = tree[index].ch[x];
                }
                return tree[index].end;
            };
        std::function<bool(const std::string &, int , int)> _is_palidome
            = [&](const std::string &word, int left, int right){
                if(left>=right)return true;
                while(left<right){
                    if(word[left++] != word[right--])return false;
                }
                return left>=right;
            };
        int wsize = words.size();
        for(int i=0; i<wsize; ++i)_insert(words[i], i);
        std::vector<std::vector<int>> res;
        int size = 0;
        for(int i=0; i<wsize; ++i){
            if(!(size=words[i].size()))continue;
            auto temp = words[i];
            for(int j=0; j<=size; ++j){
                if(_is_palidome(temp, j, size-1)){
                    int r = _find_rev(temp, 0, j-1);
                    if(r!=-1 && r!= i)res.push_back({i, r});
                }
                if(_is_palidome(temp, 0, j)){
                    int l = _find_rev(temp, j+1, size-1);
                    if(l!=-1 && l!=i)res.push_back({l, i});
                }
            }
        }
        return res;
    }
    std::vector<std::vector<int>> palidromePairs(std::vector<std::string> &words){
        std::unordered_map<std::string_view, int> mp;
        std::vector<std::string> rev;
        std::string temp;
        int wsize = words.size();
        for(int i=0; i<wsize; ++i){
            rev.push_back(words[i]);
            reverse(rev.back().begin(), rev.back().end());
        }
        for(int i=0; i<wsize; ++i){
            mp.emplace(rev[i], i);
        }
        std::function<bool(const std::string_view &, int , int)> _is_palidome
            = [&](const std::string_view &word, int left, int right){
                if(left>=right)return true;
                while(left<right){
                    if(word[left++] != word[right--])return false;
                }
                return left>=right;
        };
        std::function<int(const std::string_view &, int, int)> _find_rev
            = [&](const std::string_view &word, int left, int right){
            auto it = mp.find(word.substr(left, right-left+1));
            return it==mp.end()?-1:it->second;
        };
        std::vector<std::vector<int>> res;
        int size = 0;
        for(int i=0; i<wsize; ++i){
            if(!(size=words[i].size()))continue;
            std::string_view sw(words[i]);
            for(int j=0; j<=size; ++j){
                if(_is_palidome(sw, j, size-1)){
                    int r = _find_rev(sw, 0, j-1);
                    if(r!=-1 && r!=i){
                        res.push_back({i, r});
                    }
                }
                if(_is_palidome(sw, 0, j)){
                    int l = _find_rev(sw, j+1, size-1);
                    if(l!=-1 && l!=i){
                        res.push_back({l, i});
                    }
                }
            }
        }
        return res;
    }
//987. 二叉树的垂序遍历
    std::vector<std::vector<int>> verticalTraversal(TreeNode *root){
        struct _node{
            int y;
            int x;
            int val;
            _node(int y1, int x1, int val1) : x(x1), y(y1), val(val1) {}
        };
        std::map<int, std::vector<_node>, std::less<int>> mp;
        std::function<void(TreeNode *, int, int)> _dfs = [&](TreeNode *root, int y, int x){
            if(!root)return;
            mp[x].push_back({y, x, root->val});
            _dfs(root->left, y-1, x-1);
            _dfs(root->right, y-1, x+1);
        };
        _dfs(root, 0, 0);
        std::vector<std::vector<int>> res;
        for(auto &[k, v] : mp){
            std::sort(v.begin(), v.end(), [&](auto &a, auto &b){
                return a.y==b.y?a.val < b.val:a.y>b.y; });
            std::vector<int> temp;
            for(auto node : v)temp.push_back(node.val);
            res.push_back(temp);
        }
        return res;
    }
//771. 宝石与石头
    int numJewelsInStones(std::string J, std::string S){
        std::unordered_set<char> mp(J.begin(), J.end());
        int res = 0;
        for(auto c : S)res += mp.count(c);
        return res;
    }
//1207. 独一无二的出现次数
    bool uniqueOccurrentces(std::vector<int> &arr){
        std::unordered_map<int, int> mp;
        for(auto x : arr)++mp[x];
        std::unordered_set<int> ans;
        for(auto [x, n] : mp)if(!ans.insert(n).second)return false;
        return true;
    }
//599. 两个列表的最小索引总和
    std::vector<std::string> findRestaurant(std::vector<std::string> &list1,
            std::vector<std::string> &list2){
        std::unordered_map<std::string,int> mp1;
        std::unordered_map<std::string,int> mp2;
        for(int i=0; i<list1.size(); ++i)mp1[list1[i]] = i;
        for(int i=0; i<list2.size(); ++i)mp2[list2[i]] = i;
        std::unordered_map<std::string, int> ans;
        int max_ = INT_MAX;
        for(auto &[w1, n1] : mp1){
            if(!mp2.count(w1))continue;
            max_ = std::min(max_, ans[w1] = n1 + mp2[w1]);
        }
        std::vector<std::string> res;
        for(auto [w, n] : ans){
            if(n==max_)res.push_back(w);
        }
        return res;
    }
//645. 错误的集合
    std::vector<int> findErrorNums(std::vector<int> &nums){
        std::unordered_map<int, int> mp;
        int ans1, ans2;
        for(auto x : nums)++mp[x];
        int size = nums.size();
        for(int i=1; i<=size; ++i){
            if(mp[i]==0)ans2 = i;
            if(mp[i]==2)ans1 = i;
        }
        return {ans1, ans2};
    }
//508. 出现次数最多的子树元素和
    std::vector<int> findFrequencetreeSum(TreeNode *root){
        std::unordered_map<int, int> mp;
        int max_ = 0;
        int ans  = 0;
        std::function<int(TreeNode *)> _dfs = [&](TreeNode *root){
            if(!root)return 0;
            ans  = root->val + _dfs(root->left) + _dfs(root->right);
            max_ = std::max(max_, ++mp[ans]);
            return ans;
        };
        _dfs(root);
        std::vector<int> res;
        for(auto [x, n] : mp){
            if(n==max_)res.push_back(x);
        }
        return res;
    }
//389. 找不同
    char findTheDifference(std::string s, std::string t){
        std::unordered_map<char, int> mp;
        for(auto c : s)++mp[c];
        for(auto c : t)if(--mp[c]<0)return c;
        return ' ';
    };
//953. 验证外星语词典
    bool isAlienSorted(std::vector<std::string> &words, std::string order){
        std::unordered_map<char, int> mp;
        for(int i=0; i<order.size(); ++i)mp[order[i]] = i;
        auto temp = words;
        std::sort(temp.begin(), temp.end(), [&](auto &a, auto &b){
            int sizea = a.size();
            int sizeb = b.size();
            int i     = 0;
            while(i<sizea && i<sizeb){
                if(mp[a[i]] < mp[b[i]])return true;
                if(mp[a[i]] > mp[b[i]])return false;
                ++i;
            }
            if(sizea > sizeb)return false;
            return true;
        });
        int wsize = words.size();
        for(int i=0; i<wsize; ++i){
            if(temp[i]!=words[i])return false;
        }
        return true;
    }
//966. 元音拼写检查器
    std::vector<std::string> spellchecker(std::vector<std::string> &wordList,
            std::vector<std::string> &queries){
        int qsize = queries.size();
        int wsize = wordList.size();
        std::unordered_set<std::string> wmp(wordList.begin(), wordList.end());
        std::unordered_map<std::string, int> lmp;
        std::unordered_map<std::string, int> mmp;
        std::unordered_set<char> ori = {'a', 'e', 'i', 'o', 'u'};
        std::function<std::string(std::string &)> _encode = [&](std::string &w){
            std::string ans = w;
            std::transform(w.begin(), w.end(), ans.begin(),[&](char& c){
                    if(ori.count(c))return 'a';
                    return c;
            });
            return ans;
        };
        for(int i=wsize-1; i>=0; --i){
            auto temp = wordList[i];
            std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            lmp[temp] = i;
            mmp[_encode(temp)] = i;
        }
        std::vector<std::string> res(qsize);
        for(int i=0; i<qsize; ++i){
            auto w = queries[i];
            if(wmp.count(w)){
                res[i] = (w);
                continue;
            }
            std::transform(w.begin(), w.end(), w.begin(), ::tolower);
            if(lmp.count(w)){
                res[i] = (wordList[lmp[w]]);
                continue;
            }
            w = _encode(w);
            if(mmp.count(w)){
                res[i] = (wordList[mmp[w]]);
            }
        }
        return res;
    }
    std::vector<std::string> spellchecker_fuck(std::vector<std::string> &wordList,
            std::vector<std::string> &queries){
        int qsize = queries.size();
        std::vector<std::string> res;
        std::unordered_map<std::string, int> mplower;
        std::unordered_set<std::string> mp(wordList.begin(), wordList.end());
        std::unordered_set<char> ori{'a', 'e', 'i', 'o', 'u'};
        for(int i=wordList.size()-1; i>=0; --i){
            auto w = wordList[i];
            std::transform(w.begin(), w.end(), w.begin(), ::tolower);
            mplower[w] = i;
        }
        std::function<bool(std::string &, int)> _dfs = [&](std::string &w, int i){
            if(i==w.size())return false;
            std::string temp = w;
            if(mplower.count(temp)){
                res.push_back(wordList[mplower[temp]]);
                return true;
            }
            int size = temp.length();
            for(int j=i; j<size; ++j){
                if(!ori.count(temp[j]))continue;
                char k = temp[j];
                for(auto &c : ori){
                    if(c==k)continue;
                    temp[j] = c;
                    if(_dfs(temp, i+1))return true;
                    temp[j] = k;
                }
            }
            return false;
        };
        std::function<bool(std::string &)> _calc = [&](std::string &w){
            if(mp.count(w)){
                res.push_back(w);
                return true;
            }
            std::string temp = w;
            std::transform(w.begin(), w.end(), temp.begin(), ::tolower);
            if(mplower.count(temp)){
                res.push_back(wordList[mplower[temp]]);
                return true;
            }
            return _dfs(temp, 0);
        };
        for(int i=0; i<qsize; ++i){
            if(!_calc(queries[i]))res.push_back("");
        }
        return res;
    }
//451. 根据字符出现频率排序
    std::string frequenceSort(std::string s){
        std::unordered_map<char, int> mp;
        for(auto &c : s)++mp[c];
        std::priority_queue<std::pair<int, char>> q;
        for(auto [c, n] : mp)q.push({n, c});
        std::string res;
        while(q.size()){
            char c = q.top().second;
            q.pop();
            res += std::string(mp[c], c);
        }
        return res;
    }
//204. 计数质数
    int countPrimes_int(int n){
        std::vector<int> mp(n, 1);
        int res = 0;
        for(int i=2; i<n; ++i){
            if(!mp[i])continue;
            ++res;
            for(int j=i+i; j<n; j+=i)mp[j]=0;
        }
        return res;
    }
    int countPrimes_bit(int n){
         const int size = 8 * sizeof(int);
         int mp[n/size+1];
         memset(mp, 0, sizeof mp);
         int res = 0;
         for(int i=2; i<n; ++i){
             if(mp[i/size]&(1<<(i&(size-1))))continue;
             ++res;
             for(int j=i+i; j<n; j+=i){
                 mp[j/size] |= (1<<(j&(size-1)));
             }
         }
         return res;
    }
//387. 字符串中的第一个唯一字符
    int firstUniqChar(std::string s){
        std::unordered_map<char, int> mp;
        for(auto &c : s)++mp[c];
        for(int i=0; i<s.length(); ++i){
            if(mp[s[i]]==1)return i;
        }
        return -1;
    }
//149. 直线上最多的点数
    int maxPoints(std::vector<std::vector<int>> &points){
        if(points.size() < 2)return points.size();
        std::sort(points.begin(), points.end(), [&](auto &a, auto &b){
                return a[0]==b[0]?a[1]<b[1]:b[0]>a[0]; });
        int n = points.size();
        std::vector<int> mp(n);
        for(int i=0; i<n; ++i){
            int t = i;
            while(t<n && points[i]==points[t])++t;
            mp[i] = t - i;
            i = t - 1;
        }
        //for(auto &x : mp)std::cout<<x<<std::endl;
        int res = 2;
        for(int i=0; i<n; ++i){
            if(!mp[i])continue;
            for(int j=i+1; j<n; ++j){
                if(!mp[j])continue;
                long long x1  = points[i][0] - points[j][0];
                long long y1  = points[i][1] - points[j][1];
                int len = mp[i] + mp[j];
                for(int k=j+1; k<n; ++k){
                    if(!mp[k])continue;
                    long long x2 = points[i][0] - points[k][0];
                    long long y2 = points[i][1] - points[k][1];
                    if(x1*y2 == x2*y1)len += mp[k];
                }
                res = std::max(res, len);
            }
        }
        return std::max(res, *max_element(mp.begin(), mp.end()));
    }
//30. 串联所有单词的子串
    std::vector<int> findSubstring(std::string s, std::vector<std::string> &words){
        std::unordered_map<std::string, int> mp;
        for(auto &w : words)++mp[w];
        std::vector<int> res;
        int len   = words[0].size();
        int sizew = words.size();
        int sizes = s.length();
        for(int i=0; i<len; ++i){
            int left  = i;
            int right = i;
            int cnt   = 0;
            std::unordered_map<std::string, int> temp;
            while(left+len*sizew <= sizes){
                std::string word;
                while(cnt < sizew){
                    word = s.substr(right, len);
                    if(temp[word] >= mp[word])break;
                    ++cnt;
                    ++temp[word];
                    right += len;
                }
                if(cnt==sizew)res.push_back(left);
                if(mp.count(word)){
                    --temp[s.substr(left, len)];
                    --cnt;
                    left += len;
                }else{
                    right += len;
                    left = right;
                    cnt = 0;
                    temp.clear();
                }
            }
        }
        return res;
    }
    std::vector<int> findSubstring_fuck(std::string s, std::vector<std::string> &words){
        std::vector<int> mp(26);
        int sizeb = s.length();
        int sizea = 0;
        for(auto &ss : words){
            sizea += ss.length();
            for(auto &c : ss)++mp[c-'a'];
        }
        if(sizea > sizeb)return {};
        int need = sizea;
        for(int i=0; i<sizea; ++i){
            if(--mp[s[i]-'a']>=0)--need;
        }
        std::vector<int> res;
        for(int i=sizea; i<sizeb; ++i){
            if(!need)res.push_back(i-sizea);
            if(--mp[s[i]-'a']>=0)--need;
            if(++mp[s[i-sizea]-'a']>0)++need;
        }
        return res;
    }
//1001. 网格照明
    std::vector<int> gridIllumination(int N, std::vector<std::vector<int>> &lamps, std::vector<std::vector<int>> &queries){
        std::unordered_map<int,int> row;
        std::unordered_map<int,int> col;
        std::unordered_map<int,int> dial;
        std::unordered_map<int,int> diar;
        std::unordered_set<uint64_t> lights;
        for(auto &p : lamps){
            int x = p[0];
            int y = p[1];
            ++row[x];++col[y];
            ++dial[x+y];
            ++diar[x-y];
            lights.insert(static_cast<uint64_t>(x)<<32 | y);
        }
        std::vector<int> _fun = {0, 0, -1, 1, 1, -1, -1, 0, 1, 0};
        std::vector<int> res;
        for(auto &p : queries){
            int x = p[0];
            int y = p[1];
            int stat = (row[x] || col[y] || dial[x+y] || diar[x-y]);
            res.push_back(stat);
            for(int f=0; f<9; ++f){
                int i1 = x + _fun[f];
                int j1 = y + _fun[f+1];
                if(i1<0 || j1<0 || i1>=N || j1>=N)continue;
                uint64_t index = static_cast<uint64_t>(i1)<<32 | j1;
                if(!lights.count(index))continue;
                --row[i1];--col[j1];
                --dial[i1+j1];
                --diar[i1-j1];
                lights.erase(index);
            }
        }
        return res;
    }
    std::vector<int> gridIllumination_fuck(int N, std::vector<std::vector<int>> &lamps, std::vector<std::vector<int>> &queries){
        int qsize = queries.size();
        int lsize = lamps.size();
        std::vector<int> _fun = {0, 0, -1, 1, 1, -1, -1, 0, 1, 0};
        std::vector<std::unordered_set<int>> qmp(qsize);
        for(int i=0; i<qsize; ++i){
            auto p = queries[i];
            for(int f=0; f<9; ++f){
                int i1 = p[0] + _fun[f];
                int j1 = p[1] + _fun[f+1];
                if(i1<0 || j1<0 || i1>=N ||  j1>=N)continue;
                for(int k=0; k<lsize; ++k){
                    auto l = lamps[k];
                    if(l[0]==i1 && l[1]==j1){
                        qmp[i].insert(k);
                        break;
                    }
                }
            }
        }
        std::vector<int> res(qsize);
        std::unordered_set<int> lights;
        for(int i=0; i<lsize; ++i)lights.insert(i);
        std::function<bool(int, int)> _clac = [&](int x, int y){
            for(auto i : lights){
                int row = lamps[i][0];
                int col = lamps[i][1];
                if(row==x || col==y || abs(row-x)==abs(col-y))return true;
            }
            return false;
        };
        for(int i=0; i<qsize; ++i){
            if(_clac(queries[i][0], queries[i][1]))res[i] = 1;
            for(auto l : qmp[i])lights.erase(l);
        }
        return res;
    }
//992. K 个不同整数的子数组
    int subarraysWIthDistict(std::vector<int> &A, int K){
        std::function<int(int)> _calc = [&](int k){
            int l = 0,r = -1;
            int ans = 0,cnt = 0;
            std::vector<int> mp(A.size()+1, 0);
            while(++r < A.size()){
                if(!mp[A[r]]++)++cnt;
                while(cnt>k)if(!--mp[A[l++]])--cnt;
                ans += r - l + 1;
            }
            return ans;
        };
        return _calc(K) - _calc(K-1);
    }
    void solveSudoku(std::vector<std::vector<char>> &board){
        std::vector<int> row(9);
        std::vector<int> col(9);
        std::vector<std::vector<int>> mat(3, std::vector<int>(3));
        std::vector<std::pair<int,  int>> points;
        std::function<void(int, int, int)> _set_mask = [&](int i, int j, int mask){
            row[i] ^= (1<<mask);
            col[j] ^= (1<<mask);
            mat[i/3][j/3] ^= (1<<mask);
        };
        std::function<bool(int)> _dfs = [&](int pos){
            if(pos == points.size())return true;
            auto [i, j] = points[pos];
            int can = ~(row[i] | col[j] | mat[i/3][j/3]) & 0x1ff;
            for(; can; can&=(can-1)){
                int digit = __builtin_ctz(can);
                _set_mask(i, j, digit);
                board[i][j] = digit + 0 + '1';
                if(_dfs(pos+1))return true;
                _set_mask(i, j, digit);
            }
            return false;
        };
        for(int i=0; i<9; ++i){
            for(int j=0; j<9; ++j){
                if(board[i][j] == '.')continue;
                _set_mask(i, j, board[i][j]-'0'-1);
            }
        }
        while(true){
            int flag = false;
            for(int i=0; i<9; ++i){
                for(int j=0; j<9; ++j){
                    if(board[i][j] != '.')continue;
                    int mask = ~(row[i] | col[j] | mat[i/3][j/3]) & 0x1ff;
                    if(mask & (mask-1))continue;
                    flag = true;
                    int digit = __builtin_ctz(mask);
                    _set_mask(i, j, digit);
                    board[i][j] = '0' + 1 + digit;
                }
            }
            if(!flag)break;
        }
        for(int i=0; i<9; ++i){
            for(int j=0; j<9; ++j){
                if(board[i][j]=='.')points.push_back({i, j});
            }
        }
        _dfs(0);
    }
    void solveSudoku_fuck_fuck(std::vector<std::vector<char>> &board){
            std::function<int(int)> _index = [&](int pos){
                int j = pos % 9;
                int i = pos / 9;
                int p = 0;
                if(j<3){
                    ;
                }else if(j>5){
                    p = 2;
                }else{
                    p = 1;
                }
                if(i<3)return 0 + p;
                if(i>5)return 6 + p;
                return 3 + p;
            };
            std::vector<std::unordered_set<char>> rows(9);
            std::vector<std::unordered_set<char>> cols(9);
            std::vector<std::unordered_set<char>> mat(9);
            std::unordered_map<int, std::unordered_set<int>> mp;
            for(int i=0; i<9; i++){
                for(int j=0; j<9; j++){
                    if(board[i][j]=='.')continue;
                    mat[_index(9*i+j)].insert(board[i][j]);
                }
            }
            for(int i=0; i<9; ++i){
                for(int j=0; j<9; ++j){
                    if(board[i][j]!='.')rows[i].insert(board[i][j]);
                    if(board[j][i]!='.')cols[i].insert(board[j][i]);
                }
            }
            std::unordered_set<char> temp;
            int total = 0;
            for(int i=1; i<=9; ++i)temp.insert('0'+i);
            for(int i=0; i<9; ++i){
                for(int j=0; j<9; ++j){
                    if(board[i][j]!='.')continue;
                    ++total;
                    auto tmp = temp;
                    for(auto &w : rows[i])if(tmp.count(w))tmp.erase(w);
                    for(auto &w : cols[j])if(tmp.count(w))tmp.erase(w);
                    for(auto &w : mat[_index(i*9+j)])if(tmp.count(w))tmp.erase(w);
                    for(auto &w : tmp)mp[i*9+j].insert(w);
                }
            }
            std::vector<int> _begin = {0, 3, 6, 27, 30, 33, 54, 57, 60};
            std::function<void(int, char)> _inflect = [&](int pos, char c){
                int i = pos / 9;
                int j = pos % 9;
                for(int j1=0; j1<9; ++j1){
                    if(mp[i*9+j1].count(c))mp[i*9+j1].erase(c);
                }
                for(int i1=0; i1<9; ++i1){
                    if(mp[i1*9+j].count(c))mp[i1*9+j].erase(c);
                }
                int index = _index(pos);
                int begin = _begin[index];
                for(int i=0; i<3; ++i){
                    if(mp[pos+i].count(c))mp[pos+i].erase(c);
                    if(mp[pos+9+i].count(c))mp[pos+9+i].erase(c);
                    if(mp[pos+18+i].count(c))mp[pos+18+i].erase(c);
                }
            };
         //   cout<<*mp[6*9+5].begin()<<endl;
           // _inflect(6*9+5, *mp[6*9+5].begin());
     /*      for(int i=0; i<9; ++i){
                for(int j=0; j<9; ++j){
                    if(board[i][j]=='.')std::cout<<mp[i*9+j].size()<<"  ";
                }
                std::cout<<std::endl;
            }*/
           // return;
            while(total){
                if(total<3)std::cout<<total<<std::endl;
                for(int i=0; i<9; ++i){
                    for(int j=0; j<9; ++j){
                        if(board[i][j] != '.')continue;
                        if(mp[i*9+j].size() != 1)continue;
                        board[i][j] = *mp[i*9+j].begin();
                        _inflect(i*9+j, *mp[i*9+j].begin());
                        mp[i*9+j].clear();
                        --total;
                    }
                }
            }
        }
//1090. 受标签影响的最大值
        int largestValsFromLabels(std::vector<int> &values, std::vector<int> &labels,
                int num_wanted, int use_limit){
            int size = labels.size();
            int res  = 0;
            std::vector<std::vector<int>> items(size, std::vector<int>(2));
            for(int i=0; i<size; ++i)items[i][0] = values[i], items[i][1] = labels[i];
            std::sort(items.begin(), items.end(), [&](auto &a, auto &b){
                    return a[0] > b[0]; });
            std::unordered_map<int, int> mp;
            for(auto &it : items){
                if(mp[it[1]] >= use_limit)continue;
                res += it[0];
                if(--num_wanted<=0)break;
                mp[it[1]]++;
            }
            return res;
        }
//739. 每日温度
        std::vector<int> dailyTemperatures(std::vector<int> &T){
            int size = T.size();
            std::vector<int> q;
            std::vector<int> res(size, 0);
            for(int i=0; i<size; ++i){
                while(q.size() && T[q.back()] < T[i]){
                    res[q.back()] = i - q.back();
                    q.pop_back();
                }
                q.push_back(i);
            }
            return res;
        }
//648. 单词替换
        std::string replaceWords_better(std::vector<std::string> &dictionary, std::string sectence){
            struct _wd_node{
                _wd_node():end(""){ childs.resize(26); }
               ~_wd_node(){ for(int i=0; i<26; ++i)if(childs[i])delete childs[i]; }
                std::string end;
                std::vector<_wd_node *> childs;
            };
            _wd_node *tree = new _wd_node();
            std::function<void(std::string &)> _add = [&](std::string &wd){
                _wd_node *hd = tree;
                for(char c : wd){
                    if(!hd->childs[c-'a'])hd->childs[c-'a'] = new _wd_node();
                    hd = hd->childs[c-'a'];
                }
                hd->end = wd;
            };
            std::function<std::string(std::string &)> _search = [&](std::string &wd){
                _wd_node *hd = tree;
                for(auto &c : wd){
                    if(hd->end.size())return hd->end;
                    if(!(hd=hd->childs[c-'a']))return wd;
                }
                return wd;
            };
            for(auto &w : dictionary)_add(w);
            std::string res, wd;
            std::stringstream ss(sectence);
            while(ss >> wd)res+=_search(wd) + " ";
            res.pop_back();
            return res;
        }
        std::string replaceWords(std::vector<std::string> &dictionary, std::string sectence){
            std::unordered_set<std::string> mp(dictionary.begin(), dictionary.end());
            std::string res;
            std::string wd;
            std::stringstream ss;
            ss.str(sectence);
            while(ss >> wd){
                std::string temp;
                for(auto &c : wd){
                    if(mp.count(temp+=c))break;
                }
                res += temp + " ";
            }
            res.pop_back();
            return res;
        }
//面试题 17.26. 稀疏相似度
        std::vector<std::string> computsSimilarities(std::vector<std::vector<int>> &docs){
            const double EXTRA = 1e-9;
            std::map<int, std::vector<int>> mp;
            std::map<std::pair<int, int>, int> inter;
            int size = docs.size();
            for(int i=0; i<size; ++i){
                for(auto &w : docs[i]){
                    mp[w].push_back(i);
                }
            }
            for(auto [w , vi] : mp){
                int n = vi.size();
                for(int i=0; i<n; ++i){
                    for(int j=i+1; j<n; ++j){
                        ++inter[{vi[i], vi[j]}];
                    }
                }
            }
            std::vector<std::string> res;
            std::stringstream ss;
            std::string temp;
            for(auto [p, n] : inter){
                int i      = p.first;
                int j      = p.second;
                double ans = double((double)n/(docs[i].size() + docs[j].size()-n) + EXTRA);
                ss.clear();
                ss << std::setprecision(4) << std::setiosflags(std::ios::fixed) << ans;
                ss >> temp;
                res.push_back(std::to_string(i)+","+std::to_string(j)+": "+temp);
            }
            return res;
        }
        std::vector<std::string> computsSimilarities_fuck(std::vector<std::vector<int>> &docs){
            int n = docs.size();
            std::vector<std::unordered_set<int>> mp(n);
            for(int i=0; i<n; ++i){
                for(auto &x : docs[i])mp[i].insert(x);
            }
            std::vector<std::string> res;
            std::string temp;
            std::stringstream ss;
            const float EXTRA = 1e-9;
            for(int i=0; i<n; ++i){
                if(!mp[i].size())continue;
                for(int j=i+1; j<n; ++j){
                    if(!mp[j].size())continue;
                    auto hp1 = mp[i];
                    auto hp2 = mp[j];
                    if(hp1.size() > hp2.size()) std::swap(hp1, hp2);
                    int inter = 0;
                    for(auto &p : hp1){
                        inter += hp2.count(p);
                    }
                    if(!inter)continue;
                    double ans = (double)((double)inter/(hp1.size()+hp2.size()-inter)*1.0) + EXTRA;
                    ss.clear();
                    ss <<std::setiosflags(std::ios::fixed)<< std::setprecision(4) << ans;
                    ss >> temp;
                    res.push_back(std::to_string(i)+","+std::to_string(j)+": "+ temp);
                }
            }
            return res;
        }
//面试题 16.24. 数对和
        std::vector<std::vector<int>> pairsSums(std::vector<int> &nums, int target){
            std::unordered_map<int, int> mp;
            for(auto &n : nums)++mp[n];
            std::vector<std::vector<int>> res;
            for(auto &f : nums){
                if(!mp.count(target - f))continue;
                if(mp[target-f]<=0 || mp[f]<=0 || (f*2==target && mp[f]<2))continue;
                --mp[target-f];
                --mp[f];
                res.push_back({f, target-f});
            }
            return res;
        }
//884. 两句话中的不常见单词
        std::vector<std::string> uncommonFromSectience(std::string A, std::string B){
            std::stringstream ss;
            std::string temp;
            std::unordered_map<std::string, int> mp_1;
            std::unordered_map<std::string, int> mp_2;
            ss.str(A);
            while(ss >> temp)++mp_1[temp];
            ss.clear();
            ss.str(B);
            while(ss >> temp)++mp_2[temp];
            std::vector<std::string> res;
            for(auto &[str, n] : mp_1)if(n==1 && !mp_2.count(str))res.push_back(str);
            for(auto &[str, n] : mp_2)if(n==1 && !mp_1.count(str))res.push_back(str);
            return res;
        }
//554. 砖墙
        int leastBricks(std::vector<std::vector<int>> &wall){
            int m = wall.size();
            std::unordered_map<int, int> mp;
            for(auto &w : wall){
                int n = w.size();
                if(n==1)continue;
                ++mp[w[0]];
                for(int i=1; i<n-1; ++i)++mp[(w[i]+=w[i-1])];
            }
            int l = -1;
            for(auto &p : mp){
                l = std::max(l, p.second);
            }
            return l==-1?m:m-l;
        }
//609. 在系统中查找重复文件
        std::vector<std::vector<std::string>> findDuplicate(std::vector<std::string> &paths){
            using vpii = std::vector<std::pair<int, int>>;
            std::unordered_map<std::string, vpii> mp;
            int n = paths.size();
            std::string temp;
            std::stringstream ss;
            for(int i=0; i<n; ++i){
                ss.clear();
                ss << paths[i];
                int k = 1;
                ss>>temp;
                while(ss>>temp){
                    int l = temp.find('(');
                    if(l == temp.size())continue;
                    int r = temp.find(')');
                    auto txt = temp.substr(l+1, r-l-1);
                    mp[txt].push_back({i, k});
                    ++k;
                }
            }
            std::vector<std::vector<std::string>> res;
            for(auto &p : mp){
                if(p.second.size() < 2)continue;
                std::vector<std::string> ans;
                for(auto &[h, i] : p.second){
                    ss.clear();
                    ss.str(paths[h]);
                    ss >> temp;
                    ans.push_back(temp);
                    while(i--)ss >> temp;
                    ans.back() += ("/"+temp.substr(0, temp.find("(")));
                }
                res.push_back(ans);
            }
            return res;
        }
//面试题 16.14. 最佳直线
        std::vector<int> bestLine(std::vector<std::vector<int>> &points){
            std::vector<int> res;
            int max_ = 1;
            int n    = points.size();
            for(int i=0; i<n; ++i){
                for(int j=i+1; j<n; ++j){
                    if(max_ >= n-j+1)break;
                    int len = 2;
                    long long x1  = points[i][0] - points[j][0];
                    long long y1  = points[i][1] - points[j][1];
                    for(int k=j+1; k<n; ++k){
                        long long x2 = points[i][0] - points[k][0];
                        long long y2 = points[i][1] - points[k][1];
                        if(x1*y2==x2*y1)++len;
                    }
                    if(len > max_){
                        res  = {i, j};
                        max_ = len;
                    }
                }
            }
            return res;
        }
//1365. 有多少小于当前数字的数字
        std::vector<int> smallerNumbersThanCunrent(std::vector<int> &nums){
            std::vector<int> cnt(101);
            for(auto &n : nums)++cnt[n];
            for(int i=1; i<100; ++i)cnt[i] += cnt[i-1];
            std::vector<int> res(nums.size(), 0);
            for(int i=0; i<nums.size(); ++i){
                if(nums[i])res[i] = cnt[nums[i]-1];
            }
            return res;
        }
//954. 二倍数对数组
        bool canReorderDoubled(std::vector<int> &A){
            std::unordered_map<int, int> mp;
            for(auto a : A)++mp[a];
            std::sort(A.begin(), A.end(), [&](int a, int b){
                    return abs(a) < abs(b); });
            for(auto x : A){
                if(mp[x]<=0)continue;
                if(mp[x*2]<=0)return false;
                --mp[x];
                --mp[x*2];
            }
            return true;
        }
 //面试题 10.02. 变位词组
        std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string> &strs){
            std::vector<std::vector<std::string>> res;
            std::unordered_map<std::string, std::vector<int>> mp;
            for(int i=0; i<strs.size(); ++i){
                auto ss = strs[i];
                std::sort(ss.begin(), ss.end());
                mp[ss].push_back(i);
            }
            for(auto sn : mp){
                std::vector<std::string> ans;
                for(auto i : sn.second)ans.push_back(strs[i]);
                res.push_back(ans);
            }
            return res;
        }
};
