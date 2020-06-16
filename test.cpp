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
#include <cstring>
#include <algorithm>
using namespace std;
int main(int argc, const char *argv[]) {
    //struct node{
        //int a;

    //}
    int node1 = 9;
    double k  = 20.8;
    unsigned str[sizeof(node1)+sizeof(k)];
    memset(str,node1,sizeof(node1));
    memset(str,k,sizeof(k));
    int node2 = (int)*(str);
    double k1 = (double)*(str+sizeof(node1));
    cout<<node1<<endl;
    cout<<k1<<endl;
}
