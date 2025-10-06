#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main(void) {
    int N;
    cin >> N;

    vector<deque<int>> yards(N);
    
    int container_cnt;
    int container_weight;
    for(int i = 0; i < N; i++) {
        cin >> container_cnt;
        for(int j = 0; j < container_cnt; j++) {
            cin >> container_weight;
            yards[i].push_back(container_weight);
        }
    }
    

    // lets process ~~~
    while (true) {
        // update highest/lowest
        int highest = yards[0].size();
        int lowest  = yards[0].size();
        
        for(auto& yard: yards) {
            int yard_size = yard.size();
            if (yard_size > highest) highest = yard_size;
            if (yard_size < lowest)  lowest  = yard_size;
        }

        // break condition check
        if (highest - lowest <= 1) break;

        // get need to move container (highest and heavier)
        int mv_container_yard;
        int heavier_container = -1;
        for(int i = 0; i < N; i++) {
            if (yards[i].size() == highest) {
                if (yards[i].back() > heavier_container) {
                    mv_container_yard = i;
                    heavier_container = yards[i].back();
                }
            }
        }

        // find target yard (lowest and lower index)
        int target_yard;
        for(int i = 0; i < N; i++) {
            if (yards[i].size() == lowest) {
                target_yard = i;    
                break;
            }
        }

        // pop mv container and push contanier
        yards[mv_container_yard].pop_back();
        yards[target_yard].push_back(heavier_container);

    }
        
    // print result
    for(auto& yard: yards) {
        if (yard.size() == 0) {
            cout << "0\n";
        } else {
            for(int container: yard) {
                cout << container << " ";
            }
            cout << '\n';
        }
    }

    return EXIT_SUCCESS;
}