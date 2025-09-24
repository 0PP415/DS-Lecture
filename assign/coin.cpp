#include <cstdio>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>

using namespace std;

struct Data {
    int time;
    double value;    
};

struct minMAX {
    double min;
    double max;
};

vector<Data> datas;
vector<minMAX> tree;

minMAX operator + (const minMAX& mm1, const minMAX& mm2) {
    double a = min(mm1.min, mm2.min);
    double b = max(mm1.max, mm2.max);
    
    return {a, b};
}

minMAX tree_init(int start, int end, int index) {
    if (start == end) {
        return tree[index] = {datas[start].value, datas[start].value};
    }
    int mid = (start + end) / 2;
    return tree[index] = tree_init(start, mid, index*2) + tree_init(mid+1, end, index*2 + 1); 
}

minMAX tree_query(int start, int end, int index, int q_begin, int q_end) {
    if (q_begin > end || q_end < start) return {numeric_limits<double>::infinity(),-1.0};

    if (q_begin <= start && end <= q_end) return tree[index];

    int mid = (start + end) / 2;
    return tree_query(start, mid, index*2, q_begin, q_end) + tree_query(mid+1, end, index*2 + 1, q_begin, q_end);

}

int get_index(int time) {
    auto itr = upper_bound(datas.begin(), datas.end(), time, 
        [](int time_val, const Data& data_element) {
            return time_val < data_element.time;
    });

    if (itr == datas.begin()) return 0;
    itr--;

    return itr - datas.begin();
}

int main() {
    FILE* file = fopen("Pitcoin.txt", "r");

    int N;
    int time;
    double value;

    fscanf(file, "%d", &N);
    while (fscanf(file, "%d %lf", &time, &value) == 2) {
        datas.push_back({time, value});
    }
    fclose(file);
    
    tree.resize(N*4);
    tree_init(0, N-1, 1);   

    int M;
    minMAX query_result;
    scanf("%d", &M);

    while (M--) {
        int t_begin, t_end;
        scanf("%d %d", &t_begin, &t_end);

        int i_begin = get_index(t_begin);
        int i_end = get_index(t_end);

        query_result = tree_query(0, N-1, 1, i_begin, i_end);
        printf("%.3lf %.3lf\n", query_result.min, query_result.max);
    }

    return 0;
}
