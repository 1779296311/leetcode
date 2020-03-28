#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {};
};

class Solusion{
    public:
        ListNode *addTwoNumbers(ListNode *l1, ListNode *l2){
            int flag  = 0;
            int value = 0;
            ListNode *resault  = l1, *tmp;
            while(l1 || l2){
                (l1) ? (tmp = l1, l1 = l1->next, value = tmp->val + flag) : (tmp->next = l2, tmp = l2, value = flag);
                (l2) ? (value = l2->val + value, l2 = l2->next) : (tmp->next = l1);
                tmp->val      = value % 10;
                (value > 9) ?(flag = 1):(flag = 0);
            }
            if(flag == 1 && l1==NULL && l2==NULL){
                tmp->next    = new ListNode(1);
            }
            return resault;
        }

};

/(l1) ? (pre = l1, l1 = l1->next, value = pre->val+flag):(pre->next = l2,pre = next, value = flag);
//(l2) ? (value = value + l2->val, l2 = l2->next):(pre->next = l1);
