/*********************************************
*     ------------------------
*     ------------------------
*     file name: 83.cpp
*     author   : @ JY
*     date     : 2020--02--26
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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode **__tmp = &head;
        ListNode **__t   = NULL;
        while(*__tmp &&(__t = __tmp)){
            while(*__t &&(*__tmp)->val == (*__t)->val){
                __t = &(*__t)->next;
            }
            (*__tmp)->next = *__t;
            __tmp          =  __t;
        }
        return head;
    }
};
