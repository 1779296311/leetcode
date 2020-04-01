/*********************************************
*     ------------------------
*     ------------------------
*     file name: LFU.cpp
*     author   : @ JY
*     date     : 2020--03--31
**********************************************/
struct Node{
    int k;
    int v;
    Node *up;
    Node *down;
    int times;
    Node(int kk, int vv):k(kk),v(vv),up(this),down(this),times(1){}
};
struct Mlist{
    Mlist* next;
    Mlist* pre;
    Node * node;
    Mlist(Node* n):next(NULL),pre(NULL),node(n){}
};
class LFUCache{
    public:
        LFUCache(int s):maxSize(s){
            head       = new Mlist(NULL);
            head->next = head;
            head->pre  = head;
        }
        ~LFUCache(){
            Mlist *tmp = head->next;
            Mlist *t   = NULL;
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
        Mlist* head;
        unordered_map<int,Node*> hash_kn;
        unordered_map<Node*,Mlist*> hash_nl;
    public:
        int put(int k, int v){
            if(hash_kn.find(k) == hash_kn.end()){
                set_new(k,v);
            }else{
                modify(k,v);
            }
            return hash_kn[k]->v;
        }
        int get(int k){
            typename unordered_map<int,Node*>::iterator a = hash_kn.find(k);
            if(a == hash_kn.end()){
                return int(-1);
            }else{
                move(k);
            }
            return hash_kn[k]->v;
        }
    private:
        void move(int k){
            modify(k,hash_kn[k]->v);
        }
        void insert_node(Node* node, Mlist* newList){
           Node *oldHead = newList->node;

           node->up           = oldHead;
           oldHead->down->up  = node;
           node->down         = oldHead->down;
           oldHead->down      = node;

           newList->node      = node;
        }
        void insert_list(Mlist preList, Mlist* newList){
            newList->next      = preList->next;
            preList->next->pre = newList;
            preList->next      = newList;
            newList->pre       = preList;
        }
        void remove_node(Node* rm, Mlist* hList){
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
        void modify(int k,int v){
            Node*  mv       = hash_kn[k];
            Mlist* oldList  = hash_nl[mv];
            Mlist* nextList = oldList->next;
            remove_node(mv,oldList);
            if((nextList == head)||(nextList->node->times != (++hash_kn[k]->times))){
                Mlist* newList = new Mlist(mv);
                insert_list(nextList->pre,newList);
                hash_nl[mv]   = newList;
            }else{
                insert_node(mv,nextList);
                hash_nl[mv]   = nextList;
            }
            hash_kn[k]->v = v;
        }
        void del_list(Mlist* delList){
            delList->next->pre = delList->pre;
            delList->pre->next = delList->next;
            delete(delList);
        }
        void del_Old(){
            Mlist* d = head->next;
            hash_kn.erase(d->node->down->k);
            hash_nl.erase(d->node->down);
            if(d->node->down  == d->node){
                delete(d->node);
                del_list(d);
            }else{
                Node* lastNode = d->node->down;
                d->node->down       = lastNode->down;
                lastNode->up        = d->node;
                delete(lastNode);
            }
        }
        void set_new(int k, int v){
            if(hash_kn.size() == maxSize){
                del_Old();
            }
            Node *tmp = new Node(k,v);
            if(head->next == head ||(head->next->node->times != 1)){
                Mlist* list1 = new Mlist(tmp);
                insert_list(head,list1);
            }else{
                insert_node(tmp,head->next);
            }
            hash_kn[k]         = tmp;
            hash_nl[tmp]       = head->next;
        }
        void del_node(Node* node){
            Node* tmp = node->down;
            Node* t   = NULL;
            while(tmp != node){
                t   = tmp->down;
                delete(tmp);
                tmp = t;
            }
            delete(node);
        }
};
int main(int argc,const char *argv[]){
    LFUCache<char,int> te(3);
    cout<<"--set-----"<<endl;
    cout<<te.set('a',1)<<endl;
    cout<<te.set('b',2)<<endl;
    cout<<te.set('c',3)<<endl;
    cout<<te.set('d',4)<<endl;
    cout<<"--------"<<endl;
    cout<<te.get('a')<<endl;
    cout<<te.get('b')<<endl;
    cout<<te.get('c')<<endl;
    cout<<te.get('d')<<endl;
    cout<<"--set-----"<<endl;
    cout<<te.set('d',7)<<endl;
    cout<<te.set('e',8)<<endl;
    cout<<te.set('f',9)<<endl;
    cout<<te.set('g',10)<<endl;
    cout<<"---get-----"<<endl;
    cout<<te.get('d')<<endl;
    cout<<te.get('e')<<endl;
    cout<<te.get('f')<<endl;
    cout<<te.get('g')<<endl;
    return 0;
}
