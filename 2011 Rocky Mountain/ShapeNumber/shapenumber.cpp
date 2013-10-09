#include <iostream>
#include <vector>

using namespace std;

// Booth's algorithm
// From http://en.wikipedia.org/wiki/Lexicographically_minimal_string_rotation
inline int LCS(string &S) {
    int n = S.length();
    S += S; // Concatenate string to self to avoid modular arithmetic
    vector<int> f(2*n, -1);
    int k = 0;  // Least rotation of string found so far
    for (int j = 1; j < 2*n; ++j) {
        int i = f[j-k-1];
        while(i != -1 && S[j] != S[k+i+1]) {
            if (S[j] < S[k+i+1])
                k = j-i-1;
            i = f[i];
        }
        if (i == -1 && S[j] != S[k+i+1]) {
            if (S[j] < S[k+i+1])
                k = j;
            f[j-k] = -1;
        } else
            f[j-k] = i+1;
    }
    return k;
}

int main() {
    string code;
    while (cin >> code) {
        short int diff;
        string difference(code);
        int len = code.length();
        for (int i = 0; i < len; ++i)
        {
            diff = (code[(i+1) % len] - code[i]) % 8;
            diff = (diff < 0) ? 8+diff : diff;
            difference[i] = '0' + diff;
        }
        int pos = LCS(difference);
        for (int i = pos; i < (pos + len); ++i)
            cout << difference[i];
        cout << endl;
    }
}