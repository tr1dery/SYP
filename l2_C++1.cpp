#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;
int main() {
    setlocale(LC_ALL, "Russian");
    string word = "барабан";
    unordered_map<char, int> freq_map;

    // Подсчет частоты символов
    for (char c : word) {
        freq_map[c]++;
    }

    // Поиск максимальной частоты
    int max_freq = 0;
    for (const auto& pair : freq_map) {
        if (pair.second > max_freq) {
            max_freq = pair.second;
        }
    }

    // Вывод символов с максимальной частотой
    vector<char> max_chars;
    for (const auto& pair : freq_map) {
        if (pair.second == max_freq) {
            max_chars.push_back(pair.first);
        }
    }

    cout << "Наиболее часто встречающиеся символы: ";
    for (char c : max_chars) {
        cout << c << " ";
    }
    cout << endl;

    return 0;
}
