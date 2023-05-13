
#include <iostream>
#include <string>
int bruteForceSearch(std::string str, std::string substr) {
    std::size_t i = 0, j = 0; // Инициализация индексов
    while (i < str.size() && j < substr.size()) {
        if (str[i] == substr[j]) { // Символы совпадают, продолжаем поиск
            i++;
            j++;
        } else { // Символы не совпадают, переходим к следующему символу в строке
            i = i - j + 1; // Смещаем i на j позиций + 1
            j = 0; // Сбрасываем индекс j
        }
    }
    if (j == substr.size()) { // Найдена подстрока
        return i - j;
    } else { // Подстрока не найдена
        return -1;
    }
}
int main() {
    std::cout << "Полный перебор. Деревяго. \n ";
    std::string text, pattern;
    std::cout << "Введите текст: ";
    std::getline(std::cin, text);
    std::cout << "Введите шаблон: ";
    std::getline(std::cin, pattern);
    int pos = bruteForceSearch(text, pattern);
    if (pos != -1) {
        std::cout << "Подстрока найдена в позиции " << pos << std::endl;
    } else {
        std::cout << "Подстрока не найдена" << std::endl;
    }
    return 0;
}
