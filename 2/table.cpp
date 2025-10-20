#include "table.h"
#include <algorithm>
using namespace std;

Table::Table(int key)
{
    if (key <= 0) throw invalid_argument("Ключ должен быть > 0");
    cols = key;
}

wstring Table::encrypt(const wstring& plain)
{
    if (plain.empty()) throw invalid_argument("Текст не может быть пустым");

    int n = static_cast<int>(plain.length());
    int rows = (n + cols - 1) / cols;

    vector<vector<wchar_t>> grid(rows, vector<wchar_t>(cols, 0));
    int pos = 0;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (pos < n) grid[r][c] = plain[pos++];
        }
    }

    wstring out;
    out.reserve(n);
    for (int c = cols - 1; c >= 0; --c) {
        for (int r = 0; r < rows; ++r) {
            if (grid[r][c] != 0) out += grid[r][c];
        }
    }
    return out;
}

wstring Table::decrypt(const wstring& cipher)
{
    if (cipher.empty()) throw invalid_argument("Текст не может быть пустым");

    int n = static_cast<int>(cipher.length());
    int rows = (n + cols - 1) / cols;
    int k = n % cols;

    vector<vector<wchar_t>> grid(rows, vector<wchar_t>(cols, 0));
    int pos = 0;

    for (int c = cols - 1; c >= 0; --c) {
        int h = rows;
        if (k != 0 && c >= k) h = rows - 1;
        for (int r = 0; r < h; ++r) {
            grid[r][c] = cipher[pos++];
        }
    }

    wstring out;
    out.reserve(n);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] != 0) out += grid[r][c];
        }
    }
    return out;
}