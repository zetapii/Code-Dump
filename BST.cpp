#include <bits/stdc++.h>
using namespace std;

template<typename T>
class BST
{
    class Node 
    {
        public:
        T val;
        Node* lftPtr;
        Node* rghtPtr;

        Node(T val_) : val(val_),lftPtr(nullptr),rghtPtr(nullptr) {};

        bool operator < (Node& other)
        {            
            return val < other.val;
        }

        bool operator == (Node& other)
        {
            return val == other.val;
        }

    };


    Node* head;

    public:

    BST():head(nullptr){}

    void insert(T val)
    {
        Node* nodeToInsert = new Node(val);
        head = insert(nodeToInsert,head);
        return ;      
    }

    Node* insert(Node* nodeToInsert,Node* curNode)
    {
        if(curNode == nullptr) return nodeToInsert;

        else if(*nodeToInsert < *curNode) curNode->lftPtr = insert(nodeToInsert,curNode->lftPtr);

        else curNode->rghtPtr = insert(nodeToInsert,curNode->rghtPtr);

        return curNode;
    }

    Node* find(T val)
    {
        return find(head,val);
    }

    Node* find(Node* curNode,T val)
    {
        if(curNode == nullptr) return nullptr;

        else if(val == curNode->val) return curNode;
        else if(val < curNode->val) return find(curNode->lftPtr,val);

        else return find(curNode->rghtPtr,val);
    }


    class iterator
    {

        Node* iterNode;

        public : 
        iterator(Node* iterNode_) : iterNode(iterNode_){}
        Node* next(Node* curNode)
        { 
            if(curNode == nullptr) return curNode;
            
            if(curNode->rghtPtr)
            {
                curNode = curNode->rghtPtr;
                while(curNode->lftPtr) curNode = curNode->lftPtr;
                return curNode;
            }
            else 
                return nullptr;
        }

        iterator& operator ++ () 
        {
            iterNode = next(iterNode);
            return *this;
        }

        T& operator * ()
        {
            return iterNode->val;
        }

        bool operator == (iterator& other)
        {
            return other.iterNode == iterNode;
        }

        bool operator != (iterator& other)
        {
            return other.iterNode != iterNode;
        }

    };
    
    iterator begin()
    {
        Node* curNode = head;
        while(curNode->lftPtr) curNode = curNode->lftPtr;
        return curNode;
    }

    Node* delete_(T val) 
    {
        //Deletion is a bit more complex
        return head = delete_(head,val);
    }

    Node* delete_(iterator toDelete)
    {
        return head = delete_(head,*toDelete);
    }

    Node* delete_(Node* curNode,T toDelete)
    {
        if(curNode == nullptr) return nullptr;

        if(curNode->val == toDelete)
        {
            if(curNode->lftPtr == nullptr)
            {
                Node* ret = curNode->rghtPtr;
                curNode->rghtPtr = nullptr;   
                return ret;
            }
            else if(curNode->rghtPtr == nullptr)
            {
                Node* ret = curNode->lftPtr;
                curNode->lftPtr = nullptr;
                return ret;
            }
            else 
            {
                Node* ret;
                curNode = curNode->rghtPtr;
                if(curNode->rghtPtr->lftPtr == nullptr)
                {
                    ret=curNode->rghtPtr;
                    curNode->rghtPtr = curNode->rghtPtr->rghtPtr;
                    return ret;
                }
                else 
                {
                    curNode = curNode->rghtPtr;
                    while(curNode->lftPtr->lftPtr != nullptr)
                        curNode = curNode->lftPtr;
                    ret=curNode->lftPtr;
                    curNode->lftPtr = curNode->lftPtr->rghtPtr;
                    return ret;
                }
            }
        }

        else if(toDelete <= curNode->val) curNode->lftPtr =  delete_(curNode->lftPtr,toDelete);
        
        else curNode->rghtPtr = delete_(curNode->rghtPtr,toDelete);

        return curNode;
    }

};

template<typename T>
void print(T f)
{
    typename T::iterator it = f.begin();

    typename T::iterator fin(nullptr);
    while(it!=fin)
    {
        cout<<*it<<" ";
        ++it;
    }
    cout<<endl;
    return ;
}

signed main() 
{
    BST<int> bst;
    for(int i=1;i<=10;i++)
    {
        bst.insert(i);    
    }
    print(bst);
    bst.delete_(1);
    print(bst);
    bst.delete_(7);
    print(bst);
    return 0;
}
