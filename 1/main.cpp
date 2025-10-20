#include <iostream>
#include <string>
#include <locale>
#include <cstdlib>
#include "modAlphaCipher.h"


std::wstring utf8ToWstring(const std::string& str)
{
    if (str.empty()) return std::wstring();
    
    std::vector<wchar_t> buffer(str.size() + 1);
    int size = std::mbstowcs(buffer.data(), str.c_str(), str.size());
    if (size < 0) {
        throw std::runtime_error("Ошибка преобразования UTF-8 в wide string");
    }
    return std::wstring(buffer.data(), size);
}

std::string wstringToUtf8(const std::wstring& wstr)
{
    if (wstr.empty()) return std::string();
    
    std::vector<char> buffer(wstr.size() * 4 + 1);
    int size = std::wcstombs(buffer.data(), wstr.c_str(), buffer.size());
    if (size < 0) {
        throw std::runtime_error("Ошибка преобразования wide string в UTF-8");
    }
    return std::string(buffer.data(), size);
}

int main()
{
    std::locale::global(std::locale(""));
    std::cout.imbue(std::locale());
    std::cin.imbue(std::locale());

    std::cout << "Шифр для русского языка\n";
    
    std::cout << "Введите ключ: ";
    std::string keyInput;
    std::getline(std::cin, keyInput);
    
    try {
        std::wstring key = utf8ToWstring(keyInput);
        modAlphaCipher cipher(key);
        std::cout << "Ключ получен!\n\n";
        
        unsigned int choice;
        while (true) {
            std::cout << "Выберите операцию:\n";
            std::cout << "0 - Выход\n";
            std::cout << "1 - Зашифровать\n";
            std::cout << "2 - Расшифровать\n";
            std::cout << "Ваш выбор: ";
            
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Неверный ввод! Попробуйте снова.\n\n";
                continue;
            }
            
            std::cin.ignore();
            
            if (choice == 0) {
                std::cout << "До свидания!\n";
                break;
            }
            
            if (choice != 1 && choice != 2) {
                std::cout << "Неверный выбор! Используйте 0, 1 или 2.\n\n";
                continue;
            }
            
            std::cout << "Введите текст: ";
            std::string textInput;
            std::getline(std::cin, textInput);
            
            std::wstring text = utf8ToWstring(textInput);
            
            try {
                if (choice == 1) {
                    std::wstring encrypted = cipher.encrypt(text);
                    std::cout << "Зашифрованный текст: " << wstringToUtf8(encrypted) << "\n\n";
                } else {
                    std::wstring decrypted = cipher.decrypt(text);
                    std::cout << "Расшифрованный текст: " << wstringToUtf8(decrypted) << "\n\n";
                }
            }
            catch (const std::exception& e) {
                std::cout << "Ошибка при обработке текста: " << e.what() << "\n\n";
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
