#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define group vector<vector<int>>

using namespace std;

int main() {
    int N;
    cin >> N;

    group groups(5);
    while (N--) {
        int id, age, idx = 2;
        char sex;
        cin >> id >> age >> sex;

        if (age > 15) idx = sex == 'F' ? 3 : 4;
        if (age > 60) idx = sex == 'M' ? 0 : 1;

        groups[idx].push_back(id);
    }
    
    for(auto g: groups) for(auto i: g) cout << i << endl;
}
