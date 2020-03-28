/*********************************************
*     ------------------------
*     ------------------------
*     file name: manacher.cpp
*     author   : @ JY
*     date     : 2020--03--25
**********************************************/
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        string init(string s1){
            string tmp = "";
            for(int i=0; i<s1.length(); ++i){
                tmp = tmp + "#";
                tmp = tmp + s1[i];
            }
            return tmp+"#";
        }
        int manacher(string s1){
            s1        = init(s1);
            int size  = s1.length();
            int __res = 1;
            vector<int> p(size,0);
            int mid = 0;
            int R   = 0;
            int i   = 0;
            while(i<size){
                p[i] = R>i?(p[(mid<<1)-i],R-i):1;
                while(i+p[i]<size && i-p[i]>=0 && s1[i+p[i]] == s1[i-p[i]]){
                    ++p[i];
                }
                if(i+p[i] > R){
                    R   = i+p[i];
                    mid = i;
                }
                __res = max(__res,p[i]);
                ++i;
            }
            return --__res;
        }
        string min_add_palindrome(string s1){
            string s2(s1);
            s1        = init(s1);
            int size  = s1.length();
            int R     = 0;
            int i     = 0;
            int mid   = 0;
            vector<int> p(size,0);
            while(i<size){
                p[i] = R>i?(min(R-i,p[(mid<<1)-i])):1;
                while(i-p[i]>=0 && i+p[i]<size && s1[i+p[i]] == s1[i-p[i]]){
                    ++p[i];
                }
                if(R<i+p[i]){
                    R   = i+p[i];
                    mid = i;
                }
                if(R == size-1){
                    break;
                }
                ++i;
            }
            string __res(s2);
            //mid  = mid>>1;
            for(int k=mid-(R>>2)-2; k>=0; --k){
                __res = __res + s2[k];
            }
            return __res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    string s1 = "ab";
    cout<<te.min_add_palindrome(s1)<<endl;
    cout<<te.manacher(s1)<<endl;
    return 0;
}
