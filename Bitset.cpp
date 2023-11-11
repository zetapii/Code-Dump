#include <iostream>
#include <stdlib.h>
#include <memory>
using namespace std;

#define unit 31

template<size_t len>
class Bitset 
{
    bool flipped;
    array<int,(len-1)/unit+1> vec;
    int cnt;
    int tot;
    public:
    Bitset():cnt(0),tot(len),flipped(false),vec{}
    {   
    }
    
    int get(int idx)
    {
        if(vec[idx/unit]&(1<<(idx%unit)))
            return 1;
        return 0;
    }

    void fix(int idx) 
    {
        if(!get(idx))
            cnt++;
        vec[idx/unit]|=(1<<(idx%unit));
    }
    
    void unfix(int idx) 
    {
        if(get(idx))
            cnt--;
        vec[idx/unit]&=~(1<<(idx%unit));
    }
    
    void flip() 
    {
        for(int i=0;i<tot;i++)
            if(get(i))
                unfix(i);
            else 
                fix(i);
        return ;
    }

    int getcnt()
    {
        return cnt;
        if(flipped)
            return tot-cnt;
        return cnt;
    }    

    bool all() 
    {
        return getcnt()==tot;
    }
    
    bool one() 
    {
        return getcnt()>0;
    }
    
    int count() 
    {
        return getcnt();
    }
    
    string toString() 
    {
        string ret="";
        for(int i=0;i<tot;i++)
        {
            if(get(i))
                ret+="1";
            else 
                ret+="0";
        }
        return ret;
    }
};


int main() 
{
    Bitset<11> myBitset;

    std::cout << "Initial Bitset: " << myBitset.toString() << std::endl;

    myBitset.fix(1);
    myBitset.fix(5);
    myBitset.fix(10);

    std::cout << "After fixing some bits: " << myBitset.toString() << std::endl;

    myBitset.unfix(5);

    std::cout << "After unfixing a bit: " << myBitset.toString() << std::endl;

    myBitset.flip();

    std::cout << "After flipping all bits: " << myBitset.toString() << std::endl;

    std::cout << "All bits set? " << (myBitset.all() ? "Yes" : "No") << std::endl;

    std::cout << "At least one bit set? " << (myBitset.one() ? "Yes" : "No") << std::endl;

    std::cout << "Number of set bits: " << myBitset.count() << std::endl;

    return 0;
}

