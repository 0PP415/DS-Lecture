#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int K, i, time_points;
    cin >> K;

    vector<pair<int, int>> vertices(K);
    vector<pair<int, int>> move_info(K); 
    
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    for(i = 0; i < K; i++) {
        cin >> vertices[i].first >> vertices[i].second;
    }
    cin >> time_points;
    
    for(int i = 0; i < K; i++) {
        pair<int, int> now  = vertices[i];
        pair<int, int> next = vertices[(i+1)%K];
        
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
    }
    
    int c1_direction = 0; // clock
    int c2_dircetion = 1; // anti-clock


    return EXIT_SUCCESS;
}