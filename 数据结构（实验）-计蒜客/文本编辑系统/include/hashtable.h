#ifndef HASHTABLE_
#define HASHTABLE_

#include <iostream>
#include <string>
#include <utility>
using namespace std;

class Node {
private:
    pair<string, int> p;
public:
    Node();
    Node(const char *str);
    Node(const string &str);
    bool operator!=(const char *str);
    bool operator!=(const string &str);
    bool operator==(const char *str);
    bool operator==(const string &str);
    bool operator!=(Node &n);
    bool operator==(Node &n);
    char operator[](const int index);
    int length();
    int &second();
    const pair<string, int>* get_pair() const;
    ~Node();
};

class HashTable {
private:
    Node *elem;
    int size;
public:
    HashTable();
    ~HashTable();
    int hash(Node &index);
    bool search(Node &index, int &pos, int &times);
    int insert(Node &index);
    int insert(const char *str);
    int get_size() const;
    const pair<string, int> *get_pair(int index);
    const pair<string, int> *get_pair(int index) const;
};

#endif
