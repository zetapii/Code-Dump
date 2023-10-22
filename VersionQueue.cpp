#include <iostream>
using namespace std;


template<typename T>
class Vector
{
    public:
    int cap;
    int siz;
    T* arr;
    
    public:
    Vector()
    {
        cap=0;
        siz=0;
        arr=nullptr;
        reserve(1);
    }

    void reserve(int new_size)
    {
        if (new_size > cap)
        {
            T* tmp = static_cast<T*>(::operator new(sizeof(T) * new_size)); 
            for (int i = 0; i < siz; i++)
                new (&tmp[i]) T(arr[i]); 
            cap = new_size;
            if(arr!=nullptr)
                ::operator delete(arr);
            arr = tmp;
        }
        return ;
    }

    void push_back(const T val)
    {
        if(cap==siz)
        {
            reserve(2*cap);
        }
        arr[siz]=val;
        siz++;
        return ;
    }
    size_t size()
    {
        return siz;
    }
    T& back()
    {
        if(siz==0)
        {
            throw::runtime_error("out of range");
        }
        return arr[siz-1];
    }
    T& operator [] (size_t idx)
    {
        if(idx>=siz)
        {
            throw::runtime_error("out of range");
        }
        else 
            return arr[idx];
    }
    ~Vector()
    {
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
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
