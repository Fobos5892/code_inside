#ifndef GENERATION_H
#define GENERATION_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//элемемнты лабиринта
struct maze_type
{
       char wall; //стена
       char flour; //пол
       char start; //начало
       char finish; //конец
       char step; //шаг

       maze_type()
       {
           wall = '#';
           flour = '.';
           start = 'A';
           finish = 'Z';
           step = '+';
       }
};



class Generation
{
public:
    Generation();

    void Maze_Generator();

    vector<vector<char>> Maze_read();
};

#endif // GENERATION_H
