/*********************************************
*     ------------------------
*     ------------------------
*     file name: 235.cpp
*     author   : @ JY
*     date     : 2020--05--02
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!q || !p || !root){
            return root;
        }
        int v1 = min(q->val,p->val);
        int v2 = max(p->val,q->val);
        int tmp=0;
        while(root){
            if(root->val>=v1 && root->val<=v2){
                return root;
            }else if(root->val>v2){
                root = root->left;
            }else if(root->val<v1){
                root = root->right;
            }
        }
        return root;
    }
};
