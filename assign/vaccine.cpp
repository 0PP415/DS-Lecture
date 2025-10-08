#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, id, age; 
    cin >> N;
    
    vector<vector<int>> g(5);
    while (N--) {
        char s; 
        cin >> id >> age >> s;

        g[age>60 ? s=='M'?0:1 : age>15 ? s=='F'?3:4 : 2].push_back(id);
    }
    for (auto v:g) for (int x:v) cout << x << endl;
}
