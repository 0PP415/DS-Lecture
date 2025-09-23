#include <cstdio>
#include <vector>

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

minMAX operator + (const minMAX& mm1, const minMAX& mm2) {
    float a = min(mm1.min, mm2.min);
    float b = max(mm1.max, mm2.max);
    
    return {a, b};
}

void tree_init() {
    
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
    
    vector<minMAX> tree(N*4);




    return 0;
}