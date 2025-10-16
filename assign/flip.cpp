#include <iostream>
#include <set>

#define pixel unsigned long long

using namespace std;

void set_boundary(set<pixel>& flip, pixel boundary) {
    if (flip.count(boundary) == 0) flip.insert(boundary);
    else flip.erase(boundary);
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    pixel N;
    int k;
    cin >> N >> k;

    set<pixel> flip;

    pixel i, j;
    while(k--) {
        cin >> i >> j;
        set_boundary(flip, i);
        set_boundary(flip, j+1);
    }
    
    if (flip.empty()) {
        cout << "0 0\n";
    } else {
        int run = flip.size()/2;
        if (flip.size()%2 != 0) {
            flip.insert(N);
        }
    
        pixel cnt = 0;
        for(auto it = flip.cbegin(); it != flip.cend(); it++) {
            pixel start = *it;
            ++it;
            pixel end   = *it;
            cnt += end - start;
        }

        cout << run << " " << cnt << '\n';
    }

    return EXIT_SUCCESS;
}
