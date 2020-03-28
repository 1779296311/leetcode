/********************************************* 
*     ------------------------                 
*     ------------------------                 
*     file name: addTwoNumbers.cpp
*     author   : @JY    
*     data     : 2019--09--04
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;

struct ListNode{
    int number;
    ListNode *next;
    ListNode(int x): number(x), next(NULL) {};
};


class Solution{
    public:
        ListNode *addTwoBumbers(ListNode *L1, ListNode *L2){
            ListNode *p1, *p2, *resault;
            p1 = L1, p2 = L2;
            int flag = 0;
            int num  = 0;
            vector<int> num1, num2;
            while(p1 != NULL){
                num1.push_back(p1->number);
                p1    = p1->next;
            }
            while(p2 != NULL){
                num2.push_back(p2->number);
                p2    = p2->next;
            }

            while(!num1.empty() || !num2.empty()){
                int     number1 = num1.empty() ? 0 : num1.back();
                int     number2 = num2.empty() ? 0 : num2.back();
                if(flag == 1){
                    num     = number1 + number2 + 1;
                }else{
                    num     = number1 + number2;
                }
                flag        = 0;
                if(num >= 10){
                    num     = num - 10;
                    flag    = 1; 
                }


                if(!num1.empty()){
                    num1.pop_back();
                }
                if(!num2.empty()){
                    num2.pop_back();
                }

                ListNode *tmp     = new ListNode(num);
                resault->next     = tmp;
            }
            resault         = resault->next;

            return resault;
        }
};

int main(int argc,const char *argv[]){
    struct ListNode l1(1);

    return 0;
} 
