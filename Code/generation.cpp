#include "generation.h"
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>

Generation::Generation()
{

}

//сканируем лабиринт на наличие непроходимых путей
bool scan_maze(char** m, const int i, int j)
{
    int newRow = i - 1;

    maze_type elements;

    //сканируем лабиринт на наличие непреходимых путей
    if (m[newRow][j + 1] == elements.wall && m[newRow][j - 1] == elements.wall || m[newRow][j - 1] == elements.flour && m[newRow][j + 1] == elements.wall)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//генерируем лабиринт
void Generation::Maze_Generator()
{
    int x = 20;
    int y = 22;

    char **maze_write = new char*[x];

    maze_type elements;

    ofstream maze_file;
    maze_file.open("maze.txt"); // создаём файл для записи матрицы

    srand(time(NULL));

    enum STEP {YES, NO};

    for(int i = 0; i < x; i++)
    {
        maze_write[i] = new char[y];
        for(int j = 0; j < y; j++)
        {
            maze_write[i][j] = elements.flour;
            if(rand() % 6 == 0)
            {
               maze_write[i][j] = elements.wall;
            }
        }

    }
    for(int i = 0; i < x; i++)
    {
        maze_write[i][0] = elements.wall;
        maze_write[i][y-1] = elements.wall;
    }
    for(int i = 0; i < y; i++)
    {
        maze_write[0][i] = elements.wall;
        maze_write[x-1][i] = elements.wall;
    }

    int p = 0;
    while(p < (x+y) / 7 )
    {
        int xx = (rand()%(x-1));
        int yy = (rand()%(y-1));

        maze_write[xx][yy] = elements.wall;

        p++;
    }

    bool startstop = false;
    bool start = false;
    while(startstop==false)
    {
            int xx = (rand()%(x-1));
            int yy = (rand()%(y-1));


            if((maze_write[xx][yy] == elements.flour) && (start == false))
            {
                    maze_write[xx][yy] = elements.start;
                    start = true;
            }
            if((maze_write[xx][yy] == elements.flour) && (start == true))
            {
                maze_write[xx][yy] = elements.finish;
                startstop = true;
            }

    }


    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {

            maze_file<<maze_write[i][j];
        }
        maze_file<<"\n";
    }

    for(int i = 0; i < x; i++)
    {
        delete []maze_write[i];
    }
    delete []maze_write;

    cout<<"labirinth has done" << endl;

    maze_file.close();
}

//читаем лабиринт из файла
vector<vector<char>> Generation::Maze_read()
{
    ifstream file;
    vector<vector<char>> return_read;

    file.open("maze.txt");

    if(file.is_open() == false)
    {
        cout<<"file not_found" << endl;
        return return_read;
    }

    string row;
    int i = 0;
    while(file>>row)
    {
        vector<char> read_string;
        return_read.push_back(read_string);
        for(int j = 0; j < row.length(); j++)
        {
            return_read[i].push_back(row[j]);
        }
        i++;
    }
    return return_read;
}
