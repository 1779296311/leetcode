/*********************************************
*     ------------------------
*     ------------------------
*     file name: 104.cpp
*     author   : @ JY
*     date     : 2019--10--24
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        int maxDepth(TreeNode* root){
            if(!root){
                return 0;
            }
            int left  = maxDepth(root->left);
            int right = maxDepth(root->right);
            return ((left > right ? left : right) +1);
        }
};
