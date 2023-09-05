#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class File
{
    private:
    string file_name;
    string file_content;
    public:
    File(string file_name_,string file_content_="")
    {
        file_name=file_name_;
        file_content=file_content_;
    }
    string getName()
    {
        return file_name;
    }
};

class Directory
{
    private:
    string name;
    vector<File*> files;
    vector<Directory*> dir;
    public:
    Directory(string name_)
    {
        name=name_;
    }
    string getName()
    {
        return name;
    }
    void addDirectory(Directory* chld)
    {
        dir.push_back(chld);
        return ;
    }
    void addFile(File* chld)
    {
        files.push_back(chld);
        return ;
    }
    File* searchFile(string name)
    {
        for( auto A:files)
        {
            if(A->getName()==name)
            return A;
        }
        return NULL;
    }
    vector<File*> getAllFiles()
    {
        return files;
    }
    vector<Directory*> getAllDirectory()
    {
        return dir;
    }
};


void print(Directory* curfolder,string name,string curName)
{
    curName+=curfolder->getName()+"/";
    if(curfolder->searchFile(name))
    {
        cout<<"File found at "<<curName+name<<endl;
    }
    vector<Directory*> chld=curfolder->getAllDirectory();
    for(auto A:chld)
    {
        print(A,name,curName);
    }
    return ;
}

void printStructure(Directory* curfolder,string name,string curName)
{
    curName+=curfolder->getName();
    cout<<name+curName<<endl<<"|"<<endl;
    name+="-----";
    vector<File*> chldFiles=curfolder->getAllFiles();
    vector<Directory*> chldDirectory=curfolder->getAllDirectory();
    for(auto A:chldFiles)
    {
        cout<<name+curName+"/"+A->getName()<<endl<<endl;
    }
    for(auto A:chldDirectory)
    {
        printStructure(A,name,curName+"/");
    }
    return ;
}
int main() 
{

    Directory* d1= new Directory("root");
    Directory* d2= new Directory("subroot1");
    Directory* d3= new Directory("subroot1");
    Directory* d4= new Directory("subroot3");
    d1->addDirectory(d2);
    d1->addDirectory(d3);
    d3->addDirectory(d4);
    File* f1=new File("file-1");
    File* f2=new File("file-2");
    File* f3=new File("file-3");
    d2->addFile(f1);
    d3->addFile(f2);
    d4->addFile(f3);
    print(d1,"file-2","");
    printStructure(d1,"","");
    return 0;
}
