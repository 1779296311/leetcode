/*********************************************
*     ------------------------
*     ------------------------
*     file name: findMinShots.cpp
*     author   : @ JY
*     date     : 2020--03--15
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        int findMinShots(std::vector<std::pair<int,int>>& points){
            int size  = points.size();
            if(!size){
                return 0;
            }
            int begin = points[0].first;
            int end   = points[0].second;
            int shot  = 1;
            for(int i=1; i<size; ++i){
                if(end>=points[i].first){
                    begin = points[i].first;
                    end   = min(end,points[i].second);
                }else{
                    ++shot;
                    begin = points[i].first;
                    end   = points[i].second;
                }
            }
            return shot;
        }
    private:
};
int main(int argc,const char *argv[]){
    Solution te;
    vector<pair<int,int>> points;
    points.push_back(pair<int,int>(1,6));
    points.push_back(pair<int,int>(2,8)); 
    points.push_back(pair<int,int>(7,12));
    points.push_back(pair<int,int>(10,16));
    cout<<te.findMinShots(points)<<endl;
    return 0;
}
