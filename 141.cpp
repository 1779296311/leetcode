/*********************************************
*     ------------------------
*     ------------------------
*     file name: 141.cpp
*     author   : @ JY
*     date     : 2020--02--25
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
    bool hasCycle(ListNode *head) {
        if(!head || !head->next){
            return false;
        }
        ListNode *__r   = head;
        ListNode *__l   = head->next;
        while(__r != __l){
            if(!__l || !__l->next){
                return false;
            }
            __r = __r->next;
            __l = __l->next->next;
        }
        return true;
    }
};
