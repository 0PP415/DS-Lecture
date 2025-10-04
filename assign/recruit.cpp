#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Student {
    int id;
    int cote;
};

struct CANU {
    string code;
    int size;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int N, k;
    cin >> N >> k;

    unordered_map<string, vector<Student>> datas;

    string code;
    while (N--) {
        cin >> code;
        if (code == "POP") {
            // do query
            int p, q;
            cin >> p >> q;
            
            int total_student = 0;
            vector<CANU> ranked_CANU;

            for (auto& data: datas) {
                int CANU_size = data.second.size();
                if (CANU_size >= k) {
                    ranked_CANU.push_back({data.first, CANU_size});
                }
            }

            // p, q integity check
            if (p < 1 || total_student < q) continue;

            sort(ranked_CANU.begin(), ranked_CANU.end(), [](auto& a, auto& b) {
                if (a.second != b.second) return a.second > b.second;
                else return a.first > b.first;
            });




        } else {
            // add data into map
            int id, cote;
            cin >> id >> cote;
            datas[code].push_back({id, cote});
        }
    }
    return EXIT_SUCCESS;
}
