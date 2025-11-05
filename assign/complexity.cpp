#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    char c;
    vector<char> block;
    while (cin.get(c)) {
        if (c == '{' || c == '}') block.push_back(c);
    }

    int res = 0;
    int depth = 0;
    for(char ch: block) {
        if (ch == '{') res += ++depth;
        else depth--;
    }

    cout << res;
    return EXIT_SUCCESS;
}
