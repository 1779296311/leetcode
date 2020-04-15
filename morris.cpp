/*********************************************
*     ------------------------
*     ------------------------
*     file name: morris.cpp
*     author   : @ JY
*     date     : 2020--03--27
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
struct tree{
    tree *left;
    tree *right;
    int val;
    tree(int v):val(v),left(NULL),right(NULL){}
};
class Solution{
    public:
        void morris_PreOrder(tree *head){
            tree *cur    = head;
            tree *rightM = NULL;
            while(cur){
                rightM   = cur->left;
                if(rightM){
                    while(rightM->right && rightM->right != cur){
                        rightM = rightM->right;
                    }
                    if(!rightM->right){
                        cout<<cur->val<<" ";
                        rightM->right = cur;
                        cur           = cur->left;
                        continue;
                    }else{
                        rightM->right = NULL;
                    }
                }else{
                    cout<<cur->val<<" ";
                }
                cur = cur->right;
            }
        }
        void morris_InOrder(tree *head){
            tree *cur    = head;
            tree *rightM = NULL;
            while(cur){
                rightM = cur->left;
                if(rightM){
                    while(rightM->right && rightM->right != cur){
                        rightM = rightM->right;
                    }
                    if(!rightM->right){
                        rightM->right = cur;
                        cur           = cur->left;
                        continue;
                    }else{
                        cout<<cur->val<<" ";
                        rightM->right = NULL;
                    }
                }else{
                    cout<<cur->val<<" ";
                }
                cur = cur->right;
            }
        }
        void morris_PostOrder(tree *head){
            tree *cur    = head;
            tree *rightM = NULL;
            while(cur){
                rightM   = cur->left;
                if(rightM){
                    while(rightM->right && rightM->right != cur){
                        rightM = rightM->right;
                    }
                    if(!rightM->right){
                        rightM->right = cur;
                        cur = cur->left;
                        continue;
                    }else{
                        rightM->right = NULL;
                        PostNext(cur->left);
                    }
                }
                cur = cur->right;
            }
            PostNext(head);
        }
        void PostNext(tree *head){
            tree *tmp_head = recerse(head);
            tree *old_head = tmp_head;
            while(tmp_head){
                cout<<tmp_head->val<<" ";
                tmp_head = tmp_head->right;
            }
            recerse(old_head);
        }
        tree *recerse(tree *head){
            tree *pre  = NULL;
            tree *next = NULL;
            while(head){
                next        = head->right;
                head->right = pre;
                pre         = head;
                head        = next;
            }
            return pre;
        }
};
int main(int argc,const char *argv[]){
    tree *head         = new tree(1);
    head->left         = new tree(2);
    head->left->right  = new tree(6);
    head->left->left   = new tree(7);
    head->right        = new tree(3);
    head->right->left  = new tree(4);
    head->right->right = new tree(5);
    Solution te;
    te.morris_PreOrder(head);
    cout<<"\n---------------------"<<endl;
    te.morris_InOrder(head);      
    cout<<"\n---------------------"<<endl;
    te.morris_PostOrder(head);
    return 0;
}
