/*********************************************
*     ------------------------
*     ------------------------
*     file name: build_tree_withHeap.cpp
*     author   : @ JY
*     date     : 2020--03--27
**********************************************/
#include <iostream>
#include <stdlib.h>
struct tree{
    int val;
    tree *left;
    tree *right;
    tree(int v):val(v),left(NULL),right(NULL){}
};
//建二叉树左右子树 < parent
using  namespace  std;
class Solution{
    public:
        void heapfy(int *nums, int size, int index){
            int left = (index<<1)+1;
            int now  = left;
            while(left<size){
                now = (left+1<size && nums[left+1]>nums[left])?left+1:left;
                now = nums[now]>nums[index]?now:index;
                if(now == index){
                    break;
                }
                swap(nums,now,index);
                index = now;
                left  = (index<<1)+1;
            }
        }
        tree *build_tree_withHeap(int *nums,int size){
            tree *head = NULL;
            for(int i=size/2-1; i>=0; --i){
                heapfy(nums,size,i);
            }
            head = build_tree(nums,size);
            debug(nums,size);
            return head;
        }
        tree* build_tree(int *nums, int size){
            tree *t[size] = {0};
            for(int i=0; i<size; ++i){
                t[i] = new tree(nums[i]);
            }
            int index = 0;
            while(index*2+1 < size){
                t[index]->left = t[index*2+1];
                if(index*2+2<size){
                    t[index]->right = t[index*2+2];
                }
                ++index;
            }
            return t[0];
        }
        void debug(int *nums, int size){
            for(int i=0; i<size; ++i){
                cout<<nums[i]<<" ";
            }
            cout<<endl;
        }
        void debug(tree *t){
            if(!t){
                return;
            }
            debug(t->left);
            cout<<t->val<<"  ";
            debug(t->right);
        }
        void swap(int *nums, int a, int b){
            if(nums[a] == nums[b]){
                return;
            }
            nums[a] = nums[a] ^ nums[b];
            nums[b] = nums[a] ^ nums[b];
            nums[a] = nums[a] ^ nums[b];
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    int nums[] = {2,4,1,6,7};
    tree* head = te.build_tree_withHeap(nums,*(&nums+1)-nums);
    te.debug(head);
    return 0;
}
