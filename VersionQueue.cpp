#include <iostream>
using namespace std;


template <typename T>
class Vector
{
private:
    int cap;
    int siz;
    T *arr;

public:
    // Define iterator type
    class Iterator
    {
    public:

        Iterator(T* ptr) : m_itr_ptr(ptr) {}
        Iterator operator++()
        {
            Iterator old_itr = *this;
            m_itr_ptr++;
            return old_itr;
        }

        Iterator operator++(int dummy)
        {
            m_itr_ptr++;
            return *this;
        }

        Iterator operator--()
        {
            Iterator old_itr = *this;
            m_itr_ptr--;
            return old_itr;
        }

        Iterator operator--(int dummy)
        {
            m_itr_ptr--;
            return *this;
        }

        T& operator*() const { return *m_itr_ptr; }

        T* operator->() const { return m_itr_ptr; }

        bool operator==(const Iterator &rhs) { return m_itr_ptr == rhs.m_itr_ptr; }

        bool operator!=(const Iterator &rhs) { return m_itr_ptr != rhs.m_itr_ptr; }

    private:
        T* m_itr_ptr;
    };

    // Begin and end functions to get iterators
    Iterator begin() { return Iterator(arr); }
    Iterator end() { return Iterator(arr + siz); }

    Vector()
    {
        cap = 0;
        siz = 0;
        arr = nullptr;
        reserve(1);
    }

    void reserve(int new_size)
    {
        if (new_size > cap)
        {
            T *tmp = static_cast<T *>(::operator new(sizeof(T) * new_size));
            for (int i = 0; i < siz; i++)
                new (&tmp[i]) T(arr[i]);
            cap = new_size;
            if (arr != nullptr)
                ::operator delete(arr);
            arr = tmp;
        }
        return;
    }

    void push_back(const T val)
    {
        if (cap == siz)
        {
            reserve(2 * cap);
        }
        new (&arr[siz]) T(val);
        siz++;
        return;
    }

    size_t size()
    {
        return siz;
    }

    T &back()
    {
        if (siz == 0)
        {
            throw std::runtime_error("out of range");
        }
        return arr[siz - 1];
    }

    T &operator[](size_t idx)
    {
        if (idx >= siz)
        {
            throw std::runtime_error("out of range");
        }
        else
            return arr[idx];
    }

    ~Vector()
    {
        for (int i = 0; i < siz; i++)
        {
            arr[i].~T();
        }
        ::operator delete(arr);
    }
};

template<typename T>
struct node 
{
    T data;
    struct node* nxt;
    struct node* prv;
    node(T d, struct node* p, struct node* n)
    {
        data = d;
        nxt = n;
        prv = p;
    }
};

template<typename T>
class VersionQueue
{
    private:

    int curVersion;
    Vector<node<T>*> head;  
    Vector<node<T>*> tail; 

    public:

    VersionQueue()
    {
        curVersion = 0;
        head.push_back(NULL);
        tail.push_back(NULL);
    }

    void enqueue(T x)
    {
        if (head[curVersion] == NULL)
        {
            curVersion++;
            head.push_back(new node<T>(x, NULL, NULL));
            tail.push_back(head.back());
        }
        else 
        {
            curVersion++;
            head.push_back(head[curVersion - 1]);            
            tail.push_back(new node<T>(x, tail[curVersion - 1], NULL));          
            tail[curVersion - 1]->nxt = tail[curVersion];
        }

    }

    void dequeue()
    {
        if (head[curVersion] == NULL)
        {
            return;
        }
        else 
        {
            curVersion++;
            head.push_back(head[curVersion - 1]->nxt);
            tail.push_back(tail[curVersion - 1]);
        }
    }

    void print(int version)
    {
            if (version > curVersion)
                return;

            node<T>* cur = head[version];
            while (cur)
            {
                cout << cur->data << " ";
                if (cur == tail[version])
                    break;
                cur = cur->nxt;
            }
            cout << endl;
            return;
        }
};

int main() 
{
    Vector<int> vec;
    for(int A=0;A<=6;A++)
        vec.push_back(A);
    Vector<int>::Iterator it=vec.begin();
    for(;it!=vec.end();it++)
        std::cout<<*it<<" ";
    try
    {
        /* code */
        VersionQueue<int> qu;
        qu.enqueue(4);
        qu.enqueue(5);
        qu.enqueue(100);
        qu.print(2);
        // qu.dequeue();
        qu.enqueue(100);
        qu.enqueue(200);
        qu.print(3);
        qu.print(5);

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
