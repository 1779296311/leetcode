/*********************************************
*     ------------------------
*     ------------------------
*     file name: build_tree_byPostOrder.cpp
*     author   : @ JY
*     date     : 2020--04--20
**********************************************/
#include <iostream>
#include <stack>
#include <stdlib.h>
using  namespace  std;
struct Node{
    Node *left;
    Node *right;
    int value;
    Node(int v):value(v),left(NULL),right(NULL){}
};
class Solution{
    public:
        Node* build_tree_byPostOrder(int *nums, int size){
            return build_tree_byPostOrder(nums,0,size-1);
        }
        Node* build_tree_byPostOrder(int *nums, int s, int e){
            if(s > e){
                return NULL;
            }
            Node* head = new Node(nums[e]);
            if(s == e){
                return head;
            }
            //2 F
            int L = s;
            int M = s - 1;
            int R = e - 1;
            int mid;
            while(L <= R){
                mid = L+((R-L)>>1);
                if(nums[mid] > nums[R]){
                    R = --mid;
                }else if(nums[mid] < nums[R]){
                    M = mid;
                    L = ++mid;
                }else{
                    break;
                }
            }
            //int M = s - 1;
            //for(int i=e-1; i>=s; --i){
                //if(nums[e] > nums[i]){
                    //M = i;
                    //break;
                //}
            //}
            head->left  = build_tree_byPostOrder(nums,s,M);
            head->right = build_tree_byPostOrder(nums,M+1,e-1);
            return head;
        }
        void postOrder(Node* head){
            if(!head){
                return;
            }
            stack<Node*> st;
            st.push(head);
            Node* last = head;
            Node* tmp  = NULL;
            while(!st.empty()){
                tmp = st.top();
                if(tmp->left && tmp->left != last && tmp->right != last){
                    st.push(tmp->left);
                }else if(tmp->right && tmp->right != last){
                    st.push(tmp->right);
                }else{
                    cout<<tmp->value<<endl;
                    last = tmp;
                    st.pop();
                }
            }
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    int nums[] = {1,3,2,5,7,6,4};
    //int nums[] = {2,3,4,5,6};
    int size   = *(&nums+1) - nums;
    te.postOrder(te.build_tree_byPostOrder(nums,size));
    return 0;
}
