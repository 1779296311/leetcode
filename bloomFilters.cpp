/*********************************************
*     ------------------------
*     ------------------------
*     file name: bloomFilters.cpp
*     author   : @ JY
*     date     : 2020--03--13
**********************************************/
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "url.h"
using  namespace  std;
#define LEN strlen(key)
const int bSIZE = 1000;
class Solution{
    private:
        typedef int(*hf)(const char*,int,int);
        int bloomSize;
        int hashFunSize;
    public:
        int *bloom;
        int (**hashFun)(const char*,int,int);
    public:
        ~Solution(){
            if(bloom){
                delete [] bloom;
            }
            if(hashFun){
                delete [] hashFun;
            }
        }
        Solution(int (*p[])(const char*,int,int), int size, int bsize=bSIZE, int hsize=hSIZE){
            bloomSize   = bsize;
            hashFunSize = hsize;
            bloom       = new int[bloomSize];
            hashFun     = new hf[hashFunSize];
            for(int i=0; i<size&&i<hashFunSize; ++i){
                hashFun[i] = p[i];
            }
        }
        void addKey(const char *key){
            for(int i=0; i<hashFunSize; ++i){
                int tmp       = hashFun[i](key,LEN,bloomSize*4*8);
                int index1    = tmp/32;
                int index2    = tmp%32;
                bloom[index1] = bloom[index1] | (1<<index2);
            }
        }
        bool searchKey(const char *key){
            for(int i=0; i<hashFunSize; ++i){
                int tmp    = hashFun[i](key,LEN,bloomSize*4*8);
                int index1 = tmp/32;
                int index2 = tmp%32;
                if(!(bloom[index1]&(1<<index2))){
                    return false;
                }
            }
            return true;
        }
};
int main(int argc,const char *argv[]){
    int Usize = *(&url+1)-url;
    int Fsize = *(&Hfun+1)-Hfun;
    Solution te(Hfun,Fsize);
    for(int i=0; i<Usize; ++i){
        te.addKey(url[i]);
    }
    for(int i=0; i<Usize; ++i){
        if(!te.searchKey(url[i])){
            cout<<"not"<<i<<endl;
        }
    }
    cout<<te.searchKey(url[6])<<endl;
    cout<<te.searchKey(url[7])<<endl;
    cout<<te.searchKey(url[8])<<endl;
    cout<<te.searchKey(url[9])<<endl;
    cout<<te.searchKey(url[11])<<endl;
    cout<<te.searchKey(url[15])<<endl;
    cout<<te.searchKey("fuckfuckfuck")<<endl;
    return 0;
}
