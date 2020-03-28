/*********************************************
*     ------------------------
*     ------------------------
*     file name: 226.cpp
*     author   : @ JY
*     date     : 2019--12--05
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode *invertTree(TreeNode* root) {
        if(root){
            TreeNode *__t1 = invertTree(root->right);
            TreeNode *__t2 = invertTree(root->left);
            root->left     = __t1;
            root->right    = __t2;
            return root;
        }
        return NULL;
    }
    TreeNOde *invertTree(TreeTode *__root){
        if(!__root){
            return NULL;
        }
        stack<TreeNode*> __st;
        __st.push(__root);
        while(!__st.empty()){
            TreeNode *__tmp = __st.top();
            __st.pop();
            TreeNode *__r   = __tmp->right;
            __tmp->right    = __tmp->left;
            __tmp->left     = __r;
            if(__tmp->right){
                __st.push(__tmp->right);
            }
            if(__tmp_.left){
                __st.push(__tmp->left);
            }
        }
        return __root;
    }
};
