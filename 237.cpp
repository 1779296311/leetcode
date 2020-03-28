/*********************************************
*     ------------------------
*     ------------------------
*     file name: 237.cpp
*     author   : @ JY
*     date     : 2019--09--22
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };
class Solution {
public:
    void deleteNode(ListNode* node) {
        node->val  = node->next-value;
        node->next = node->next->next;
    }
};
