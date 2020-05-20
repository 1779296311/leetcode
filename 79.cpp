/*********************************************
*     ------------------------
*     ------------------------
*     file name: 79.cpp
*     author   : @ JY
*     date     : 2020--05--02
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if(word.length() > board.size()*board[0].size()){
            return false;
        }
        vector<vector<int>> mp(board.size(),vector<int>(board[0].size(),0));
        for(int i=0; i<board.size(); ++i){
            for(int j=0; j<board[0].size(); ++j){
                if(board[i][j] == word[0]){
                    if(exist(board,word,i,j,0,mp)){
                        return true;
                    }
                }
            }
        }
        return false;
    }
    bool exist(vector<vector<char>>& board, string s, int i, int j, int l,vector<vector<int>>& mp){
        if(l == s.length()){
            return true;
        }
        if(i<0 || j<0 || i>=board.size() || j>=board[0].size()){
            return false;
        }
        if(mp[i][j]>0 || board[i][j] != s[l]){
            return false;
        }
        ++mp[i][j];
        return (
            exist(board,s,i+1,j,l+1,mp)||
            exist(board,s,i,j+1,l+1,mp)||
            exist(board,s,i-1,j,l+1,mp)||
            exist(board,s,i,j-1,l+1,mp)
            )
            ?
            true:({--mp[i][j],false;});
    }
    bool exist1(vector<vector<char>>& board, string s, int i, int j, int l,vector<vector<int>>& mp){
        if(l == s.length()){
            return true;
        }
        if(i<0 || j<0 || i>=board.size() || j>=board[0].size()){
            return false;
        }
        ++mp[i][j];
        if(mp[i][j]>1 || board[i][j] != s[l]){
            return false;
        }

        if(exist(board,s,i+1,j,l+1,mp)){
            return true;
        }else if(i+1<board.size()){
            --mp[i+1][j];
        }
        if(exist(board,s,i,j+1,l+1,mp)){
            return true;
        }else if(j+1<board[0].size()){
            --mp[i][j+1];
        }
        if(exist(board,s,i-1,j,l+1,mp)){
            return true;
        }else if(i>0){
            --mp[i-1][j];
        }
        if(exist(board,s,i,j-1,l+1,mp)){
            return true;
        }else if(j>0){
            --mp[i][j-1];
        }
        return false;
    }
};
int main(int argc,const char *argv[]){
    Solution te;;
    //vector<vector<char>> board =
    //{
        //{ 'A','B','C','E' },
        //{ 'S','F','C','S' },
        //{ 'A','D','E','E' }
    //};
    vector<vector<char>> board = {
     {'a','a','a'},
     {'a','b','b'},
     {'a','b','b'},
     {'b','b','b'},
     {'b','b','b'},
     {'a','a','a'},
     {'b','b','b'},
     {'a','b','b'},
     {'a','a','b'},
     {'a','b','a'}};
    string word = "aabaaaabbb";
    //string word = "aabbbbaabbbab";
    //string word = "bacd";
    //vector<vector<char>> board = {{'a','b'},{'c','d'}};
 //vector<vector<char>> board = { { 'a','a','a','a' },{ 'a','a','a','a' },{ 'a','a','a','a'}};
//"aaaaa aaaa aaaa"   };
    //string word = "ABCCED";
    //string word = "aaaaaaaaaaaaa";
    cout<<te.exist(board,word)<<endl;
    return 0;
}
