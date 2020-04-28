/*********************************************
*     ------------------------
*     ------------------------
*     file name: 134.cpp
*     author   : @ JY
*     date     : 2020--03--16
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int size = gas.size();
        for(int i=0,j; i<size; i+=j+1){
            int tmp = 0;
            for(j=0; j<size; ++j){
                tmp = tmp + gas[(i+j)%size];
                if(tmp<cost[(i+j)%size]){
                    break;
                }
                tmp = tmp - cost[(i+j)%size];
            }
            if(j==size){
                return i;
            }
        }
        return -1;
    }
    vector<bool> canComplete(vector<int>& gas, vector<int>& cost){
        int size = gas.size();
        vector<bool> res(size,false);
        if(size != cost.size()){
            return res;
        }
        int need  = 0;
        int rest  = 0;
        int init  = changeGas(gas,cost);
        int start = init;
        int end   = nextIndex(start,size);
        do{
            if(start!=init && end==preIndex(start,size)){
                break;
            }
            if(gas[start] < need){
                need = need - gas[start];
            }else{
                rest = rest + gas[start] - need;
                need = 0;
                while(rest>=0&&end != start){
                    end  = nextIndex(end,size);
                    rest = rest + gas[end];
                }
                if(end == start){
                    res[start] = true;
                    getRes(gas,res,init,preIndex(start,size));
                    break;
                }
            }
        }while(start != init);
        return res;
    }
    void getRes(vector<int>& gas,vector<bool>&res, int init, int start){
        int size = gas.size();
        int need = 0;
        while(start != init){
            if(gas[start] < need){
                need  = need - gas[start];
            }else{
                res[start] = true;
                need       = 0;
            }
            start = preIndex(start,size);
        }
    }
    int changeGas(vector<int>& gas,vector<int>& cost){
        int init;
        for(int i=0; i<gas.size(); ++i){
            gas[i] = gas[i] - cost[i];
            if(gas[i]>=0){
                init = i;
            }
        }
        return init;
    }
    int preIndex(int index, int size){
        return !index?size-1:--index;
    }
    int nextIndex(int index,int size){
        return ++index==size?0:index;
    }
    void debug(vector<bool>& res){
        for(int i=0; i<res.size(); ++i){
            cout<<res[i]<<" ";
        }
        cout<<endl;
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    vector<int> gas  = {2,3,4,5,6};
    vector<int> cost = {3,3,5,3,3};
    vector<bool> res(te.canComplete(gas,cost));
    te.debug(res);
    return 0;
}
