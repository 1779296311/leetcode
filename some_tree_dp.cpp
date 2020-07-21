/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_tree_dp.cpp
*     author   : @ JY
*     date     : 2020--07--15
**********************************************/
#include <iostream>
#include <vector>
#include <deque>
#include <stdlib.h>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution{
    public:
//从左向右遍历一个数组，通过不断将其中的元素插入树中可以逐步地生成一棵二叉搜索树。给定一个由不同节点组成的二叉搜索树，输出所有可能生成此树的数组。
        std::vector<std::vector<int>> BSTSequence(TreeNode * root){
            std::deque<TreeNode*> q;
            std::vector<int> buf;
            std::vector<std::vector<int>>res;
            q.push_back(root);
            get_res(q, buf, res);
            return res;
        }
        void get_res(std::deque<TreeNode*>& q, std::vector<int>& buf, std::vector<std::vector<int>>& res){
            if(q.empty()){
                res.push_back(buf);
                return ;
            }
            int size = q.size();
            while(size--){
                TreeNode *r = q.front();
                q.pop_front();
                buf.push_back(r->val);
                int c    = 0;
                if(r->left){
                    ++c;
                    q.push_back(r->left);
                }
                if(r->right){
                    ++c;
                    q.push_back(r->right);
                }
                get_res(q, buf, res);
                while(c--)q.pop_back();

                q.push_back(r);
                buf.pop_back();
            }
        }
};
