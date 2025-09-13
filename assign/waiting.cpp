#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
    int N, k;
    cin >> N >> k;

    vector<vector<int>> waitroom;
    int num_occur[10001] = {0,};

    char cmd;
    int  number;
    while (N--) {
        // for (const vector<int> chair: waitroom) {
        //     for (const int num: chair) {
        //         cout << num << ' ';
        //     }
        //     cout << '\n';
        // }
        
        cin >> cmd >> number;
        if (cmd == '+') {
            num_occur[number] = 1;

            if (waitroom.empty()) {
                waitroom.push_back(vector<int>());
                waitroom[0].push_back(number);
                continue;
            }

            int chair = 0;
            for (int i = 0; i < waitroom.size(); i++) {
                if (number >= waitroom[i][0]) {
                    chair = i;
                }
                else break;
            }
            waitroom[chair].push_back(number);
            sort(waitroom[chair].begin(), waitroom[chair].end());

            if (waitroom[chair].size() >= 2*k) {
                waitroom.insert(waitroom.begin() + chair + 1, vector<int>(k));
                for (int i = k-1; i >= 0 ; i--) {
                    waitroom[chair+1][i] = waitroom[chair][i+k];
                    waitroom[chair].pop_back();
                }
            }            
        }
        else {
            if (!num_occur[number]) continue;

            int chair = 0;
            for (int i = 0; i < waitroom.size(); i++) {
                if (number >= waitroom[i][0]) {
                    chair = i;
                }
                else break;
            }

            waitroom[chair].erase(
                remove(waitroom[chair].begin(), waitroom[chair].end(), number)
            );

            if (waitroom[chair].empty()) {
                waitroom.erase(waitroom.begin() + chair);
            }

            num_occur[number] = 0;
        }
    }

    for (const vector<int> chair: waitroom) {
        cout << chair[0] << '\n';
    }

    return EXIT_SUCCESS;
}