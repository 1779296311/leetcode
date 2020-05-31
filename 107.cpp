/*********************************************
*     ------------------------
*     ------------------------
*     file name: 107.cpp
*     author   : @ JY
*     date     : 2019--10--31
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <stack>
using  namespace  std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> res;
        if(!root){
            return res;
        }
        int  end   = 0;
        int  begin = -1;
        vector<TreeNode*> qu;
        qu.push_back(root);
        while(end != begin){
            vector<int> tmp;
            int size = end - begin;
            for(int i=0; i<size; i++){
                TreeNode* rt   = qu[++begin];
                tmp.push_back(rt->val);
                if(rt->left){
                    qu.push_back(rt->left);
                    end++;
                }
                if(rt->right){
                    qu.push_back(rt->right);
                    end++;
                }
            }
            res.push_back(tmp);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
