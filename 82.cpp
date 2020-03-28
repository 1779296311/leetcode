/*********************************************
*     ------------------------
*     ------------------------
*     file name: 82.cpp
*     author   : @ JY
*     date     : 2020--02--24
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
        ListNode  *H = new ListNode(-1);
        H->next      = head;
        ListNode **p = &(H->next);
        ListNode **e = NULL;
        while(*p){
            e = p;
            while(*e && (*p)->val == (*e)->val){
                e = &(*e)->next;
            }
            if(e == &(*p)->next){
                p = e;
            }else{
               *p = *e;
            }
        }
        return H->next;
    }
};
