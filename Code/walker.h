#ifndef WALKER_H
#define WALKER_H

#include <vector>
#include "generation.h"
#include <fstream>

#define WALL false
#define WAY true

using namespace std;

// Нужно, чтобы добавлять координату пути
// В очередь или вектор
struct coordinates {
    int x;
    int y;
    coordinates(int x, int y) : x(x), y(y) {};
};

class Walker
{
public:
    Walker();

    vector<pair<int, int>> Walking(vector<vector<char>>);
    void printToFIle(vector<vector<char>>, vector<pair<int,int>>);

private:
    maze_type element;
    bool dead_end_scan(coordinates,vector<vector<char>> &);

protected:
    char signum(int, int);
    bool can_move(int, int, vector<vector<char>>);
    int length(coordinates, coordinates);
    coordinates find_start(vector<vector<char>>);
    coordinates find_finish(vector<vector<char>>);

};

#endif // WALKER_H
