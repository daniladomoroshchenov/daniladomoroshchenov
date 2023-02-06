#include <iostream>
#include <map>
#include <list>
#include <vector>

using namespace std;

vector<char> code;
map<char, vector<char>> table;

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

void print_vector(vector<bool> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
    }
}

string zip(string str) {
    string res = "";
    map<char, int> m;
    for (int i = 0; i < str.length(); i++) {
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
    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        vector<char> x = table[c];
        for (int j = 0; j < x.size(); j++) {
            res += x[j];
        }
    }
    return res;
}

int main() {
    string str;
    string binary_str;
    getline(cin, str);
    for (int i = 0; i < size(str); i++) {
        binary_str += char_to_binary(str[i]);
    }
    cout << "Original code: " << binary_str << endl;
    cout << "Zip code: " << zip(str) << endl;
    return 0;
}
