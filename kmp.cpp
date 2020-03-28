/*********************************************
*     ------------------------
*     ------------------------
*     file name: kmp.cpp
*     author   : @ JY
*     date     : 2020--03--24
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        void getNextArray(vector<int>& next, string s2){
            int size  = s2.length();
            next[0]   = -1;
            int index = 2;
            int jump  = 0;
            while(index < size){
                if(s2[index-1] == s2[jump]){
                    next[index++] = ++jump;
                }else if(!jump){
                    next[index++] = 0;
                }else{
                    jump = next[jump];
                }
            }
        }
        int kmp(string s1, string s2){
            int size1 = s1.length();
            int size2 = s2.length();
            int l1    = 0;
            int l2    = 0;
            vector<int> next(size2,0);
            getNextArray(next,s2);
            while(l1<size1 && l2<size2){
                if(s1[l1] == s2[l2]){
                    ++l1;
                    ++l2;
                }else if(!l2){
                    ++l1;
                }else{
                    l2 = next[l2];
                }
            }
            return l2==size2?l1-l2:-1;
        }
        string min_child_add(string s1){
            int size = s1.length();
            vector<int> next(size+1,0);
            next[0]   = -1;
            int jump  = 0;
            int index = 2;
            while(index<=size){
                if(s1[index-1] == s1[jump]){
                    next[index++] = ++jump;
                }else if(!jump){
                    ++index;
                }else{
                    jump = next[jump];
                }
            }
            cout<<string __res(s1)<<endl;
            __res.insert(__res.end(),s1.begin()+next[size],s1.end());
            return __res;
        }
};
int main(int argc,const char *argv[]){
    string s1 = "aldhqhwrasabctghcyyqwrnnzbxcbbhhioqwoehl";
    string s2 = "abctghhgabcyy";
    string s3 = "abcsdabcs";
    Solution te;
    cout<<te.kmp()<<endl;
    cout<<te.min_child_add(s3)<<endl;
    return 0;
}
