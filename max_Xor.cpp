/*********************************************
*     ------------------------
*     ------------------------
*     file name: max_Xor.cpp
*     author   : @ JY
*     date     : 2020--04--01
**********************************************/
#include <iostream>
#include <vector>
#include <climits>
#include <stdlib.h>
using  namespace  std;
struct Node{
    Node *path[2]={0};
};
class Solution{
    public:
        Solution(){
            tireTree = new Node();
        }
       ~Solution(){
           del_tree(tireTree);
        }
    private:
       void del_tree(Node* head){
           if(!head){
               return;
           }
           del_tree(head->path[0]);
           del_tree(head->path[1]);
           delete(head);
       }
    private:
        Node *tireTree;
    public:
        int max_xor(vector<int>& nums){
            int size  = nums.size();
            int __xor = 0;
            int __res = INT_MIN;
            for(int i=0; i<size; ++i){
                add(__xor);
                __xor = __xor ^ nums[i];
                __res = max(__res,get_res(__xor));
            }
            return __res;
        }
        void add(int num){
            Node *tmp = tireTree;
            for(int i=31; i>=0; --i){
                int p        = ((num>>i)&1);
                tmp->path[p] = (!tmp->path[p])?new Node():tmp->path[p];
                tmp          = tmp->path[p];
            }
        }
        int get_res(int num){
            Node *tmp = tireTree;
            int __res = 0;
            for(int i=31; i>=0; --i){
                int p    = ((num>>i)&1);
                int best = i==31?p:(p^1);
                best     = tmp->path[best]?best:(best^1);

                __res    = __res | ((p^best)<<i);
                tmp      = tmp->path[best];
            }
            return __res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    vector<int> nums = {3,-28,-29,2};
    cout<<te.max_xor(nums)<<endl;
    return 0;
}
