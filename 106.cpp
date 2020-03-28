/*********************************************
*     ------------------------
*     ------------------------
*     file name: 106.cpp
*     author   : @ JY
*     date     : 2019--10--29
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <stack>
#include <vector>
using  namespace  std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(inorder.empty() || postorder.empty()){
            return NULL;
        }
        stack<TreeNode*> st;
        int p_size     = postorder.size();
        TreeNode *root = new TreeNode (postorder[p_size-1]);
        st.push(root);
        int i = p_size - 2;
        int j = inorder.size()-1;
        for(;i>=0;i--){
            TreeNode *cur  = new TreeNode(postorder[i]);
            TreeNode *back = NULL;
            while(!st.empty() && inorder[j] == st.top()->val){
                back = st.top();
                st.pop();
                j--;
            }
            if(back){
                back->left = cur;
            }else{
                st.top()->right = cur;
            }
            st.push(cur);
        }
        return root;
    }
    TreeNode* buildTree(vector<int>& in, vector<int>& po){
        if(in.size() == 0 || po.size() ==0){
            return NULL;
        }

        int i_size = in.size();
        int index  = 0;
        for(int i=0; i<i_size; i++){
            if(in[i] == po.back()){
                index = i;
                break;
            }
        }
        TreeNode *root = new TreeNode(po.back());
        vector<int> i_left (in.begin(),in.begin()+index);
        vector<int> i_right(in.begin()+index+1,in.end());

        vector<int> p_left (po.begin(),po.begin()+index);
        vector<int> p_right(po.begin()+index+1,po.end()-1);

        root->left  = buildTree(i_left,p_left);
        root->right = buildTree(i_right,p_right);

        return root;
    }
};

