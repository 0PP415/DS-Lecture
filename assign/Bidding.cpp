#include <iostream>
#include <string>
#include <queue>

using namespace std;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, bid;
    string name;
    int bid_occur[10001] = {0,};
    priority_queue<pair<int, string>> bettings;
    
    cin >> N;
    while (N--) {
        cin >> name;
        cin >> bid;

        bettings.push({bid, name});
        bid_occur[bid]++;
    }

    string winner = "NONE";
    while (!bettings.empty()) {
        if (bid_occur[bettings.top().first] > 1) {
            bettings.pop();
        }
        else {
            winner = bettings.top().second;
            break;
        }
    }

    cout << winner << '\n';
    return 0;
}
