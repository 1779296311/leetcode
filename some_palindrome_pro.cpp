/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_palindrome_pro.cpp
*     author   : @ JY
*     date     : 2020--04--14
**********************************************/
#include <iostream>
#include <cmath>
#include <climits>
#include <vector>
#include <algorithm>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        //最少在结尾添加字符可以变成回文串
        int min_add_end(string a){
            string res(a);
            a        = init(a);
            int size = a.length();
            vector<int> p(size,0);
            int right = 0;
            int mid   = 0;
            for(int i=0; i<size; ++i){
                p[i] = right>i?min(right-i,p[(mid<<1)-i]):1;
                while(i+p[i]<size && i-p[i]>=0 && a[i+p[i]] == a[i-p[i]]){
                    ++p[i];
                }
                if(i+p[i] > right){
                    right = i+p[i];
                    mid   = i;
                }
                if(right == size-1){
                    break;
                }
            }
            string tmp(res);
            int s = mid-(right>>1)-1;
            for(int i=s; i>=0; --i){
                res = res + tmp[i];
            }
            cout<<res<<endl;
            return ++s;
        }
        //最少任意位置添加字符可以变成回文串
        int min_add_all(string a){
            int size = a.length();
            vector<vector<int>> dp(size,vector<int>(size,0));
            for(int d=1; d<size; ++d){
                for(int l=0; l+d<size; ++l){
                    int r = l + d;
                    if(a[l] == a[r]){
                        dp[l][r] = dp[l+1][r-1];
                    }else{
                        dp[l][r] = min(dp[l+1][r],dp[l][r-1])+1;
                    }
                }
            }
            return dp[0][size-1];
        }
        string init(string a){
            string tmp = "#";
            for(int i=0; i<a.length(); ++i){
                tmp = tmp + a[i] + "#";
            }
            return tmp;
        }
        //最长回文子串
        int manacher(string a){
            a         = init(a);
            int size  = a.length();
            int __res = 0;
            vector<int> p(size,0);
            int right = 0;
            int mid   = 0;
            for(int i=0; i<size; ++i){
                p[i]  = right>i?(min(right-i,p[(mid<<1)-i])):1;
                while(i+p[i]<size && i-p[i]>=0 && a[i+p[i]] == a[i-p[i]]){
                    ++p[i];
                }
                if(p[i]+i > right){
                    right = p[i] + i;
                    mid   = i;
                }
                __res = max(p[i],__res);
            }
            return --__res;
        }
        //最长回文子序列
        int longest_XL(string a){
            string b(a);
            reverse(b.begin(),b.end());
            return longest_XL(a,b);
        }
        //最长公共子串
        int longest_Son(string a, string b){
            int sizea = a.length();
            int sizeb = b.length();
            int row   = 0;
            int col   = sizeb - 1;
            int len   = 0;
            int end   = 0;
            int __res = 0;
            while(row<sizea){
                int r = row;
                int c = col;
                len   = 0;
                while(r<sizea && c<sizeb){
                    if(a[r] == b[c]){
                        ++len;
                    }else{
                        len = 0;
                    }
                    if(__res < len){
                        __res = len;
                        end   = r;
                    }
                    ++c;
                    ++r;
                }
                if(col>0){
                    --col;
                }else{
                    ++row;
                }
            }
            return __res;
        }
        //最长公共子序列
        int longest_XL(string a, string b){
            int sizea = a.length();
            int sizeb = b.length();
            vector<int> dp(sizea+1,0);
            int oldN  = 0;
            int newN  = 0;
            int __res = 0;
            for(int i=1; i<=sizeb; ++i){
                for(int j=1; j<=sizea; ++j){
                    newN  = dp[j];
                    dp[j] = max(dp[j],dp[j-1]);
                    if(a[j-1] == b[i-1]){
                        dp[j] = oldN + 1;
                    }
                    oldN  = newN;
                    __res = max(__res,dp[j]);
                }
                oldN = 0;
            }
            return __res;
        }
        //最shao划分
        int min_split_palindrome(string a){
            int size = a.length();
            if(!size){
                return 0;
            }
            vector<vector<bool>> dp_1(size,vector<bool>(size,0));
            get_array(a,dp_1);
            vector<int> dp(size+1,INT_MAX);
            dp[0] = 0;
            for(int i=1; i<=size; ++i){
                for(int j=0; j<i; ++j){
                    if(dp_1[j][i-1]){
                        dp[i] = min(dp[i],dp[j]+1);
                    }
                }
            }
            //debug(dp);
            return dp[size]-1;
        }
        void get_array(string a, vector<vector<bool>>& dp){
            int size = a.length();
            for(int d=0; d<size; ++d){
                for(int left=0; left+d<size; ++left){
                    int right = left + d;
                    if(!d || (dp[left+1][right-1]&&(a[left]==a[right]))){
                        dp[left][right] = true;
                    }
                }
            }
        }
        void debug(vector<int>& a){
            for(int i=0; i<a.size();++i){
                cout<<a[i]<<"  ";
            }
            cout<<endl;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    string a3 = "asjaskdjlasjdlkasfoiqefhadglsjdhffddkajsfh";
    string c3 = "aaaaaaaaaasjaskdjlasjdlkasfoiqefhadglsjdhffddkajsfhasdassdasdjahsfjhalkfzlvxhklxcvxhvsdkdjlajsdlkafsoiqehfadglsjdhffddkajsfh";

    string b = "abadab";
    string a = "baaaass";
    string c = "s";
    cout<<te.min_add_end(a)<<endl;
    //cout<<a3.length()<<endl;;
    //cout<<te.longest_Son(a,c)<<endl;
    //cout<<te.min_split_palindrome(a)<<endl;
    //cout<<te.min_add_all(b)<<endl;
    //cout<<a<<endl;
    //cout<<te.min_add_end(a)<<endl;
    //cout<<"------"<<endl;
    //cout<<te.min_add_end(a)<<endl;
    //cout<<"------"<<endl;
    //cout<<te.min_add_end(c)<<endl;
    //cout<<te.longest_XL(c)<<endl;
    //cout<<te.longest_Son(b,c)<<endl;
    //cout<<te.longestPalindrome_XL(c,b)<<endl;
    //cout<<te.manacher(a)<<endl;
    return 0;
}
