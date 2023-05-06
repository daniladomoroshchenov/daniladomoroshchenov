#ifndef CODER_DECODER_H
#define CODER_DECODER_H

#include <string>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

// Формирование сообщения
string str_to_bin(string str);
int char_to_int(char c);
void sup(string &str1, string &str2);
string pseudo_random_seq(string polinom, string number);
string module_add(string str1, string str2);

// Кодирование кодом Хемминга
string dec_to_bin(int n);
bool bit_even(int n);
int count_check_bit(string seq, unsigned n);
string coder(string str);

// Внесение ошибки и поиск ошибки
string random_error(string str);
string error_check(string str);
int bin_to_dec(string bin);

// Исправление ошибки
string correct(string error_string, string sindrom_matrix);

// Декодирование кода Хемминга
string del_bit_even(string str);
string decoder(string coder_str);

#endif