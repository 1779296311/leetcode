/*********************************************
*     ------------------------
*     ------------------------
*     file name: 679.cpp
*     author   : @ JY
*     date     : 2020--07--15
**********************************************/
#include <iostream>
#include <vector>
#include <deque>
class Solution{
    private:
        const double esp = 1e-5;
    public:
        bool judgePoint24(std::vector<int>& nums){
            std::deque<double> q;
            q.push_back(nums[0]);
            q.push_back(nums[1]);
            q.push_back(nums[2]);
            q.push_back(nums[3]);
            return get_res(q);
        }
        bool get_res(std::deque<double>& q){
            int size = q.size();
            if(size==1)return abs(q.front() - 24) < esp;
            for(int i=0; i<size; ++i){
                double a = q.front();
                q.pop_front();
                for(int j=1; j<size; ++j){
                    double b = q.front();
                    q.pop_front();

                    q.push_back(a+b);
                    if(get_res(q))return true;
                    q.pop_back();

                    q.push_back(a-b);
                    if(get_res(q))return true;
                    q.pop_back();

                    q.push_back(a*b);
                    if(get_res(q))return true;
                    q.pop_back();

                    q.push_back(a/b);
                    if(b && get_res(q))return true;
                    q.pop_back();

                    q.push_back(b);
                }
                q.push_back(a);
            }
            return false;
        }
};
