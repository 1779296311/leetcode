/*********************************************
*     ------------------------
*     ------------------------
*     file name: 129.cpp
*     author   : @ JY
*     date     : 2019--11--28
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    int sumNumbers(TreeNode* root){
        if(!root || !root->val){
            return 0;
        }
        //vector<string> __res;
        //string __tmp = "";
        //__my_fun(__res, __tmp, root);
        //int sum = 0;
        //for(int i=0; i<__res.size(); i++){
            //sum = sum + stoi(__res[i]);
        //}

        //better
        int sum = 0;
        __better_fun(__sum, 0, __root);
        return __sum;
    }
    void __my_fun(vector<string>& __res, string __tmp, TreeNode* __root){
        if(__root){
            __tmp = __tmp + to_string(__root->val);
            if(!__root->left && !__root->right){
                __res.push_back(__tmp);
            }else{
                __my_fun(__res, __tmp, __root->left);
                __my_fun(__res, __tmp, __root->right);
            }
        }
        return;
    }
    void __better_fun(int &__res, int __tmp, TreeNode* __root){
        if(__root){
            __tmp  = __tmp*10 + __root->val;
            if(!__root->left && !__root->right){
                __res = __res + __tmp;
            }else{
                __better_fun(__res, __tmp, __root->left);
                __better_fun(__res, __tmp, __root->right);
            }
        }
        return;
    }
};
