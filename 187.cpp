/*********************************************
*     ------------------------
*     ------------------------
*     file name: 187.cpp
*     author   : @ JY
*     date     : 2020--02--19
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <bitset>
#include <string>
using  namespace  std;
class Solution {
public:
    /*vector<string> findRepeatedDnaSequences(string s) {
        int __size = s.length();
        vector<string> __res;
        vector<string> __m;
        if(__size < 10){
            return __res;
        }
        int k         = 0;
        string __argv = s;
        for(int i=0; i<__size-9; ++i){
            string __tmp = __argv.substr(i,10);
            string __s   = __argv.substr(i+1);
            for(k=0; k<__m.size(); ++k){
                if(__m[k] == __tmp){
                    break;
                }
            }
            if(k != __res.size()){
                continue;
            }
            __m.push_back(__tmp);
            if(!KMP(__tmp,__s)){
                continue;
            }
            __res.push_back(__tmp);
        }
        return __res;
    }
    bool KMP(string __t, string __s){
        int __size0 = __t.size();
        int __size1 = __s.size();
        if(__size0 != 10 || __size1 < __size0){
            return false;
        }
        int _nt[__size0+1];
        _nt[0]  = -1;
        int i   = 0;
        int j   = -1;
        while(i < __size0){
            if(j == -1 || __t[i] == __t[j]){
                _nt[++i] = ++j;
            }else{
                j = _nt[j];
            }
        }
        i = 0;
        j = 0;
        while(i<__size1 && j<__size0){
            if(j == -1 || __t[j] == __s[i]){
                ++i;
                ++j;
            }else{
                j = _nt[j];
            }
        }
        if(j == __size0){
            return true;
        }
        return false;
    }*/
    int hashB(char a){
        switch(a){
            case 'A':
                return 0;
            case 'G':
                return 1;
            case 'C':
                return 2;
            case 'T':
                return 3;
        }
        return -1;
    }
    vector<string> findRepeatedDnaSequences(string s){
        int __size = s.length();
        vector<string> __res;
        bitset<1<<20> fi;
        bitset<1<<20> se;
        if(__size < 10){
            return __res;
        }
        int val = 0;
        for(int i=0; i<10; i++){
            val = (val << 2) | hashB(s[i]);
        }
        fi.set(val);
        for(int i=10; i<s.size(); ++i){
            val = ((val<<2) & 0xfffff)| hashB(s[i]) ;
            if(fi[val]){
                if(!se[val]){
                    __res.push_back(s.substr(i-9,10));
                    se.set(val);
                }
            }else{
                fi.set(val);
            }
        }
        return __res;
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    string __s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTCCCAAAAACCCCCCAAAAAGGGTTT";
    //string __b = "AAAAACCCCC";
    //string __b = "AAAAACCCCC";
    //string __b = "AAAAACCgdf";
    //cout<<te.KMP(__b, __s)<<endl;
    //string __s = "asjdhkajshkjsahaksjfhkasjh";
    vector<string> r;
    r = te.findRepeatedDnaSequences(__s);
    for(int i=0; i<r.size(); ++i){
        cout<<r[i]<<endl;
    }

    return 0;
}
