#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct frame {
    string name;
    int index = 0;
};

int main(void) {
    int N, k1, k2;
    cin >> N >> k1 >> k2;

    vector<string> result_seq;
    result_seq.push_back("");

    unordered_map<string, vector<string>> functions;
    unordered_set<string> function_names;
    stack<frame> stk;

    string name;
    string statement;
    for (int i = 0; i < N; i++) {
        cin >> name;
        function_names.insert(name);
        while (true) {
            cin >> statement;
            if (statement == "$") {
                functions[name].push_back("$");
                break;
            } 
            else functions[name].push_back(statement);
        }
    }

    unordered_set<string> stk_tracing;

    stk.push({"M", 0});
    stk_tracing.insert("M");
    while (!stk.empty()) {
        frame& now = stk.top();
        string& statement = functions[now.name][now.index];
        // function call
        if (function_names.count(statement)) {
            if (stk_tracing.count(statement)) {
                cout << "DEADLOCK\n";
                return EXIT_SUCCESS;
            }

            now.index++;
            stk.push({statement, 0});
            stk_tracing.insert(statement);
        } 
        // return
        else if (statement == "$") {
            stk_tracing.erase(now.name);
            stk.pop();
        } 
        // execute
        else {
            now.index++;
            result_seq.push_back(now.name + "-" + statement);
        }
    }

    int seq_size = result_seq.size() - 1;
    k1 += (k1 < 0) * (seq_size + 1);
    k2 += (k2 < 0) * (seq_size + 1);

    if (0 < k1 && k1 <= seq_size) cout << result_seq[k1] << '\n';
    else cout << "NONE\n";

    if (0 < k2 && k2 <= seq_size) cout << result_seq[k2] << '\n';
    else cout << "NONE\n";

    return EXIT_SUCCESS;
}
