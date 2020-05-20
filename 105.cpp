/*********************************************
*     ------------------------
*     ------------------------
*     file name: 105.cpp
*     author   : @ JY
*     date     : 2019--10--24
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stack>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
using  namespace  std;
class  Solution{
    public:
        TreeNode* buildTree3(vector<int>& preorder, vector<int>& inorder){
            return partition1(preorder,inorder,0,0,inorder.size()-1);
        }
        TreeNode* partition1(vector<int>& pre, vector<int>& in, int root, int begin, int end){
            if(begin > end){
                return nullptr;
            }
            int index = 0;
            while(pre[root] != in[index]){++index;}
            TreeNode* head = new TreeNode(pre[root]);
            head->left     = partition1(pre,in,root+1,begin,index-1);
            head->right    = partition1(pre,in,root+1+index-begin,index+1,end);
            return head;
        }
        //////------------------------------------------------------////
        TreeNode* buildTree2(vector<int>& preorder, vector<int>& inorder){
            if(preorder.empty() || preorder.size() != inorder.size()){
                return NULL;
            }
            TreeNode*  res = new TreeNode(preorder[0]);
            int size       = preorder.size();
            int i          = 1;
            int j          = 0;
            stack<TreeNode*> st;
            st.push(res);
            for(; i<size; i++){
                TreeNode* back = NULL;
                TreeNode* cur  = new TreeNode(preorder[i]);
                while(!st.empty() && st.top()->val == inorder[j]){
                    back = st.top();
                    st.pop();
                    j++;
                }
                if(back){
                    back->right    = cur;
                }else{
                    st.top()->left = cur;
                }
                st.push(cur);
            }
            return res;
        }
        TreeNode* buildTree1(vector<int>& pre, vector<int>& in){
            int size = pre.size();
            if(size == 0){
                return NULL;
            }
            TreeNode *res = new TreeNode(pre[0]);
            vector<int> pre_left, pre_right, in_left, in_right;
            int i = 0;
            for(; i<in.size() ;i++){
                if(in[i] == pre[0]){
                    break;
                }
            }

            for(int j=0; j<i; j++){
                pre_left.push_back(pre[j+1]);
                in_left.push_back(in[j]);
            }
            for(int j=i+1; j<size; j++){
                pre_right.push_back(pre[j]);
                in_right.push_back(pre[j]);
            }

            res->left  = buildTree(pre_left,in_left);
            res->right = buildTree(pre_right,in_right);
            return res;
        }
};
