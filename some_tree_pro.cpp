/*********************************************
*     ------------------------
*     ------------------------
*     file name: commonAncestor.cpp
*     author   : @ JY
*     date     : 2020--03--10
**********************************************/
#include <iostream>
#include <queue>
#include <stack>
#include <climits>
#include <stdlib.h>
using  namespace  std;
struct ListNode {
     int val;
     ListNode *parent;
     ListNode *left;
     ListNode *right;
     ListNode(int x) : val(x) {}
 };
struct Info{
    bool isBst;
    int  mi;
    int  ma;
    Info(bool a, int b, int c):isBst(a),mi(b),ma(c){}
};
struct Info2{
    int high;
    int maxDistance;
    Info2(int h, int d):high(h),maxDistance(d){}
};
struct Info1{
    int minV;
    int maxV;
    int maxNum;
    ListNode* maxSearchHead;
    Info1(int a, int b,int n,ListNode* m):
        minV(a),maxV(b),maxNum(n),maxSearchHead(m){}
};
class Solution{
    public:
        ListNode *commonAncestor_1(ListNode *root, ListNode *a, ListNode *b){
            if(!root || root==a || root==b){
                return root;
            }
            ListNode *left  = commonAncestor_1(root->left,a,b);
            ListNode *right = commonAncestor_1(root->right,a,b);
            if(left && right){
                return root;
            }
            return left?left:right;
        }
        //is search;
        ListNode *commonAncestor_2(ListNode *root, ListNode *a, ListNode *b){
            int min;
            int max;
            max = (a->val>b->val)?({min=b->val,a->val;}):({min=a->val,b->val;});
            while(root){
                if(max>root->val && min<root->val){
                    return root;
                }else if(max>root->val && min>root->val){
                    root = root->right;
                }else{
                    root = root->left;
                }
            }
            return root;
        }
        ListNode *commonAncestor_3(ListNode *a, ListNode *b){
            ListNode *a1 = a;
            ListNode *b1 = b;
            while(a1 != b1){
                a1 = a1?a1->parent:b;
                b1 = b1?b1->parent:a;
            }
            return a1;
        }
        bool isSearch_1(ListNode *root,int max, int min){
            if(!root){
                return true;
            }
            if(root->val>max || root->val<min){
                return false;
            }
            if(!isSearch_1(root->left,root->val,min) || !isSearch_1(root->right,max,root->val)){
                return false;
            }
            return true;
        }
        Info *isSearch_2_(ListNode *root){
            if(!root){
                return NULL;
            }
            Info *left  = isSearch_2_(root->left);
            Info *right = isSearch_2_(root->right);
            int mi      = root->val;
            int ma      = root->val;
            if(left){
                mi = min(mi,left->mi);
                ma = max(ma,left->ma);
            }
            if(right){
                mi = min(mi,right->mi);
                ma = max(ma,right->ma);
            }
            bool isBst = false;
            bool a = left?(left->isBst && left->ma < root->val):true;
            bool b = right?(right->isBst && right->mi > root->val):true;
            if(a && b){
                isBst = true;
            }
            delete(left);
            delete(right);
            return new Info(isBst,mi,ma);
        }
        bool isSearch_3(ListNode *head){
            static int a;
            if(!head){
                return true;
            }
            if(!isSearch_3(head->left)){
                return false;
            }
            if(a>=head->val){
                return false;
            }
            a = head->val;
            if(!isSearch_3(head->right)){
                return false;
            }
            return true;
        }
        bool isSearch_2(ListNode *head){
            Info *info = isSearch_2_(head);
            bool __res = info->isBst;
            delete(info);
            return __res;
        }
        bool isComplete(ListNode *head){
            queue<ListNode*>q;
            q.push(head);
            int flag = 0;
            while(!q.empty()){
                ListNode *tmp = q.front();
                q.pop();
                ListNode *l   = tmp->left;
                ListNode *r   = tmp->right;
                if((flag && l && r)
                        ||
                  (!l&&r)){
                    return false;
                }
                if(!l){
                    q.push(l);
                }
                if(!r){
                    q.push(r);
                }else{
                    flag = 1;
                }
            }
            return true;
        }
        void printWidth(ListNode *head){
            queue<ListNode*>q;
            q.push(head);
            while(!q.empty()){
                int size = q.size();
                for(int i=0; i<size; ++i){
                    ListNode *tmp = q.front();
                    q.pop();
                    cout<<tmp->val<<endl;
                    if(tmp->left){
                        q.push(tmp->left);
                    }
                    if(tmp->right){
                        q.push(tmp->right);
                    }
                }
                cout<<"-------"<<endl;
            }
        }
        void printPostOrder(ListNode *head){
            if(!head){
                return;
            }
            ListNode *t = NULL;
            ListNode *l = head;
            stack<ListNode*> st;
            st.push(head);
            while(!st.empty()){
                t = st.top();
                //if((!t->left&&!t->right)  || t->right==l){
                    //cout<<t->val<<endl;
                    //st.pop();
                    //l = t;
                //}else if(t->left && t->left != l){
                    //st.push(t->left);
                //}else if(t->right){
                    //st.push(t->right);
                //}
                if(t->left && t->left!=l && t->right!=l){
                    st.push(t->left);
                }else if(t->right && t->right!=l){
                    st.push(t->right);
                }else{
                    cout<<t->val<<endl;
                    st.pop();
                    l = t;
                }
            }
        }
        int getTreeNodeNum(ListNode *head,int level, int high){
            if(level==high){
                return 1;
            }
            if(maxHigh(head->right,level+1)==high){
                return ((1<<(high-level))+(getTreeNodeNum(head->right,level+1,high)));
            }else{
                return ((1<<(high-level-1))+(getTreeNodeNum(head->left,level+1,high)));
            }
        }
        int nodeNum(ListNode *node){
            return node?getTreeNodeNum(node,1,maxHigh(node,1)):0;
        }
        int maxHigh(ListNode *node, int level){
            while(node){
                node = node->left;
                ++level;
            }
            return --level;
        }
    Info1 max_Child_isSearchTree(ListNode* head){
        if(!head){
            return Info1(INT_MAX,INT_MIN,0,NULL);
        }
        Info1 left  = max_Child_isSearchTree(head->left);
        Info1 right = max_Child_isSearchTree(head->right);
        int maxN    = 0;
        if(head->left  == left.maxSearchHead &&
           head->right == right.maxSearchHead &&
           left.maxV<head->val && right.minV>head->val){
            maxN = left.maxNum + right.maxNum + 1;
        }
        ListNode *tmp = NULL;
        maxN          = max(max(left.maxNum,right.maxNum),maxN);
        if(maxN == (left.maxNum + right.maxNum + 1)){
            tmp = head;
        }else{
            tmp = left.maxNum>right.maxNum?left.maxSearchHead:right.maxSearchHead;
        }
        int b = min(min(left.minV,right.minV),head->val);
        int a = max(max(left.maxV,right.maxV),head->val);
        return Info1(b,a,maxN,tmp);
    }
    ListNode* get_max_Child_isSearchTree(ListNode* head){
        cout<<max_Child_isSearchTree(head).maxNum<<endl;
        return max_Child_isSearchTree(head).maxSearchHead;
    }
//最长距离
    Info2 max_distance(ListNode *head){
        if(!head){
            return Info2(0,0);
        }
        Info2 left  = max_distance(head->left);
        Info2 right = max_distance(head->right);
        int h       = max(left.high,right.high)+1;
        int m       = max(max(left.maxDistance,right.maxDistance),(left.high+right.high+1));

        return Info2(h,m);
    }
    int get_max_distance(ListNode *head){
        return max_distance(head).maxDistance;
    }
};

int main(int argc,const char *argv[]){
    Solution te;
    ListNode *head    = new ListNode(5);
    head->left        = new ListNode(3);
    head->left->left  = new ListNode(1);
    head->left->right = new ListNode(4);

    head->right        = new ListNode(2);
    head->right->right = new ListNode(9);
    head->right->left  = new ListNode(6);
    cout<<te.get_max_distance(head)<<endl;
    //cout<<te.get_max_Child_isSearchTree(head)->val<<endl;
    //cout<<te.nodeNum(head)<<endl;
    //te.printPostOrder(head);
    //te.printWidth(head);
    //if(te.isSearch_1(head,INT_MAX,INT_MIN)){
        //cout<<"isSeearch1"<<endl;
    //}
    //if(te.isSearch_2(head)){
        //cout<<"isSeearch2"<<endl;
    //}
    //if(te.isSearch_3(head)){
        //cout<<"isSeearch3"<<endl;
    //}
    return 0;
}

