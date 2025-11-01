#include <iostream>
#include <string>
#include <list>
#include <unordered_map>

using namespace std;

struct File {
    string name;
    int size;
};

int main(void) {
    int V;
    cin >> V;

    list<File> disk;
    unordered_map<string, list<File>::iterator> file_map;
    int remain = V;

    disk.push_back({"free", V});
    file_map["free"] = prev(disk.end());

    string cmd;
    string fn; // file name
    int fs;    // file size
    while (true) {
        cin >> cmd;
        if (cmd == "end") break;

        if (cmd == "write") {
            cin >> fn >> fs;
            if (file_map.count(fn)) {
                cout << "error\n";
                continue;
            }



        } else if (cmd == "delete") {
            cin >> fn;
        } else if (cmd == "show") {
            cin >> fn;
        } else if (cmd == "compact") {
            
        } else {

        }
        
    }



    return EXIT_SUCCESS;
}