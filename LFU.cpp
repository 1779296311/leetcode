/*********************************************
*     ------------------------
*     ------------------------
*     file name: LFU.cpp
*     author   : @ JY
*     date     : 2020--03--31
**********************************************/
#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#define get_addrBy_mem(struct_name,struct_mem,mem_addr) ({ \
        const typeof(((struct_name*)0)->struct_mem)* ptr = (mem_addr); \
        (struct_name*)((char*)(ptr)-((size_t)&((struct_name*)0)->struct_mem));})

using  namespace  std;
template<class K, class V>
struct Node{
    K k;
    V v;
    Node *up;
    Node *down;
    int times;
    Node(K kk, V vv):k(kk),v(vv),up(this),down(this),times(1){}
};
template<class K, class V>
struct Mlist{
    Mlist* next;
    Mlist* pre;
    Node<K,V> * node;
    Mlist(Node<K,V>* n):next(NULL),pre(NULL),node(n){}
};
template<class K, class V>
class LFUCache{
    public:
        LFUCache(int s):maxSize(s){
            head       = new Mlist<K,V>(NULL);
            head->next = head;
            head->pre  = head;
        }
        ~LFUCache(){
            Mlist<K,V> *tmp = head->next;
            Mlist<K,V> *t   = NULL;
            while(tmp != head){
                t   = tmp->next;
                del_node(tmp->node);
                delete(tmp);
                tmp = t;
            }
            delete(head);
        }
    private:
        int maxSize;
        Mlist<K,V>* head;
        unordered_map<K,Node<K,V>*> hash_kn;
        unordered_map<Node<K,V>*,Mlist<K,V>*> hash_nl;
    public:
        V set(K k, V v){
            if(!maxSize){return -1;}
            if(hash_kn.find(k) == hash_kn.end()){
                set_new(k,v);
            }else{
                modify(k,v);
            }
            return hash_kn[k]->v;
        }
        V get(K k){
            typename unordered_map<K,Node<K,V>*>::iterator a = hash_kn.find(k);
            if(a == hash_kn.end()){
                //for(auto t : hash_kn){
                    //cout<<t.first<<endl;
                //}
                return V(-1);
            }else{
                move(k);
            }
            return hash_kn[k]->v;
        }
    private:
        void move(K k){
            modify(k,hash_kn[k]->v);
        }
        void insert_node(Node<K,V>* node, Mlist<K,V>* newList){
           Node<K,V> *oldHead = newList->node;

           node->up           = oldHead;
           oldHead->down->up  = node;
           node->down         = oldHead->down;
           oldHead->down      = node;

           newList->node      = node;
        }
        void insert_list(Mlist<K,V>* preList, Mlist<K,V>* newList){
            newList->next      = preList->next;
            preList->next->pre = newList;
            preList->next      = newList;
            newList->pre       = preList;
        }
        void remove_node(Node<K,V>* rm, Mlist<K,V>* hList){
            if(rm->down == rm){
                hList->node       = NULL;
                del_list(hList);
            }else{
                if(hList->node == rm){
                    hList->node = rm->up;
                }
                rm->down->up = rm->up;
                rm->up->down = rm->down;
            }
            rm->down = rm;
            rm->up   = rm;
        }
        void modify(K k,V v){
            Node<K,V>*  mv       = hash_kn[k];
            Mlist<K,V>* oldList  = hash_nl[mv];
            Mlist<K,V>* nextList = oldList->next;
            remove_node(mv,oldList);
            if((nextList == head)||(nextList->node->times != (mv->times+1))){
                Mlist<K,V>* newList = new Mlist<K,V>(mv);
                insert_list(nextList->pre,newList);
                hash_nl[mv]   = newList;
            }else{
                insert_node(mv,nextList);
                hash_nl[mv]   = nextList;
            }
            hash_kn[k]->v = v;
            ++hash_kn[k]->times;
            //cout<<k<<"times"<<hash_kn[k]->times<<endl;
        }
        void del_list(Mlist<K,V>* delList){
            delList->next->pre = delList->pre;
            delList->pre->next = delList->next;
            delete(delList);
        }
        void del_Old(){
            Mlist<K,V>* d = head->next;
            hash_kn.erase(d->node->down->k);
            hash_nl.erase(d->node->down);
            if(d->node->down  == d->node){
                delete(d->node);
                del_list(d);
            }else{
                Node<K,V>* lastNode = d->node->down;
                d->node->down       = lastNode->down;
                d->node->down->up   = d->node;
                delete(lastNode);
            }
        }
        void set_new(K k, V v){
            if(hash_kn.size() == maxSize){
                del_Old();
            }
            Node<K,V> *tmp = new Node<K,V>(k,v);
            if(head->next == head ||(head->next->node->times != 1)){
                Mlist<K,V>* list1 = new Mlist<K,V>(tmp);
                insert_list(head,list1);
            }else{
                insert_node(tmp,head->next);
            }
            hash_kn[k]         = tmp;
            hash_nl[tmp]       = head->next;
        }
        void del_node(Node<K,V>* node){
            Node<K,V>* tmp = node->down;
            Node<K,V>* t   = NULL;
            while(tmp != node){
                t   = tmp->down;
                delete(tmp);
                tmp = t;
            }
            delete(node);
        }
    public:
        void debug(){
            Node<K,V>* t = head->next->node;
            cout<<t->v<<endl;
            t = t->down;
            while(t != head->next->node){
                cout<<t->v<<endl;
                t = t->down;
            }
        }
};
int main(int argc,const char *argv[]){
    LFUCache<char,int> te(2);
    cout<<"--set-----"<<endl;
    cout<<te.set('a',1)<<endl;
    cout<<te.set('a',2)<<endl;
    cout<<"---get-----"<<endl;
    cout<<te.get('a')<<endl;
    cout<<"--set-----"<<endl;
    cout<<te.set('b',1)<<endl;
    cout<<te.set('c',4)<<endl;
    cout<<"---get-----"<<endl;
    cout<<te.get('a')<<endl;

    //cout<<te.set('a',2)<<endl;
    //cout<<te.set('c',3)<<endl;
    //cout<<te.set('d',4)<<endl;
    //cout<<"---get-----"<<endl;
    //cout<<te.get('a')<<endl;
    //cout<<te.get('b')<<endl;
    //cout<<te.get('c')<<endl;
    //cout<<te.get('d')<<endl;
    //cout<<"--set-----"<<endl;
    //cout<<te.set('d',7)<<endl;
    //cout<<te.set('e',8)<<endl;
    //cout<<te.set('f',9)<<endl;
    //cout<<te.set('g',10)<<endl;
    //cout<<"---get-----"<<endl;
    //cout<<te.get('d')<<endl;
    //cout<<te.get('e')<<endl;
    //cout<<te.get('f')<<endl;
    //cout<<te.get('g')<<endl;
    return 0;
}
