/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_heap_pro.cpp
*     author   : @ JY
*     date     : 2020--05--04
**********************************************/
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <vector>
#include <stdlib.h>
using  namespace  std;
template<class V=int, class CMP=less<V>>
class heap{
    public:
        heap(int size, CMP c):maxSize(size),cmp(c),heapSize(0){}
        heap(int size):maxSize(size),heapSize(0){}
        heap():maxSize(-1),heapSize(0){}
    public:
        V& top(){
            return heapArr[0];
        }
        int heapPush(V& v){
            if(maxSize != -1){
                return limitPush(v);
            }else{
                return noLimitPush(v);
            }
        }
        V heapPop(){
            int tmp = heapArr[0];
            swap(0,size()-1);
            heapfy(0,--heapSize);
            return tmp;
        }
    protected:
        int limitPush(V& v){
            if(maxSize <=0 ){
                return -1;
            }
            if(size()<maxSize){
                return heapInsert(v);
            }else{
                return topKInsert(v);
            }
        }
        void noLimitPush(V& v){
            heapInsert(v);
        }
        int heapInsert(V& v){
            if(size() == heapArr.size()){
                heapArr.push_back(v);
                ++heapSize;
            }else{
                heapArr[heapSize++] = v;
            }
            int index  = size() - 1;
            int parent = (index-1)/2;
            while(index && cmp(v,heapArr[parent])){
                heapArr[index] = heapArr[parent];
                index          = parent;
                parent         = (index-1)/2;
            }
            heapArr[index] = v;
            return index;
        }
        int topKInsert(V& v){
            if(cmp(v,heapArr[0])){
                return -1;
            }else{
                heapArr[0] = v;
                return heapfy(0,heapSize);
            }
        }
    public:
        int heapfy(int index,int heapSize){
            int left = (index<<1)+1;
            int cur  = index;
            while(left<heapSize){
                left = (left+1<heapSize&&cmp(heapArr[left+1],heapArr[left]))?left+1:left;
                left = cmp(heapArr[left],heapArr[cur])?left:cur;
                if(left == cur){
                    return cur;
                }else{
                    swap(left,cur);
                    cur  = left;
                    left = (cur<<1)+1;
                }
            }
            return cur;
        }
        int size(){
            return heapSize;
        }
        bool empty(){
            return !size();
        }
    protected:
        void swap(int a, int b){
            V tmp      = heapArr[a];
            heapArr[a] = heapArr[b];
            heapArr[b] = tmp;
        }
    protected:
        vector<V> heapArr;
        const int maxSize;
        int       heapSize;
    protected:
        CMP cmp;
    public:
        void debug(){
            for(int i=0; i<heapArr.size(); ++i){
                cout<<heapArr[i]<<" ";
            }
            cout<<endl;
        }
};
///-----------------动态词频统计----------------------------------------------------------------------------------------
template<class V>
struct cmpLess{
    bool operator()(V& a, V& b){
        return a.times < b.times;
    }
};
template<class V>
struct node1{
    V value;
    int times;
    node1(){}
    node1(V v,int t):value(v),times(t){}
};
template<class V, class Node,class CMP=less<V>>
class topKHeap: protected heap<Node,CMP>{
    typedef heap<Node,CMP> parent;
    public:
        topKHeap(int sizeLimit,CMP c):parent(sizeLimit,c){}
        topKHeap(int sizeLimit)      :parent(sizeLimit){}
    public:
        void push(V v){
            if(wordFrequence.find(v) == wordFrequence.end()){
                wordFrequence.insert(make_pair(v,Node(v,1)));
                wordIndex.insert(make_pair(v,-1));
            }else{
                ++wordFrequence[v].times;
            }
            if(wordIndex[v] != -1){
                parent::heapArr[wordIndex[v]].times = wordFrequence[v].times;
                this->heapfy(wordIndex[v],parent::size());
            }else if(parent::size() < parent::maxSize){
                wordIndex[v] = parent::size();
                this->heapInsert(wordFrequence[v]);
            }else if(parent::cmp(parent::top(),wordFrequence[v])){
                wordIndex[parent::top().value] = -1;
                wordIndex[v]                   = 0;
                parent::top()                  = wordFrequence[v];
                this->heapfy(0,parent::size());
            }
        }
        Node pop(){
            this->swap(0,parent::size()-1);
            this->heapfy(0,--parent::heapSize);
            return parent::heapArr[parent::heapSize];
        }
        Node top(){
            return parent::top();
        }
    private:
        map<V,Node> wordFrequence;
        map<V,int>  wordIndex;
    private:
        int heapInsert(Node& v){
            if(parent::size() == parent::heapArr.size()){
                parent::heapArr.push_back(v);
                ++parent::heapSize;
            }else{
                parent::heapArr[parent::heapSize++] = v;
            }
            int index  = parent::size() - 1;
            int parent = (index-1)/2;
            while(index && parent::cmp(v,parent::heapArr[parent])){
                this->swap(index,parent);
                index                  = parent;
                parent                 = (index-1)/2;
            }
            return index;
        }
        int heapfy(int index, int size){
            int left = (index<<1)+1;
            int cur  = index;
            while(left<size){
                left = (left+1<parent::heapSize&&parent::cmp(parent::heapArr[left+1],parent::heapArr[left]))?left+1:left;
                left = parent::cmp(parent::heapArr[left],parent::heapArr[cur])?left:cur;
                if(left == cur){
                    return cur;
                }else{
                    this->swap(left,cur);
                    cur  = left;
                    left = (cur<<1)+1;
                }
            }
            return cur;
        }
        void swap(int a, int b){
            Node v1 = parent::heapArr[a];
            Node v2 = parent::heapArr[a];

            Node tmp           = parent::heapArr[a];
            parent::heapArr[a] = parent::heapArr[b];
            parent::heapArr[b] = tmp;

            int t               = wordIndex[v1.value];
            wordIndex[v1.value] = wordIndex[v2.value];
            wordIndex[v2.value] = t;;
        }
    public:
        map<int, int>::iterator iter;
        void debug(){
            auto it = wordFrequence.begin();
            while(it !=wordFrequence.end()){
                cout<<it->first<<"->"<<it->second.times<<endl;
                ++it;
            }
            cout<<"/*----------------------------------------------------*/\n"<<endl;
            for(int i=0; i<parent::heapSize; ++i){
                cout<<parent::heapArr[i].value<<" ";
            }
            cout<<endl;
        }
        void printK(){
            for(int i=0; i<parent::heapSize; ++i){
                cout<<parent::heapArr[i].value<<" ";
            }
            cout<<endl;
        }
};
///-----------------多个数组前k大的所有数(sorted)----------------------------------------------------------------------------------------
struct Node1{
    int index;
    int arrNum;
    int size;
    Node1():index(-1),arrNum(-1),size(-1){}
    Node1(int i, int n,int s):index(i),arrNum(n),size(s){}
};
template<class V, class v=int>
struct cmpGreater{
    bool operator()(Node1& n1, Node1& n2, vector<vector<v>>& nums){
        return nums[n1.arrNum][n1.index]>nums[n2.arrNum][n2.index];
    }
};
template<class V, class CMP=less<int>>
class SortArrHeap{
    public:
        SortArrHeap(CMP c):maxSize(-1),size(0),cmp(c){}
        SortArrHeap():maxSize(-1),size(0){}
    private:
        vector<Node1> heapArr;
        int size;
        int maxSize;
        CMP cmp;
    public:
        vector<Node1> dowork(vector<vector<V>>& nums, int k){
            heapArr = vector<Node1>(k,Node1());
            maxSize = k;
            for(int i=0; i<nums.size(); ++i){
                heapInsert(Node1(nums[i].size()-1,i,nums[i].size()),nums);
            }
            int n = 0;
            vector<Node1> res;
            for(int i=0; i<k && !empty(); ++i){
                res.push_back(pop(nums));
            }
            return res;
        }
    public:
        Node1 pop(vector<vector<V>>& nums){
            Node1 node = heapArr[0];
            if(node.size <= 1){
                swap(0,--size);
                heapfy(0,size,nums);
            }else{
                heapArr[0].size--;
                heapArr[0].index--;
                heapfy(0,size,nums);
            }
            return node;
        }
        int heapfy(int index,int size, vector<vector<V>>& nums){
            int left = (index<<1)+1;
            while(left<size){
                left = (left+1<size&&cmp(heapArr[left+1],heapArr[left],nums))?left+1:left;
                left = cmp(heapArr[left],heapArr[index],nums)?left:index;
                if(left == index){
                    return index;
                }
                swap(left,index);
                index = left;
                left  = (index<<1)+1;
            }
            return index;
        }
        int heapInsert(Node1 node, vector<vector<V>>& nums){
            int index  = size;
            int parent = (index-1)/2;
            ++size;
            while(index&&cmp(node,heapArr[parent],nums)){
                heapArr[index] = heapArr[parent];
                index = parent;
                parent = (index-1)/2;
            }
            heapArr[index] = node;
            return index;
        }
        bool empty(){
            return size == 0;
        }
        void swap(int a, int b){
            if(a == b){
                return;
            }
            auto t     = heapArr[a];
            heapArr[a] = heapArr[b];
            heapArr[b] = t;
        }
void debug(vector<Node1>& nodes, vector<vector<V>>& nums){
    for(int i=0; i<nodes.size(); ++i){
        cout<<"from "<<nodes[i].arrNum<<" at Index: "<<nodes[i].index<<" ";
        cout<<nums[nodes[i].arrNum][nodes[i].index]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

};
////-----------------------数据流中位数-------------------------------------------------------------------------
class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {
    }
    void addNum(int num){
        if(small.size() == big.size()){
            small.push(num);
            big.push(small.top());
            small.pop();
        }else if(small.size() == big.size()-1){
            big.push(num);
            small.push(big.top());
            big.pop();
        }
    }
    double findMedian(){
        if(small.size() == big.size()){
            return (double)(small.top()+big.top())/2;
        }else if(small.size()>big.size()){
            return small.top();
        }else{
            return big.top();
        }
    }
private:
    priority_queue<int,vector<int>,less<int>> small;
    priority_queue<int,vector<int>,greater<int>> big;
};
int main(int argc,const char *argv[]){
    vector<vector<int>> nums = {{1,2,3,6,7},{3,7,9,10},{12,234},{-1,8,10},{12,13,14}};
    SortArrHeap<int,cmpGreater<Node1>> SA;
    vector<Node1> res  = SA.dowork(nums,7);
    SA.debug(res,nums);
    //int a;
    //topKHeap<string,node1<string>,cmpLess<node1<string>>> hp1(5);
    //vector<vector<string>>s = {
        //{"qppq","ww","ee","rr","t1t"},{"q","ww","ee","rr","tt"},
        //{"qooq","ww","ee","rr","t1et"},{"qr","ew","ee","rsrr","tsdt"},
        //{"qooq","ww","ee","rr","tet"},{"qq","ww","ee","rr","tsdrt"},
        //{"qiiq","wrw","ee","rr","t1t"},{"qq","w","ee","rr","tt"},
        //{"qtttq","wrw","ee","rr","1et"},{"qq","wsdw","ee","rr","tsdt"},
        //{"qreeq","wrw","ee","rr","t1e"},{"qq","ww","esie","rr","tuut"}};
    //for(int i=0; i<s.size(); ++i){
        //for(int j=0; j<s[0].size(); ++j){
            //hp1.push(s[i][j]);
        //}
        //hp1.printK();
        //cin>>a;
    //}
    //hp1.debug();
    //cout<<hp1.pop().value<<endl;
    //hp1.debug();
    return 0;
}
