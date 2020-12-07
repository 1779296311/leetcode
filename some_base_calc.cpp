/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_base_calc.cpp
*     author   : @ JY
*     date     : 2020--09--29
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cstring>
#include <climits>
#include <functional>
#include <numeric>
#include <queue>
#include <map>
#include <stack>
#include <stdlib.h>
#include <cmath>

class Solution{
    public:
//770. 基本计算器 IV
        std::vector<std::string> caculateIIII(std::string &expression,
                std::vector<std::string> &evalvars, std::vector<int> &evalints){
            using vs   = std::vector<std::string>;
            struct _cmp{
                bool operator()(const vs &a, const vs &b) const{
                    return a.size()==b.size()?a<b:a.size()>b.size(); }
            };
            using mvsi = std::map<vs, int, _cmp>;
            std::unordered_map<std::string, int> e_v;
            int size = evalvars.size();
            for(int i=0; i<size; ++i)e_v[evalvars[i]] = evalints[i];
            std::function<mvsi(std::string &)> _calc = [&](std::string &exp){
                    mvsi mul = {{{},1}}, ans;
                    std::string sub = "";
                    int f   = 1;
                    int len = exp.size();
                    for(int i=0; i<=len; ++i){
                        if(i<len && ' ' == exp[i])continue;
                        if(i<len && std::isalnum(exp[i])){
                            sub += exp[i];
                        }else if(i<len && '(' == exp[i]){
                            ++i;
                            for(int k=1; ;++i){
                                k += exp[i]=='(';
                                k -= exp[i]==')';
                                if(!k)break;
                                sub += exp[i];
                            }
                        }else{
                            if(sub.size()==len){
                                if(e_v.count(sub))return mvsi{{{}, e_v[sub]}};
                                if(std::isdigit(sub[0]))return mvsi{{{},std::stoi(sub)}};
                                return mvsi{{{sub}, 1}};
                            }
                            mvsi va, temp;
                            if(sub.size())va = _calc(sub);
                            for(auto &&[v1, n1] : mul){
                                for(auto &&[v2, n2] : va){
                                    vs t = v1;
                                    t.insert(end(t), begin(v2), end(v2));
                                    std::sort(begin(t), end(t));
                                    temp[t] += n1 * n2;
                                }
                            }
                            mul = std::move(temp);
                            if(i==len || exp[i]!='*'){
                                for(auto &&[v, n] : mul)ans[v] += n*f;
                                f   = i<len&&exp[i]=='-'?-1:1;
                                mul = {{{}, 1}};
                            }
                            sub = "";
                        }
                    }
                    return ans;
                };
            mvsi ans = _calc(expression);
            vs res;
            for(auto &&[v , n] : ans){
                if(!n)continue;
                res.push_back(std::to_string(n));
                for(auto &r : v)res.back() += '*'+r;
            }
            return res;
        }
//227. 基本计算器 II
        int calculateII(std::string s){
            int len = s.length();
            std::unordered_set<char> op = {'+', '-', '*', '/', ')'};
            std::function<int(int &)> _calc = [&](int &i){
                std::stack<int> st;
                char pre_op   = '+';
                int  pre_num  = 0;
                long long num = 0;
                for(; i<len; ++i){
                    if(std::isdigit(s[i]))num = num*10+s[i]-'0';
                    if(s[i]=='(')num = _calc(++i),++i;
                    if(i>=len-1 || op.count(s[i])){
                        switch(pre_op){
                            case '+':
                                st.push(num);
                                break;
                            case '-':
                                st.push(-num);
                                break;
                            case '*':
                                pre_num = st.top();st.pop();
                                st.push(pre_num * num);
                                break;
                            case '/':
                                pre_num = st.top();st.pop();
                                st.push(pre_num / num);
                                break;
                        }
                        num = 0;
                        if(i<len)pre_op = s[i];
                    }
                    if(s[i]==')')break;
                }
                int ans = 0;
                while(st.size()){
                    ans += st.top();
                    st.pop();
                }
                return ans;
            };
            int begin = 0;
            return _calc(begin);
        }
//224. 基本计算器
        int calculateI(std::string s){
            std::stack<int> sign;
            sign.push(1);
            long long num = 0;
            int res = 0;
            int f   = 1;
            for(char c : s){
                if(c==' ')continue;
                if(std::isdigit(c)){
                    num = num * 10 + c - '0';
                    continue;
                }
                res += f*num;
                num = 0;
                if(c=='-'){
                    f = -sign.top();
                }else if(c=='+'){
                    f = sign.top();
                }else if(c=='('){
                    sign.push(f);
                }else{
                    sign.pop();
                }
            }
            return res + f*num;
        }
};
