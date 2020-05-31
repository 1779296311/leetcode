/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ32.cpp
*     author   : @ JY
*     date     : 2020--05--23
**********************************************/
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <queue>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    ::std::vector<int> levelOrder1(TreeNode* root) {
        if(!root)return ::std::vector<int>{};
        ::std::vector<int> res;
        ::std::queue<TreeNode*> q;
        q.push(root);
        TreeNode* tmp = nullptr;
        while(!q.empty()){
            tmp = q.front();
            q.pop();
            res.push_back(tmp->val);
            if(tmp->left){
                q.push(tmp->left);
            }
            if(tmp->right){
                q.push(tmp->right);
            }
        }
        return res;
    }
    ::std::vector<::std::vector<int>> levelOrder2(TreeNode* root){
        if(!root)return ::std::vector<::std::vector<int>>{};
        ::std::vector<::std::vector<int>>res;
        ::std::vector<TreeNode*>q;
        TreeNode* t = nullptr;
        int begin   = -1;
        int end     = 0;
        int size    = 0;
        q.push_back(root);
        while(begin != end){
            ::std::vector<int>tmp;
            size = end - begin;
            for(int i=0; i<size; ++i){
                t = q[++begin];
                tmp.push_back(t->val);
                if(t->left){
                    ++end;
                    q.push_back(t->left);
                }
                if(t->right){
                    ++end;
                    q.push_back(t->right);
                }
            }
            res.push_back(tmp);
        }
        return res;
    }
    ::std::vector<::std::vector<int>> levelOreder3(TreeNode* root){
        if(!root)return ::std::vector<::std::vector<int>>{};
        ::std::vector<::std::vector<int>> res;
        ::std::vector<TreeNode*> q;
        q.push_back(root);
        int begin   = -1;
        int size    = 0;
        int end     = 0;
        int flag    = 1;
        TreeNode* t = nullptr;
        while(end != begin){
            ::std::vector<int>tmp;
            size = end - begin;
            for(int i = 0; i<size; ++i){
                t = q[++begin];
                tmp.push_back(t->val);
                if(t->left){
                    ++end;
                    q.push_back(t->left);
                }
                if(t->right){
                    ++end;
                    q.push_back(t->right);
                }
            }
            if((++flag)&1){
                reverse(tmp.begin(),tmp.end());
            }
            res.push_back(tmp);
        }
        return res;
    }
};
