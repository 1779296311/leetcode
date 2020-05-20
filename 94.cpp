/*********************************************
*     ------------------------
*     ------------------------
*     file name: 94.cpp
*     author   : @ JY
*     date     : 2020--05--01
**********************************************/
#include <iostream>
#include <vector>
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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode *cur   = root;
        TreeNode *mostR = NULL;
        while(cur){
            mostR = cur->left;
            if(mostR){
                while(mostR->right && mostR->right!=cur){
                    mostR = mostR->right;
                }
                if(!mostR->right){
                    mostR->right = cur;
                    cur          = cur->left;
                    continue;
                }else{
                    mostR->right = NULL;
                    res.push_back(cur->val);
                }
            }else{
                res.push_back(cur->val);
            }
            cur = cur->right;
        }
        return res;
    }
};
