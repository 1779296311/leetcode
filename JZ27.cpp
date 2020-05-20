/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ27.cpp
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
    TreeNode* mirrorTree(TreeNode* root) {
        return partition(root);
    }
    TreeNode* partition(TreeNode* root){
        if(!root){
            return nullptr;
        }
        TreeNode* newHead = new TreeNode(root->val);
        newHead->left     = partition(root->right);
        newHead->right    = partition(root->left);
        return newHead;
    }
};
