/*********************************************
*     ------------------------
*     ------------------------
*     file name: 99.cpp
*     author   : @ JY
*     date     : 2020--05--06
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
public:
    void recoverTree(TreeNode*& root) {
        TreeNode* err1 = nullptr;
        TreeNode* err2 = nullptr;
        getErr(root,&err1,&err2);
        if(err1 && err2){
            recoverTree(&root,err1,err2);
        }
    }
    void recoverTree(TreeNode** root, TreeNode* err1, TreeNode* err2){
        TreeNode* parent1 = nullptr;
        TreeNode* parent2 = nullptr;
        getParent(*root,err1,&parent1);
        getParent(*root,err2,&parent2);
        parent1 = recoverTree(err1,parent1,err2,parent2);
        *root   = parent1?parent1:*root;
    }
    TreeNode* recoverTree(TreeNode* err1, TreeNode* parent1, TreeNode* err2, TreeNode* parent2){
        TreeNode* r1 = nullptr;
        TreeNode* r2 = nullptr;
        TreeNode* l1 = nullptr;
        TreeNode* l2 = nullptr;
        if(parent1 == nullptr){
            l1       = err1->left;
            l2       = err2->left;
            r2       = err2->right;
            if(err1 == parent2){
                err2->right = err1;
            }else{
                r1 = err1->right;
                if(parent2->left && parent2->left==err2){
                    parent2->left  = err1;
                }else{
                    parent2->right = err1;
                }
                err2->right = r1;
            }
            err2->left  = l1;
            err1->left  = l2;
            err1->right = r2;
            return err2;
        }else if(parent2 == nullptr){
            l1       = err1->left;
            r1       = err1->right;
            r2       = err2->right;
            if(err2 == parent1){
                err1->left  = err2;
            }else{
                l2 = err2->left;
                if(parent1->left && parent1->left == err1){
                    parent1->left = err2;
                }else{
                    parent1->right = err2;
                }
                err1->left  = l2;
            }
            err1->right = r2;
            err2->left  = l1;
            err2->right = r1;
            return err1;
        }else{
            l1 = err1->left;
            r2 = err2->right;
            if(parent1 == err2){
                r1 = err2->right;
                if(parent2->left && parent2->left == err2){
                    parent2->left  = err1;
                }else{
                    parent2->right = err1;
                }
                err1->left  = err2;
                err2->right = r1;
            }else if(parent2 == err1){
                l2 = err2->left;
                if(parent1->left && parent1->left == err1){
                    parent1->left  = err2;
                }else{
                    parent1->right = err2;
                }
                err2->right = err1;
                err1->left  = l2;
            }else{
                r1 = err1->right;
                l2 = err2->left;
                if(parent1->left && parent1->left == err1){
                    parent1->left  = err2;
                }else{
                    parent1->right = err2;
                }
                if(parent2->left && parent2->left == err2){
                    parent2->left  = err1;
                }else{
                    parent2->right = err1;
                }
                err1->left  = l2;
                err2->right = r1;
            }
            err2->left  = l1;
            err1->right = r2;
            return nullptr;
        }
    }
    void getParent(TreeNode* root,TreeNode*err, TreeNode** parent){
        if(root->val == err->val){
            return;
        }
        TreeNode* rightMost = nullptr;
        TreeNode* cur       = root;
        while(cur){
            *parent = (!*(parent) && cur->right && cur->right->val == err->val)?cur:*parent;
            *parent = (!*(parent) && cur->left  && cur->left->val  == err->val)?cur:*parent;
            rightMost = cur->left;
            if(rightMost){
                while(rightMost->right && rightMost->right != cur){
                    rightMost = rightMost->right;
                }
                if(!rightMost->right){
                    rightMost->right = cur;
                    cur              = cur->left;
                    continue;
                }else{
                    rightMost->right = nullptr;
                }
            }else{
                ;;;;;;;;;;;;;;;;;;;;;;;
            }
            cur = cur->right;
        }
    }
    void getErr(TreeNode* root, TreeNode** err1, TreeNode** err2){
        TreeNode* rightMost = nullptr;
        TreeNode* cur       = root;
        TreeNode* pre       = nullptr;
        while(cur){
            rightMost = cur->left;
            if(rightMost){
                while(rightMost->right && rightMost->right != cur){
                    rightMost = rightMost->right;
                }
                if(!rightMost->right){
                    rightMost->right = cur;
                    cur              = cur->left;
                    continue;
                }else{
                    *err1 = (pre&&pre->val>cur->val&&!(*err1))?pre:*err1;
                    *err2 = (pre&&pre->val>cur->val)?cur:*err2;
                    pre   = cur;
                    rightMost->right = nullptr;
                }
            }else{
                *err1 = (pre&&pre->val>cur->val&&!(*err1))?pre:*err1;
                *err2 = (pre&&pre->val>cur->val)?cur:*err2;
                pre   = cur;
            }
            cur = cur->right;
        }
    }
    void inOrder(TreeNode* root){
        TreeNode* cur   = root;
        TreeNode* mostR = nullptr;
        while(cur){
            mostR = cur->left;
            if(mostR){
                while(mostR->right && mostR->right!=cur){
                    mostR = mostR->right;
                }
                if(!mostR->right){
                    mostR->right = cur;
                    cur = cur->left;
                    continue;
                }else{
                    cout<<cur->val<<" ";
                    mostR->right = nullptr;
                }
            }else{
                    cout<<cur->val<<" ";
            }
            cur = cur->right;
        }
        cout<<endl;
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    TreeNode *root           = new TreeNode(5);
    root->left               = new TreeNode(3);
    root->left->left         = new TreeNode(2);
    root->left->right        = new TreeNode(4);
    root->right              = new TreeNode(8);
    root->right->left        = new TreeNode(6);
    root->right->right       = new TreeNode(9);
    root->right->right->left = new TreeNode(7);
    //root->right       = new TreeNode(4);
    //root->right->left = new TreeNode(2);
    te.inOrder(root);
    te.recoverTree(root);
    te.inOrder(root);

    ////root->left->right        = new TreeNode(6);
    ////root->left->right->left  = new TreeNode(60);
    ////root->left->right->right = new TreeNode(61);

    //root->right               = new TreeNode(4);
    //root->right->left         = new TreeNode(-1);
    //root->right->left->left   = new TreeNode(-2);
    //root->right->left->right  = new TreeNode(-3);
    //root->right->right        = new TreeNode(5);
    //root->right->right->left  = new TreeNode(-4);
    //root->right->right->right = new TreeNode(-5);
    //TreeNode* p = nullptr;
    //te.getParent(root,root->left->left,&p);
    //cout<<p->val<<endl;
    //te.recoverTree(root);
    return 0;
}
