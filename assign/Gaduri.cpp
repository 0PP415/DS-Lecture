#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.14159265358979;

int main(void) {
    int x1, y1, r1;
    int x2, y2, r2;

    cin >> x1 >> y1 >> r1;
    cin >> x2 >> y2 >> r2;

    double outskirts    = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) - (r2-r1)*(r2-r1));
    double echelon_area = (r1 + r2) * outskirts; 

    double center_angle = atanf(outskirts/abs(r2-r1));

    int r_max = r2, r_min = r1;
    if (r1 > r2) {
        r_max = r1;
        r_min = r2;
    }

    double sector_length1 = r_max * (PI - center_angle);
    double sector_length2 = r_min * center_angle;
    
    double sector_area1 = r_max * sector_length1;
    double sector_area2 = r_min * sector_length2;

    cout << floor(echelon_area + sector_area1 + sector_area2) << ' ';
    cout << floor(2*(outskirts + sector_length1 + sector_length2)) << endl;

    return EXIT_SUCCESS;
}
