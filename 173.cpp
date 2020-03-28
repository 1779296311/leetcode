/*********************************************
*     ------------------------
*     ------------------------
*     file name: 173.cpp
*     author   : @ JY
*     date     : 2019--12--04
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <stack>
using  namespace  std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class BSTIterator {
public:
    TreeNode  *__T;
    stack<TreeNode*> __st;
    BSTIterator(TreeNode* root) {
        if(root){
            push_node(root);
        }
    }
    /** @return the next smallest number */
    int next(){
        int __res = __st.top()->val;
        TreeNode *__tmp = __st.top()->right;
        __st.pop();
        if(__tmp){
            push_node(__tmp);
        }
        return __res;
    }
    /** @return whether we have a next smallest number */
    bool hasNext(){
        return !__st.empty();
    }
    void push_node(TreeNode *__root){
        TreeNode *__tmp = __root;
        while(__tmp){
            __st.push(__tmp);
            __tmp = __tmp->left;
        }
    }
};

