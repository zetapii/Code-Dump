#include "bits/stdc++.h"
#include <unistd.h>
using namespace std;

template<typename T>
class UniquePtr
{
    private:
    T* ptr;
    
    public:
    
    UniquePtr():ptr(NULL){}
    UniquePtr(T* ptr_):ptr(ptr_){}

    UniquePtr(const UniquePtr& other)=delete;
    
    UniquePtr(UniquePtr&& other)
    {
        ptr=other.ptr;
        other.ptr=NULL;
    }

    UniquePtr& operator = (const UniquePtr& other)=delete;
    
    UniquePtr& operator = (UniquePtr&& other)
    {
        if(this!=&other)
        {
            if(ptr)
                delete ptr;
            ptr=other.ptr;
            other.ptr=NULL;
        }
        return *this;
    }
    
    T get()
    {
        if(ptr)
        return *ptr;
        return 0;
    }

    ~UniquePtr()
    {
        if(ptr)
            delete ptr;
    }
};

int main()
{
    UniquePtr<int> f(new int(10));
    cout<<f.get()<<endl;
    UniquePtr<int> s(new int(20));
    cout<<s.get()<<endl;
    f=std::move(s);
    cout<<f.get()<<endl;
    cout<<s.get();
    return 0;
}
