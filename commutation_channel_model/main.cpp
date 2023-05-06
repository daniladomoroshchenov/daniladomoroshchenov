#include "coder_decoder.h"

using namespace std;

int main() {
    string str;
    string polinom = "100101";// порождающий полином - x^5 + x^2 + 1
    string number = "111";// номер по списку - 7

    getline(cin, str);
    
    // Формирование сообщения

    string seq = pseudo_random_seq(polinom, number);
    string encrypted_str = module_add(str_to_bin(str), seq);
    cout << "Encrypted message: " << encrypted_str << endl;

    // Кодирование и отправка сообщения

    string coder_str = coder(encrypted_str);
    cout << "Sent message with Hamming code: " << coder_str << endl;

    // Принятие сообщения

    string error_string = random_error(coder_str);; 
    cout << "Message received with error: " << error_string << endl;

    // Исправление ошибок

    string sindrom_matrix = error_check(error_string);
    string corrected_str = correct(error_string, sindrom_matrix); 
    cout << "Corrected message: " << corrected_str << endl;

    // Декодирование

    string decoder_str = del_bit_even(corrected_str);
    decoder_str = module_add(decoder_str, seq);
    if (str_to_bin(str).length() < seq.length()) {
        decoder_str.erase(0, seq.length() - str_to_bin(str).length());
    }
    cout << "Decoder message: " << decoder(decoder_str) << endl;

    return 0;
}
