#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Функция для проверки, является ли заданная часть строки суффиксом
bool isSuffix(const string& str, int start, int end)
{
    int suffixLength = end - start + 1;
    for (int i = 0; i < suffixLength; ++i) {
        if (str[i + start] != str[i]) {
            return false;
        }
    }
    return true;
}

// Функция для нахождения длины самого длинного суффикса, который является префиксом
int lengthOfLongestSuffix(const string& str, int position)
{
    int suffixLength = 0;
    int strLength = str.length();
    int i = position;
    int j = strLength - 1;

    while (i >= 0 && str[i] == str[j]) {
        suffixLength++;
        i--;
        j--;
    }

    return suffixLength;
}

// Функция для создания массива правил плохих символов
void generateBadCharacterRule(const string& pattern, vector<int>& badCharacter)
{
    int patternLength = pattern.length();
    badCharacter.resize(256, -1); // Инициализируем массив значением -1

    for (int i = 0; i < patternLength; ++i) {
        badCharacter[pattern[i]] = i;
    }
}

// Функция для создания массива правил хороших суффиксов
void generateGoodSuffixRule(const string& pattern, vector<int>& goodSuffix)
{
    int patternLength = pattern.length();
    int lastPrefixPosition = patternLength;

    for (int i = patternLength - 1; i >= 0; --i) {
        if (isSuffix(pattern, i + 1, patternLength - 1)) {
            lastPrefixPosition = i + 1;
        }
        goodSuffix[i] = lastPrefixPosition + (patternLength - 1 - i);
    }

    for (int i = 0; i < patternLength - 1; ++i) {
        int suffixLength = lengthOfLongestSuffix(pattern, i);
        if (pattern[i - suffixLength] != pattern[patternLength - 1 - suffixLength]) {
            goodSuffix[patternLength - 1 - suffixLength] = patternLength - 1 - i + suffixLength;
        }
    }
}

// Функция для поиска шаблона в тексте с использованием алгоритма Бойера-Мура
int boyerMoore(const string& text, const string& pattern)
{
    int textLength = text.length();
    int patternLength = pattern.length();

    vector<int> badCharacter(256, -1);
    vector<int> goodSuffix(patternLength, 0);

    generateBadCharacterRule(pattern, badCharacter);
    generateGoodSuffixRule(pattern, goodSuffix);

    int shift = 0;
    while (shift <= textLength - patternLength) {
        int mismatchIndex = patternLength - 1;

        while (mismatchIndex >= 0 && pattern[mismatchIndex] == text[shift + mismatchIndex]) {            
            mismatchIndex--;
        }

        if (mismatchIndex < 0) {
            // Совпадение найдено
            return shift;
        } else {
            int badCharacterShift = mismatchIndex - badCharacter[text[shift + mismatchIndex]];
            int goodSuffixShift = 0;

            if (mismatchIndex < patternLength - 1) {
                goodSuffixShift = goodSuffix[mismatchIndex + 1];
            }

            shift += max(badCharacterShift, goodSuffixShift);
        }
    }

    // Совпадение не найдено
    return -1;
}

int main()
{
    cout << "Бойера-Мура. Деревяго. \n ";
    string text, pattern;
    cout << "Введите текст: ";
    getline(cin, text);
    cout << "Введите шаблон: ";
    getline(cin, pattern);

    int result = boyerMoore(text, pattern);

    if (result != -1) {
        cout << "Шаблон найден в позиции " << result << endl;
    } else {
        cout << "Шаблон не найден" << endl;
    }

    return 0;
}
