/*********************************************
*     ------------------------
*     ------------------------
*     file name: isChildTree.cpp
*     author   : @ JY
*     date     : 2020--03--25
**********************************************/
#include <iostream>
#include <vector>
#include <cstring>
#include <stack>
#include <stdlib.h>
#define to_String(s) #s
using  namespace  std;
struct tree{
    int val;
    tree* left;
    tree* right;
    tree(int n):val(n),left(NULL),right(NULL){}
};
class Solution{
    public:
        bool is_child_tree(tree *a, tree *b){
            string a1 = string_serialize(a);
            string b1 = string_serialize(b);
            return kmp(a1,b1);
        }
        vector<int> get_next_array(string b){
            int size = b.length();
            vector<int> next(size,0);
            --next[0];
            int M    = 2;
            int jump = 0;
            while(M<size){
                if(b[M-1] == b[jump]){
                    next[M++] = ++jump;
                }else if(!jump){
                    ++M;
                }else{
                    jump = 0;
                }
            }
            return next;
        }
        int kmp(string a, string b){
            int i = 0;
            int j = 0;
            vector<int> next = get_next_array(b);
            while(i<a.length() && j<b.length()){
                if(a[i] == b[j]){
                    ++i;
                    ++j;
                }else if(!j){
                    ++i;
                }else{
                    j = next[j];
                }
            }
            return j==b.length()?1:0;
        }
        string string_serialize(tree *t){
            string __res = "";
            stack<tree*> st;
            st.push(t);
            while(!st.empty()){
                tree* tmp = st.top();
                st.pop();
                __res = __res + to_string(tmp->val) + '_';
                if(!tmp->left){
                    __res  = __res + "#_";
                }
                if(!tmp->right){
                    __res  = __res + "#_";
                }
                if(tmp->right){
                    st.push(tmp->right);
                }
                if(tmp->left){
                    st.push(tmp->left);
                }
            }
            return __res;
        }
        tree* string_reveiver(string s,string p){
            vector<string> t;
            size_t pos = s.find(p);
            while(pos != s.npos){
                string tmp = s.substr(0,pos);
                t.push_back(tmp);
                s   = s.substr(pos+1,s.length());
                pos = s.find(p);
            }
            if(!t.size()){
                return NULL;
            }
            int index = 0;
            return build_tree_pre(t,index);
        }
        tree* build_tree_pre(vector<string>& t,int& index){
            if(t[index] == "#"){
                ++index;
                return NULL;
            }
            tree* head  = new tree(stoi(t[index++]));
            head->left  = build_tree_pre(t,index);
            head->right = build_tree_pre(t,index);
            return head;
        }
        void preorder(tree *t){
            if(!t){
                return;
            }
            cout<<t->val<<endl;
            preorder(t->left);
            preorder(t->right);
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    tree *head1        = new tree(3);
    head1->left        = new tree(4);
    head1->right       = new tree(1);
    //head1->left         = new tree(3);
    //head1->left->left   = new tree(4);
    //head1->left->right  = new tree(7);

    tree *head         = new tree(9);
    head->right        = new tree(2);
    head->right->right = new tree(6);
    head->left         = new tree(3);
    head->left->left   = new tree(4);
    head->left->right  = new tree(1);
    return 0;
    te.
}
