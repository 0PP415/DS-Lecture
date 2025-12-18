#include <cstdio>
#include <stdint.h>
#include <unordered_set>

using namespace std;

#define PUSH(t, c) t = ((t << 3) + (t << 1)) + (c & 0x0F)

#define PARSE(buf, K, H) do { \
    K = 0; H = 0; \
    PUSH(H, buf[0]); PUSH(H, buf[1]); \
    PUSH(K, buf[2]); PUSH(K, buf[3]); PUSH(K, buf[4]); PUSH(K, buf[5]); \
    \
    PUSH(H, buf[6]); PUSH(H, buf[7]); \
    PUSH(K, buf[8]); PUSH(K, buf[9]); PUSH(K, buf[10]); PUSH(K, buf[11]); \
    \
    PUSH(H, buf[12]); PUSH(H, buf[13]); \
    PUSH(K, buf[14]); PUSH(K, buf[15]); PUSH(K, buf[16]); PUSH(K, buf[17]); \
    \
    PUSH(H, buf[18]); PUSH(H, buf[19]); \
} while (0)


#define HM 100000000
unsigned long PNUhash(unsigned long long x, int salt) {
    x = x + salt ;
    x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
    x = x ^ (x >> 31);
    return x%HM;
}

int main(void) {
    int N;
    long long salt;
    scanf("%d %lld", &N, &salt);

    char buf[21];
    unsigned long long K, H;

    unordered_set<unsigned long long> isUsed;
    isUsed.reserve(N);
    
    int valid   = 0;
    int invalid = 0;
    int used    = 0;

    for (int i = 0; i < N; i++) {
        scanf("%s", buf);
        PARSE(buf, K, H);

        if (PNUhash(K, salt) != H) invalid++;
        else {
            if (isUsed.insert(K).second) valid++;
            else used++;
        }
    }

    printf("%d\n%d\n%d\n", valid, invalid, used);

    return 0;
}
