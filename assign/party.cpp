#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<int> graph[26];
int g_visit[26];

class Friend {
public:
    queue<int> que;
    bool visited[26] = {};

    Friend(int node) {
        que.push(node);
        visited[node] = true;
        g_visit[node]++;
    }

    void takeStep() {
        int queSize = que.size();

        while (queSize--) {
            int curr = que.front();
            que.pop();

            for(int next: graph[curr]) {
                if (!visited[next]) {
                    visited[next] = true;
                    que.push(next);
                    g_visit[next]++;
                }
            }
        }
    }

    bool isDone() {
        return que.empty();
    }
};

int main(void) {
    int N;
    cin >> N;

    char start, dest;

    vector<Friend> friends;
    for (int i = 0; i < 3; i++) {
        cin >> start;
        friends.push_back({start-'a'});
    }

    for (int i = 0; i < N; i++) {
        cin >> start;
        while (cin >> dest && dest != '$') {
            graph[start-'a'].push_back(dest-'a');
        }    
    }

    int time = -2;
    bool done = false;
    while (true) {
        for (int i = 0; i < 26; i++) {
            if (g_visit[i] == 3) {
                cout << static_cast<char>(i+'a') << "\n" << ((time == -2) ? 0 : time) << '\n';
                done = true;
                break;
            }
        }
        if (done) break;
    
        bool isMoved = false;
        for (Friend& f: friends) {
            if (!f.isDone()) {
                f.takeStep();
                isMoved = true;
            }
        }

        if (!isMoved) {
            cout << "@\n-1\n"; 
            break;
        }

        time += 3;
    }

    return EXIT_SUCCESS;
}