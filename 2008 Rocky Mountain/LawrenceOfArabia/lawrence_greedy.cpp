// Greedy solution. Faster than the DP one, but not optimal.

#include <iostream>
#include <vector>

using namespace std;

int attack_val(vector<int> &depots_array, int init, int attacks) {
    if (!attacks)
        return 0;
    int max_lost = 0, new_init = init, depots = depots_array.size();
    for (int i = init + 1; i < depots; ++i)
    {
        int lost = 0;
        for (int j = init; j < i; ++j)
            for (int k = i; k < depots; ++k)
                lost += depots_array[j] * depots_array[k];
        if (lost > max_lost) {
            max_lost = lost;
            new_init = i;
        }
    }
    return max_lost + attack_val(depots_array, new_init, attacks - 1);
}

int main() {
    while(true) {
        int depots, attacks;
        cin >> depots >> attacks;
        if (!depots && !attacks)
            break;
        vector<int> depots_array;
        for (int i = 0; i < depots; ++i)
        {
            int value;
            cin >> value;
            depots_array.push_back(value);
        }
        int val = 0;
        for (int i = 0; i < depots; ++i)
            for (int j = i + 1; j < depots; ++j)
                val += depots_array[i] * depots_array[j];
        cout << val - attack_val(depots_array, 0, attacks) << endl;
    }
}