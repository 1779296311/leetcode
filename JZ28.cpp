/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ28.cpp
*     author   : @ JY
*     date     : 2020--05--11
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
    bool isSymmetric(TreeNode* root) {
        return root?partition(root->left,root->right):1;
    }
    bool partition(TreeNode* l, TreeNode* r){
        if(!r && !l){
            return true;
        }else if(!r && l){
            return false;
        }else if(r && !l){
            return false;
        }
        if(l->val != r->val){
            return false;
        }
        return partition(l->left,r->right) && partition(l->right,r->left);
    }
};
