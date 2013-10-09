#include <iostream>

using namespace std;

long long int P[31][31];

long long int pills(int H, int W) {
    if (P[H][W] != -1)
        return P[H][W];
    long long int sol;
    if (!W)
        sol = 1;
    else if (!H)
        sol = pills(H+1, W-1);
    else
        sol = pills(H-1, W) + pills(H+1, W-1);
    P[H][W] = sol;
    return sol;
}

int main() {
    for (int i = 0; i < 31; ++i)
        for (int j = 0; j < 31; ++j)
            P[i][j] = -1;
    int N;
    while(cin >> N && N)
        cout << pills(0, N) << endl;
}
