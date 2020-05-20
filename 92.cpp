/*********************************************
*     ------------------------
*     ------------------------
*     file name: 92.cpp
*     author   : @ JY
*     date     : 2020--04--30
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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode *head1 = new ListNode(0);
        head1->next     = head;
        ListNode *tmp   = head1;
        int m1          = m;
        while(--m1){
            tmp = tmp->next;
        }
        head           = tmp->next;
        ListNode *next = NULL;
        ListNode *pre  = NULL;
        while(m++<=n){
            next       = head->next;
            head->next = pre;
            pre        = head;
            head       = next;
        }
        tmp->next->next = head;
        tmp->next       = pre;
        return head1->next;
    }
    void debug(ListNode *head){
        while(head){
            cout<<head->val<<"  ";
            head = head->next;
        }
        cout<<endl;
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    ListNode*head                      = new ListNode(1);
    head->next                         = new ListNode(2);
    head->next->next                   = new ListNode(3);
    head->next->next->next             = new ListNode(4);
    head->next->next->next->next       = new ListNode(5);
    //head->next->next->next->next->next = new ListNode(5);
    te.debug(head);
    head = te.reverseBetween(head,2,4);
    te.debug(head);
    return 0;
}
