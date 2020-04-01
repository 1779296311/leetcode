/*********************************************
*     ------------------------
*     ------------------------
*     file name: LRU.cpp
*     author   : @ JY
*     date     : 2020--03--30
**********************************************/
//为LRU Cache设计一个数据结构，它支持两个操作：
//get(key)：如果key在cache中，则返回对应的value值，否则返回-1
//set(key,value):如果key不在cache中，则将该(key,value)插入cache中（注意，如果cache已满，则必须把最近最久未使用的元素从cache中删除）；如果key在cache中，则重置value的值。
//
#include <iostream>
#include <unordered_map>
#include <stdlib.h>
using  namespace  std;
template<class K>
struct Node{
    K k;
    int v;
    Node *pre;
    Node *next;
    Node(K kk,int vv):k(kk),v(vv),pre(NULL),next(NULL){}
    ~Node(){}
};

template<class K>
class LRU_Cache{
    public:
        LRU_Cache(int s):size(s){
            mlist       = new Node<K>(0,0);
            mlist->pre  = mlist;
            mlist->next = mlist;
        }
    private:
        int  size;
        Node<K> *mlist;
        unordered_map<K,Node<K>*> htb;
    public:
        int get(K k){
            auto t = htb.find(k);
            if(t == htb.end()){
                return -1;
            }
            Node<K> *tmp = t->second;
            if(tmp != mlist->next){
                //remove
                tmp->pre->next = tmp->next;
                tmp->next->pre = tmp->pre;
                //insert
                tmp->next        = mlist->next;
                mlist->next->pre = tmp;
                tmp->pre         = mlist;
                mlist->next      = tmp;
            }
            return tmp->v;
        }
        Node<K>*  set(K k,int value){
            if(htb.size() == size && mlist->pre != mlist){
                htb.erase(mlist->pre->k);
                Node<K>* tmp   = mlist->pre;
                tmp->pre->next = tmp->next;
                tmp->next->pre = tmp->pre;
                delete(tmp);
            }
            if(get(k) != -1){
                htb[k]->v = value;
            }else{
                Node<K>* tmp     = new Node<K>(k,value);
                htb[k]           = tmp;

                tmp->next        = mlist->next;
                mlist->next->pre = tmp;
                tmp->pre         = mlist;
                mlist->next      = tmp;
            }
            return htb[k];
        }
};
int main(int argc,const char *argv[]){
    LRU_Cache<char> lru(5);
    lru.set('a',1);
    lru.set('b',2);
    lru.set('c',3);
    lru.set('d',4);
    lru.set('e',5);
    cout<<lru.get('a')<<endl;
    cout<<lru.get('b')<<endl;
    cout<<lru.get('c')<<endl;
    cout<<lru.get('d')<<endl;
    cout<<lru.get('e')<<endl;
    lru.set('f',6);
    lru.set('g',7);
    lru.set('h',8);
    lru.set('i',9);
    lru.set('k',10);
    cout<<"--------"<<endl;
    cout<<lru.get('a')<<endl;
    cout<<lru.get('b')<<endl;
    cout<<lru.get('c')<<endl;
    cout<<lru.get('d')<<endl;
    cout<<lru.get('e')<<endl;
    cout<<"--------"<<endl;
    cout<<lru.get('f')<<endl;
    cout<<lru.get('g')<<endl;
    cout<<lru.get('h')<<endl;
    cout<<lru.get('i')<<endl;
    cout<<lru.get('k')<<endl;
    return 0;       
}
