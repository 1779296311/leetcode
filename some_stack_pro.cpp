/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_stack_pro.cpp
*     author   : @ JY
*     date     : 2020--05--03
**********************************************/
#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
#include <climits>
#include <vector>
#include <stack>
#include <stdlib.h>
using  namespace  std;

#define peek(st)({ \
        auto v = st.top(); \
        st.pop(); \
        v;      })

class Solution{
    public:
        int remove_Stack_Last(stack<int>& st){
            int tmp = st.top();
            st.pop();
            if(st.empty()){
                return tmp;
            }else{
                int res = remove_Stack_Last(st);
                st.push(tmp);
                return res;
            }
        }
        void reverse_Stack(stack<int>& st){
            if(st.empty()){
                return;
            }
            int tmp = remove_Stack_Last(st);
            reverse_Stack(st);
            st.push(tmp);
        }
        void debug(){
            stack<int> st;
            st.push(0);
            st.push(1);
            st.push(2);
            st.push(3);
            st.push(4);
            st.push(5);
            //cout<<remove_Stack_Last(st)<<endl;
            reverse_Stack(st);
            while(!st.empty()){
                cout<<st.top()<<" ";
                st.pop();
            }
            cout<<endl;
        }

//-------max---tree----------
        struct Node{
            int val;
            Node* left;
            Node* right;
            Node(int n):val(n),left(nullptr),right(nullptr){}
        };

        Node *build_max_tree(::std::vector<int>& nums){
            int size = nums.size();
            ::std::vector<Node*> nodes;
            for(int i=0; i<size; ++i){
                nodes.push_back(new Node(nums[i]));
            }
            ::std::vector<Node*> maxL(size);
            ::std::vector<Node*> maxR(size);
            ::std::list<int> lt;
            for(int i=0; i<size; ++i){
                while(lt.size() && nums[i]>nums[lt.back()]){
                    int index = lt.back();
                    lt.pop_back();
                    maxL[index] = lt.size()?nodes[lt.back()]:nullptr;
                    maxR[index] = nodes[i];
                }
                lt.push_back(i);
            }
            while(lt.size()){
                int index = lt.back();
                lt.pop_back();
                maxL[index] = lt.size()?nodes[lt.back()]:nullptr;
                maxR[index] = nullptr;
            }

            //for(int i=0; i<maxL.size(); ++i){
                //if(maxL[i])
                    //::std::cout<<maxL[i]->val<<"       ";
                //else
                    //::std::cout<<" No       ";
            //}
            //::std::cout<<::std::endl;;
            //for(int i=0; i<maxL.size(); ++i){
                //if(maxR[i])
                    //::std::cout<<maxR[i]->val<<"       ";
                //else
                    //::std::cout<<" No       ";
            //}

            Node *head;
            for(int i=0; i<size; ++i){
                if(maxL[i]==nullptr && maxR[i]==nullptr){
                    head = nodes[i];
                }else if(maxL[i]==nullptr){
                    if(maxR[i]->left==nullptr){
                        maxR[i]->left  = nodes[i];
                    }else{
                        maxR[i]->right = nodes[i];
                    }
                }else if(maxR[i]==nullptr){
                    if(maxL[i]->left==nullptr){
                        maxL[i]->left = nodes[i];
                    }else{
                        maxL[i]->right = nodes[i];
                    }
                }else{
                    Node *p = maxL[i]->val>maxR[i]->val?maxR[i]:maxL[i];
                    if(p->left==nullptr){
                        p->left = nodes[i];
                    }else{
                        p->right = nodes[i];
                    }
                }
            }
            return head;
        }
        void print_width(Node* head){
            ::std::queue<Node*> qu;
            qu.push(head);
            while(qu.size()){
                int size = qu.size();
                for(int i=0; i<size; ++i){
                    Node *tmp = qu.front();
                    qu.pop();
                    ::std::cout<<tmp->val<<"    ";
                    if(tmp->left)qu.push(tmp->left);
                    if(tmp->right)qu.push(tmp->right);
                }
                ::std::cout<<::std::endl;
            }
        }
//-------min-------------
        void getMinNum(::std::vector<int>& nums){
            int size = nums.size();
            ::std::vector<int> minl(size);
            ::std::vector<int> minr(size);

            ::std::stack<int> st;
            int res = -1;
            for(int i=0; i<size; ++i){
                while(st.size() && nums[st.top()] >= nums[i]){
                    int index   = peek(st);
                    minl[index] = st.size()?st.top():-1;
                    minr[index] = i;
                    res = ::std::max(res, (minr[index]-minl[index]-1)*nums[index]);
                }
                st.push(i);
            }
            while(st.size()){
                int index   = peek(st);
                minl[index] = st.size()?st.top():-1;
                minr[index] = size;
                res = ::std::max(res, (minr[index]-minl[index]-1)*nums[index]);
            }

            //-----------------debug;
            for(int i=0; i<size; ++i){
                ::std::cout<<nums[i]<<"        ";
            }
            ::std::cout<<::std::endl;
            for(int i=0; i<size; ++i){
                ::std::cout<<minl[i]<<"        ";
            }
            ::std::cout<<::std::endl;
            for(int i=0; i<size; ++i){
                ::std::cout<<minr[i]<<"         ";
            }
            //int res = nums[0];
            //for(int i=0; i<size; ++i){
                //res = ::std::max(res, (minr[i]-minl[i]-1)*nums[i]);
            //}
            ::std::cout<<::std::endl;
            ::std::cout<<res<<::std::endl;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    //::std::vector<int> nums = {3,5,1,345,6578,21,124};
    ::std::vector<int> nums = {3,3,2,3,4,4,4};
    te.getMinNum(nums);
    //te.print_width(te.build_max_tree(nums));
    return 0;
}
