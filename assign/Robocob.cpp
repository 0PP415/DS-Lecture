#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int N;
    vector<pair<int, int>> vertices;  
    vector<pair<int, int>> move_info; 
    int time_points[5]; 
    int max_time = 0; 
    
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    
    cin >> N;
    for(int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        vertices.push_back({x, y});
    }
    for(int i = 0; i < 5; ++i) {
        cin >> time_points[i];
        if (time_points[i] > max_time) {
            max_time = time_points[i];
        }
    }
    
    for(int i = 0; i < N; ++i) {
        pair<int, int> now  = vertices[i];
        pair<int, int> next = vertices[(i+1)%N];
        
        int distance;
        int direction = 0;

        if ((next.first - now.first) != 0) { 
            distance = next.first - now.first;
            direction += 2;
        }
        else {
            distance = next.second - now.second;
        }

        if (distance < 0) {
            distance  *= -1;    
            direction +=  1;
        }

        move_info.push_back({distance, direction});
    }

    pair<int, int> now = vertices.front();
    int next_move = 0; 
    int distance  = 0;
    int direction;   

    pair<int, int> answers[5];

    for(int now_time = 0; now_time <= max_time; ++now_time) {
        for(int i = 0; i < 5; i++) {
            if (time_points[i] == now_time) {
                answers[i] = now;
            }
        }
        if (distance == 0) {
            distance  = move_info[next_move].first;
            direction = move_info[next_move].second;
            next_move = (next_move+1)%N;
        }
        now.first  += 1 * dx[direction];
        now.second += 1 * dy[direction];
        distance   -= 1;
    }

    for(const pair<int, int> answer: answers) {
        cout << answer.first << ' ' << answer.second << '\n';
    }

    return EXIT_SUCCESS;
}
