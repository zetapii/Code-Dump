#include <bits/stdc++.h>
using namespace std;

class GenericAllocator 
{
    public:
    ~GenericAllocator() = default;
    static void* allocate_memory(size_t sz)
    {
        void* ptr=malloc(sz);
        return ptr;
    }
    static void deallocate_memory(void* b)
    {
        //free
    }
};

template<typename T>
struct block
{
    T ptr;
    block* nxt;
};

template<typename T>
class MyAllocator 
{
    private: 
    block<T>* head;
    
    public:
    MyAllocator(int numElements)
    {
        head = nullptr;
        block<T>* itr = nullptr;
        void* cur = GenericAllocator::allocate_memory(sizeof(block<T>)*numElements); 
        block<T>* newBlock = reinterpret_cast<block<T>*>(cur); 

        for(size_t i = 0; i < numElements; i++)
        {
            if(head == nullptr)
            {
                head = newBlock;
                itr = newBlock;
                itr->nxt=nullptr;
            }
            else 
            {
                itr->nxt = newBlock;
                itr = newBlock;
                itr->nxt=nullptr;
            }
            newBlock++;
        }
    }

    T* allocate_memory() 
    {
        if(head == nullptr)
        {
            return nullptr;
        }
        T* toAllocate = &(head->ptr); 
        head = head->nxt;
        return toAllocate;
    }

    void deallocate_memory(T* ptr)
    {
        block<T>* newBlock = reinterpret_cast<block<T>*>(ptr);
        newBlock->nxt = head;
        head = newBlock;
    }
};

int main() 
{
    MyAllocator<int> allocator(10);
    vector<int*> vec;
    for(int i=0;i<10;i++)
    {
        vec.push_back(allocator.allocate_memory());
    }
    int j=0;
    for(auto A:vec)
    {
        *A=j++;
        cout<<*A;
    }
    return 0;
}
