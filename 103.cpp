/*********************************************
*     ------------------------
*     ------------------------
*     file name: 103.cpp
*     author   : @ JY
*     date     : 2019--12--03
**********************************************/
#include <iostream>
#include <algorithm>
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> __res;
        if(!root){
            return __res;
        }
        int end   = 0;
        int begin = -1;
        vector<TreeNode*> __tmp;
        __tmp.push_back(root);
        while(end != begin){
            int size = end -begin;
            vector<int> __m;
            for(int i=0; i<size; i++){
                TreeNode *__r = __tmp[++begin];
                __m.push_back(__r->val);
                if(__r->left){
                    __tmp.push_back(__r->left);
                    ++end;
                }
                if(__r->right){
                    __tmp.push_back(__r->right);
                    ++end;
                }
            }
            __res.push_back(__m);
        }
        for(int i=1; i<__res.size(); i+=2){
            reverse(__res[i].begin(),__res[i].end());
        }
        return __res;
    }
};
int main(int argc,const char *argv[]){
    Solution te;

    return 0;
}
