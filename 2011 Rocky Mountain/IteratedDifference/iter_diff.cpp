#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    int A[20];
    int N;
    int cse = 0;
    while(cin >> N && N && ++cse) {
        bool isEqual = true;
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
            if (isEqual)
                isEqual = (A[0] == A[i]);
        }
        if (isEqual) {
            cout << "Case " << cse << ": 0 iterations\n";
            continue;
        }
        for (int i = 1; i <= 1000; ++i)
        {
            isEqual = true;
            int firstPos = A[0];
            for (int j = 0; j < N; ++j) {
                int seg = ((j+1)%N) ? A[j+1] : firstPos;
                A[j] = abs(A[j] - seg);
                if (isEqual)
                    isEqual = (A[0] == A[j]);
                cout << A[j] << " ";
            }
            cout << "\n";
            if (isEqual) {
                cout << "Case " << cse << ": " << i << " iterations\n";
                break;
            }
        }
        if (!isEqual)
            cout << "Case " << cse << ": not attained\n";
    }
}