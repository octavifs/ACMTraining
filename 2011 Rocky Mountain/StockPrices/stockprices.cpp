#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>

using namespace std;

bool inv(pair<int,int> lhs, pair<int,int> rhs) {
    return lhs.second < rhs.second;
}

int main() {
    int N, K1, K2, ct=0;
    while(cin >> N >> K1 >> K2 && N && K1 && K2 && ++ct) {
        vector<pair<int, int> > stock(N);
        cout << "Case " << ct << endl;
        for (int i = 0; i < N; ++i)
        {
            cin >> stock[i].first;
            stock[i].second = i+1;
        }
        sort(stock.begin(), stock.end());
        sort(stock.begin(), stock.begin()+K1, inv);
        sort(stock.end()-K2, stock.end(), inv);
        for (int i = 0; i < K1; ++i)
            cout << stock[i].second << " ";
        cout << endl;
        for (int i = N-1; i >= N-K2; --i)
            cout << stock[i].second << " ";
        cout << endl;
    }
}