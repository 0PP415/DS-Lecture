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
    int cote_sum;
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
            
            int CANU_cnt = 0;
            int total_student = 0;
            vector<CANU> ranked_CANU;

            for (auto& data: datas) {
                int CANU_size = data.second.size();
                if (CANU_size >= k) {
                    CANU_cnt += 1;
                    total_student += CANU_size;

                    int cote_sum = 0;
                    for (auto& item: data.second) {
                        cote_sum += item.cote;
                    }
                    ranked_CANU.push_back({data.first, CANU_size, cote_sum});
                }
            }

            // p, q integity check
            if (p < 1 || total_student < q) continue;

            sort(ranked_CANU.begin(), ranked_CANU.end(), [](CANU& a, CANU& b) {
                if (a.size != b.size) return a.size > b.size;
                else return a.cote_sum > b.cote_sum;
            });

            for (CANU& item: ranked_CANU) {
                sort(datas[item.code].begin(), datas[item.code].end(), [](Student& a, Student& b) {
                    if (a.cote != b.cote) return a.cote > b.cote;
                    else return a.id > b.id;
                });
            }

            



        } else {
            // add data into map
            int id, cote;
            cin >> id >> cote;
            datas[code].push_back({id, cote});
        }
    }
    return EXIT_SUCCESS;
}
