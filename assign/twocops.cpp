#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int N;
    cin >> N;

    vector<pair<int, int>> vertices(N);  
    vector<pair<int, int>> move_info(N); 

    int time_point; 
    
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    
    for(int i = 0; i < N; i++) {
        cin >> vertices[i].first >> vertices[i].second;
    }
    cin >> time_point;
    
    int total_distance = 0;
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

    int upper_zone = 0;
    for(int i = 0; i < (N/2)-1; i++) {
        upper_zone += move_info[i].first;
    }
    int lower_zone = total_distance-upper_zone;
    
    lower_zone /= 2;
    lower_zone += upper_zone;
    upper_zone /= 2;

    pair<int, int> ans[2];
    pair<int, int> now = vertices[0];

    int next_move      = 0; 
    int next_distance  = 0;
    int next_direction;   
    
    int remain_distance = time_point % total_distance;

    int index = 0;
    if (upper_zone < remain_distance && remain_distance <= lower_zone) {
        index = 1;
    }
    
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
    ans[index] = now;   

    now = vertices[(N/2)-1];
    next_move      = (N/2)-2; 
    next_distance  = 0;
    next_direction;   
    
    remain_distance = time_point % total_distance;

    if (index) index = 0;
    else index = 1;

    while (remain_distance != 0) {
        if (next_distance == 0) {
            next_distance  = move_info[next_move].first;
            next_direction = move_info[next_move].second;

            if (next_direction == 0 || next_direction == 2) {
                next_direction += 1;
            }
            else {
                next_direction -= 1;
            }

            next_move = (next_move-1+N)%N;
        }
        now.first  += 1 * dx[next_direction];
        now.second += 1 * dy[next_direction];
        next_distance--;
        remain_distance--;
    }
    ans[index] = now;

    cout << ans[0].first << " " << ans[0].second << '\n';
    cout << ans[1].first << " " << ans[1].second << '\n';

    return EXIT_SUCCESS;
}
