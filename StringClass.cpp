#include "bits/stdc++.h"
using namespace std;

class String
{
    public:
    char* data;
    size_t len;

    public:
    String(const char* str)
    {
        len=strlen(str);
        data = new char[len+1];
        strcpy(data,str);
    }

    ~String()
    {
        if(data)
            delete[] data;
    }

    //copy constructor
    String(const String& other)
    {
        len=other.len;
        data = new char[len+1];
        strcpy(data,other.data);
    }

    //move constructor
    String(String&& other)
    {
        len=other.len;
        data=other.data;
        other.len=0;
        other.data=NULL;
    }

    //copy assignment operator    
    String& operator = (String& other)
    {
        if(this!=&other)
        {
            if(data)
                delete[] data;
            len=other.len;
            data=new char[len+1];
            strcpy(data,other.data);
        }
        return *this;
    }

    //move assignment operator
    String& operator = (String&& other)
    {
        if(this!=&other)
        {
            if(data)
                delete[] data;
            len=other.len;
            data=other.data;
            other.len=0;
            other.data=NULL;
        }
        return *this;
    }
    friend ostream& operator << (ostream& output,const String& str);
};

ostream& operator << (ostream& output,const String& str)
{
    if(str.data)
    output<<str.data;
    return output;
}

int main()
{
    String currentString("bcdef");
    String otherString("lmaof");
    cout<<currentString<<" "<<otherString<<endl;
    currentString=otherString;
    cout<<currentString<<endl;
    currentString=std::move(otherString);
    cout<<currentString<<" "<<otherString.len<<endl;
    return 0;
}
