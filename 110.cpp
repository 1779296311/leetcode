/*********************************************
*     ------------------------
*     ------------------------
*     file name: 110.cpp
*     author   : @ JY
*     date     : 2019--11--27
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
    bool isBalanced(TreeNode* root) {
        if(root){
            int l = __get_Height(root->left);
            int r = __get_Height(root->right);
            if(2 > abs(l-r) && isBalanced(root->left) && isBalanced(root->right)){
                return true;
            }else{
                return false;
            }
        }
        return true;
    }
    int __get_Height(TreeNode* __root){
        if(!__root){
            return 0;
        }
        return max(__get_Height(__root->left),__get_Height(__root->right)) + 1;
    }
    int better(Treenode* __root){
        if(__root){
            int left = better(__root->left);
            if(left == -1){
                return -1;
            }
            int left = better(__root->right);
            if(right == -1){
                return -1;
            }
            if(abs(left - right) > 1){
                return -1;
            }
            return max(left,right)+1;
        }
    }
};
int main(int argc,const char *argv[]){
    return 0;
}
