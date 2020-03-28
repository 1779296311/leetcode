/*********************************************
*     ------------------------
*     ------------------------
*     file name: 109.cpp
*     author   : @ JY
*     date     : 2019--11--26
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
// struct ListNode {
//     int val;
//     ListNode *next;
//     ListNode(int x) : val(x), next(NULL) {}
// };
// struct TreeNode {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
// };

class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if(!head){
            return NULL;
        }
        return my_fun(head, 0);
    }
    TreeNode* my_fun(ListNode* __b, ListNode* __e){
        if(__e != __b){
            ListNode* __t1 = __b;
            ListNode* __t2 = __b;
            while(__t1 && __t1->next){
                __t1 = __t1->next;
                __t1 = __t1->next;
                __t2 = __t2->next;
            }
            TreeNode* __root = new TreeNode(__t2->val);
            __root->left     = my_fun(__b, __t2);
            __root->right    = my_fun(__t2->next, __e);
            return __root;
        }
        return NULL;
    }
};
