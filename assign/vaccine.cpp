#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define group vector<vector<int>>

#define find_idx(idx, age, sex) \
    do { \
        idx = 2; \
        if (age > 60) idx = sex == 'M' ? 0 : 1; \
        else if (age > 15) idx = sex == 'F' ? 3 : 4; \
    } while (0)

#define print(vec) \
    do { \
        for(auto i: vec) { \
            for(auto j: i) cout << j << endl; \
        } \
    } while (0)

using namespace std;

int main() {
    int N;
    cin >> N;

    group groups(5);
    while (N--) {
        int id, age, idx;
        char sex;
        cin >> id >> age >> sex;

        find_idx(idx, age, sex);
        groups[idx].push_back(id);
    }
    
    print(groups);
}
