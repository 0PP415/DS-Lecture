#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct Now {
    int y;
    int x;
};

string qts;
vector<string> img;
int qts_index = 0;

// qts -> img
void decoding(const Now now, const int now_size) {
    char value = qts[qts_index++];
    if (value == '(') {
        int next_size = now_size / 2;
        
        decoding({now.y, now.x}, next_size);
        decoding({now.y, now.x-next_size}, next_size);
        decoding({now.y+next_size, now.x-next_size}, next_size);
        decoding({now.y+next_size, now.x}, next_size);
        qts_index++;
    } else {
        for (int row = 0; row < now_size; row++) {
            for (int col = 0; col < now_size; col++) {
                img[now.y+row][now.x-col] = value;
            }
        }
    }
}

// img -> qts
void encoding(const Now now, const int now_size) {
    if (now_size == 1) {
        qts.push_back(img[now.y][now.x]);
        return;
    }

    bool is_leaf = true;
    int leaf_value = img[now.y][now.x];
    for (int row = 0; row < now_size; row++) {
        if (!is_leaf) break;
        for (int col = 0; col < now_size; col++) {
            if (img[now.y+row][now.x-col] != leaf_value) {
                is_leaf = false;
                break;
            }
        }
    }

    if (is_leaf) {
        qts.push_back(leaf_value);
    } else {
        int next_size = now_size / 2;
    
        qts.push_back('(');
        encoding({now.y, now.x}, next_size);
        encoding({now.y, now.x-next_size}, next_size);
        encoding({now.y+next_size, now.x-next_size}, next_size);
        encoding({now.y+next_size, now.x}, next_size);
        qts.push_back(')');
    }
}

int main(void) {
    int k;
    string sel;

    cin >> k >> sel;

    int mat_size = pow(2, k);
    Now now = {0, mat_size-1}; // y, x

    if (sel == "QTS") {
        cin >> qts;
        img.assign(mat_size, string(mat_size, ' '));

        decoding(now, mat_size);
        for(const string& i: img) {
            for(const char j: i) {
                    cout << j;
            }
            cout << '\n';
        }            
    } else if (sel == "IMG") {
        string row;
        for(int i = 0; i < mat_size; i++) {
            cin >> row;
            img.push_back(row);
        }

        encoding(now, mat_size);
        cout << qts << '\n';
    } 

    return EXIT_SUCCESS;
}
