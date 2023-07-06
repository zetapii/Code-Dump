#include <iostream>
using namespace std;

template<typename T>
class Vector
{
    private:
    T* vec;
    size_t cap;
    size_t siz;
    public:
    Vector()
    {
        vec = new T[1];
        cap = 1;
        siz = 0;
    }
    ~Vector()
    {
        delete [] vec;
    }
    int size()
    {
        return siz;
    }
    void push_back(const T element)
    {
        if(siz==cap)
        {
            T* tmp = new T[2*cap];
            for(int i=0;i<siz;i++)
                tmp[i]=vec[i];
            delete [] vec;
            cap*=2;
            vec=tmp;
        }
        vec[siz++]=element;
        return ;
    }
    T& back() 
    {
        return vec[siz - 1];
    }
    const T& operator[](size_t index) const
    {
        if (index >= siz) 
        {
            throw std::out_of_range("Index out of range");
        }
        return vec[index];
    }
    T& operator[](size_t index)
    {
        if (index >= siz) 
        {
            throw std::out_of_range("Index out of range");
        }
        return vec[index];
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
        qu.print(1);
        qu.dequeue();
        qu.enqueue(100);
        qu.enqueue(200);
        qu.print(4);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
