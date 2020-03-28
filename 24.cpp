/*********************************************
*     ------------------------
*     ------------------------
*     file name: 24.cpp
*     author   : @ JY
*     date     : 2019--09--25
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
/*
给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
给定 1->2->3->4, 你应该返回 2->1->4->3.*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head == NULL || head->next == NULL){
            return head;
        }
        ListNode *tmp_head = new ListNode(0);
        tmp_head->next     = head;
        ListNode* tmp      = tmp_head;
        while(tmp->next && tmp->next->next){
            ListNode *m = tmp->next;
            tmp->next   = m->next;
            ListNode *n = tmp->next;
            m->next     = n->next;
            n->next     = m;

            tmp = m;
        }
        return tmp_head->next;
    }
};
