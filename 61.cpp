/*********************************************
*     ------------------------
*     ------------------------
*     file name: 61.cpp
*     author   : @ JY
*     date     : 2019--10--03
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
    ListNode* rotateRight(ListNode* head, int k) {
        ListNode *p        = head;
        ListNode *q        = head;
        ListNode *old_head = head;
        int num            = 0;
        if(head == NULL || head->next == NULL || k == 0){
            return head;
        }
        for(; p != NULL; p=p->next){
            num++;
        }
        num = k % num;
        if(num == 0){
            return head;
        }
        p = head;
        for(int i=0; i<num; i++){
            p = p->next;
        }
        while(p->next){
            p = p->next;
            q = q->next;
        }
        head    = q->next;
        q->next = NULL;
        q       = head;
        while(q && q->next != NULL){
            q = q->next;
        }
        q->next = old_head;
        return head;
    }
};
