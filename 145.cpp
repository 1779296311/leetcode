/*********************************************
*     ------------------------
*     ------------------------
*     file name: 145.cpp
*     author   : @ JY
*     date     : 2019--12--03
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stack>
using  namespace  std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> __res;
        if(!root){
            return __res;
        }
        stack<TreeNode*> __tmp;
        TreeNode*  __p = root;
        TreeNode*  __b;
        do{
            while(__p){
                __tmp.push(__p);
                __p = __p->left;
            }
            __b = NULL;
            while(!__tmp.empty()){
                __p = __tmp.top();
                if(__p->right == __b){
                    __res.push_back(__p->val);
                    __tmp.pop();
                    __b = __p;
                }else{
                    __p = __tmp.top()->right;
                    break;
                }
            }
        }while(!__tmp.empty());

        return __res;
    }
};
