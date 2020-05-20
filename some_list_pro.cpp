/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_list_pro.cpp
*     author   : @ JY
*     date     : 2020--05--05
**********************************************/
#include <iostream>
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
            tmp->next = nullptr;
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
};
int main(int argc,const char *argv[]){
    Solution te;
    Solution ::tree* head   = new Solution::tree(0);
    head->left              = new Solution::tree(1);
    head->left->left        = new Solution::tree(3);
    head->left->right       = new Solution::tree(4);
    head->left->right->left = new Solution::tree(5);
    head->right             = new Solution::tree(-11);
    head->right->left       = new Solution::tree(6);
    head->right->right      = new Solution::tree(2);
    te.debug(te.changeTreeTolist(head));
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
