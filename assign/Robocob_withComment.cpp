#include <iostream>
#include <vector>

using namespace std;

/* 
매순간 현재위치를 갱신하는
시뮬레이션 방식으로 구현하는게
적절히 효율적이고 단순할 거 같다 (아마,,,)
*/

int main(void) {
    int N;
    vector<pair<int, int>> vertices;  // 경계면의 꼭짓점 x, y 좌표 저장
    vector<pair<int, int>> move_info; // 거리, 방향 저장
    int time_points[5]; // 시점은 5개로 고정됨
    int max_time = 0;   // 마지막에서 최대 시간까지 탐색하기 위해 저장
    
    // 상하좌우 dx dy
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    
    // 일단 입력 받고
    cin >> N;
    for(int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        vertices.push_back({x, y});
    }
    for(int i = 0; i < 5; ++i) {
        cin >> time_points[i];
        // 시간 최댓값 갱신
        if (time_points[i] > max_time) {
            max_time = time_points[i];
        }
    }
    
    // 저장한 꼭짓점 정보를 거리와 방향의 정보로 바꿔 저장하자
    for(int i = 0; i < N; ++i) {
        pair<int, int> now  = vertices[i];
        pair<int, int> next = vertices[(i+1)%N];
        
        int distance;
        int direction;

        // x 방향으로 움직이는 경우
        if ((next.first - now.first) != 0) { 
            distance = next.first - now.first;
            if (distance > 0) direction = 2;
            else {
                distance *= -1;
                direction =  3;
            }
        }
        // y 방향으로 움직이는 경우
        else {
            distance = next.second - now.second;
            if (distance > 0) direction = 0;
            else {
                distance *= -1;
                direction =  1;
            }
        }
        // 이동 정보 완성해서 저장
        move_info.push_back({distance, direction});
    }

    /*
    현재 위치, 다음 지점까지 남은 거리, 가야하는 방향 저장해두고
    계속 진행하면서 현재 지점 갱신
    만약 확인할 시점이라면 현재 위치를 저장해두고
    만약 거리가 0이라면 지점에 도착한 것이므로 다음 이동 정보 갱신
    이를 반복하자
    */

    pair<int, int> now = vertices.front(); // 현재위치
    int next_move = 0; // 다음 이동 정보 인덱스
    int distance  = 0; // 다음 지점까지 남은 거리
    int direction;     // 가야하는 방향

    pair<int, int> answers[5];

    for(int now_time = 0; now_time <= max_time; ++now_time) {
        /*
        정답 저장이 시간순이 아니라 입력 받은 순서이다
        반복마다 5번을 더 돌긴 하지만,,,,, 어쩔 수 있나?
        문제에서 t의 범위가 안 주어져 있긴 하지만
        시간복잡도에는 영향을 주진 않으니 괜찮을 거 같다는 생각이 들긴 한다.
        */
        for(int i = 0; i < 5; i++) {
            if (time_points[i] == now_time) {
                answers[i] = now;
            }

        }
        // 이동 정보 갱신
        if (distance == 0) {
            distance  = move_info[next_move].first;
            direction = move_info[next_move].second;

            next_move = (next_move+1)%N;
        }
        // 이동
        now.first  += 1 * dx[direction];
        now.second += 1 * dy[direction];
        distance   -= 1;
    }
    
    // 정답 출력으로 마무리
    for(const pair<int, int> answer: answers) {
        cout << answer.first << ' ' << answer.second << '\n';
    }

    return EXIT_SUCCESS;
}