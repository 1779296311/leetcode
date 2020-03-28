/*********************************************
*     ------------------------
*     ------------------------
*     file name: 108.cpp
*     author   : @ JY
*     date     : 2019--11--25
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stack>
using  namespace  std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* root;
    TreeNode* sortedArrayToBST(vector<int>& nums){
        if(!nums.size()){
            return NULL;
        }
        TreeNode *root = new TreeNode(nums[0]);
        TreeNode *tmp;
        stack<TreeNode*> st;
        for(int i=1; i<nums.size(); i++){
        //for(int i=1; i<3; i++){
            tmp = root;
            while(tmp){
                st.push(tmp);
                if(nums[i] < tmp->val){
                    if(!tmp->left){
                        tmp->left = new TreeNode(nums[i]);
                        st.push(tmp->left);
                        break;
                    }
                    tmp = tmp->left;
                }else if(nums[i] > tmp->val){
                    if(!tmp->right){
                        tmp->right = new TreeNode(nums[i]);
                        st.push(tmp->right);
                        break;
                    }
                    tmp = tmp->right;
                }
            }
            //cout<<endl<<"----"<<endl;
            //__in_Order(root);
            root = __insert_fix(st,nums[i]);
            //__in_Order(root);
            //cout<<endl<<"----"<<endl;
        }
//cout<<"put:"<<root->val<<endl;
//cout<<"left:"<<root->left->val<<endl;
//cout<<"right:"<<root->right->val<<endl;
        return root;
    }
    TreeNode* __insert_fix(stack<TreeNode*> &st, int __v){
        TreeNode* __tmp = root;
//cout<<"@@@@"<<endl;
        while(!st.empty()){
            __tmp = st.top();
            st.pop();
            int __l_h = __get_Height(__tmp->left);
            int __r_h = __get_Height(__tmp->right);
//cout<<" l:"<<__l_h<<" r:"<<__r_h<<endl;
            int __d   = __l_h - __r_h;
            if(abs(__d)<2){
                continue;
            }else{
                if(__d == 2){
                    if(__tmp->left->val > __v){
                        __tmp = __rorate_right(__tmp);
                    }else{
                        __tmp = __left_than_right(__tmp);
                    }
                }else if(__d == -2){
                    if(__tmp->right->val < __v){
//cout<<"555"<<endl;
                        __tmp = __rorate_left(__tmp);
                    }else{
                        __tmp = __right_than_left(__tmp);
                    }
                }
                if(!st.empty()){
//cout<<"44"<<endl;
                    if(st.top()->val < __v){
                        st.top()->right = __tmp;
                    }else{
                        st.top()->left  = __tmp;
                    }
                }
            }
        }
//cout<<"r__v:"<<__tmp->val<<endl;
        return __tmp;
//cout<<"root:";__in_Order(root);
    }
    int __get_Height(TreeNode* __r){
        if(__r){
            return max(__get_Height(__r->left),__get_Height(__r->right)) + 1;
        }
        return 0;
    }
    TreeNode* __rorate_left(TreeNode *p){
        if(p){
            TreeNode* right  = p->right;
            p->right         = right->left;
            right->left      = p;
            return right;
        }
        return NULL;
    }
    TreeNode* __rorate_right(TreeNode *p){
        if(p){
            TreeNode* left   = p->left;
            p->left          = left->right;
            left->right      = p;
            return left;
        }
        return NULL;
    }
    TreeNode* __right_than_left(TreeNode *p){
        if(p){
            p->right = __rorate_right(p->right);
            return __rorate_left(p);
        }
        return NULL;
    }
    TreeNode* __left_than_right(TreeNode *p){
        if(p){
            p->left = __rorate_left(p->left);
            return __rorate_right(p);
        }
        return NULL;
    }
    void __in_Order(TreeNode* root){
        if(root){
            __in_Order(root->left);
            cout<<"val:"<<root->val<<" ";
            __in_Order(root->right);
        }
    }
    void __in_Order(vector<int>& num){
        root = sortedArrayToBST(num);
        __in_Order(root);
    }
    void __d_h(){
        cout<<__get_Height(root->left)<<endl;
        cout<<__get_Height(root->right)<<endl;
    }
};
int main(int argc,const char *argv[]){
    vector<int> num = {-10,-3,0,5,9};
    Solution te;
    te.__in_Order(num);
    te.__d_h();
    return 0;
}
