#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <vector>

using namespace std;

struct Chunk {
    string name;
    int size;
};

int main(void) {
    int V;
    cin >> V;
    
    int total_free_space = V;
    list<Chunk> disk;
    unordered_map<string, list<list<Chunk>::iterator>> file_table;

    disk.push_back({"", V});

    string cmd, fn;
    int fs;

    while (cin >> cmd && cmd != "end") {
        if (cmd == "write") {
            cin >> fn >> fs;
            
            // 예외 먼저 처리하고 
            if (file_table.count(fn)) {
                cout << "error\n";
                continue;
            }

            if (fs > total_free_space) {
                cout << "diskfull\n";
                continue;
            }

            // toong-gonggan first
            bool is_continue = false;
            for (auto it = disk.begin(); it != disk.end(); ++it) {
                if (it->name == "" && it->size >= fs) {
                    file_table[fn].push_back(disk.insert(it, {fn, fs}));

                    it->size -= fs;                    
                    if (it->size == 0) {
                        disk.erase(it);
                    }

                    total_free_space -= fs;
                    is_continue = true;
                    break;
                }
            }
            if (is_continue) {
                continue;
            }

            // split-saved second
            int remain = fs;
            for (auto it = disk.begin(); it != disk.end(); ) {
                if (remain == 0) break;

                if (it->name == "") {
                    int write = min(remain, it->size);

                    file_table[fn].push_back(disk.insert(it, {fn, write}));

                    it->size -= write;
                    remain -= write;

                    if (it->size == 0) {
                        it = disk.erase(it);
                    } else {
                        ++it;
                    }
                } else {
                    ++it;
                }
            }
            total_free_space -= fs;
        } else if (cmd == "delete") {
            cin >> fn;
            
            // 마찬가지로 예외 처리하고
            if (!file_table.count(fn)) {
                cout << "error\n";
                continue;
            }

            // 포지션끼리 이어놓은거 삭제
            int free_space = 0;
            auto& chunk_iters = file_table[fn];

            for (auto chunk_it : chunk_iters) {
                free_space += chunk_it->size;
                chunk_it->name = "";
            }

            total_free_space += free_space;
            file_table.erase(fn);

            // 근데 A 지우고 바로 B 지우면 쪼개진 빈공간 있을 수 있으니
            // free space 병합
            auto it = disk.begin();
            while (it != disk.end()) {
                auto next_it = next(it);
                
                if (next_it != disk.end() && it->name == "" && next_it->name == "") {
                    it->size += next_it->size;
                    disk.erase(next_it);
                } else {
                    ++it;
                }
            }
        } else if (cmd == "show") {
            cin >> fn;
            
            if (!file_table.count(fn)) {
                cout << "error\n";
                continue;
            }

            // 그냥 disk O(n) 으로 순회하며 출력만 하기 
            int current_size = 0;
            for (auto disk_it = disk.begin(); disk_it != disk.end(); ++disk_it) {
                if (disk_it->name == fn) cout << current_size << " "; 
                current_size += disk_it->size;
            }
            cout << "\n";
        } else if (cmd == "compact") {
            // 일단 빈공간을 지워
            auto it = disk.begin();
            while (it != disk.end()) {
                if (it->name == "") {
                    it = disk.erase(it);
                } else {
                    ++it;
                }
            }

            // 같은 파일(free space도) 합치고
            it = disk.begin();
            while (it != disk.end()) {
                auto next_it = next(it);
                
                if (next_it != disk.end() && it->name == next_it->name) {
                    it->size += next_it->size;
                    disk.erase(next_it);
                } else {
                    ++it;
                }
            }

            // 끝에 빈공간 추가하고
            if (total_free_space > 0) {
                disk.push_back({"", total_free_space});
            }

            // 파일 테이블 갱신
            file_table.clear();
            for (auto it = disk.begin(); it != disk.end(); ++it) {
                if (it->name != "") {
                    file_table[it->name].push_back(it);
                }
            }
        }
    }

    return 0;
}