/*********************************************
*     ------------------------
*     ------------------------
*     file name: 67.cpp
*     author   : @ JY
*     date     : 2019--10--13
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        string addBinary(string a, string b){
            string s;
            s.reserve(a.size()+b.size());
            int i    = a.size() - 1;
            int j    = b.size() - 1;
            int flag = 0;
            while(i>=0 || j>=0 || flag_and_num==1){
                flag_and_num = flag_and_num + (i>=0 ? a[i--] - '0' : 0);
                flag_and_num = flag_and_num + (j>=0 ? b[j--] - '0' : 0);
                s.push_back((flag_and_num & 1)+'0');
                flag_and_num = flag_and_num>>1;
            }
            reverse(s.begin(),s.end());
            return s;
        }
};
