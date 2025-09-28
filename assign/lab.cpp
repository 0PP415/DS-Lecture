#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Features {
    int means[6];
    string name;
};


int main(void) {
    int N, k;
    int order[5];
    
    cin >> N >> k;
    cin >> order[0] >> order[1] >> order[2] >> order[3] >> order[4];

    vector<Features> students(N);

    string name;
    int score;
    for(int i = 0; i < N; i++) {
        int attendance = 0;
        int total_score = 0;
        int max_score = -1;
        int min_score = 101;
        int perfect_score = 0;

        cin >> name;
        for(int j = 0; j < k; j++) {
            cin >> score;
            total_score += score;
            if (score == 0) attendance++;
            else if (score == 100) perfect_score++;
            else if (score > max_score) max_score = score;
            else if (score < min_score) min_score = score;
        }

        students[i] = {{0, attendance, total_score, max_score, min_score, perfect_score}, name};
    }

    sort(students.begin(), students.end(), [&](const Features& a, const Features& b) {
        if (a.means[order[0]] != b.means[order[0]]) return a.means[order[0]] < b.means[order[0]];
        if (a.means[order[1]] != b.means[order[1]]) return a.means[order[1]] < b.means[order[1]];
        if (a.means[order[2]] != b.means[order[2]]) return a.means[order[2]] < b.means[order[2]];
        if (a.means[order[3]] != b.means[order[3]]) return a.means[order[3]] < b.means[order[3]];
        if (a.means[order[4]] != b.means[order[4]]) return a.means[order[4]] < b.means[order[4]];
        return a.name < b.name;
    });

    for(auto s: students) {
        cout << s.name << '\n';
    }

    return EXIT_SUCCESS;
}
