#include <iostream>
#include <vector>

using namespace std;

int main() {
    while(true) {
        int apts, width, length, height, area, openings, openings_area, apt_area, net_area, cans;
        cin >> apts >> width >> length >> height >> area >> openings;
        if (!apts && !width && !length && !height && !area && !openings)
        {
            break;
        }
        apt_area = (2 * width * height) + (2 * length * height) + (width * length);
        openings_area = 0;
        for (int i = 0; i < openings; ++i)
        {
            int w,l;
            cin >> w >> l;
            openings_area += (w * l);
        }
        net_area = apts * (apt_area - openings_area);
        if (net_area % area)
        {
            cans = net_area / area + 1;
        }
        else {
            cans = net_area / area;
        }
        cout << cans << endl;
    }
}