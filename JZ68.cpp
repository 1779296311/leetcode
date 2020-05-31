/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ68.cpp
*     author   : @ JY
*     date     : 2020--05--23
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==nullptr || root==p || root==q){
            return root;
        }
        TreeNode* left  = lowestCommonAncestor(root->left,p,q);
        TreeNode* right = lowestCommonAncestor(root->right,p,q);
        if(left && right){
            return root;
        }
        return left?left:right;
    }
    TreeNode* lowestCommonAncestorSerach(TreeNode* root, TreeNode* p, TreeNode* q){
        int minV = ::std::min(p->val,q->val);
        int maxV = ::std::max(p->val,q->val);
        while(root){
            if(root->val>=minV && root->val<=maxV){
                return root;
            }else if(root->val<minV){
                root = root->right;
            }else{
                root = root->left;
            }
        }
        return nullptr;
    }
};
