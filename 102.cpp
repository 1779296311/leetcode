/*********************************************
*     ------------------------
*     ------------------------
*     file name: 102.cpp
*     author   : @ JY
*     date     : 2019--10--23
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        vector<vector<int>> levelOrder(TreeNode* root){
            vector<vector<int>> res;
            if(!root){
                return res;
            }
            vector<TreeNode*> st;
            st.push_back(root);
            int begin = -1;
            int end   = 0;
            while(begin != end){
                vector<int> num;
                int size = end - begin;
                for(int i=0; i<size; i++){
                    TreeNode* tmp = st[++begin];
                    num.push_back(tmp->val);
                    if(tmp->left){
                        st.push_back(tmp->left);
                        end++;
                    }
                    if(tmp->right){
                        st.push_back(tmp->right);
                        end++;
                    }
                }
                res.push_back(num);
            }
            return res;
        }
};
