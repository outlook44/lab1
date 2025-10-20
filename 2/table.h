#pragma once
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

class Table
{
private:
    int cols;
public:
    explicit Table(int key);
    wstring encrypt(const wstring& plain);
    wstring decrypt(const wstring& cipher);
};