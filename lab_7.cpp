#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int strongPasswordChecker(string password) { // +N*4
        int n = password.size(); // +4
        bool hasLower = false, hasUpper = false, hasDigit = false; // +1*3=3
        
        // Проверяем наличие строчной буквы, заглавной буквы и цифры
        for (char c : password) { // +4
            if (islower(c)) hasLower = true;
            else if (isupper(c)) hasUpper = true;
            else if (isdigit(c)) hasDigit = true;
        }
        
        // Считаем количество недостающих типов символов
        int missingTypes = (!hasLower) + (!hasUpper) + (!hasDigit); // +4
        
        int replace = 0, oneSeq = 0, twoSeq = 0; // +4*3=12
        
        // Поиск последовательностей из трёх и более одинаковых символов
        for (int i = 2; i < n; ) { // +4
            if (password[i] == password[i - 1] && password[i] == password[i - 2]) {
                int length = 2; // +4
                // Считаем длину текущей последовательности
                while (i < n && password[i] == password[i - 1]) {
                    length++;
                    i++;
                }
                // Количество замен для устранения этой последовательности
                replace += length / 3;
                if (length % 3 == 0) oneSeq++; // Остаток 0: требует минимальных замен
                else if (length % 3 == 1) twoSeq++; // Остаток 1: требует чуть больше замен
            } else {
                i++;
            }
        }
        
        // Если пароль слишком короткий
        if (n < 6) {
            // Нужно добавить символы до минимальной длины, учитывая недостающие типы
            return max(6 - n, missingTypes);
        } else if (n <= 20) {
            // Если длина пароля в пределах нормы, исправляем только повторения и недостающие типы
            return max(replace, missingTypes);
        } else {
            // Если пароль слишком длинный
            int excess = n - 20; // Избыточное количество символов // +4
            
            // Уменьшаем количество замен, удаляя избыточные символы из последовательностей
            replace -= min(excess, oneSeq * 1) / 1; // Убираем из последовательностей с остатком 0
            replace -= min(max(excess - oneSeq, 0), twoSeq * 2) / 2; // Убираем из последовательностей с остатком 1
            replace -= max(excess - oneSeq - 2 * twoSeq, 0) / 3; // Убираем из остальных последовательностей
            
            // Итог: сумма удалений и оставшихся исправлений
            return excess + max(replace, missingTypes);
        }
    }
}; // N*4 + 4 + 3 + 4 + 4 + 12 + 4 + 4 + 4 = N*4 + 39 байт

int main() {
    Solution();
    return 0;
}