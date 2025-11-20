#include <iostream>
#include <queue>
#include <vector>

using namespace std;

bool grid[25][25];
int dist[25][25][4];

struct State {
    int time;
    int y, x;
    int dir;

    bool operator > (const State& other) const {
        return time > other.time;
    }
};

int main(void) {
    int N, t;
    cin >> N >> t;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }

    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            for(int k=0; k<4; k++)
                dist[i][j][k] = 1e9;

    // 상 하 좌 우
    int dy[] = {1, -1, 0, 0};
    int dx[] = {0, 0, -1, 1};

    priority_queue<State, vector<State>, greater<State>> pq;

    for (int i = 0; i < 4; i++) {
        dist[N-1][0][i] = 0;
        pq.push({0, N-1, 0, i});

    }

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();

        // 메모리제이션
        if (curr.time > dist[curr.y][curr.x][curr.dir]) continue;

        // 직진
        int ny = curr.y + dy[curr.dir];
        int nx = curr.x + dx[curr.dir];
        if (ny >= 0 && ny < N && nx >= 0 && nx < N && grid[ny][nx] == 0) {
            int nt = curr.time + 1;
            if (nt < dist[ny][nx][curr.dir]) {
                dist[ny][nx][curr.dir] = nt;
                pq.push({nt, ny, nx, curr.dir});
            }
        } 

        // 회전
        for(int i = 0; i < 4; i++) {
            if (curr.dir == i) continue;
            
            int nt = curr.time + t;
            if (nt < dist[curr.y][curr.x][i]) {
                dist[curr.y][curr.x][i] = nt;
                pq.push({nt, curr.y, curr.x, i});
            }
        }
    }

    int ans = 1e9;
    for (int i = 0; i < 4; i++) {
        if (dist[0][N-1][i] < ans) ans = dist[0][N-1][i];
    }

    if (ans == 1e9) cout << "-1\n";
    else cout << ans << '\n';

    return EXIT_SUCCESS;
}