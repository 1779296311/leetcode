/*********************************************
*     ------------------------
*     ------------------------
*     file name: trieTree.cpp
*     author   : @ JY
*     date     : 2020--03--11
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class TrieTree{
    public:
        int p;
        int e;
        TrieTree *next[26]={NULL,};
        TrieTree(int p, int e) : p(p),e(e) {};
};
class Solution{
    public:
        TrieTree *head;
        Solution(){
            head = new TrieTree(0,0);
        }
       ~Solution(){
            if(head != NULL){
                destructorTree(head);
            }
       }
        void insertWord(char *word, int num){
            char *wd       = word;
            TrieTree *tree = head;
            ++head->p;
            while(*wd && --num>=0){
                if(!tree->next[*wd-'a']){
                    tree->next[*wd-'a'] = new TrieTree(0,0);
                }
                tree = tree->next[*wd-'a'];
                ++tree->p;
                ++wd;
            }
            ++tree->e;
        }
        void insertWord(char *word){
            char *wd       = word;
            TrieTree *tree = head;
            ++head->p;
            while(*wd){
                if(!tree->next[*wd-'a']){
                    tree->next[*wd-'a'] = new TrieTree(0,0);
                }
                tree = tree->next[*wd-'a'];
                ++tree->p;
                ++wd;
            }
            ++tree->e;
        }
        int deleteWord(char *word){
            char *wd       = word;
            TrieTree *tree = head;
            if(!wd || !searchEnd(wd)){
                return 0;
            }
            while(*wd){
                if(!tree->next[*wd-'a']){
                    return 0;
                }
                if(!(--tree->next[*wd-'a']->p)){
                    destructorTree(tree->next[*wd-'a']);
                    tree->next[*wd-'a'] = NULL;
                    return 1;
                }
                tree = tree->next[*wd-'a'];
                ++wd;
            }
            --tree->e;
            return 1;
        }
        void destructorTree(TrieTree *node){
            if(!node){
                return;
            }
            for(int i=0; i<26; ++i){
               destructorTree(node->next[i]);
               node->next[i] = NULL;
            }
            delete node;
        }
        int searchEnd(char *word){
            char *wd       = word;
            TrieTree *tree = head;
            while(*wd){
                if(!tree->next[*wd-'a']){
                    return 0;
                }
                tree = tree->next[*wd-'a'];
                ++wd;
            }
            return tree->e;
        }
        int searchPass(char *word){
            char *wd       = word;
            TrieTree *tree = head;
            while(*wd){
                if(!tree->next[*wd-'a']){
                    return 0;
                }
                tree = tree->next[*wd-'a'];
                ++wd;
            }
            return tree->p;
        }
        void debug(){
            for(int i=0; i<26; ++i){
                if(head->next[i]){
                    cout<<(char)'a'+i<<endl;
                }
            }
        }
};

char *txt = "looks the ladder of human progress. This is a quote from gorky. I think that's true. A good book, can give the human human more, more abundant knowledge, can multifaceted for the human mind to create more perfect and thorough image of beauty. Make a lot of people gradually climb the peak of literature, become the leader of ten thousand people.Reading, can make a wounded young mind to be comforted; Can make is in the trough of life in the baptism of knowledge and obtain the encouragement and confidence; Can make a mistake of the ignorant human stray, lead to the rainbow of success; Can make the vagrants or overseas Chinese get a long time to look forward to and find the warmth; To make the just into the palace of literature children received the baton of knowledge, to gain strength, for the country's future step down a solid foundation...;  Many people say that books the best way for people to learn. Yes, there things you didn't learn in school, wonderful worlds you never knew, and a spirit of fearlessness that everyone celebrates. In my eyes, a book is a plaster. It will absorb my troubles and intensify all the troubles that shouldn't exist. Reading is a habit, a habit that everyone should have. Reading has a kind of infinite power, make me keep running in the hall of literature, this power gave me infinite power, bit by bit erosion, control me to run, or the speed of light seems to fly past more image, the next fan, in this way, by my great power to open. It was reading that made my childhood more interesting.Reading makes a man wise, and reading makes him wise.This is training to read the explanation. Each book has its own characteristics and advantages. Before we read a book, we should also consider the value and significance of the book, because should read and should not read will cause two different results. A good book can make people deep feelings, increase interest, enrich knowledge, in the sky of knowledge, people into the rainbow top; And a bad book. Can only make the existence of life in a bad environment, hovering on the edge of the rubble of the trembling mountain, a little will forever sleep in the valley.";
int main(int argc,const char *argv[]){
    Solution te;
    char *words = txt;
    while(*words){
        while(*words && !((*words>='a'&&*words<='z')||(*words>='A'&&*words<='Z')) ){
            ++words;
        }
        char *tmp = words;
        while(*words && (*words>='a'&&*words<='z')||(*words>='A'&&*words<='Z')){
            ++words;
        }
        if(!*words){
            break;
        }
        te.insertWord(tmp,words-tmp);
    }
    cout<<te.searchEnd("more")<<endl;
    cout<<te.searchPass("next")<<endl;
    return 0;
}
