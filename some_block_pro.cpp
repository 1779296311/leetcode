/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_block_pro.cpp
*     author   : @ JY
*     date     : 2020--06--24
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>

class Sulotion{
    public:
//[>57<] 插入区间
//[>�<]��出一个无重叠的 ，按照区间起始端点排序的区间列表。
//[>�<]��列表中插入一个新的区间，你需要确保列表中的区间仍然有序且不重叠（如果有必要的话，可以合并区间）
        ::std::vector<::std::vector<int>> insert(::std::vector<::std::vector<int>>& intervals,
                                                 ::std::vector<int>& newvals){
            int size = intervals.size();
            if(size == 0){
                intervals.push_back(newvals);
                return intervals;
            }else if(newvals[1] < intervals[0][0]){
                intervals.insert(intervals.begin(), newvals);
                return intervals;
            }else if(newvals[0] > intervals[size-1][1]){
                intervals.push_back(newvals);
                return intervals;
            }
            ::std::vector<::std::vector<int>> res;
            int i = 0;
            while(i<size){
                auto arr = intervals[i];
                if(newvals[0] > arr[1]){
                    res.push_back(arr);
                }else if(newvals[1] < arr[0]){
                    res.push_back(newvals);
                    break;
                }else{
                    int l    = newvals[0]>=arr[0]?arr[0]:newvals[0];
                    int j    = i;
                    int flag = 0;
                    while(j<size && newvals[1]>=intervals[j][0]){
                        if(newvals[1] <= intervals[j][1]){
                            ++flag;
                            break;
                        }
                        ++j;
                    }
                    if(j==size || newvals[1]<intervals[j][0]){
                        res.push_back({l,newvals[1]});
                    }else if(flag==1){
                        res.push_back({l,intervals[j++][1]});
                    }
                    i = j;
                    break;
                //}else if(newvals[0]<arr[0]){
                    //int l    = newvals[0];
                    //int j    = i;
                    //int flag = 0;
                    //while(j<size && newvals[1] >= intervals[j][0]){
                        //if(newvals[1] <= intervals[j][1]){
                            //flag = 1;
                            //break;
                        //}
                        //++j;
                    //}
                    //if(j==size || newvals[1]<intervals[j][0]){
                        //res.push_back({l,newvals[1]});
                    //}else if(flag==1){
                        //res.push_back({l,intervals[j++][1]});
                    //}
                    //i = j;
                    //break;
                }
                ++i;
            }
            while(i<size)res.push_back(intervals[i++]);
            return res;
        }
};
