#include <iostream>
#include <string>
using namespace std;
// Функция для проверки монотонности булевой функции
bool isMonotonic(const string& booleanVector) {
    for (size_t i = 0; i < booleanVector.length() - 1; ++i) {
        if (booleanVector[i] > booleanVector[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");

    string booleanVector = "0100011111";
    bool result = isMonotonic(booleanVector);

    if (result) {
        cout << "Булева функция монотонна: true" << endl;
    }
    else {
        cout << "Булева функция не монотонна: false" << endl;
    }

    return 0;
}
