/*********************************************
*     ------------------------
*     ------------------------
*     file name: __Morris_Inorder.cpp
*     author   : @ JY
*     date     : 2019--12--03
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class TreeNode{
    public:
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int __v) val(__v) {}
};
void __morris_Inorder(TreeNode *__root){
    if(!__root){
        return;
    }
    TreeNode *__cur = __root;
    while(__cur){
        if(!__cur->left){
            cout<<__cur->val<<endl;
            __cur = __cur->right;
        }else{
            TreeNode *__tmp = __cur->left;
            while(__tmp->right && __tmp->right != __cur){
                __tmp = __tmp->right;
            }
            if(!__tmp->right){
                __tmp->right = __cur;
                __cur        = __cur ->left;
            }else if(__tmp->right == __cur){
                cout<<__cur->val<<endl;
                __tmp->right = NULL;
                __cur        = __cur->right;
            }
        }
    }
}
void __morris_Postorder(TreeNode *__root){
    if(!__root){
        return;
    }
    TreeNode *__tmp = new TreeNode(-1);
    __tmp->left     = __root;
    TreeNode *__cur = __tmp;
    while(__cur){
        if(!__cur->left){
            __cur = __cur->right;
        }else{
            TreeNode *__l = __cur->left;
            while(__l->right && __l->right != __cur){
                __l = __l->right;
            }
            if(!__l->right){
                __l->right = __cur;
                __cur  = __cur->left;
            }else{
                __l->right = NULL;
                TreeNode *__t = __cur->left;
                vector<TreeNode*> __v;
                while(__t){
                    __v.push_back(__t);
                    __t = __t->right;
                }
                for(int i=__v.size()-1; i>=0; i--){
                    cout<<__v[i]->val<<endl;
                }
                __cur = __cur->right;
            }
        }
    }
}
