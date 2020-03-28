/*********************************************
*     ------------------------
*     ------------------------
*     file name: 144.cpp
*     author   : @ JY
*     date     : 2019--11--29
**********************************************/
#include <iostream>
#include <vector>
#include <stack>
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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> __res;
        if(!root){
            return __res;
        }
        TreeNode* __tmp = root;
        stack<TreeNode*> __st;
        while(!__st.empty() || __tmp){
            while(__tmp){
                __st.push(__tmp);
                __res.push_back(__tmp->val);
                __tmp = __tmp->left;
            }
            if(!__st.empty()){
                __tmp = __st.top()->right;
                __st.pop();
            }
        }
        return __res;
    }
};
