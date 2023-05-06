#include "coder.h"

using namespace std;

int main() {
    string str, binary_str;
    getline(cin, str);
    binary_str = str_to_binary(str);
    cout << "Original code: " << binary_str << endl;
    cout << "Zip code: " << zip(str) << endl;
    return 0;
}
