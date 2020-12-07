/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_backtracking_pro.cpp
*     author   : @ JY
*     date     : 2020--10--31
**********************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <climits>
#include <numeric>
#include <map>
#include <set>
#include <utility>
#include <unordered_set>
#include <string>
#include <sstream>
#include <cstring>
#include <unordered_map>
#include <functional>
#include <stdlib.h>

class Solution{
    public:
//[LeetCode] 351. 安卓系统手势解锁
        int numberOfPatterns_better(int m, int n){
            int res = 0;
            std::vector<int> vi(10);
            std::vector<std::vector<int>> mp(10, std::vector<int>(10));
            std::function<int(int, int)> _dfs =[&](int all, int num){
                int ans = 0;
                if(all >= m)++ans;
                if(++all > n)return ans;
                vi[num] = 1;
                for(int i=1; i<10; ++i){
                    if(vi[i] || !vi[mp[num][i]])continue;
                    res += _dfs(all, i);
                }
                vi[num] = 0;
                return ans;
            };
            mp[1][3] = mp[3][1] = 2;
            mp[1][7] = mp[7][1] = 4;
            mp[3][9] = mp[9][3] = 6;
            mp[7][9] = mp[9][7] = 8;
            mp[8][2] = mp[2][8] = mp[4][6] = mp[6][4] = 5;
            mp[9][1] = mp[1][9] = mp[3][7] = mp[7][3] = 5;
            return _dfs(1, 1)*4 + _dfs(1, 2)*4 + _dfs(1, 5);
        }
//LeetCode 254. 因子的组合
        std::vector<std::vector<int>> getFactors_better(int n){
            std::vector<std::vector<int>> res;
            std::function<std::vector<std::vector<int>>(int, int)> _dfs= [&](int n, int div){
                std::vector<std::vector<int>> ans;
                for(int i=div; i*i<=n; ++i){
                    if(n % i)continue;
                    ans.push_back({i, n/i});
                    auto temp = _dfs(n/i, i);
                    for(auto &val : temp){
                        val.emplace_back(i);
                        ans.emplace_back(val);
                    }
                }
                return ans;
            };
            return _dfs(n, 2);
        }
        std::vector<std::vector<int>> getFactors(int n){
            if(n==1)return {};
            std::set<std::vector<int>> res;
            std::vector<int> ans;
            std::function<void(int)> _dfs = [&](int n){
                if(n==1){
                    auto x = ans;
                    std::sort(begin(x), end(x));
                    if(ans.size() > 1)res.insert(x);
                    return;
                }
                for(int i=n; i>1; --i){
                    if((n % i))continue;
                    ans.emplace_back(i);
                    _dfs(n / i);
                    ans.pop_back();
                }
            };
            _dfs(n);
            return {begin(res), end(res)};
        }
//Leetcode 1215：步进数
//如果一个整数上的每一位数字与其相邻位上的数字的绝对差都是 1，那么这个数就是一个「步进数」。 例如，321 是一个步进数，而 421 不是。
        std::vector<int> countSteppingNumbers(int l, int r){
            std::vector<int> res;
            std::function<void(int)> _dfs = [&](int ans){
                if(ans==0 || ans > r)return;
                if(ans>=l && ans<=r)res.emplace_back(ans);
                int e  = ans % 10;
                int s1 = ans * 10 + e + 1;
                int s2 = ans * 10 + e - 1;
                if(e == 0){
                    _dfs(s1);
                }else if(e == 9){
                    _dfs(s2);
                }else{
                    _dfs(s1);
                    _dfs(s2);
                }
            };
            if(!l)res.emplace_back(0);
            for(int i=0; i<10; ++i)_dfs(i);
            std::sort(begin(res), end(res));
            return res;
        };
//给定一个单词集合 （没有重复），找出其中所有的 单词方块 。 一个单词序列形成了一个有效的单词方块的意思是指从第 k 行和第 k 列 (0 ≤ k < max(行数, 列数)) 来看都是相同的字符串。
//[LeetCode] 425. 单词方块
        std::vector<std::vector<std::string>> wordSquares(std::vector<std::string> &words){
            struct _node{
                std::string end;
                std::vector<_node*> next;
                _node () : next(26){}
                ~_node(){
                    for(auto &x : next){
                        if(x)delete x;
                    }
                }
            };
            _node *root = new _node();
            for(auto &wd : words){
                _node *cur = root;
                for(auto &c : wd){
                    if(!cur->next[c-'a'])cur->next[c-'a'] = new _node();
                    cur = cur->next[c-'a'];
                }
                cur->end = wd;
            }
            std::vector<std::string> wds;
            std::function<void(_node *)> _get_words = [&](_node *cur){
                if(cur && cur->end.size()){
                    wds.emplace_back(cur->end);
                }
                for(auto &x : cur->next){
                    if(x)_get_words(x);
                }
            };
            int len = words[0].size();
            std::vector<std::vector<std::string>> res;
            std::vector<std::string> ans;
            std::function<void(int)> _dfs = [&](int i){
                if(i == len-1){
                    res.emplace_back(ans);
                    return;
                }
                std::string pre;
                for(auto &wd : ans)pre += wd[i+1];
                _node *cur = root;
                for(auto &c : pre){
                    if(!(cur = cur->next[c-'a']))return;
                }
                wds.clear();
                _get_words(cur);
                for(auto &wd : wds){
                    ans.emplace_back(wd);
                    _dfs(i+1);
                    ans.pop_back();
                }
            };
            for(auto &wd : words){
                ans.emplace_back(wd);
                _dfs(0);
                ans.pop_back();
            }
            return res;
        }
//LeetCode 294. 翻转游戏 II
//你和朋友玩一个叫做「翻转游戏」的游戏， 游戏规则：给定一个只有 + 和 - 的字符串。 你和朋友轮流将 连续 的两个 "++" 反转成 "--"。 当一方无法进行有效的翻转时便意味着游戏结束，则另一方获胜。 请你写出一个函数来判定起始玩家是否存在必胜的方案
        bool canWin(std::string s){
            int len = s.size();
            if(len < 2)return false;
            std::unordered_map<std::string, bool> dp;
            std::function<bool(void)> _dfs = [&](void){
                if(dp.count(s))return dp[s];
                for(int i=1; i<len; ++i){
                    if(s[i] == s[i-1] && s[i] == '+'){
                        s[i] = s[i-1] = '-';
                        bool ans = _dfs();
                        s[i] = s[i-1] = '+';
                        if(!ans)return dp[s] = true;
                    }
                }
                return dp[s] = false;
            };
            return _dfs();
            //for(auto &[str, n] : dp)std::cout<<str<<"   "<<n<<std::endl;
        };
//Leetcode 1258：近义词句子
        std::vector<std::string> generateSentences(
                std::vector<std::vector<std::string>> synonyms,
                std::string text){
            std::unordered_map<int, std::unordered_set<std::string>> mp;
            std::unordered_map<std::string, int> si;
            int code = 0;
            for(auto &s : synonyms){
                if(!si.count(s[0]))si[s[0]] = code++;
                if(!si.count(s[1]))si[s[1]] = code++;
            }
            std::vector<int> _f(code);
            std::iota(begin(_f), end(_f), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i] == i ? i : _f[i] = _find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                _f[_find(a)] = _f[_find(b)]; };
            for(auto &s : synonyms)_union(si[s[0]], si[s[1]]);
            for(auto &s : synonyms){
                int p = _find(si[s[1]]);
                mp[p].insert(s[0]);
                mp[p].insert(s[1]);
            }
            std::vector<std::string> words;
            std::string ans;
            std::stringstream ss(text);
            while(ss >> ans)words.emplace_back(ans);
            int len = words.size();
            std::vector<std::string> res;
            ans = "";
            std::function<void(int)> _dfs = [&](int i){
                if(i == len){
                    res.emplace_back(ans);
                    return;
                }
                auto ori = ans;
                if(!si.count(words[i])){
                    ans += words[i] + " ";
                    _dfs(i+1);
                    ans = ori;
                }else{
                    for(auto &s : mp[_find(si[words[i]])]){
                        ans += s + " ";
                        _dfs(i + 1);
                        ans = ori;
                    }
                }
            };
            _dfs(0);
            return res;
        }
//给你一种规律 pattern 和一个字符串 str，请你判断 str 是否遵循其相同的规律。 这里我们指的是 完全遵循，例如 pattern 里的每个字母和字符串 str 中每个 非空 单词之间，存在着双向连接的对应规律。
//LeetCode 291. 单词规律 II
        bool wordPatternMatch(std::string pattern, std::string str){
            int len = str.size(), size = pattern.size();
            std::vector<std::string> mp(26);
            std::function<bool(int, int)> _dfs = [&](int i, int j){
                if(j == len)return i == size;
                if(i == size)return j == len;
                if(mp[pattern[i]-'a'].size()){
                    for(auto &c : mp[pattern[i]-'a']){
                        if(j>=len || c!=str[j++])return false;
                    }
                    return _dfs(i+1, j);
                }
                std::string ori = mp[pattern[i]-'a'];
                for(int l=1; l+j<=len; ++l){
                    mp[pattern[i]-'a'] = str.substr(j, l);
                    if(_dfs(i+1, j+l))return true;
                    mp[pattern[i]-'a'] = ori;
                }
                return false;
            };
            return _dfs(0, 0);
        }
//给定一个字符串s，返回它的所有回文排列(不重复)。如果不能形成回文置换，返回一个空列表。
        std::vector<std::string> generatePalidromes(std::string s){
            int len = s.size(), eve = 0, index = -1;
            std::vector<int> mp(26);
            for(auto &c : s)++mp[c-'a'];
            for(int i=0; i<26; ++i){
                if(mp[i]  & 1){
                    ++eve;
                    index = i;
                }
            }
            if(eve > 1)return {};
            std::string ans;
            std::vector<std::string> res;
            std::function<void(int)> _dfs = [&](int i){
                if(i == len){
                    res.emplace_back(ans);
                    return;
                }
                auto ori = ans;
                for(int c=0; c<26; ++c){
                    if(!mp[c])continue;
                    mp[c] -= 2;
                    ans = (char)(c + 'a') + ans + (char)(c + 'a');
                    _dfs(i+2);
                    mp[c] += 2;
                    ans = ori;
                }
            };
            if(eve){
                --mp[index];
                ans = index + 'a';
                _dfs(1);
            }else{
                _dfs(0);
            }
            return res;
        }
//leetcode 1087
        std::vector<std::string> expand(std::string s){
            std::vector<std::string> res;
            int len = s.size();
            std::string ans;
            std::function<void(int)> _dfs = [&](int i){
                if(i == len){
                    res.emplace_back(ans);
                    return;
                }
                if(s[i]!='{'){
                    ans += s[i];
                    _dfs(i+1);
                    ans.pop_back();
                }else{
                    std::vector<char> chars;
                    while(s[i] != '}'){
                        if(std::isalpha(s[i]))chars.emplace_back(s[i]);
                        ++i;
                    }
                    for(auto &x : chars){
                        ans += x;
                        _dfs(i+1);
                        ans.pop_back();
                    }
                }
            };
            _dfs(0);
            return res;
        };
//给一个目标字符串和一个字符串字典，为目标字符串找一个 最短 长度的缩写字符串，同时这个缩写字符串不是字典中其他字符串的缩写形式。 缩写形式中每一个 数字 或者字母都被视为长度为 1 。比方说，缩写形式 "a32bc" 的长度为 4 而不是 5
//[LeetCode] 411. 最短特异单词缩写
        std::string minAbbreviation(std::string target, std::vector<std::string> &dictionary){
            std::vector<std::string> all;
            int len = target.size(), zero = 0;
            std::string temp;
            for(int state=0; state < (1<<len); ++state){
                zero = 0, temp = "";
                for(int i=0; i<len; ++i){
                    if(state & (1<<i)){
                        ++zero;
                    }else{
                        if(zero)temp += zero + '0';
                        temp += target[i];
                        zero = 0;
                    }
                }
                if(zero)temp += '0' + zero;
                all.emplace_back(temp);
            }
            std::sort(begin(all), end(all), [&](auto &s1, auto &s2){
                    return s1.size() < s2.size(); });
            std::function<bool(std::string &, std::string &)> _check
                = [&](std::string &s1, std::string &s2){
                    int len1 = s1.size(), len2 = s2.size();
                    int l1 = 0, l2 = 0, cnt = 0;
                    while(l1 < len1 && l2 < len2){
                        if(std::isdigit(s1[l1])){
                            cnt = 0;
                            while(l1<len1 && std::isdigit(s1[l1])){
                                cnt = cnt * 10 + s1[l1++] - '0';
                            }
                            l2 += cnt;
                        }else if(s1[l1++] != s2[l2++]){
                            return true;
                        }
                    }
                    return l1<len1 || l2<len2;
                };
            for(auto &ans : all){
                int f = 0;
                for(auto &s : dictionary){
                    if(!_check(ans, s)){
                        f = 1;
                        break;
                    }
                }
                if(!f)return ans;
            }
            return "";
        };

//LeetCode 1066. 校园自行车分配 II
//在由 2D 网格表示的校园里有 n 位工人（worker）和 m 辆自行车（bike），n <= m。所有工人和自行车的位置都用网格上的 2D 坐标表示。 我们为每一位工人分配一辆专属自行车，使每个工人与其分配到的自行车之间的曼哈顿距离最小化。 p1 和 p2 之间的曼哈顿距离为 Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y - p2.y|。 返回每个工人与分配到的自行车之间的曼哈顿距离的最小可能总和。
        int assignBikes(std::vector<std::vector<int>> &workers,
                std::vector<std::vector<int>> &bikes){
            int res = INT_MAX, len = workers.size();
            std::vector<int> vi(bikes.size());
            std::function<int(int, int)> _dis = [&](int w, int b){
                return abs(workers[w][0] - bikes[b][0]) + abs(workers[w][1] - bikes[b][1]);
            };
            std::function<void(int, int)> _dfs = [&](int i, int sum){
                if(i == len){
                    res = std::min(res, sum);
                    return;
                }
                if(sum > res)return;
                for(int j=0; j<bikes.size(); ++j){
                    if(vi[j])continue;
                    vi[j] = 1;
                    _dfs(i+1, sum + _dis(i, j));
                    vi[j] = 0;
                }
            };
            _dfs(0, 0);
            return res;
        }
        int assignBikes_(std::vector<std::vector<int>> &workers,
                std::vector<std::vector<int>> &bikes){
            int m = workers.size(), n = bikes.size();
            std::function<int(int, int)> _dis = [&](int w, int b){
                return abs(workers[w][0] - bikes[b][0]) + abs(workers[w][1] - bikes[b][1]);
            };
            const int INF = 0x3f3f3f3f;
            std::vector<std::vector<int>> dp(1 << m, std::vector<int>(n, INF));
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    dp[1<<i][j] = _dis(i, j);
                }
            }
            for(int i=0; i<n; ++i){
                for(int state=0; state<(1<<m); ++state){
                    for(int j=0; j<m; ++j){
                        if(state & (1<<j))continue;
                        for(int k=0; k<i; ++k){
                            dp[state|(1<<j)][i] = std::min(dp[state|(1<<j)][i], dp[state][k] + _dis(j, i));
                        }
                    }
                }
            }
            return *std::min_element(begin(dp[(1<<m)-1]), end(dp[(1<<m)-1]));
        }
        int assignBikes_dp(std::vector<std::vector<int>> &workers,
                std::vector<std::vector<int>> &bikes){
            int m = workers.size(), n = bikes.size();
            std::vector<std::vector<int>> dis(m, std::vector<int>(n));
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    dis[i][j] = abs(workers[i][0] - bikes[j][0]) +
                                abs(workers[i][1] - bikes[j][1]);
                }
            }
            const int INF = 0x3f3f3f3f;
            std::vector<std::vector<int>> dp(1 << m, std::vector<int>(1 << n, INF));
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    dp[1<<i][1<<j] = dis[i][j];
                }
            }
            for(int i=0; i<(1 << m); ++i){
                for(int j=0; j<(1 << n); ++j){
                    int _i = i, _j = j, t = j & (-j);
                    while(_i){
                        int lo = _i & (-_i);
                        dp[i][j] = std::min(dp[i][j], dp[i ^ lo][j ^ t] + dp[lo][t]);
                        _i &= _i - 1;
                    }
                    t = i & (-i);
                    while(_j){
                        int lo = _j & (-_j);
                        dp[i][j] = std::min(dp[i][j], dp[i ^ t][j ^ lo] + dp[t][lo]);
                        _j &= _j - 1;
                    }
                }
            }
            return *std::min_element(begin(dp[(1<<m) - 1]), end(dp[(1<<m) - 1]));
        }
        std::vector<std::string> generateAbbreviations_bit(std::string word){
            std::vector<std::string> res;
            std::string ans;
            int len = word.size(), zero = 0;
            for(int i=0; i<(1 << len); ++i){
                zero = 0, ans = "";
                for(int j=0; j<len; ++j){
                    if(i & (1<<j)){
                        if(zero)ans += '0' + zero;
                        zero = 0;
                        ans += word[j];
                    }else{
                        ++zero;
                    }
                }
                if(zero) ans += zero +'0';
                res.emplace_back(ans);
            }
            return res;
        }
        std::vector<std::string> generateAbbreviations(std::string word){
            std::vector<std::string> res;
            std::string ans;
            int len = word.size();
            std::function<void(int, int)> _dfs = [&](int i, int x){
                if(i == len){
                    if(x)ans += i + '0';
                    res.emplace_back(ans);
                    return;
                }
                auto ori = ans;
                _dfs(i+1, x+1);
                ans = ori;

                if(x) ans += x+'0';
                ans += word[i];
                _dfs(i+1, 0);
                ans = ori;

            };
            _dfs(0, 0);
            return res;
        }
//LeetCode 1088. 易混淆数 II
//易混淆数（Confusing Number）指的是一个数字在整体旋转 180° 以后，能够得到一个和原来 不同 的数，且新数字的每一位都应该是有效的。（请注意，旋转后得到的新数字可能大于原数字） 给出正整数 N，请你返回 1 到 N 之间易混淆数字的数量。
        int confusingNumberII(int N){
            std::vector<int> num {0, 1, 6, 8, 9};
            int res = 0;
            std::function<bool(int)> _ok = [&](int n){
                int ori = n, _new = 0, bit = 0;
                while(n){
                    bit = n % 10;
                    n /= 10;
                    if(n==9){
                        n = 6;
                    }else if(n==6){
                        n = 9;
                    }
                    _new = _new * 10 + bit;
                }
                return ori != _new;
            };
            std::function<void(long long)> _dfs = [&](long long n){
                if(n > N)return;
                res += _ok(n);
                for(auto &b : num)_dfs(n*10+b);
            };
            for(int i=1; i<5; ++i)_dfs(num[i]);
            return res;
        }
//52. N皇后 II
        int totalNqueens_better(int n){
            std::function<int(int, int, int, int)> _dfs
                = [&](int x, int sm, int sl, int sr){
                    if(x == n)return 1;
                    int avai = ((1<<n)-1) & ( ~ (sm | sl | sr)), ans = 0;
                    while(avai){
                        int p = avai & (~avai + 1);
                        ans += _dfs(x+1, sm|p, (sl|p)<<1, (sr|p)>>1);
                        avai &= (avai - 1);
                    }
                    return ans;
                };
            return _dfs(0, 0, 0, 0);
        }
        int totalNqueens(int n){
            int res = 0;
            std::unordered_set<int> s1,s2, s3;
            std::function<void(int)> _dfs
                = [&](int x){
                    if(x == n){
                        ++res;
                        return;
                    }
                    for(int y=0; y<n; ++y){
                        if(s1.count(y) || s2.count(x+y) || s3.count(x-y)){
                            continue;
                        }
                        s1.insert(y), s2.insert(x+y), s3.insert(x-y);
                        _dfs(x+1);
                        s1.erase(y), s2.erase(x+y), s3.erase(x-y);
                    }
                };
            _dfs(0);
            return res;
        }
//89. 格雷编码
        std::vector<int> grayCode(int n){
            std::vector<int> res;
            for(int i=0; i<(1<<n); ++i){
                res.push_back(i ^ (i >> 1));
            }
            return res;
        }

//22. 括号生成
        std::vector<std::string> generateParenthesis(int n){
            std::vector<std::string> res;
            std::string ans;
            std::function<void(int)> _dfs = [&](int dif){
                if(dif > 0)return;
                if(ans.size() == (n << 1)){
                    if(!dif)res.emplace_back(ans);
                    return;
                }
                ans += '(';
                _dfs(dif-1);
                ans.pop_back();

                ans += ')';
                _dfs(dif+1);
                ans.pop_back();
            };
            _dfs(0);
            return res;
        }
//1291. 顺次数
        std::vector<int> squentialDigits_(int low, int high){
            std::vector<int> res;
            for(int i=1; i<=9; ++i){
                int num = i;
                for(int j=i+1; j<=9 && num <= high; ++j){
                    num = num * 10 + j;
                    if(num >= low){
                        res.emplace_back(num);
                    }
                }
            }
            return res;
        }
        std::vector<int> squentialDigits(int low, int high){
            std::vector<int> all {12,23,34,45,56,67,78,89,123,234,345,456,567,678,789,1234,2345,3456,4567,5678,6789,12345,23456,34567,45678,56789,123456,234567,345678,456789,1234567,2345678,3456789,12345678,23456789,123456789 };
            return
               {std::lower_bound(begin(all), end(all), low),
                std::upper_bound(begin(all), end(all), high)};
        }
//1079. 活字印刷
        int numTilePossibilities(std::string tiles){
            std::sort(begin(tiles), end(tiles));
            int res = 0, len = tiles.size(), state = 0;
            std::function<void(void)> _dfs = [&](void){
                res += !!state;
                for(int i=0; i<len; ++i){
                    if(i && !(state & (1<<(i-1)))
                       && tiles[i] == tiles[i-1]) continue;
                    if(state & (1 << i))continue;
                    state |= (1 << i);
                    _dfs();
                    state ^= (1 << i);
                }
            };
            _dfs();
            return res;
        }
//784. 字母大小写全排列
        std::vector<std::string> letterCasePermutation(std::string S){
            int len = S.size();
            std::vector<std::string> res;
            std::string ans;
            std::function<void(int)> _dfs = [&](int i){
                if(i == len){
                    res.emplace_back(ans);
                    return;
                }
                if(std::isalpha(S[i])){
                    ans += std::islower(S[i]) ? std::toupper(S[i]) : std::tolower(S[i]);
                    _dfs(i+1);
                    ans.pop_back();
                }
                ans += S[i];
                _dfs(i+1);
                ans.pop_back();
            };
            _dfs(0);
            return res;
        }
//1219. 黄金矿工
        int getMaximumGold(std::vector<std::vector<int>> &grid){
            int m = grid.size(), n = grid[0].size(), res = 0;
            std::vector<int> _fun = {0, 1, 0, -1, 0};
            std::function<int(int, int)> _dfs = [&](int x, int y){
                if(!grid[x][y])return 0;
                int t = grid[x][y];
                grid[x][y] = 0;
                int ans = 0;
                for(int f=0; f<4; ++f){
                    int i = x + _fun[f];
                    int j = y + _fun[f+1];
                    if(i<0 || j<0 || i>=m || j>=n)continue;
                    if(!grid[i][j])continue;
                    ans = std::max(ans, _dfs(i, j));
                }
                grid[x][y] = t;
                return ans + t;
            };
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    if(!grid[i][j])continue;
                    res = std::max(res, _dfs(i, j));
                }
            }
            return res;
        }
//306. 累加数
        bool isAddiriveNumber(std::string num){
            int len = num.size();
            std::function<bool(int, int, float, float)> _dfs
                = [&](int i, int n, float ppre, float pre){
                if(i == len)return n > 2;
                for(int l=1; i+l<=len; ++l){
                    if(l!=1 && num[i]=='0')continue;
                    float now = std::stof(num.substr(i, l));
                    if(ppre==-1 || ppre + pre == now){
                        if(_dfs(i+l, n+1, pre, now))return true;
                    }else if(ppre + pre < now){
                        return false;
                    }
                }
                return false;
            };
            return _dfs(0, 0, -1, -1);
        }
//1307. 口算难题
        bool isSolvable(std::vector<std::string> &words, std::string result){
            std::vector<std::vector<int>> op(8, std::vector<int>(26));
            std::vector<std::vector<int>> chars(8);
            std::vector<int> zero(26);
            words.emplace_back(result);
            int len = words.size();
            for(int i=0; i<len; ++i){
                int index = 0;
                zero[words[i][0]-'A'] = words[i].size() > 1;
                for(int j=words[i].size()-1; j>=0; --j){
                    op[index++][words[i][j]-'A'] += (i==len-1) ? -1 : 1;
                }
            }
            int state = 0;
            for(int i=0; i<8; ++i){
                for(int j=0; j<op[i].size(); ++j){
                    if(op[i][j] == 0)continue;
                    if(state & (1<<j))continue;
                    state |= (1<<j);
                    chars[i].emplace_back(j+'A');
                }
            }
            std::vector<int> cn(26, -1);
            std::function<bool(int, int&)> _check = [&](int lv, int &inc){
                auto &opl = op[lv];
                int sum = inc;
                for(int i=0; i<26; ++i){
                    sum += opl[i] * cn[i];
                }
                inc = sum / 10;
                return !(sum % 10);
            };
            state = 0;
            std::function<bool(int, int, int)> _dfs = [&](int lv, int lvi, int inc){
                if(lvi == chars[lv].size()){
                    return
                       _check(lv, inc) && (lv==7 || _dfs(lv+1, 0, inc));
                }
                char c = chars[lv][lvi];
                for(int i=0; i<10; ++i){
                    if(state & (1<<i))continue;
                    if(!i && zero[c-'A'])continue;
                    cn[c-'A'] = i;
                    state |= (1 << i);
                    if(_dfs(lv, lvi+1, inc))return true;
                    state ^= (1 << i);
                }
                return false;
            };
            return _dfs(0, 0, 0);
        }
        bool isSolvable_fuck(std::vector<std::string> &words, std::string result){
            std::map<char, int> mp;
            std::function<bool(void)> _check = [&](void){
                if(!mp[result[0]] && result.size() == 1)return false;
                std::string t;
                for(auto &c : result)t += mp[c] + '0';
                int ans = std::stoi(t);
                int sum = 0;
                for(auto &wd : words){
                    t = "";
                    if(!mp[wd[0]] && wd.size() == 1)return false;
                    for(auto &c : wd)t += mp[c] + '0';
                    sum += std::stoi(t);
                }
                return sum == ans;
            };
            std::unordered_set<char> chars;
            for(auto &c : result)chars.insert(c);
            for(auto &wd : words){
                for(auto &c : wd)chars.insert(c);
            }
            int size = chars.size();
            int cs = 0, ns = 0;
            std::function<bool(void)> _dfs = [&](void){
                if(mp.size() == size)return _check();
                for(auto &c : chars){
                    if((1<<(c-'A')) & cs)continue;
                    cs |= (1<<(c-'A'));
                    for(int i=0; i<=9; ++i){
                        if((1<<i) & ns)continue;
                        ns |= (1<<i);
                        mp.insert({c, i});
                        if(_dfs())return true;
                        mp.erase(c);
                        ns ^= (1<<i);
                    }
                    cs ^= (1<<(c-'A'));
                }
                return false;
            };
            return _dfs();
        }
//526. 优美的排列
        int countArrangement(int N){
            int res   = 0;
            int state = 0;
            std::function<void(int)> _dfs = [&](int i){
                if(i == N + 1){
                    ++res;
                    return;
                }
                for(int n=1; n<=N; ++n){
                    if(!((1<<n)&(state)) && (!(i%n) || !(n%i))){
                        state |= (1<<n);
                        _dfs(i+1);
                        state ^= (1<<n);
                    }
                }
            };
            _dfs(1);
            return res;
        }
//212. 单词搜索 II
        std::vector<std::string> findWords(std::vector<std::vector<char>> &board,
                std::vector<std::string> &words){
            int m = board.size(), n = m ? board[0].size() : 0;
            if(!m || !n)return {};
            struct _node{
                std::vector<_node*> next;
                std::string end;
                _node () : next (26,0) {}
                ~_node(){
                    for(auto node : next){
                        if(node) delete node;
                    }
                }
            };
            _node *root = new _node();
            for(auto &wd : words){
                _node *cur = root;
                for(auto &c : wd){
                    int index = c - 'a';
                    if(cur->next[index] == 0)cur->next[index] = new _node ();
                    cur = cur->next[index];
                }
                cur->end = wd;
            }
            std::vector<int> _fun {0, 1, 0, -1, 0};
            std::vector<std::string> res;
            std::function<void(_node *, int, int)> _dfs
                = [&](_node *head, int i, int j){
                    char c = board[i][j];
                    if(head->next[c-'a'] == 0)return;
                    head = head->next[c-'a'];
                    if(head->end.size()){
                        res.emplace_back(head->end);
                        head->end = "";
                    }
                    board[i][j] = '.';
                    for(int f=0; f<4; ++f){
                        int x = i + _fun[f];
                        int y = j + _fun[f+1];
                        if(x<0 || y<0 || x>=m || y>=n)continue;
                        if(board[x][y] == '.')continue;
                        _dfs(head, x, y);
                    }
                    board[i][j] = c;
            };
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    _dfs(root, i, j);
                }
            }
            return res;
        }

//93. 复原IP地址93. 复原IP地址
        std::vector<std::string> restoreIpAddresses(std::string s){
            int len = s.size();
            if(len > 12)return {};
            std::vector<std::string> res;
            std::string ans;
            std::function<void(int, int)> _dfs = [&](int i, int cnt){
                if(i == len){
                    if(cnt == 4){
                        res.emplace_back(ans);
                        res.back().pop_back();
                    }
                    return;
                }
                if(cnt == 4)return;
                for(int l=1; i+l<=len && l<=3; ++l){
                    if(l>1 && s[i]=='0')continue;
                    int now = std::stoi(s.substr(i, l));
                    if(now > 255)continue;
                    for(int j=0; j<l; ++j)ans += s[i+j];
                    ans += '.';
                    _dfs(i+l, cnt+1);
                    ans.pop_back();
                    for(int j=0; j<l; ++j)ans.pop_back();
                }
            };
            _dfs(0, 0);
            return res;
        }
//面试题 08.07. 无重复字符串的排列组合
        std::vector<std::string> permutationII(std::string S){
            int len = S.size();
            std::string ans;
            std::vector<int> vi(len);
            std::vector<std::string> res;
            std::function<void(void)> _dfs = [&](void){
                if(ans.size() == len){
                    res.emplace_back(ans);
                    return ;
                }
                for(int i=0; i<len; ++i){
                    if(vi[i])continue;
                    vi[i] = 1;
                    ans += S[i];
                    _dfs();
                    vi[i] = 0;
                    ans.pop_back();
                }
            };
            _dfs();
            return res;
        }
//面试题 08.08. 有重复字符串的排列组合
        std::vector<std::string> permutationI(std::string S){
            std::vector<std::string> res;
            std::string ans;
            int len = S.size();
            std::vector<int> vi(len);
            std::function<void(void)> _dfs = [&](void){
                if(ans.size() == len){
                    res.emplace_back(ans);
                    return;
                }
                for(int j=0; j<len; ++j){
                    if(j && !vi[j-1] && S[j] == S[j-1])continue;
                    if(vi[j])continue;
                    vi[j] = 1;
                    ans += S[j];
                    _dfs();
                    vi[j] = 0;
                    ans.pop_back();
                }
            };
            std::sort(begin(S), end(S));
            _dfs();
            return res;
        }
//1239. 串联字符串的最大长度
        int maxLength_better(std::vector<std::string> &arr){
            int len = arr.size();
            std::function<bool(int , int &)> _ok = [&](int i, int &s){
                for(auto &c : arr[i]){
                    if((1<<(c-'a')) & s)return false;
                    s |= (1<<(c-'a'));
                }
                return true;
            };
            std::function<int(int, int &)> _dfs = [&](int i, int &state){
                if(i == len)return 0;
                int s = state;
                if(!_ok(i, s))return _dfs(i+1, state);
                return std::max((int)arr[i].size() + _dfs(i+1, s), _dfs(i+1, state));
            };
            int state = 0;
            return _dfs(0, state);
        }
        int maxLength(std::vector<std::string> &arr){
            int res = 0, len = arr.size();
            std::function<int(int)> _calc = [&](int state){
                int word = 0, ans = 0;
                while(state){
                    int index = __builtin_ctz(state);
                    state &= (state - 1);
                    for(char &c : arr[index]){
                        if((1<<(c-'a')) & word)return -1;
                        word |= (1<<(c-'a'));
                        ++ans;
                    }
                }
                return ans;
            };
            for(int state=0; state<(1<<len); ++state){
                res = std::max(res, _calc(state));
            }
            return res;
        }
//842. 将数组拆分成斐波那契序列
        std::vector<int> splitIntorFibonacci(std::string S){
            int len = S.size();
            std::vector<int> res;
            std::function<bool(int)> _dfs = [&](int i){
                int size = res.size();
                if(i == len) return size >= 3;
                for(int l=1; l+i<=len && l<=10; ++l){
                    long long now = std::stoull(S.substr(i, l));
                    if(now > INT_MAX)continue;
                    if(l>1 && S[i]=='0')continue;
                    if(size > 1 && (long long)res[size-1] + (long long)res[size-2] != now)continue;
                    res.push_back(now);
                    if(_dfs(i+l))return true;
                    res.pop_back();
                }
                return false;
            };
            return _dfs(0) ? res : std::vector<int>{};
        }

//1467. 两个盒子中球的颜色数相同的概率
        double getProbability(std::vector<int> &balls){
            std::function<double(int)> _fac = [&](int a){
                double ans = 1;
                for(int i=1; i<=a; ++i)ans *= i;
                return ans;
            };
            int len = balls.size(), all = std::accumulate(begin(balls), end(balls), 0) >> 1;
            std::function<double(std::vector<int> &)> _comb = [&](std::vector<int> &b){
                int sum = std::accumulate(begin(b), end(b), 0);
                double ans = _fac(sum);
                for(auto &x : b) ans /= _fac(x);
                return ans;
            };
            double ln = 0, rn = 0, fz = 0;
            std::vector<int> left(len), right(len);
            std::function<void(int)> _dfs = [&](int n){
                if(ln > all || rn > all)return;
                if(n == left.size()){
                    int l = 0, r = 0;
                    for(auto x : left)l += !!x;
                    for(auto x : right)r += !!x;
                    if(l == r)fz += _comb(left) * _comb(right);
                    return ;
                }
                for(int i=0; i<=balls[n]; ++i){
                    left[n]  = i;
                    right[n] = balls[n] - i;
                    ln += i, rn += balls[n] - i;
                    _dfs(n + 1);
                    ln -= i, rn -= balls[n] - i;
                }
            };
            double t = _comb(balls);
            _dfs(0);
            return fz / t;
        }
//1415. 长度为 n 的开心字符串中字典序第 k 小的字符串
        std::string getHappyString(int n, int k){
            std::set<std::string> mp;
            std::string ans;
            std::function<void(int)> _dfs = [&](int i){
                if(i == n){
                    mp.insert(ans);
                    return;
                }
                for(int j=0; j<3; ++j){
                    if(i && ans[i-1] == j+'a')continue;
                    ans += j + 'a';
                    _dfs(i+1);
                    ans.pop_back();
                }
            };
            _dfs(0);
            if(mp.size() < k)return "";
            for(auto &s : mp){
                if(!--k)return s;
            }
            return "";
        }
//面试题 08.12. 八皇后
        std::vector<std::vector<std::string>> solveNqueens_better(int n){
            std::vector<std::string> ans(n, std::string(n, '.'));
            std::vector<std::vector<std::string>> res;
            std::unordered_set<int> s1, s2, s3;
            std::function<void(int)> _dfs = [&](int i){
                if(i == n){
                    res.emplace_back(ans);
                    return;
                }
                for(int j=0; j<n; ++j){
                    if(s1.count(j) || s2.count(i+j) || s3.count(i-j)){
                        continue;
                    }
                    s1.insert(j), s2.insert(i+j), s3.insert(i-j);
                    ans[i][j] = 'Q';
                    _dfs(i+1);
                    s1.erase(j), s2.erase(i+j), s3.erase(i-j);
                    ans[i][j] = '.';
                }
            };
            _dfs(0);
            return res;
        }
        std::vector<std::vector<std::string>> solveNqueens(int n){
            std::vector<std::string> ans(n, std::string(n, '.'));
            std::vector<std::vector<std::string>> res;
            std::vector<std::pair<int, int>> mp;
            std::function<void(int)> _dfs = [&](int i){
                if(i == n){
                    res.emplace_back(ans);
                    return;
                }
                for(int j=0; j<n; ++j){
                    int f = 0;
                    for(auto &[x, y] : mp){
                        if(j==y || i+j==x+y || i-j==x-y){
                            f = 1;
                            break;
                        }
                    }
                    if(f)continue;
                    mp.emplace_back(i, j);
                    ans[i][j] = 'Q';
                    _dfs(i+1);
                    mp.pop_back();
                    ans[i][j] = '.';
                }
            };
            _dfs(0);
            return res;
        }
};

template<class T>
void debug(std::vector<T> &arr, std::string M="\n"){
    for(auto &x : arr){
        std::cout<<x<<"   "+M;
    }
    std::cout<<std::endl;
}
template<class T>
void debug(std::vector<std::vector<T>> &arr, std::string M=""){
    for(auto &vals : arr){
        for(auto &x : vals){
            std::cout<<x<<"   "+M;
        }
        std::cout<<std::endl;
    }
}
int main(int argc,const char *argv[]){
    Solution te;
    int m = 1, n = 1;
    std::cout<<te.numberOfPatterns_better(m, n)<<std::endl;
    //int n = 32;
    //int n = 12;
    //auto arr = te.getFactors(n);
    //auto arr = te.getFactors_better(n);
    //debug(arr);
    //int l = 0, r = 123;
    //auto arr = te.countSteppingNumbers(l, r);
    //debug(arr);
    //std::vector<std::string> words {"area","lead","wall","lady","ball"};
    //std::vector<std::string> words { "abat","baba","atan","atal" };
    //auto arr = te.wordSquares(words);
    //debug(arr);
    //std::string s {"+-++"};
    //std::string s {"++++"};
    //std::string s {"+++++"};
    //std::cout<<te.canWin(s)<<std::endl;
    //std::vector<std::vector<std::string>> s { { "happy","joy" },{ "sad","sorrow" },{ "joy","cheerful" } };
    //std::string str {"I am happy today but was sad yesterday"};
    //auto arr = te.generateSentences(s, str);
    //debug(arr);
    //std::string p {"abab"};
    //std::string s {"redblueredblue"};
    //std::string p {"aaaa"};
    //std::string s {"asdasdasdasd"};
    //std::string p {"aabb"};
    //std::string s {"xyzabcxzyabc"};
    //std::cout<<te.wordPatternMatch(p, s)<<std::endl;
    //std::string wd {"kkiioonnbbvvccyioiyyy"};
    //auto arr = te.generatePalidromes(wd);
    //debug(arr);
    //std::string s {"{a,b}c{d,e}f"};
    //std::string s {"{a,b}{d,e}f"};
    //std::string s {"abdef"};
    //auto x = te.expand(s);
    //debug(x);
    //std::cout<<std::isdigit('0')<<std::endl;
    //std::string word = "apple";
    //std::vector<std::string> all {"blade"};
    //std::vector<std::string> all {"plain", "amber", "blade"};
    //std::cout<<te.minAbbreviation(word, all)<<std::endl;
    //std::vector<std::vector<int>> wo {{0, 0}, {2, 1}};
    //std::vector<std::vector<int>> bi {{1, 2}, {3, 3}};
    //std::vector<std::vector<int>> wo {{0, 0}, {1, 1}, {2, 0}};
    //std::vector<std::vector<int>> bi {{1, 0}, {2, 2}, {2, 1}};
    //std::cout<<te.assignBikes_(wo, bi)<<std::endl;
    //std::cout<<te.assignBikes(wo, bi)<<std::endl;
    //std::cout<<te.assignBikes_dp(wo, bi)<<std::endl;
    //std::cout<<std::endl;
    //std::vector<std::vector<int>> wo1 {{0, 1}, {2, 1}, {2, 1}};
    //std::vector<std::vector<int>> bi1 {{1, 0}, {2, 2}, {2, 1}, {0, 1}, {2, 4}};
    //std::cout<<te.assignBikes_(wo1, bi1)<<std::endl;
    //std::cout<<te.assignBikes(wo1, bi1)<<std::endl;
    //std::cout<<te.assignBikes_dp(wo1, bi1)<<std::endl;
    //std::cout<<std::endl;
    //std::vector<std::vector<int>> wo2 {{4, 1}, {2, 3}, {1, 1},{0, 1}, {2, 1}, {2, 1}};
    //std::vector<std::vector<int>> bi2 {{1, 0}, {2, 2}, {2, 1}, {0, 1}, {2, 4}, {4, 5}, {2, 3}, {1, 1}};
    //std::vector<std::vector<int>> bi3 {{5, 5}, {0, 0}, {3, 1}, {6, 3}, {1, 0}, {2, 2}, {2, 1}, {0, 1}, {2, 4}, {4, 5}, {2, 3}, {1, 1}};
    //std::cout<<te.assignBikes_(wo2, bi2)<<std::endl;
    //std::cout<<te.assignBikes(wo2, bi2)<<std::endl;
    //std::cout<<te.assignBikes_dp(wo2, bi2)<<std::endl;
    //std::cout<<std::endl;
    //std::cout<<te.assignBikes_(wo, bi3)<<std::endl;
    //std::cout<<te.assignBikes(wo, bi3)<<std::endl;
    //std::cout<<te.assignBikes_dp(wo, bi3)<<std::endl;
    //std::cout<<std::endl;
    //std::string word {"qwert"};
    //auto res0 = te.generateAbbreviations(word);
    //auto res1 = te.generateAbbreviations(word);
    //debug(res0);
    //debug(res1);
    //return 0;
}
