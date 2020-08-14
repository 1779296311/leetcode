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
//给你一棵二叉树，它的根为 root 。请你删除 1 条边，使二叉树分裂成两棵子树，且它们子树和的乘积尽可能大。 由于答案可能会很大，请你将结果对 10^9 + 7 取模后再返回。
        int MOD = 1e9 + 7;
        int maxProduct(TreeNode* root){
            long long res = 0, sum = 0;
            dfs(root, sum);
            dfs(root, res, sum);
            return res;
        }
        void dfs(TreeNode* root, long long& sum){
            if(!root)return;
            sum += root->val;
            dfs(root->left, sum);
            dfs(root->right, sum);
        }
        long long dfs(TreeNode* root, long long & res, long long& sum){
            if(!root)return 0;
            long long l_sum = 0;
            long long r_sum = 0;

            l_sum  = dfs(root->left,  res, sum);
            r_sum  = dfs(root->right, res, sum);

            res = std::max(res, ((sum - l_sum)*l_sum));
            res = std::max(res, ((sum - r_sum)*r_sum));

            return l_sum + r_sum + root->val;
        }
//给你一棵以 root 为根的二叉树，二叉树中的交错路径定义如下：
//选择二叉树中 任意 节点和一个方向（左或者右）。
//如果前进方向为右，那么移动到当前节点的的右子节点，否则移动到它的左子节点。
//改变前进方向：左变右或者右变左。
//重复第二步和第三步，直到你在树中无法继续移动。
//交错路径的长度定义为：访问过的节点数目 - 1（单个节点的路径长度为 0 ）。
        int longestZigZag(TreeNode* root){
            int res = 0;
            dfs(root, 0, res, 0);
            dfs(root, 1, res, 0);
            return res;
        }
        void dfs(TreeNode* root, int f, int& res, int len){
            if(!root)return;
            res = std::max(res, len);
            if(f){
                if(root->right)dfs(root->right, !f, res, len+1);
                dfs(root->left, f, res, 1);
            }else{
                if(root->left)dfs(root->left, !f, res, len+1);
                dfs(root->right, f, res, 1);
            }
        }
};
