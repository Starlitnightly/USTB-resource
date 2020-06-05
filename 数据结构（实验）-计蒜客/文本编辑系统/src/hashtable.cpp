#include "hashtable.h"

bool Node::operator!=(const char *str) {
    if(str==NULL)return true;
    if(this->p.first.compare(str)==-1)
        return true;

}

bool Node::operator!=(const string &str) {
    if(this->p.first.compare(str)==-1)
        return true;

}

bool Node::operator==(const char *str) {
    if(str==NULL)return false;
    if(this->p.first.compare(str)==0)
        return true;

}

bool Node::operator==(const string &str) {
    if(this->p.first.compare(str)==0)
        return true;

}

bool Node::operator!=(Node &n) {
    if(this->p.first.compare(n.p.first)==-1)
        return true;

}

bool Node::operator==(Node &n) {
    if(this->p.first.compare(n.p.first)==0)
        return true;

}

char Node::operator[](const int index) {
    if(index>=0 && index<length())
        return this->p.first[index];
    else
        return this->p.first[0];
    
}

int Node::length() { //return length of the string
    return p.first.length();
}

int &Node::second() {
    //std::cout<<p.second<<endl;
    return p.second;
}

const pair<string, int>* Node::get_pair() const {
    
    return &p;
}

Node::~Node() {
    
}

HashTable::HashTable() {
    elem=new Node[100000]();
    size=100000;
}

HashTable::~HashTable() {
    delete[] elem;
}

int HashTable::hash(Node &index) {
    //RS 哈希函数
    int b     = 378551;  
    int a     = 63689;  
    int h = 0;  
    
    for(int i = 0; i < index.length(); i++)  
    {  
         h = h * a + index[i];  
         a    = a * b;  
    } 
    if(h<0)
        h=0-h;
    h=h%size;
    //cout<<"hash"<<h<<endl;
    return h;  
}

bool HashTable::search(Node &index, int &pos, int &times) {
    int h=hash(index);  
    times=0;
    while (h<=size && elem[h].get_pair()->first.compare("#")!=0 && elem[h].get_pair()->first.compare(index.get_pair()->first)!=0)
    {
        h++,times++;
        if(h==size)
            h=0;
    }
    pos=h;
    if(elem[h].get_pair()->first.compare(index.get_pair()->first)==0)
    {
        
        return true;
    }
    return false;
}

int HashTable::insert(Node &index) {   
    //int h=hash(index);
    int pos,times;
    if(search(index,pos,times))
    {
        elem[pos].second()++;
        return 2;
    }
    else
        elem[pos]=index;
    //cout<<elem[h].get_pair()->first<<endl;

    return 1;
}

int HashTable::insert(const char * str) {
    Node *tmp=new Node(str);
    //int h=hash(*tmp);
    int pos,times;
    if(search(*tmp,pos,times))
    {
        elem[pos].second()++;
        return 2;
    }
    else
        elem[pos]=*tmp;
    delete tmp;
    //cout<<elem[h].get_pair()->second<<endl;
    return 1;
}

/*
 ==========================================================================
 =================Please Do Not Modify Functions Below=====================
 ========================请不要修改下列函数实现================================
 ==========================================================================
 */

Node::Node() {
    p = make_pair(string("#"), 1);
}

Node::Node(const char *str) {
    p = make_pair(string(str), 1);
}

Node::Node(const string &str) {
    p = make_pair(str, 1);
}

int HashTable::get_size() const {
    return size;
}

const pair<string, int>* HashTable::get_pair(int index) {
    if (index < size && index >= 0) {
        return (elem[index].get_pair());
    }
    return NULL;
}

const pair<string, int>* HashTable::get_pair(int index) const {
    if (index < size && index >= 0) {
        return (elem[index].get_pair());
    }
    return NULL;
}
