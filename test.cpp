/********************************************* 
*     ------------------------                 
*     ------------------------                 
*     file name: test.cpp
*     author   : @JY    
*     data     : 2019--09--03
**********************************************/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//bool tmp(int a, int b){
    //return a > b;
//}
//class Solution {
//public:
    //TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        //int size = preorder.size();
        //if(!size){
            //return NULL;
        //}
        //TreeNode *__st[size+1];
        //TreeNode *__root = new TreeNode(preorder[0]->val);
        //__st[0]          = __root;
        //int end          = 0;
        //int j            = 0;
        //for(int i=1; i<size; i++){
            //TreeNode *__tmp = new preorder[i];
            //TreeNode *__R   = NULL;
            //while(end && __st[end]->val == inorder[j]){
                //__R         = __st[end--];
                //j++;
            //}
            //if(__R){
                //__R->right = __tmp;
            //}else{
                //__st[end]->left = __tmp;
            //}
            //__st[++end] = __tmp;
        //}
        //return __root;
    //}
//};
int aaa(int p){
    return p;
}
int test(int b){
  if(b == 1) {
    ;
  }else if(b == 8){
    ;
  }else if(b == 0){
    ;
  }
  return b;
}
int main(int argc, const char *argv[]) {
  int size = 9;
  vector<int> memo(size);
  for (int i = 0; i <= 9; ++i) {
    cout << memo[i] << endl;
  }
  if (1 != 2) {
  }
  return 0;
}
