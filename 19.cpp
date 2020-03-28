/*********************************************
*     ------------------------
*     ------------------------
*     file name: 19.cpp
*     author   : @ JY
*     date     : 2019--09--27
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *tmp   = new ListNode(0);
        tmp->next       = head;
        ListNode *right = tmp;
        ListNode *left  = tmp;
        for(int i=0; i<n; i++){
            left = left->next;
        }
        while(left->next){
            left  = left->next;
            right = right->next;
        }
        right->next = right->next->next;
        return tmp->next;
    }
};
