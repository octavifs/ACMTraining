#include <iostream>
using namespace std;
int main() {
    while(true) {
        int cal, fat, carb, protein;
        double cal_min, cal_max;
        cin >> cal >> fat >> carb >> protein;
        if (!cal && !fat && !carb && !protein)
            break;
        cal_min = (fat ? fat-0.5 : 0) *9 + (carb ? carb-0.5 : 0) * 4 + (protein ? protein-0.5 : 0) * 4;
        cal_max = (fat+0.5) *9 + (carb+0.5) * 4 + (protein+0.5) * 4;
        if (cal_min <= cal && cal < cal_max)
        {
            cout << "yes" << endl;
        }
        else
        {
            cout << "no" << endl;
        }

    }
}