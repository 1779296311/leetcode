/*********************************************
*     ------------------------
*     ------------------------
*     file name: lintcode_131.cpp
*     author   : @ JY
*     date     : 2020--03--29
**********************************************/
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <stdlib.h>
using  namespace  std;
struct node{
    bool dic;
    int  index;
    int  high;
    node(){}
    node(bool d, int i, int h):dic(d),index(i),high(h){}
};
struct cmp{
    bool operator()(node a, node b){
        return a.index < b.index;
    }
};
class Solution{
    public:
        vector<vector<int>> buildingOutLine(vector<vector<int>>& build){
            vector<vector<int>> __res;
            int size = build.size();
            if(!size){
                return __res;
            }
            vector<node> bd(size*2);
            for(int i=0; i<size; ++i){
                bd[i*2]   = node(true,build[i][0],build[i][2]);
                bd[i*2+1] = node(false,build[i][1],build[i][2]);
            }
            sort(bd.begin(),bd.end(),cmp());
            map<int,int>  htMP;
            map<int,int>  pmMP;
            for(int i=0; i<bd.size(); ++i){
                if(bd[i].dic){
                    if(htMP.find(bd[i].high) == htMP.end()){
                        htMP[bd[i].high] = 1;
                    }else{
                        ++htMP.at(bd[i].high);
                    }
                }else{
                    if(htMP.find(bd[i].high) != htMP.end()){
                        if(!(--htMP.at(bd[i].high))){
                            htMP.erase(bd[i].high);
                        }
                    }
                }
                if(htMP.empty()){
                    pmMP[bd[i].index] = 0;
                }else{
                    auto m = max_element(htMP.begin(),htMP.end(),[](const pair<int,int> &x,const pair<int,int> &y){
                            return x.first < y.first;
                            });
                    pmMP[bd[i].index]=(*m).first;
                }
            }
            debug(pmMP);
            int start  = 0;
            int high   = 0;
            for(map<int, int>::iterator iter = pmMP.begin(); iter != pmMP.end(); iter++){
                if(high != iter->second){
                    if(high){
                        vector<int> tmp;
                        tmp.push_back(start);
                        tmp.push_back(iter->first);
                        tmp.push_back(high);
                        __res.push_back(tmp);
                    }
                    start = iter->first;
                    high  = iter->second;
                }
            }
            debug(__res);
            return __res;
        }
        void debug(vector<vector<int>>& line){
            for(int i=0; i<line.size(); ++i){
                cout<<line[i][0]<<" "<<line[i][1]<<" "<<line[i][2]<<endl;
            }
        }
        void debug(map<int,int>& pm){
            for (map<int, int>::iterator iter = pm.begin(); iter != pm.end(); iter++){
                cout << iter->first << " ==> " << iter->second << endl;
            }
        }
        void debug(vector<node>& nd){
            for(int i=0; i<nd.size(); ++i){
                cout<<nd[i].index<<endl;
            }
        }
};
//1 ==> 3
//2 ==> 4
//3 ==> 4
//4 ==> 0
//5 ==> 1
//6 ==> 0
int main(int argc,const char *argv[]){
    Solution te;
    vector<vector<int>>  build = {{1,3,3},{2,4,4},{5,6,1}};
    te.buildingOutLine(build);
    return 0;
}
