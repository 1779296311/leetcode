/*********************************************
*     ------------------------
*     ------------------------
*     file name: 160.cpp
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode * __ha = headA;
        ListNode * __hb = headB;
        if(!(__ha || __hb)){
            return NULL;
        }
        while(__ha != __hb){
            __ha = __ha==NULL?headB:__ha->next;
            __hb = __hb==NULL?headA:__hb->next;
        }
        return __ha;
    }
};
