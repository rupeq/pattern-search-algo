#include <iostream>
#include <string>
#include <vector>

void computePartialMatchTable(const std::string& pattern, std::vector<int>& table) {
    int m = pattern.length();
    table.resize(m);

    table[0] = 0;
    int j = 0, i = 1;
    while (i < m) {
        if (pattern[i] == pattern[j]) {
            j++;
            table[i] = j;
            i++;
        } else {
            if (j != 0) {
                j = table[j - 1];
            } else {
                table[i] = 0;
                i++;
            }
        }
    }
}

void searchPattern(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();

    std::vector<int> table;
    computePartialMatchTable(pattern, table);

    int i = 0, j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            std::cout << "Подстрока найдена под индексом " << i - j << std::endl;
            j = table[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = table[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    std::cout << "КМП. Деревяго. \n ";

    std::string text, pattern;

    std::cout << "Введите текст: ";
    std::getline(std::cin, text);

    std::cout << "Введите шаблон: ";
    std::getline(std::cin, pattern);

    searchPattern(text, pattern);

    return 0;
}
 
