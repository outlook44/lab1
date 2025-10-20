#pragma once
#include <vector>
#include <string>
#include <map>

class modAlphaCipher
{
private:
    std::wstring alphabet;
    std::map<wchar_t, int> charToIndex;
    std::vector<int> key;
    
    std::vector<int> textToIndices(const std::wstring& text) const;
    std::wstring indicesToText(const std::vector<int>& indices) const;
    std::wstring normalizeText(const std::wstring& text) const;
    bool validateText(const std::wstring& text) const; // 

public:
    explicit modAlphaCipher(const std::wstring& key);
    std::wstring encrypt(const std::wstring& plaintext) const;
    std::wstring decrypt(const std::wstring& ciphertext) const;
};