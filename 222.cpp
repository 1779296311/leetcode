/*********************************************
*     ------------------------
*     ------------------------
*     file name: 222.cpp
*     author   : @ JY
*     date     : 2019--12--04
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
    int countNodes(TreeNode* root) {
        if(root){
            return countNodes(root->left) + countNodes(root->right) + 1;
        }
        return 0;
    }
};
