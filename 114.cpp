/*********************************************
*     ------------------------
*     ------------------------
*     file name: 114.cpp
*     author   : @ JY
*     date     : 2019--10--21
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

class Solution{
    public:
        void flatten(TreeNode* root){
            if(!root){
                return;
            }
            flatten(root->left);
            flatten(root->right);
            if(root->left){
                TreeNode* tmp = root->left;
                while(tmp->right){
                    tmp = tmp->right;
                }
                tmp->right  = root->right;
                root->right = root->left;
                root->left  = NULL;
            }
            return;
        }
};
