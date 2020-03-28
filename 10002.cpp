/*********************************************
*     ------------------------
*     ------------------------
*     file name: 10002.cpp
*     author   : @ JY
*     date     : 2020--02--19
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution {
public:
    vector<string> commonChars(vector<string>& A) {
        int __tmp[26]={0};
        vector<string> __res;
        for(int i=0; i<A[0].size(); ++i){
            ++__tmp[A[0][i] - 'a'];
        }
        for(int i=1; i<A.size(); ++i){
            int __t[26]={0};
            for(int j=0; j<A[i].size(); ++j){
                ++__t[A[i][j] - 'a'];
            }
            for(int k=0; k<26; ++k){
                if(__t[k] < __tmp[k]){
                    __tmp[k] = __t[k];
                }
            }
        }
        for(int i=0; i<26; ++i){
            while(__tmp[i]-- > 0){
                string a(1,i+'a');
                __res.push_back(a);
            }
        }
        return __res;
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    vector<string> a = {"bella","label","roller"};
    vector<string> __res;
    __res = te.commonChars(a);
    for(int i=0; i<__res.size(); i++){
        cout<<__res[i]<<endl;
    }
    return 0;
}
