#include <iostream>
#include <vector>
#include <map>
#include <bits/stdc++.h>
using namespace std;

class Node 
{
    public:
    int val;
    int key;
    Node* nxt;
    Node* pre;
    Node(int key_, int val_) 
    {
        pre = NULL;
        nxt = NULL;
        val = val_;
        key = key_;
    }
};

class Cache 
{
    public:
    virtual void put(int key, int val) = 0;
    virtual int get(int key) = 0;
    virtual ~Cache() {}
};

class LRUCache:public Cache
{
    public:
    Node* head;
    Node* tail;
    int cap;
    unordered_map<int,Node*> maps;
    LRUCache(int cap_)
    {
        cap=cap_;
        head = new Node(-1,-1);
        tail = new Node(-1,-1);
        head -> nxt = tail;
        tail -> pre = head;
    }
    
    void pushFront(Node* cur)
    {
        head->nxt->pre=cur;
        cur->nxt=head->nxt;
        head->nxt=cur;
        cur->pre=head;
        return ;
    }

    void put(int key,int val)
    {
        if(maps.find(key)==maps.end())
        {
            if(maps.size()==cap)
            {
                 maps.erase(maps.find(tail->pre->key));
                 tail->pre->pre->nxt=tail;
                 tail->pre=tail->pre->pre;
            }
            Node* cur = new Node(key,val);
            pushFront(cur);
            maps[key]=cur;
        }
        else 
        {
            Node* cur=maps[key];
            cur->pre->nxt=cur->nxt;
            cur->nxt->pre=cur->pre;
            pushFront(cur);
            cur->val=val;
        }
    }

    int get(int key)
    {
        if(maps.find(key)==maps.end())
        {
            return -1;
        }
        else 
        {
            Node* cur=maps[key];
            cur->pre->nxt=cur->nxt;
            cur->nxt->pre=cur->pre;
            pushFront(cur);
            return cur->val;
        }
    }
    ~LRUCache()
    {
        Node* cur=head;
        while(cur!=NULL)
        {
            Node* tmp=cur;
            cur=cur->nxt;
            delete(tmp);
        }
    }
};

class FCFCCache : public Cache 
{
    public: 
    unordered_map<int, int> data;
    
    void put(int key, int val) override 
    {
        data[key] = val;
    }

    int get(int key) override 
    {
        if (data.find(key) != data.end()) 
        {
            return data[key];
        }
        return -1;
    }
};

class CacheFactory 
{
    public:
    static Cache* createCache(int cap, string type) 
    {
        if (type=="LRU") 
        {
            return new LRUCache(cap);
        }
        else if(type=="FCFS") 
        {
            return new FCFCCache();
        }
        else 
        {
            return NULL;
        }
    }
};

int main() 
{

    Cache* cache = CacheFactory::createCache(3, "LRU");

    cache->put(1, 10);
    cache->put(2, 20);
    cache->put(3, 30);

    cout << cache->get(2) << endl; // Output: 20

    cache->put(4, 40);

    cout << cache->get(1) << endl; // Output: -1 (not found)

    delete cache;

    return 0;
}
