/*********************************************
*     ------------------------
*     ------------------------
*     file name: loopList.cpp
*     author   : @ JY
*     date     : 2020--03--09
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };
class Solution{
    public:
        ListNode *getFirstLoop(ListNode *head){
            if(!head || !head->next || !head->next->next){
                return NULL;
            }
            ListNode *fast = head;
            ListNode *slow = head;
            do{
                slow = slow->next;
                fast = fast->next->next;
            }while(fast && slow && fast->next && fast != slow);
            if(fast != slow){
                return NULL;
            }
            fast = head;
            while(fast != slow){
                fast = fast->next;
                slow = slow->next;
            }
            return fast;
        }
        ListNode *noLoop(ListNode *head1, ListNode *head2){
            ListNode *tmp1 = head1;
            ListNode *tmp2 = head2;
            while(tmp1 != tmp2){
                tmp1 = tmp1?tmp1->next:head2;
                tmp2 = tmp2?tmp2->next:head1;
            }
            return tmp1;
        }
        ListNode *withLoop(ListNode *head1, ListNode *loop1,
                           ListNode *head2, ListNode *loop2){
            if(loop1 == loop2){
                ListNode *tmp1 = head1;
                ListNode *tmp2 = head2;
                while(tmp1 != tmp2){
                    tmp1 = (tmp1!=loop1)?tmp1->next:head2;
                    tmp2 = (tmp2!=loop2)?tmp2->next:head1;
                }
                return tmp1;
            }else{
                cout<<"loop1 != loop2"<<endl;
                ListNode *tmp1 = loop1;
                while(tmp1 && tmp1 != loop2){
                    tmp1 = tmp1->next;
                }
                return tmp1;
            }
            return NULL;
        }
        ListNode *listCycle(ListNode *head1, ListNode *head2){
            if(!head1 || !head2){
                return NULL;
            }
            ListNode *loop1 = getFirstLoop(head1);
            ListNode *loop2 = getFirstLoop(head2);
            if(!loop1 && !loop2){
                cout<<"noLoop"<<endl;
                return noLoop(head1,head2);
            }else if(loop1 && loop2){
                cout<<"withLoop"<<endl;
                return withLoop(head1,loop1,head2,loop2);
            }
            return NULL;
        }
        void debug(ListNode *node){
            if(node){
                cout<<node->val<<endl;
            }else{
                cout<<"NULL"<<endl;
            }
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    ListNode *head1               = new ListNode(1);
    head1->next                   = new ListNode(2);
    head1->next->next             = new ListNode(3);
    head1->next->next->next       = new ListNode(4);
    head1->next->next->next->next = new ListNode(5);
    ListNode *head2               = new ListNode(-1);
    head2->next                   = new ListNode(-2);
    head2->next->next             = new ListNode(-3);
    head2->next->next->next       = new ListNode(-4);
    head2->next->next->next->next = new ListNode(-5);

    ListNode *head3               = new ListNode(100);
    head3->next                   = new ListNode(200);
    head3->next->next             = new ListNode(300);
    head3->next->next->next       = new ListNode(400);
    head3->next->next->next->next = new ListNode(500);
    head3->next->next->next->next->next = head3->next;

    head1->next->next->next->next = head3;
    head2->next->next->next->next = head3;
    //head2->next->next->next->next = head3->next->next->next;
    te.debug(te.listCycle(head1,head2));
    return 0;
}
 //*                    .::::.
 //*                  .::::::::.
 //*                 :::::::::::  FUCK YOU
 //*             ..:::::::::::'
 //*           '::::::::::::'
 //*             .::::::::::
 //*        '::::::::::::::..
 //*             ..::::::::::::.
 //*           ``::::::::::::::::
 //*            ::::``:::::::::'        .:::.
 //*           ::::'   ':::::'       .::::::::.
 //*         .::::'      ::::     .:::::::'::::.
 //*        .:::'       :::::  .:::::::::' ':::::.
 //*       .::'        :::::.:::::::::'      ':::::.
 //*      .::'         ::::::::::::::'         ``::::.
 //*  ...:::           ::::::::::::'              ``::.
 //* ```` ':.          ':::::::::'                  ::::..
 //*                    '.:::::'                    ':'````..
//...................................]]/@@@@@@@OO]]]`......................
//.............................,]@@@@@@@@@@@@@@@@@@@@@@@@].................
//..........................,O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@].............
//.......................,/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`..........
//.....................,O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\........
//..................../@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\......
//...................O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.....
//..................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`...
//................./@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@^..
//.................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@..
//................=@@@@@@@@@@@@@@@@........../@@@@@@@@@@@@@@@@@@@@@@@@@@@\.
//................/@@@@@@@@@@@@@@@/..*[oOOOOO@@@O][@@@\/@@@@@@@@@@@@@@@@@@`
//................O@@@@@@@@@@@@@@@^.*O@@@@@@@@@@@@@@@O@@@/@@@/@@@@@@@@@@@@^
//................=@@@@@@@@@@@@@@@^.....,OO@@@@@@@],@@@O@@\,O`=@@@@@@@@@@@\
//..@@@\...........@@@@@@@@@@@@@@@..........*o@@OO@@@/@@@@@^...\@@@@@@@@@@@
//..@@@@^...........[[O@@@@@@@@@@@.......,/OO[[\@@@o@@^\@`.....=@@@@@@@@@@@
//..@@=@\................@@^..........=OO^.*O@@].,@@/@@........O@@@@@@@@@@@
//..@@*@@*...............=@@`........./OO\]`..,@@@@@@..........@@@@@@@@@@@O
//..O@^O@^.]@@\`..........\@@`........*.O@/\@@@\]]*@@^........=@@@@@@@@@@@^
//..=@^=@@@@@@@@@^.........=@@@`.........\@@@@]]*,[\@@........=@@O@^..`....
//.O@@@\@\@@OO@O@@...........O@@@\`.......*,[[[O@@@@@@........,@@@@^.......
//=@@[/...[..=@@@@....]/@@@@@@@O@@@@@O]....[OOoooOo.@@@].......=@@@^.......
//.\@@`.......O@@O@@@@@@[@@OOOOOOOOO@@@@@@@]`.........\@@@.... ..@@O.......
//..,@@\.......O@@[`.....=@@OOOOOOOOOO@@@@@@@@@@@@@@@OO/@@@`......\@@......
//....\@@].....=@@........\@@OOOO@@OOO@@@@@@@@O]O@@@@@@@@@@@`......=@@`....
//......O@@O]..,[........]]@@@@@@@OOO@@@@@@OOO@@@@@@@@@@OOO@@`......,@@\...
//........[\@@@@@@@@@@@@@@@O[[`\@@OOO@@@@@@OOOOOOOO@@@@@OOOO@@`......,@@\..

