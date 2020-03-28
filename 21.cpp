/*********************************************
*     ------------------------
*     ------------------------
*     file name: 21.cpp
*     author   : @ JY
*     date     : 2019--09--21
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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *a = NULL;
        ListNode *b = NULL;
        if(l1->val > l2 val){
            a = l1;
            b = l2;
        }else{
            a = l2;
            b = l1;
        }
        while(b){
            if(a->next == NULL){
                a->next = b;
                return l1;
            }
            if(a->val <= b->val && a->next->val >= b->val){
                tmp     = b->next;
                b->next = a->next;
                a->next = b;
                b       = tmp;
            }
            a = a->next;
        }
        return l1;
    }
};
