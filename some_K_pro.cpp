/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_K_pro.cpp
*     author   : @ JY
*     date     : 2020--05--07
**********************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        int bfprt(int *nums, int size, int k){
            vector<int> numS(nums,nums+size);
            return bfprt(numS,k);
        }
        int bfprt(vector<int>& nums, int k){
            if(nums.size() < k){
                cout<<"K > size !!!!!!!"<<endl;
                return -1;
            }
            return bfprt(nums,0,nums.size()-1,k-1);
        }
        int bfprt(vector<int>& nums, int begin, int end, int k){
            if(begin == end){
                return nums[end];
            }
            int l      = begin;
            int r      = end;
            int midNum = getMidNum(nums,begin,end);
            partition(nums,&l,&r,midNum);
            if(k>=l && k<=r){
                return nums[k];
            }else if(k<l){
                return bfprt(nums,begin,l-1,k);
            }else{
                return bfprt(nums,r+1,end,k);
            }
        }
        int getMidNum(vector<int>&nums, int begin, int end){
            int size = end - begin + 1;
            int midN = (size/5)+((size%5)?1:0);
            vector<int>midnums(midN,0);
            int s;
            int e;
            for(int i=0; i<midN; ++i){
                s = begin + 5*i;
                e = s + 4;
                midnums[i] = getMidFrom5Num(nums,s,min(end,e));
            }
            return bfprt(midnums,0,midN-1,midN/2);
        }
        int getMidFrom5Num(vector<int>& nums, int start, int end){
            sort(nums.begin()+start, nums.begin()+end+1);
            return nums[(start+end)/2];
        }
        void partition(vector<int>&nums, int *l, int *r, int midNum){
            int L   = *l - 1;
            int R   = *r + 1;
            int cur = *l;
            while(cur<R){
                if(nums[cur]<midNum){
                    swap(nums,++L,cur++);
                }else if(nums[cur]>midNum){
                    swap(nums,--R,cur);
                }else{
                    ++cur;
                }
            }
            *l = L + 1;
            *r = R - 1;
        }
        void swap(vector<int>& nums, int a, int b){
            if(nums[a]==nums[b]){
                return;
            }
            nums[a] = nums[a] ^ nums[b];
            nums[b] = nums[a] ^ nums[b];
            nums[a] = nums[a] ^ nums[b];
        }
        //-------------------get--------k--------------------doubleNum----------------------------------------//
        vector<int> getKVector(vector<int>& nums, int K){
            int kNum = bfprt(nums,((K-1)/nums.size()+1));
            int smallKNum = 0;
            int equalKNum = 0;
            for(int i=0; i<nums.size(); ++i){
                if(nums[i] == kNum){
                    ++equalKNum;
                }else if(nums[i] < kNum){
                    ++smallKNum;
                }
            }
            int lessN = K - (smallKNum*nums.size());
            return vector<int>{kNum,bfprt(nums,((lessN-1)/equalKNum)+1)};
        }
        //-------------________________--______test___--__-_______________________________________________//
        struct cmp{
            bool operator()(pair<int,int>&a, pair<int,int>&b){
                return a.first==b.first?a.second<b.second:a.first<b.first;
            }
        };
        int test(int N){
            srand((int)time(0));
            vector<int>nums;
            for(int i=0; i<N; ++i){
                nums.push_back(rand()%N);
            }
            int k  = rand()%(N*2)+1;
            vector<int> res1 = getKVector(nums,k);
            vector<pair<int,int>> pairs;
            for(int i=0; i<nums.size(); ++i){
                pairs.push_back(make_pair(nums[i],nums[i]));
                for(int j=i+1; j<nums.size(); ++j){
                    pairs.push_back(make_pair(nums[i],nums[j]));
                    pairs.push_back(make_pair(nums[j],nums[i]));
                }
            }
            sort(pairs.begin(), pairs.end(),cmp());
            pair<int,int> res2 = pairs[k-1];
            if(res2.first == res1[0] && res2.second==res1[1]){
                //cout<<"N="<<N<<"------  k="<<k<<endl;
                //cout<<"["<<res1[0]<<","<<res1[1]<<"]"<<endl;
                //cout<<"okokok"<<endl;
                return 0;
            }else{
                for(int i=0; i<pairs.size(); ++i){
                    cout<<i<<": "<<pairs[i].first<<","<<pairs[i].second<<endl;
                }
                cout<<"["<<res1[0]<<","<<res1[1]<<"]"<<endl;
                cout<<"["<<res2.first<<","<<res2.second<<"]"<<endl;
                cout<<"fuck fuck fuck"<<endl;
                cout<<"N"<<N<<endl;
                cout<<"k"<<k<<endl;
                return 1;
            }
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    while(!te.test(1024)){}
    return 0;
}
