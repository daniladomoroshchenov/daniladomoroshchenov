#include "coder_decoder.h"

// Формирование сообщения

string str_to_bin(string str) {
    string res = "";
    for (unsigned i = 0; i < str.length(); i++) {
        string seq = dec_to_bin((int)str[i]);
        res += seq;
    }
    return res;
}

int char_to_int(char c) {
    if (c == '1') {
        return 1;
    } else {
        return 0;
    }
}

void sup(string &str1, string &str2) {
    if (str1.length() > str2.length()) {
        while (str2.length() != str1.length()) {
            str2 = '0' + str2;
        }
    } else {
        if (str1.length() < str2.length()) {
            while (str1.length() != str2.length()) {
                str1 = '0' + str1;
            }
        }
    }
}

string pseudo_random_seq(string polinom, string number) {
    int count = 0;
    string res = number;
    sup(polinom, number);
    for (unsigned i = 0; i < polinom.length(); i++) {
        if (polinom[i] == '1') {
            count++;
        }
    }
    vector<int> pos(count);
    for (unsigned i = 0; i < polinom.length(); i++) {
        if (polinom[i] == '1') {
            pos.push_back(i);
        }
    }
    for (int i = 0; i < pow(2, polinom.length() - 1); i++) {
        int n = 0;
        for (unsigned j = 0; j < pos.size(); j++) {
            n += char_to_int(number[i + pos[j]]);
        }
        number.append(to_string(n % 2));
        res.append(to_string(n % 2));
    }
    return res;
}

string module_add(string str1, string str2) {
    string res = "";
    sup(str1, str2);
    for (unsigned i = 0; i < str1.length(); i++) {
        int n = (char_to_int(str1[i]) + char_to_int(str2[i])) % 2;
        res += to_string(n);
    }
    return res;
}

// Кодирование кодом Хемминга

string dec_to_bin(int n) {
    string res = "";
    int x;
    while (n > 1) {
        x = n % 2;
        n = n / 2;
        res = to_string(x) + res;
    }
    res = to_string(n) + res;
    if (res.length() != 8) {
        while (res.length() != 8) {
            res = '0' + res;
        }
    }
    return res;
}

bool bit_even(int n) {
    return (n & (n - 1)) == (0);
}

int count_check_bit(string seq, unsigned n) {
    unsigned k = n - 1;
    int res = 0;
    while (k < seq.length()) {
        if (k + n > seq.length() - 1) {
            for (unsigned i = k; i < seq.length(); i++) {
                if (seq[i] == '1') {
                    res++;
                }
            }
        } else {
            for (unsigned i = k; i < k + n; i++) {
                if (seq[i] == '1') {
                    res++;
                }
            }
        }
        k += n * 2;
    }
    return res;
}

string coder(string str) {
    for (unsigned i = 0; i < str.length(); i++) {
        if (bit_even(i + 1)) {
            str.insert(i, to_string(0));
        }
    }
    for (unsigned i = 0; i < str.length(); i++) {
        if (bit_even(i + 1)) {
            int k = count_check_bit(str, i + 1) % 2;
            if (k == 1) {
                str[i] = '1';
            } else {
                str[i] = '0';
            }
        }
    }
    return str;
}

// Внесение ошибки и поиск ошибки

string random_error(string str) {
    int i_error = rand() % str.length();
    if (str[i_error] == '1') {
        str[i_error] = '0';
    } else {
        str[i_error] = '1';
    }
    return str;
}

string error_check(string str) {
    string res = "";
    for (unsigned i = 0; i < str.length(); i++) {
        if (bit_even(i + 1)) {
            int k = count_check_bit(str, i + 1) % 2;
            if (k == 1) {
                res = '1' + res;
            } else {
                res = '0' + res;
            }
        }
    }
    return res;
}

int bin_to_dec(string bin) {
    int res = 0;
    for (unsigned i = 0; i < bin.length(); i++) {
        if (bin[i] == '1') {
            res += 1 * (int)pow(2, bin.length() - i - 1);
        }
    }
    return res;
}

// Исправление ошибки

string correct(string error_string, string sindrom_matrix) {
    int i_error = bin_to_dec(sindrom_matrix);
    if (i_error != 0) {
        if (error_string[i_error - 1] == '1') {
            error_string[i_error - 1] = '0';
        } else {
            error_string[i_error - 1] = '1';
        }
    }
    return error_string;
}

// Декодирование

string del_bit_even(string str) {
    string res = "";
    for (unsigned i = 0; i < str.length(); i++) {
        if (!bit_even(i + 1)) {
            res += str[i];
        }
    }
    return res;
}

string decoder(string str) {
    string res = "";
    while (str != "") {
        string letter = str.substr(0, 8);
        str.erase(0, 8);
        letter = (char)bin_to_dec(letter);
        res += letter;
    }
    return res;
}
