#include "TableRouteCipher.h"
#include <vector>
#include <algorithm>
#include <stdexcept>

TableRouteCipher::TableRouteCipher(int columns)
{
    if (columns <= 0) {
        throw std::invalid_argument("Количество столбцов должно быть положительным");
    }
    numColumns = columns;
}

std::wstring TableRouteCipher::normalize(const std::wstring& text) const
{
    std::wstring result;
    std::wstring lower = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    std::wstring upper = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

    for (wchar_t c : text) {
        size_t pos = lower.find(c);
        if (pos != std::wstring::npos) {
            result += upper[pos];
        } else if (upper.find(c) != std::wstring::npos) {
            result += c;
        }
    }

    return result;
}

std::wstring TableRouteCipher::encrypt(const std::wstring& plaintext) const
{
    std::wstring cleanText = normalize(plaintext);
    if (cleanText.empty()) {
        throw std::invalid_argument("Текст не содержит допустимых русских букв");
    }

    int len = static_cast<int>(cleanText.length());
    int rows = (len + numColumns - 1) / numColumns;

    // Создаём таблицу, заполняем 'Ъ'
    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(numColumns, L'Ъ'));
    int idx = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < numColumns; ++c) {
            if (idx < len) {
                table[r][c] = cleanText[idx++];
            }
        }
    }

    // Считываем: справа налево, сверху вниз
    std::wstring result;
    for (int c = numColumns - 1; c >= 0; --c) {
        for (int r = 0; r < rows; ++r) {
            result += table[r][c];
        }
    }

    return result;
}

std::wstring TableRouteCipher::decrypt(const std::wstring& ciphertext) const
{
    if (ciphertext.empty()) {
        throw std::invalid_argument("Зашифрованный текст пуст");
    }

    int totalLen = static_cast<int>(ciphertext.length());
    if (totalLen % numColumns != 0) {
        throw std::invalid_argument("Некорректная длина зашифрованного текста");
    }

    int rows = totalLen / numColumns;

    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(numColumns));
    int idx = 0;
    for (int c = numColumns - 1; c >= 0; --c) {
        for (int r = 0; r < rows; ++r) {
            table[r][c] = ciphertext[idx++];
        }
    }

    std::wstring result;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < numColumns; ++c) {
            result += table[r][c];
        }
    }

    // Удаляем все 'Ъ' с конца
    size_t endpos = result.find_last_not_of(L'Ъ');
    if (endpos != std::wstring::npos) {
        result = result.substr(0, endpos + 1);
    } else {
        result.clear(); // вся строка из 'Ъ'
    }

    return result;
}