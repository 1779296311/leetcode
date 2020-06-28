/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_list_pro.cpp
*     author   : @ JY
*     date     : 2020--05--05
**********************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <stdlib.h>
using  namespace  std;
struct listNode{
    listNode* next;
    int val;
    listNode(int v):val(v),next(nullptr){}
};
class Solution{
    public:
        //________is___palindrome__________________///
        bool isPalindrome(listNode* head){
            listNode *slow = head;
            listNode *fast = head;
            while(fast && fast->next){
                slow = slow->next;
                fast = fast->next->next;
            }
            listNode* tmp  = slow;
            listNode* pre  = nullptr;
            listNode* next = nullptr;
            while(tmp){
                next      = tmp->next;
                tmp->next = pre;
                pre       = tmp;
                tmp       = next;
            }
            bool res = true;
            tmp      = head;
            fast     = pre;
            while(pre != slow){
                if(tmp->val != pre->val){
                    res = false;
                    break;
                }
                tmp = tmp->next;
                pre = pre->next;
            }
            if(tmp->val != pre->val){
                res = false;
            }
            pre  = nullptr;
            next = nullptr;
            while(fast->next!=slow){
                next       = fast->next;
                fast->next = pre;
                pre        = fast;
                fast       = next;
            }
            slow->next = pre;
            return res;
        }
        struct myNode{
            listNode *head;
            listNode *last;
            myNode():last(nullptr),head(nullptr){}
        };
        //--------------------------partion---------------------------------------------------------//
        listNode* partionList(listNode* head, int val){
            if(!head){
                return nullptr;
            }
            myNode *lessV    = new myNode();
            myNode *equalV   = new myNode();
            myNode *greaterV = new myNode();
            listNode *tmp    = nullptr;
            while(head){
                tmp = head->next;
                head->next = nullptr;
                if(head->val<val){
                    if(!lessV->head){
                        lessV->head = head;
                        lessV->last = head;
                    }else{
                        lessV->last->next = head;
                        lessV->last       = head;
                    }
                }else if(head->val==val){
                    if(!equalV->head){
                        equalV->head = head;
                        equalV->last = head;
                    }else{
                        equalV->last->next = head;
                        equalV->last       = head;
                    }
                }else{
                    if(!greaterV->head){
                        greaterV->head = head;
                        greaterV->last = head;
                    }else{
                        greaterV->last->next = head;
                        greaterV->last       = head;
                    }
                }
                head = tmp;
            }
            int flag = -1;
            listNode *res = new listNode(-1);
            res->next     = lessV->head==nullptr?(equalV->head==nullptr?({flag=1;greaterV->head;}):({flag=2;equalV->head;})):({flag=3;lessV->head;});
            if(flag==3){
                if(!equalV->head){
                    lessV->last->next  = greaterV->head;
                }else{
                    lessV->last->next  = equalV->head;
                    equalV->last->next = greaterV->head;
                }
            }else if(flag==2){
                equalV->last->next = greaterV->head;
            }else{
                ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            }
            return res->next;
        }
        void debug(listNode* head){
            listNode *tmp  = head;
            while(tmp){
                cout<<tmp->val<<" ";
                tmp = tmp->next;
            }
            cout<<endl;
        }
        //////-____---------------------------------copy-------with------------------------random--------------------//
        struct List{
            int val;
            List * next;
            List * random;
            List(int v):val(v),next(nullptr),random(nullptr){}
            List(int v,List* r):val(v),next(nullptr),random(r){}
        };
        List* copyWithRandom(List* head){
            if(!head){
                return head;
            }
            List* tmp  = head;
            List* next = nullptr;
            while(tmp){
                next            = tmp->next;
                tmp->next       = new List(tmp->val);
                tmp->next->next = next;
                tmp             = next;
            }
            List *res = head->next;
            List *t   = res;
            tmp       = head;
            while(tmp->next&&t->next){
                if(tmp->random){
                    t->random = tmp->random->next;
                }
                t         = t->next->next;
                tmp       = tmp->next->next;
            }
            t   = res;
            tmp = head;
            while(tmp->next&&t->next){
                tmp->next = tmp->next->next;
                t->next   = t->next->next;

                t         = t->next;
                tmp       = tmp->next;
            }
            return res;
        }
        void debug(List* head){
            List* tmp = head;
            while(tmp){
                cout<<tmp->val<<" ";
                if(tmp->random){
                    cout<<"random is "<<tmp->random->val<<"   "<<endl;
                }else{
                    cout<<"no random \n";
                }
                tmp = tmp->next;
            }
        }
        //---------------------------change-------------------tree------------to--------------list(2)----------------------------//
        struct list2{
            int val;
            list2* pre;
            list2* next;
            list2(int v,list2* p, list2* n):val(v),pre(p),next(n){}
            list2(int v):val(v),pre(nullptr),next(nullptr){}
        };
        struct tree{
            int val;
            tree* left;
            tree* right;
            tree(int v):val(v),left(nullptr),right(nullptr){}
            tree(int v,tree* l, tree* r):val(v),left(l),right(r){}
        };
        list2* changeTreeToList2(tree* head){
            if(!head){
                return nullptr;
            }
            list2 *L = changeTreeToList2(head->left);
            list2 *R = changeTreeToList2(head->right);
            list2 *h = new list2(head->val);
            h->next  = h;
            if(L && R){
                list2 *last  = L->next;
                h->pre       = L;
                L->next      = h;
                h->next      = R->next;
                R->next->pre = h;
                R->next      = last;
                return R;
            }else if(!L && R){
                h->next      = R->next;
                R->next->pre = h;
                R->next      = h;
                return R;
            }else if(L && !R){
                h->next = L->next;
                L->next = h;
                h->pre  = L;
            }
            return h;
        }
        list2* changeTreeTolist(tree* head){
            list2*  res = changeTreeToList2(head);
            list2*  tmp = res;
            res         = res->next;
            tmp->next   = nullptr;
            return res;
        }
        void debug(list2* head){
            list2* tmp = head;
            while(tmp){
                cout<<tmp->val<<" ";
                tmp = tmp->next;
            }
            cout<<endl;
        }
//-------------------------------k个一组翻转链表
        listNode* reverseK(int k,listNode* head){
            listNode* cur   = head;
            listNode* pre   = nullptr;
            listNode* next  = nullptr;
            listNode* begin = nullptr;
            int count       = 1;
            while(cur){
                next   = cur->next;
                if(count == k){
                    begin = pre==nullptr?head:pre->next;
                    head  = pre==nullptr?cur:head;
                    reverse(pre,begin,cur,next);
                    count = 0;
                    pre   = begin;
                }
                ++count;
                cur = next;
            }
            return head;
        }

        void reverse(listNode* left, listNode* begin, listNode* end, listNode* right){
            listNode* pre  = nullptr;
            listNode* next = nullptr;
            listNode* h    = begin;
            while(begin != right){
                next        = begin->next;
                begin->next = pre;
                pre         = begin;
                begin       = next;
            }
            if(left)left->next  = pre;
            h->next     = right;
        }
//---------------------------------链表相加
        listNode* add_list(listNode* l1, listNode* l2){
            listNode* pre1  = nullptr;
            listNode* pre2  = nullptr;
            listNode* next1 = nullptr;
            listNode* next2 = nullptr;
            int len1        = 0;
            int len2        = 0;
            while(l1!=nullptr && ++len1){
                next1    = l1->next;
                l1->next = pre1;
                pre1     = l1;
                l1       = next1;
            }
            while(l2!=nullptr && ++len2){
                next2    = l2->next;
                l2->next = pre2;
                pre2     = l2;
                l2       = next2;
            }
            l1 = pre1;
            l2 = pre2;
            pre1 = pre2 = nullptr;

            if(len1<len2){ swap(l1,l2); }

            listNode* H       = new listNode(-1);
            int flag          = 0;
            listNode* newNode = nullptr;
            while(len1-->0){
                int tmp = 0;
                if(l2){
                    tmp   = l2->val;

                    next2    = l2->next;
                    l2->next = pre2;
                    pre2     = l2;
                    l2       = next2;
                }
                newNode       = new listNode((tmp+l1->val+flag)%10);
                newNode->next = H->next;
                H->next       = newNode;
                flag          = tmp+l1->val+flag>=10;

                next1    = l1->next;
                l1->next = pre1;
                pre1     = l1;
                l1       = next1;
            }
            if(flag) newNode=new listNode(1),newNode->next=H->next,H->next=newNode;
            return H->next;
        }
//--------shan----chu------dao-----shu-----di----K----ge--------------------------------------------
        listNode* delete_k(int k, listNode* head){
            listNode* h = head;
            while(h){
                h = h->next;
                --k;
            }
            if(!k){
                listNode* res = head->next;
                delete(head);
                return res;
            }
            if(k>0){ return head; }
            ::std::cout<<"K: "<<k<<endl;
            h = head;
            while(++k){
                h = h->next;
            }
            listNode*tmp = h->next;
            h->next = tmp->next;
            delete(tmp);
            ::std::cout<<"val: "<<h->val<<endl;
            return head;
        }
//23. 合并K个排序链表
        struct ListNode {
            int val;
            ListNode *next;
            ListNode(int x) : val(x), next(NULL) {}
        };
        ListNode* mergeKLists(::std::vector<ListNode*>& lists) {
            ListNode* res  = new ListNode(-1);
            ::std::priority_queue<int,::std::vector<int>,::std::less<int>> big_heap;
            for(ListNode *head : lists){
                while(head){
                    big_heap.push(head->val);
                    head = head->next;
                }
            }
            while(big_heap.size()){
                ListNode* tmp = new ListNode(big_heap.top());
                tmp->next = res->next;
                res->next = tmp;
                big_heap.pop();
            }
            return res->next;
        }
//86 分隔链表
//定一个链表和一个特定值 x，对链表进行分隔，使得所有小于 x 的节点都在大于或等于 x 的节点之前。
//应当保留两个分区中每个节点的初始相对位置。
        ListNode* partition(ListNode* head, int x){
            ListNode pre(-1);

            ListNode H(INT_MAX);
            H.next          = head;
            ListNode* ahead = &H;
            ListNode* p     = &pre;
            ListNode* cur   = head;
            ListNode* next  = nullptr;
            while(cur){
                next = cur->next;
                if(cur->val<x){
                    ahead->next = next;
                    cur->next   = nullptr;
                    p->next     = cur;
                    p           = cur;
                    cur   = next;
                    continue;
                }
                ahead = cur;
                cur   = next;
            }
            if(pre.next){
                p->next = H.next;
                return pre.next;
            }
            return head;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    listNode* head                                 = new listNode(1);
    head->next                                     = new listNode(2);
    head->next->next                               = new listNode(3);
    head->next->next->next                         = new listNode(4);
    head->next->next->next->next                   = new listNode(5);
    head->next->next->next->next->next             = new listNode(6);

    listNode* head2                                 = new listNode(1);
    head2->next                                     = new listNode(3);
    head2->next->next                               = new listNode(2);
    head2->next->next->next                         = new listNode(5);
    head2->next->next->next->next                   = new listNode(5);
    head2->next->next->next->next->next             = new listNode(2);
    te.debug(head);
    
    te.debug(te.delete_k(2,head));

    //listNode* head3 = te.add_list(head,head2);
    //te.debug(head3);
    //listNode* head                                 = new listNode(1);
    //head->next                                     = new listNode(2);
    //head->next->next                               = new listNode(3);
    //head->next->next->next                         = new listNode(4);
    //head->next->next->next->next                   = new listNode(5);
    //head->next->next->next->next->next             = new listNode(6);
    //head->next->next->next->next->next->next       = new listNode(7);
    //head->next->next->next->next->next->next->next = new listNode(8);
    //te.debug(head);
    ////te.reverseK(2,head);
    //te.debug(te.reverseK(2,head));
    //te.debug(te.changeTreeTolist(head));
    //Solution::List* head                     = new Solution::List(0);
    //head->next                               = new Solution::List(1,head);
    //head->next->next                         = new Solution::List(2);
    //head->next->next->next                   = new Solution::List(3,head->next->next);
    //head->next->next->next->next             = new Solution::List(4);
    //head->next->next->next->next->next       = new Solution::List(5,head->next);
    //head->next->next->next->next->next->next = new Solution::List(6);
    //te.debug(te.copyWithRandom(head));
    //li->nextstNode *head                                 = new listNode(4);
    //head->next                                     = new listNode(3);
    //head->next->next                               = new listNode(2);
    //head->next->next->next                         = new listNode(5);
    //head->next->next->next->next                   = new listNode(5);
    //head->next->next->next->next->next             = new listNode(2);
    //head->next->next->next->next->next->next       = new listNode(3);
    //head->next->next->next->next->next->next->next = new listNode(4);
    //head->next->next->next->next->next->next->next->next = new listNode(4);
    //te.debug(te.partionList(head,3));
    return 0;
}
