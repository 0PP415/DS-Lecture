#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

struct Node {
    string item;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(const string& item) {
        this->item = item;
    }
};

Node* insert(Node* now, const string& item) {
    if (now == nullptr) {
        now = new Node(item);
        return now;
    }
    
    if (item < now->item) now->left = insert(now->left, item);
    else now->right = insert(now->right, item);

    return now;
}

Node* findMinSuccessor(Node* now) {
    while (now->left != nullptr) now = now->left;
    return now;
}
Node* findMaxSuccessor(Node* now) {
    while (now->right != nullptr) now = now->right;
    return now;
}

Node* remove(Node* bts, const string& item) {
    if (item < bts->item) bts->left = remove(bts->left, item);
    else if (item > bts->item) bts->right = remove(bts->right, item);
    else {
        if (bts->left == nullptr && bts->right == nullptr) {
            delete bts;
            return nullptr;            
        }

        if (bts->left != nullptr) {
            Node* successor = findMaxSuccessor(bts->left);
            bts->item = successor->item;
            bts->left = remove(bts->left, successor->item);
        } 
        else {
            Node* successor = findMinSuccessor(bts->right);
            bts->item = successor->item;
            bts->right = remove(bts->right, successor->item);
        }
    }
    return bts;
}

void getSameDepthItems(const Node* bts, const int depth, const int k, vector<string>& items) {
    if (bts == nullptr) return;

    if (depth == k) {
        items.push_back(bts->item);
        return;
    }

    getSameDepthItems(bts->left, depth+1, k, items);
    getSameDepthItems(bts->right, depth+1, k, items);
}

void printSameDepth(const Node* bts, const int k) {
    vector<string> items;
    getSameDepthItems(bts, 1, k, items);

    if (items.empty()) cout << "NO";
    else {
        for(const string& item: items) cout << item << " ";
    }
}

void printLeaf(const Node* bts) {
    if (bts == nullptr) return;
    
    if (bts->left == nullptr && bts->right == nullptr) {
        cout << bts->item << " ";
        return;
    } 
    printLeaf(bts->left);
    printLeaf(bts->right);
}

int main(void) {
    Node* bts = nullptr;
    unordered_set<string> items;

    string cmd;
    string item;
    int k;
    while (true) {
        cin >> cmd;
        if (cmd == "quit") break;

        if (cmd == "+") {
            cin >> item;
            if (!items.count(item)) {
                bts = insert(bts, item);
                items.insert(item);
            }
        }
        else if (cmd == "-") {
            cin >> item;
            if (items.count(item)) {
                bts = remove(bts, item);
                items.erase(item);
            }
        }
        else if (cmd == "depth") {
            cin >> k;
            printSameDepth(bts, k);
            cout << '\n';
        }
        else if (cmd == "leaf") {
            printLeaf(bts);
            cout << '\n';
        }
    }

    return EXIT_SUCCESS;
}
