/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ34.cpp
*     author   : @ JY
*     date     : 2020--05--23
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    ::std::vector<::std::vector<int>> pathSum(TreeNode* root, int sum){
        ::std::vector<::std::vector<int>> res = partition1(root,sum);
        for(int i=0; i<res.size(); ++i){
            ::std::reverse(res[i].begin(), res[i].end());
        }
        return res;
    }
    ::std::vector<::std::vector<int>> partition1(TreeNode* root, int sum){
        if(!root){
            return ::std::vector<::std::vector<int>>{};
        }
        if(sum==root->val && !(root->left) &&!(root->right)){
            return ::std::vector<::std::vector<int>>{{root->val},};
        }
        ::std::vector<::std::vector<int>> res;
        ::std::vector<::std::vector<int>> left  = partition1(root->left,sum-root->val);
        ::std::vector<::std::vector<int>> right = partition1(root->right,sum-root->val);
        for(int i=0; i<left.size(); ++i){
            left[i].push_back(root->val);
            res.push_back(left[i]);
        }
        for(int i=0; i<right.size(); ++i){
            right[i].push_back(root->val);
            res.push_back(right[i]);
        }
        return res;
    }
};
