#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class GameEntry {
private:
    string name;
    int score;

public:
    GameEntry(const string& n = "", int s = 0) 
    : name(n), score(s) {}
    string getName() const {return name;}
    int getScore() const {return score;}
};

class Scores {
private:
    int maxEntries;
    int numEntries;
    GameEntry* entries;

public:
    Scores(int maxEnt = 10): maxEntries(maxEnt), numEntries(0),
    entries(new GameEntry[maxEnt]) {}
    ~Scores() {delete[] entries;}

    void add(const GameEntry& e) {

    }
    GameEntry remove(const int i) {
        
    }
};



int main(void) {
    double f[5];
    int m[10];
    f[4] = 2.5;
    m[2] = 4;
    cout << f[m[2]];

    double vect[10][20]; // 10 row, 20 col

    int a[]  = {10, 11, 12, 13}; // no need of size
    bool b[] = {false, true};
    char c[] = {'c', 'a', 't'};

    // but in multi-dimension array
    int mat[][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 0, 1, 2},
    };

    // arr[n] == *(arr + n)
    



    return EXIT_SUCCESS;
}