#include "coder.h"

vector<char> code;
map<char, vector<char>> table;

void BuildTable(Node *root) {
    if (root->left != NULL) {
        code.push_back('0');
        BuildTable(root->left);
    }
    if (root->right != NULL) {
        code.push_back('1');
        BuildTable(root->right);
    }
    if (root->c) {
        table[root->c] = code;
    }
    code.pop_back();
}

string char_to_binary(char c) {
    int n = (int) c;
    string res = "";
    while (n != 0) {
        if (n % 2 == 0)
            res = '0' + res;
        else 
            res = '1' + res;
        n /= 2;
    }
    return res;
}

string str_to_binary(string str) {
    string res = "";
    for (unsigned i = 0; i < str.size(); i++) {
        res += char_to_binary(str[i]);
    }
    return res;
}

string zip(string str) {
    string res = "";
    map<char, int> m;
    for (unsigned i = 0; i < str.length(); i++) {
        char c = str[i];
        m[c]++;
    }

    list<Node *> t;
    map<char, int>::iterator i;
    for (i = m.begin(); i != m.end(); i++) {
        Node *p = new Node();
        p->c = i->first;
        p->a = i->second;
        t.push_back(p);
    }

    while (t.size() != 1) {
        t.sort(MyCompare());
        Node *SonL = t.front();
        t.pop_front();
        Node *SonR = t.front();
        t.pop_front();
        Node *parent = new Node(SonL, SonR);
        t.push_back(parent);
    }

    Node *root = t.front();
    BuildTable(root);

    for (unsigned i = 0; i < str.length(); i++) {
        char c = str[i];
        vector<char> x = table[c];
        for (unsigned j = 0; j < x.size(); j++) {
            res += x[j];
        }
    }
    return res;
}
