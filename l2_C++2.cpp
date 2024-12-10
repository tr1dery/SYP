#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;
// Функция для вычисления значения выражения в обратной польской записи
int polsk(const string& expression) 
{
    stack<int> s;

    for (char c : expression) 
    {
        if (isdigit(c)) 
        {
            s.push(c - '0');  // Преобразование символа в число и добавление в стек
        }
        else 
        {
            if (s.size() < 2) 
            {
                cerr << "Ошибка: недостаточно операндов.\n";
                return -1;
            }
            int b = s.top(); 
            s.pop();
            int a = s.top(); 
            s.pop();

            switch (c) 
            {
            case '+': s.push(a + b); break;
            case '-': s.push(a - b); break;
            case '*': s.push(a * b); break;
            case '/':
                if (b != 0) 
                {
                    s.push(a / b);
                }
                else 
                {
                    cerr << "Ошибка: деление на ноль.\n";
                    return -1;
                }
                break;
            default:
                cerr << "Ошибка: неизвестная операция.\n";
                return -1;
            }
        }
    }

    if (s.size() == 1) 
    {
        return s.top();  // Результат - единственный элемент, оставшийся в стеке
    }
    else 
    {
        cerr << "Ошибка: неправильное выражение.\n";
        return -1;
    }
}

int main() 
{
    setlocale(LC_ALL, "Russian");
    string expression = "24+6*";
    int result = polsk(expression);
    cout << "Результат выражения: " << result << endl;
    return 0;
}
