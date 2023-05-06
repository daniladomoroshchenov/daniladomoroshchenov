#ifndef CODER_H
#define CODER_H

#include <map>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

struct Node {
    public:
        Node() {
            left = NULL;
            right = NULL;
        }
        Node(Node *l, Node *r) {
            left = l;
            right = r;
            a = l->a + r->a;
            c = '\0';
        }
        int a;
        char c;
        Node *left, *right;
};

struct MyCompare {
    bool operator() (Node *left, Node *right) const { 
        return left->a < right->a;
    }
};

void BuildTable(Node *root);
string char_to_binary(char c);
string str_to_binary(string str);
string zip(string str);

#endif