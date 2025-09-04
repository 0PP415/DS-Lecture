#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int N;
    cin >> N;

    vector<pair<int, int>> vertices(N);  
    vector<pair<int, int>> move_info(N); 
    int total_distance = 0;
    int time_points[5]; 

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    
    for(int i = 0; i < N; i++) {
        cin >> vertices[i].first >> vertices[i].second;
    }
    for(int i = 0; i < 5; i++) {
        cin >> time_points[i];
    }
    
    for(int i = 0; i < N; i++) {
        pair<int, int> now  = vertices[i];
        pair<int, int> next = vertices[(i+1)%N];
        
        int distance = next.second - now.second;
        int direction = 0;

        if (distance == 0) { 
            distance = next.first - now.first;
            direction += 2;
        }

        if (distance < 0) {
            distance  *= -1;    
            direction +=  1;
        }

        move_info[i] = {distance, direction};
        total_distance += distance;
    }

    for(const int time: time_points) {
        pair<int, int> now = vertices[0];
        int next_move      = 0; 
        int next_distance  = 0;
        int next_direction;   
        
        int remain_distance = time % total_distance;
        
        while (remain_distance != 0) {
            if (next_distance == 0) {
                next_distance  = move_info[next_move].first;
                next_direction = move_info[next_move].second;
                next_move++;
            }
            now.first  += 1 * dx[next_direction];
            now.second += 1 * dy[next_direction];
            next_distance--;
            remain_distance--;
        }
        cout << now.first << " " << now.second << '\n';
    }

    return EXIT_SUCCESS;
}
