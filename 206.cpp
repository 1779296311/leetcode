/*********************************************
*     ------------------------
*     ------------------------
*     file name: 206.cpp
*     author   : @ JY
*     date     : 2020--05--01
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
struct ListNode{
    ListNode *next;
    int val;
    ListNode(int v):val(v),next(NULL){}
};
class Solution{
    public:
        ListNode* reverseList(ListNode* head){
            ListNode *pre  = NULL;
            ListNode *next = NULL;
            while(head){
                next       = head->next;
                head->next = pre;
                pre        = head;
                head       = next;
            }
            return pre;
        }
};
