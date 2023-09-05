#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class Cache
{
    public:
    virtual void set(int key,int value){}
    virtual int get(int key){}
};

class LRUCache:public Cache 
{
    private:
    map<int,int> maps;
    public:
    LRUCache()
    {
    }
    void set(int key,int val)
    {
        maps[key]=val;
    }
    int get(int key)
    {
        if(maps.find(key)!=maps.end())
            return maps[key];
        return -1;
    }
};

class FCFSCache:public Cache 
{
    private:
    map<int,int> maps;
    public:
    FCFSCache()
    {

    }
    void set(int key,int val)
    {
        maps[key]=val;
    }
    int get(int key)
    {
        if(maps.find(key)!=maps.end())
            return maps[key];
        return -1;
    }
};

class CacheFactory
{
    public:
    static Cache* get(string type)
    {
        if(type=="LRU")
            return new LRUCache();
        if(type=="FCFS")
            return new FCFSCache();
        return NULL;
    }
};

int main() 
{
    Cache* c1=CacheFactory::get("LRU");
    c1->set(1,2);
    cout<<c1->get(3);
    return 0;
}
