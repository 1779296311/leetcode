/*********************************************
*     ------------------------
*     ------------------------
*     file name: 101.cpp
*     author   : @ JY
*     date     : 2019--10--22
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
class Solution{
  public:
        bool isSymmetric(TreeNode* root){
            if(!root){
                return true;
            }
            vector<char> s;
            vector<char> t;
            head_1(s, root->left);
            head_2(t, root->right);
            dis(s);
            dis(t);
            if(s != t){
                return false;
            }
            return true;
        }
        void head_1(vector<char>& st, TreeNode* root){
            if(!root){
                return;
            }
            st.push_back(root->val+'0');
            head_1(st,root->left);
            if(!root->left){
                st.push_back('&');
            }
            head_1(st,root->right);
            if(!root->right){
                st.push_back('&');
            }
        }
        void head_2(vector<char>& st, TreeNode* root){
            if(!root){
                return;
            }
            st.push_back(root->val+'0');
            head_2(st,root->right);
            if(!root->right){
                st.push_back('&');
            }
            head_2(st,root->left);
            if(!root->left){
                st.push_back('&');
            }
        }
        void dis(vector<char>&st){
            for(int i=0; i<st.size(); i++){
                cout<<st[i]<<"__";
            }
            cout<<endl;
        }
        bool is_symmetric(TreeNode* root){
            return mirror(root,root);
        }
        bool mirror(TreeNode* left, TreeNode* right){
            if(!left && !right){
                return true;
            }else if(!left || !right){
                return false;
            }else{
                return(left->val == right->val)&&
                       mirror(left->left,left->right)&&
                       mirror(right->left, right->right);
            }
        }
};
int main(int argc,const char *argv[]){
    vector<int> a = {1};
    vector<int> b = {2};
    if(a == b){
        cout<<"++"<<endl;
    }
    return 0;
}
