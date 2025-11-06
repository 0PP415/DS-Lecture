#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct node {
    string name;
    int depth;
    int childs;

    node(const string& name, const int depth, const int childs) 
    : name(name), depth(depth), childs(childs) {}
};

vector<node> order;
unordered_map<string, vector<string>> tree;

int dfs(const string& now, const int depth) {
    int childs = 0;
    if (tree[now].empty()) {
        order.emplace_back(now, depth, childs);
        return childs;
    };

    for(const string& child: tree[now]) {
        childs += 1 + dfs(child, depth+1);
    }

    order.emplace_back(now, depth, childs);
    return childs;
}

int main(void) {
    int N;
    cin >> N;

    string person, boss, root;
    unordered_set<string> persons;
    for(int i = 0; i < N-1; i++) {
        cin >> person >> boss;
        
        if (!tree.count(person)) tree[person];
        tree[boss].push_back(person);
        persons.insert(person);
    }

    for(const pair<string, vector<string>>& rank: tree) {
        if (!persons.count(rank.first)) {
            root = rank.first;
            break;
        }
    }

    dfs(root, 0);

    sort(order.begin(), order.end(), [](const node& a, const node& b) {
        if (a.childs != b.childs) return a.childs > b.childs;
        else if (a.depth != b.depth) return a.depth < b.depth;
        else return a.name < b.name;
    });

    for(const node& item: order) {
        cout << item.name << '\n';
    }

    return EXIT_SUCCESS;
}