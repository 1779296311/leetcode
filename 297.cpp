/*********************************************
*     ------------------------
*     ------------------------
*     file name: 297.cpp
*     author   : @ JY
*     date     : 2020--05--01
**********************************************/
#include <iostream>
#include <vector>
#include <stack>
#include <stdlib.h>
using  namespace  std;
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution{
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res    = "";
        TreeNode* tmp = NULL;
        stack<TreeNode*> st;
        st.push(root);
        while(!st.empty()){
            tmp = st.top();
            st.pop();
            res = res + (!tmp?"#_":to_string(tmp->val)+"_");
            if(tmp){
                st.push(tmp->right);
                st.push(tmp->left);
            }
        }
        return res;
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<string> st = getST(data);
        return deserialize(getST(data));
    }
    vector<string> getST(string& s){
        vector<string> st;
        int i   = 0;
        int tmp = 0;
        while(i<s.length()){
            tmp = i;
            while(tmp <s.length() && s[tmp] !='_'){
                ++tmp;
            }
            st.push_back(s.substr(i,tmp-i));
            i = tmp + 1;
        }
        return st;
    }
    TreeNode* deserialize(vector<string> nodes){
        if(nodes.empty()){
            return NULL;
        }
        int size = nodes.size();
        stack<TreeNode*> st;
        TreeNode *tmp  = NULL;
        TreeNode *head = new TreeNode(stoi(nodes[0]));
        st.push(head);
        int i = 1;
            //"1_2_3_4_#_#_#_#_2_#_3_#_4_#_#_";
        while(i<size){
            if(nodes[i] != "#"){
                if(st.top()->left){
                    tmp = new TreeNode(stoi(nodes[i]));
                    st.top()->right = tmp;
                    st.pop();
                    st.push(tmp);
                }else{
                    st.top()->left = new TreeNode(stoi(nodes[i]));
                    st.push(st.top()->left);
                }
            }else if(i+1<size && nodes[i] =="#" && nodes[i+1] != "#"){
                tmp             = new TreeNode(stoi(nodes[i+1]));
                st.top()->right = tmp;
                st.pop();
                st.push(tmp);
                ++i;
            }else{
                ++i;
                while(i<size && nodes[i] == "#"){
                    ++i;
                    st.pop();
                }
                --i;
            }
            ++i;
        }
        return head;
    }
    TreeNode* deserialize1(vector<string> st, int& i){
        if(i == st.size() || st[i] == "#"){
            ++i;
            return NULL;
        }
        TreeNode * head = new TreeNode(stoi(st[i++]));
        head->left  = deserialize1(st,i);
        head->right = deserialize1(st,i);
        return head;
    }
    void debug(vector<string>& st ){
        for(int i=0; i<st.size(); ++i){
            cout<<st[i]<<"  ";
        }
        cout<<endl;
    }
    void debug1(TreeNode *head){
        if(!head){
            return;
        }
        cout<<head->val<<endl;
        debug1(head->left);
        debug1(head->right);
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    vector<string> st;
    //string s = "-2_-1_-8_#_#_4_#_#_6_#_7_#_#";
    string s = "1_2_3_4_#_#_#_#_2_#_3_#_4_#_#_";
    TreeNode *head = te.deserialize(s);
    te.debug1(head);
    return 0;
}
