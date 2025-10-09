#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct Customer {
    int id = 0;
    int weight = 0;
};

int main(void) {
    int N, k;
    cin >> N >> k;

    deque<Customer> que;
    vector<Customer> counters(k);

    for(int i = 0; i < N; i++) {
        int id, weight;
        cin >> id >> weight;
        que.push_back({id, weight});
    }

    while(true) {
        int empty_counter = 0;
        for(Customer& counter: counters) {
            if (!que.empty() && counter.weight <= 0) {
                counter = que.front();
                que.pop_front();
            }
        }

        for(int i = k-1; i >= 0; i--) {
            Customer& counter = counters[i];
            counter.weight--;
            if (counter.weight <= 0) {
                if (counter.id) {
                    cout << counter.id << endl;
                    counter.id = 0;
                }
                empty_counter++;
            }
        } 

        if (que.empty() && empty_counter == k) break;
    }

    return EXIT_SUCCESS;
}
