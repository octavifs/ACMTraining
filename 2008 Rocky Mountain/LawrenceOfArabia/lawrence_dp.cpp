#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int store[1001][1001];

int lawrence(vector<vector<int> > &permutations, int pos, int cuts) {
    if (!cuts)
        return permutations[pos].back();
    if (store[pos][cuts] != -1)
        return store[pos][cuts];
    int min = numeric_limits<int>::max();
    for (int i = 0; i < (permutations[pos].size() - cuts); ++i)
    {
        if (permutations[pos][i] > min)
            continue;
        int result = permutations[pos][i] + lawrence(permutations, pos + i + 1, cuts -1);
        if (result < min)
            min = result;
    }
    store[pos][cuts] = min;
    return min;
}

int main() {
    for (int i = 0; i < 1001; ++i)
    {
        for (int j = 0; j < 1001; ++j)
        {
            store[i][j] = -1;
        }
    }
    while(true) {
        int depots, attacks;
        cin >> depots >> attacks;
        if (!depots && !attacks)
            break;
        vector<int> depots_array;
        vector<vector<int> > permutations(depots);
        for (int i = 0; i < depots; ++i)
        {
            int value;
            cin >> value;
            depots_array.push_back(value);
        }
        // Init data
        for (int i = 0; i < depots; ++i)
            permutations[i].push_back(0);
        // Calc strategic values
        for (int i = 0; i < depots; ++i)
        {
            for (int j = 1; j < (depots - i); ++j)
            {
                int current = permutations[i][j-1];
                for (int k = i; k < (j + i); ++k)
                    current += depots_array[k] * depots_array[j+i];
                permutations[i].push_back(current);
            }
        }
        cout << lawrence(permutations, 0, attacks) << endl;
        for (int i = 0; i < depots; ++i)
        {
            for (int j = 0; j <= attacks; ++j)
            {
                store[i][j] = -1;
            }
        }
    }
}