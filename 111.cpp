/*********************************************
*     ------------------------
*     ------------------------
*     file name: 111.cpp
*     author   : @ JY
*     date     : 2019--11--07
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
    int minDepth(TreeNode* root) {
        if(!root){
            return 0;
        }
        if(!root->left && !root->right){
            return 1;
        }
        int l = INT_MAX;
        if(root->left){
            l = min(minDepth(root->left),l);
        }
        if(root->right){
            l = min(minDepth(root->right),l);
        }
        return l+1;
    }
};
