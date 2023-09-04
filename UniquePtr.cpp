#include "bits/stdc++.h"
#include <unistd.h>
using namespace std;

template<typename T>
class UniquePtr
{
private:
    T* ptr;

public:
    UniquePtr() : ptr(nullptr) {}
    UniquePtr(T* ptr_) : ptr(ptr_) {}

    // Delete the copy constructor and copy assignment operator
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Move constructor
    UniquePtr(UniquePtr&& other)
    {
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    // Move assignment operator
    UniquePtr& operator=(UniquePtr&& other)
    {
        if (this != &other)
        {
            if (ptr)
                delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Return a reference to the stored object
    T& get()
    {
        if (ptr)
            return *ptr;
        throw std::runtime_error("Null pointer dereference");
    }

    // Destructor
    ~UniquePtr()
    {
        if (ptr)
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
    // cout<<s.get();
    return 0;
}
