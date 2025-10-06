#pragma once
#include <string>
#include <vector>
#include <stdexcept>

class TableRouteCipher  
{
private:
    int numColumns;

    std::wstring normalize(const std::wstring& text) const;

public:
    explicit TableRouteCipher(int columns);
    std::wstring encrypt(const std::wstring& plaintext) const;
    std::wstring decrypt(const std::wstring& ciphertext) const;
};