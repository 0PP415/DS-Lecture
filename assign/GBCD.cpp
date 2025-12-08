#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

int main(void) {
    char cmd;
    int item;
    map<set<int>, set<int>> m;

    while (true) {
        cin >> cmd;
        if (cmd == '$') break;

        if (cmd == 'R') {
            set<int> s;
            while (true) {
                cin >> item;
                if (item < 0) break;
                s.insert(item);
            }            
            m[s].insert(item * -1);

        } else if (cmd == 'Q') {
            set<int> s;
            while (true) {
                cin >> item;
                if (item == 0) break;
                s.insert(item);
            }
            if (m.count(s)) {
                for(int i: m[s]) {
                    cout << i*-1 << " ";
                }
                cout << '\n';
            } else {
                cout << "None\n";
            }
        }
    }

    return EXIT_SUCCESS;
}