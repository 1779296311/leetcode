/*********************************************
*     ------------------------
*     ------------------------
*     file name: 179.cpp
*     author   : @ JY
*     date     : 2020--02--20
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution {
public:
    //string largestNumber(vector<int>& nums) {
        //string __res;
        //int __size = nums.size();
        //if(!__size){
            //return __res;
        //}
        //vector<string> __tmp;
        //__tmp.push_back(to_string(nums[0]));
        //int j = 0;
        //for(int i=1; i<__size; ++i){
            //string __t = std::to_string(nums[i]);
            //for(j=0; j<__tmp.size(); ++j){
                //if(__t[0] > __tmp[0]){
                    //vector<string>::iterator it = __tmp.begin();
                    //__tmp.insert(it,1,__t);
                    //break;
                //}else if(__t[0] < __tmp[0]){
                    //continue;
                //}else{
                    //while()
                //}
            //}
            //if(j == __tmp.size()){
                //__tmp.push_back(__t);
            //}
        //}
        //return __res;
    //}
    string largestNumber(vector<int>& nums){
        string __res;
        int __size = nums.size();
        if(!__size){
            return __res;
        }
        sort(nums.begin(),nums.end(),[](int& a,int& b){
                string a1 = to_string(a);
                string a2 = to_string(b);
                return a1+a2 > a2+a1;
                });
        for(int i=0; i<__size; ++i){
            __res = __res + to_string(nums[i]);
        }
        return __res[0]=='0'?"0":__res;
    }
};
