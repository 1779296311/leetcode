/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_split_pro.cpp
*     author   : @ JY
*     date     : 2020--04--26
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        //
        int splitA_ZDP(string s){
            int size = s.length();
            int pre  = s[size-1]=='0'?0:1;
            int tmp  = pre;
            int next = 1;
            for(int i=size-2; i>=0; --i){
                if(s[i] == '0'){
                    next = pre;
                    pre  = 0;
                }else{
                    tmp = pre;
                    if((s[i]-'0')*10+s[i+1]-'0' < 27){
                        pre = pre + next;
                    }
                    next = tmp;
                }
            }
            return pre;
        }
        int splitA_Z(string s){
            return process1(s,0);
        }
        int process1(string a, int index){
            if(index>=a.length()){
                return 1;
            }
            if(a[index] == '0'){
                return 0;
            }
            int res = process1(a,index+1);
            if(index<a.length()-1 && (a[index]-'0')*10+a[index+1]-'0' < 27){
                res = res + process1(a,index+2);
            }
            return res;
        }
/*---------------------------------------------------------------------------------------------------------------------------*/
        //express="1^0|0|0|1"
        int split_EXDP(string exp, bool target){
            int size = exp.length();
            vector<vector<int>> t(size,vector<int>(size,0));
            vector<vector<int>> f(size,vector<int>(size,0));
            for(int i=0; i<size; i=i+2){
                t[i][i] = exp[i]=='1'?1:0;
                f[i][i] = exp[i]=='1'?0:1;
                for(int j=i-2; j>=0; j=j-2){
                    for(int k=j; k<i; k=k+2){
                        switch(exp[k+1]){
                            case '|':
                                t[j][i] += t[j][k]*t[k+2][i] + f[j][k]*t[k+2][i] + t[j][k]*f[k+2][i];
                                f[j][i] += f[j][k]*f[k+2][i];
                                break;
                            case '&':
                                t[j][i] += t[j][k]*t[k+2][i];
                                f[j][i] += f[j][k]*f[k+2][i] + f[j][k]*t[k+2][i] + t[j][k]*f[k+2][i];
                                break;
                            case '^':
                                t[j][i] += f[j][k]*t[k+2][i] + t[j][k]*f[k+2][i];
                                f[j][i] += f[j][k]*t[k+2][i] + t[j][k]*f[k+2][i];
                                break;
                        }
                    }
                }
            }
            return target?t[0][size-1]:f[0][size-1];
        }
        int split_EX(string exp, bool target){
            return process2(exp,target,0,exp.length()-1);
        }
        int process2(string exp, bool target, int l, int r){
            if(l == r){
                if(exp[l] == '1'){
                    return target?1:0;
                }else{
                    return target?0:1;
                }
            }
            int res = 0;
            if(target){
                for(int i=l+1; i<r; i=i+2){
                    if(exp[i] == '|'){
                        res += process2(exp,target,l,i-1)  * process2(exp,target,i+1,r);
                        res += process2(exp,!target,l,i-1) * process2(exp,target,i+1,r);
                        res += process2(exp,target,l,i-1)  * process2(exp,!target,i+1,r);
                    }else if(exp[i] == '&'){
                        res += process2(exp,target,l,i-1)  * process2(exp,target,i+1,r);
                    }else if(exp[i] == '^'){
                        res += process2(exp,target,l,i-1)  * process2(exp,!target,i+1,r);
                        res += process2(exp,!target,l,i-1) * process2(exp,target,i+1,r);
                    }
                }
            }else{
                for(int i=l+1; i<r; i=i+2){
                    if(exp[i] == '|'){
                        res += process2(exp,target,l,i-1)  * process2(exp,target,i+1,r);
                    }else if(exp[i] == '&'){
                        res += process2(exp,target,l,i-1)  * process2(exp,target,i+1,r);
                        res += process2(exp,!target,l,i-1) * process2(exp,target,i+1,r);
                        res += process2(exp,target,l,i-1)  * process2(exp,!target,i+1,r);
                    }else if(exp[i] == '^'){
                        res += process2(exp,!target,l,i-1) * process2(exp,target,i+1,r);
                        res += process2(exp,target,l,i-1)  * process2(exp,!target,i+1,r);
                    }
                }
            }
            return res;
        }
/*---------------------------------------------------------------------------------------------------------------------------*/
        bool is_KH(string a) {
            int t = 0;
            for(int i=0; i<a.length(); ++i){
                if(a[i] == '('){
                    ++t;
                }else if(--t < 0){
                    return false;
                }
            }
            return t==0;
        }
        int longest_KH(string a){
            int res = 0;
            for(int i=a.length()-1; i>0; --i){
                if(a[i] == ')'){
                    res = max(res,process3(a,i));
                }
            }
            return res;
        }
        int process3(string a, int index){
            if(index==0){
                return 0;
            }
            if(a[index] == '('){
                return 0;
            }else if(a[index] ==')'){
                int d = process3(a,index-1);
                if(index-d-1>=0 && a[index-d-1] =='('){
                    d = d + 2;
                    if(index-d>0 && a[index-d] ==')'){
                        d = d + process3(a,index-d);
                    }
                }else{
                    d = 0;
                }
                return d;
            }
            return 0;
        }
        int longest_KHDP(string a){
            int size = a.length();
            vector<int> dp(size,0);
            int res  = 0;
            for(int i=1; i<size; ++i){
                if(a[i] == ')'){
                    if(i-dp[i-1]-1>=0 && a[i-dp[i-1]-1] == '('){
                        dp[i]  = dp[i-1] + 2;
                        dp[i] += (i-dp[i-1]-2>=0 && a[i-dp[i-1]-2]==')')?dp[i-dp[i-1]-2]:0;
                    }
                }
                res = max(res,dp[i]);
            }
            return res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    //string s = "()((()()))()))))";
    //string s1 = "()((()()))())))()()))())))";
    //string s2 = "()((()(((())))))(";
    //string s3 = "()(((()()))())))()))()))))";
    //string s4 = "()(())";
    //string s5 = "()))))";
    //cout<<te.longest_KH(s)<<endl;
    //cout<<te.longest_KHDP(s)<<endl;
    //cout<<"-------------------------------"<<endl;
    //cout<<te.longest_KH(s1)<<endl;
    //cout<<te.longest_KHDP(s1)<<endl;
    //cout<<"-------------------------------"<<endl;
    //cout<<te.longest_KH(s2)<<endl;
    //cout<<te.longest_KHDP(s2)<<endl;
    //cout<<"-------------------------------"<<endl;
    //cout<<te.longest_KH(s3)<<endl;
    //cout<<te.longest_KHDP(s3)<<endl;
    //cout<<"-------------------------------"<<endl;
    //cout<<te.longest_KH(s4)<<endl;
    //cout<<te.longest_KHDP(s4)<<endl;
    //cout<<"-------------------------------"<<endl;
    //cout<<te.longest_KH(s5)<<endl;
    //cout<<te.longest_KHDP(s5)<<endl;
    //cout<<"-------------------------------"<<endl;
    string s =  "1|0|0";
    string s1 = "0^1|0|0";
    string s2 = "1|0|0";
    string s3 = "1|0^1|0|0|0";
    string s4 = "1|1|0&0|0";
    cout<<te.split_EX(s,true)<<endl;
    cout<<te.split_EXDP(s,true)<<endl;
    cout<<"-------------------------------"<<endl;
    cout<<te.split_EX(s1,true)<<endl;
    cout<<te.split_EXDP(s1,true)<<endl;
    cout<<"-------------------------------"<<endl;
    cout<<te.split_EX(s2,true)<<endl;
    cout<<te.split_EXDP(s2,true)<<endl;
    cout<<"-------------------------------"<<endl;
    cout<<te.split_EX(s3,true)<<endl;
    cout<<te.split_EXDP(s3,true)<<endl;
    cout<<"-------------------------------"<<endl;
    cout<<te.split_EX(s4,true)<<endl;
    cout<<te.split_EXDP(s4,true)<<endl;
    cout<<"-------------------------------"<<endl;
    //string s = "221";
    //string s1 = "222143546531";
    //string s2 = "22s2314443241";
    //string s3 = "22s32341";
    //string s4 = "2286574685761";
    //cout<<te.splitA_Z(s)<<endl;
    //cout<<te.splitA_ZDP(s)<<endl;
    //cout<<"--------"<<endl;
    //cout<<te.splitA_Z(s1)<<endl;
    //cout<<te.splitA_ZDP(s1)<<endl;
    //cout<<"--------"<<endl;
    //cout<<te.splitA_Z(s2)<<endl;
    //cout<<te.splitA_ZDP(s2)<<endl;
    //cout<<"--------"<<endl;
    //cout<<te.splitA_Z(s3)<<endl;
    //cout<<te.splitA_ZDP(s3)<<endl;
    //cout<<"--------"<<endl;
    //cout<<te.splitA_Z(s4)<<endl;
    //cout<<te.splitA_ZDP(s4)<<endl;
    //cout<<"--------"<<endl;
    return 0;
}
