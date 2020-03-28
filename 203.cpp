/*********************************************
*     ------------------------
*     ------------------------
*     file name: 203.cpp
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
    ListNode* removeElements(ListNode* head, int val) {
        if(head == NULL){
            return NULL;
        }
        ListNode* right = head->next;
        ListNode* left  = head;
        while(right){
            if(right->val == val){
                left->next = right->next;
                right      = left->next;
            }else{
                right = right->next;
                left  = left->next;
            }
        }
        if(head->val == val){
            head = head->next;
        }
        return head;
    }
};
