/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ26.cpp
*     author   : @ JY
*     date     : 2020--05--09
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    bool isSubStructure(TreeNode* A, TreeNode* B){
        if(!B || !A){
            return false;
        }
        return
            (A->val==B->val?isSub(A,B):0)?1:
            (isSubStructure(A->left,B)||
            isSubStructure(A->right,B));
    }
    bool isSub(TreeNode* a, TreeNode* b){
        if(!b){
            return true;
        }
        if(!a){
            return false;
        }
        return
            a->val==b->val         &&
            isSub(a->left, b->left)&&
            isSub(a->right,b->right);
    }
    ////-----------------------------------Fuck-----Fuck-----Fuck-----Fuck-----Fuck-----Fuck----------Fuck
    bool isSubStructureError(TreeNode* A, TreeNode* B) {
        if(!B){
            return false;
        }
        string a = serialize(A);
        string b = serialize(B);
        cout<<a<<endl;
        cout<<b<<endl;
        if(b.length() > a.length()){
            return false;
        }
        return kmp(b,a);
    }
    bool kmp(string& a, string& b){
        vector<int> next(a.length(),0);
        getNextArr(next,a);
        int i = 0;
        int j = 0;
        while(j<b.length() && i<a.length()){
            if(a[i] == b[j]){
                ++i;
                ++j;
            }else if(!i){
                ++j;
            }else{
                i = next[i];
            }
        }
        return i==a.length();
    }
    void getNextArr(vector<int>& next, string& a){
        int j   = 1;
        int jmp = 0;
        while(j<a.length()-1){
            if(a[j] == a[jmp]){
                next[++j] = ++jmp;
            }else if(!jmp){
                ++j;
            }else{
                jmp = next[jmp];
            }
        }
    }
    string serialize(TreeNode* head){
        if(!head){
            return "";
            //return "#_";
        }
        string res = to_string(head->val)+"_";
        res = res + serialize(head->left);
        res = res + serialize(head->right);
        return res;
    }
};
int main(int argc,const char *argv[]){
    Solution te;;
    TreeNode* A    = new TreeNode(10);
    A->right       = new TreeNode(6);
    A->right->left = new TreeNode(11);
    A->left        = new TreeNode(12);
    A->left->left  = new TreeNode(8);
    A->left->right = new TreeNode(3);

    TreeNode* B   = new TreeNode(10);
    B->left       = new TreeNode(12);
    B->right      = new TreeNode(6);
    B->left->left = new TreeNode(8);
    cout<<te.isSubStructure(A,B)<<endl;
    return 0;
}
