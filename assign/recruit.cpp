#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Student {
    int id;
    int cote;
};

struct Uni {
    vector<Student> students;
    int size = 0;
    int cote_sum = 0;
};


int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int N, k;
    cin >> N >> k;

    unordered_map<string, Uni> datas;

    string code;
    while (N--) {
        cin >> code;
        if (code == "POP") {
            // get query range
            int p, q;
            cin >> p >> q;

            // get canus
            int total_size = 0;
            vector<string> canus;
            for (auto& data: datas) {
                int size = data.second.size;
                if (size >= k) {
                    canus.push_back(data.first);
                    total_size += size;
                }
            }
            
            // p, q range check
            if (total_size < p) continue;
            if (p < 1) p = 1;
            if (total_size < q) q = total_size;

            // canus is empty?
            if (canus.empty()) continue;

            // canus sorting
            sort(canus.begin(), canus.end(), [&](string& a, string& b) {
                if (datas[a].size != datas[b].size) return datas[a].size > datas[b].size;
                else return datas[a].cote_sum > datas[b].cote_sum;
            });

            // each canu sorting
            for (string& canu: canus) {
                sort(datas[canu].students.begin(), datas[canu].students.end(), [](Student& a, Student& b) {
                    if (a.cote != b.cote) return a.cote > b.cote;
                    else return a.id > b.id;
                });
            }

            // get rank vector
            vector<int> rank;
            rank.push_back(-1);
            int max_size = datas[canus[0]].size;
            for (int i = 0; i < max_size; i++) {
                for (string& canu: canus) {
                    vector<Student>& now = datas[canu].students;
                    if (i < now.size()) {
                        rank.push_back(now[i].id);
                    }
                }
            }            

            // get acceptance ids
            vector<int> acceptances;
            for (int i = p; i <= q; i++) {
                acceptances.push_back(rank[i]);
            }

            // pop acceptance at datas.students
            unordered_set<int> removers(acceptances.begin(), acceptances.end());
            for (string& canu: canus) {
                vector<Student>& now = datas[canu].students;
                now.erase(remove_if(now.begin(), now.end(), [&](Student& student) {
                    return removers.count(student.id);
                }), now.end());
            }

            // update datas size/cote_sum info
            for (string& canu : canus) {
                Uni& now_uni = datas[canu];
                now_uni.size = now_uni.students.size();
                
                now_uni.cote_sum = 0;
                for (Student& student : now_uni.students) {
                    now_uni.cote_sum += student.cote;
                }
            }

            // print acceptances
            for(int acceptance: acceptances) {
                cout << acceptance << " ";
            }
            cout << '\n';

        } else {
            // add data into map
            int id, cote;
            cin >> id >> cote;
            datas[code].students.push_back({id, cote});
            datas[code].size += 1;
            datas[code].cote_sum += cote;
        }
    }
    return EXIT_SUCCESS;
}
