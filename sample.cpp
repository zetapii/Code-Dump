#include <bits/stdc++.h>
using namespace std;

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
    vector<node<T>*> head;  // Removed typename keyword
    vector<node<T>*> tail;  // Removed typename keyword

public:
    VersionQueue()
    {
        curVersion = 0;
        head.resize(1, NULL);
        tail.resize(1, NULL);
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
    VersionQueue<int> qu;
    qu.enqueue(4);
    qu.enqueue(5);
    qu.print(1);
    qu.dequeue();
    qu.enqueue(100);
    qu.enqueue(200);
    qu.print(4);
    return 0;
}
