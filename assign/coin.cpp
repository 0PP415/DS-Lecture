#include <cstdio>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct Data {
    int time;
    float value;    
};

struct minMAX {
    float min;
    float max;
};

vector<Data> datas;
vector<minMAX> tree;

minMAX operator + (const minMAX& mm1, const minMAX& mm2) {
    float a = min(mm1.min, mm2.min);
    float b = max(mm1.max, mm2.max);
    
    return {a, b};
}

minMAX tree_init(int start, int end, int index) {
    if (start == end) {
        float tmp = datas[start].value;
        return tree[index] = {tmp, tmp};
    }
    int mid = (start + end) / 2;
    return tree[index] = tree_init(start, mid, index*2) + tree_init(mid+1, end, index*2 + 1); 
}

minMAX tree_query(int start, int end, int index, int q_begin, int q_end) {
    if (q_begin > end || q_end < start) return {numeric_limits<float>::infinity(),-1.0f};

    if (q_begin <= start && end <= q_end) return tree[index];

    int mid = (start + end) / 2;
    return tree_query(start, mid, index*2, q_begin, q_end) + tree_query(mid+1, end, index*2 + 1, q_begin, q_end);

}

int main() {
    FILE* file = fopen("Pitcoin.txt", "r");

    int N;
    int time;
    float value;

    fscanf(file, "%d", &N);
    while (fscanf(file, "%d %f", &time, &value) == 2) {
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

        // query_result = tree_query(0, N-1, 1, begin, end);
        printf("%.3f %.3f\n", query_result.min, query_result.max);
    }

    return 0;
}
