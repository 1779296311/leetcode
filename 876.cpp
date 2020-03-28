/*********************************************
*     ------------------------
*     ------------------------
*     file name: 876.cpp
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
    ListNode* middleNode(ListNode* head) {
        if(head == NULL || head->next == NULL){
            return head;
        }
        ListNode *slow = head;
        ListNode *fast = head;
        while(fast && fast->next){
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
};
