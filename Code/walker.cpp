#include "walker.h"
#include <cmath>

Walker::Walker() {
}

//поиск старта
coordinates Walker::find_start(vector<vector<char>> maze)
{
    coordinates return_coordinate(0,0);
    for(int i = 0; i < maze.size(); i++){
            for(int j = 0; j < maze[i].size(); j++)
            {
               if(maze[i][j] == element.start)
               {
                   return_coordinate.x = i;
                   return_coordinate.y = j;
               }
            }
        }

    return return_coordinate;
}

//поиск финиша
coordinates Walker::find_finish(vector<vector<char>> maze)
{
    coordinates return_coordinate(0,0);
    for(int i = 0; i < maze.size(); i++){
            for(int j = 0; j < maze[i].size(); j++){

                    if(maze[i][j] == element.finish){
                        return_coordinate.x = i;
                        return_coordinate.y = j;
                    }
            }
        }

    return return_coordinate;
}

//фукнция длины пути
int Walker::length(coordinates a, coordinates b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

//фукнция знака
char Walker::signum(int x, int y)
{
    return (y - x) / abs(y-x);
}
//проверка возможности продолжения пути
bool Walker::can_move(int x, int y, vector<vector<char>> maze)
{
    if(maze[x][y] == element.wall)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//поиск пути
vector<pair<int, int>> Walker::Walking(vector<vector<char>> maze)
{
    coordinates start = find_start(maze);
    coordinates finish = find_finish(maze);


    vector<pair<int, int>> wave;
    vector<pair<int, int>> oldWave;

    oldWave.push_back(pair<int, int>(1,1));

    int nstep = 0;

    int x = maze.size();
    int y = maze[0].size();

    int map[maze.size()][maze[0].size()];

    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            map[i][j] = 0;
        }
    }

    map[start.x][start.y] = nstep;
    const int step_x[] = {-1,  0, 1, 1, 1, 0, -1, -1};
    const int step_y[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    bool old_wave_bool;

    //используем волновой алгоритм
    int ox = start.x;
    int oy = start.y;

    int znak_x = signum(start.x, finish.x);
    int znak_y = signum(start.y, finish.y);

    /*
    while(oldWave.size() > 0)
    {
        ++nstep;
        wave.clear();
        for(vector<pair<int, int>>::iterator i = oldWave.begin(); i !=oldWave.end(); ++i)
        {
            for(int d = 0; d < 4; ++d)
            {
                int nx =  i -> first + step_x[d];
                int ny =  i -> second + step_y[d];
                old_wave_bool = false;
                //проверяем попали ли мы в клетку предедущей волны
                for(vector<pair<int, int>>::iterator j = oldWave.begin(); j !=oldWave.end(); ++j)
                {
                    if(nx == j->first && ny == j ->second)
                    {
                        old_wave_bool = true;
                        break;
                    }
                }
                if(nx == x - 2 && ny == y - 2)
                {
                    goto done;
                }
                if(maze[nx][ny] == element.flour && old_wave_bool == false)
                {
                    wave.push_back(pair<int, int>(nx, ny));
                    map[nx][ny] = nstep;
                }
            }

        }
        if(nstep > 500)
        {
            cout << "not end" << endl;
            break;
        }

        oldWave = wave;
    }*/

    int nx = ox + znak_x;
    int ny = oy + znak_y;
    //движемся пока не финиш
    while(x != finish.x && y != finish.y)
    {
        bool error = false;
        if(error == true)
        {
            cout<<"error"<<endl;
            break;
        }
        if(nx != finish.x)
        {
            nx = ox + znak_x;
        }
        if(ny != finish.y)
        {
            ny = oy + znak_y;
        }
        //если мы пришли к финишу
        if(nx == finish.x && ny == finish.y)
        {
           break;
        }
        //ищем обход стены
        else if(maze[nx][ny] == element.wall)
        {
            bool need_move_bool_down = false;
            bool need_move_bool_up = false;

            int size_up = 0;
            int size_down = 0;

            int up;
            int down;

            while(need_move_bool_down == false)
            {
                down = ny - size_down;
                if(down > y || down < 0)
                {
                    error = true;
                     break;
                }
                if(maze[nx+1][down] == element.wall)
                {
                    size_down++;
                }
                else
                {
                  need_move_bool_down = true;
                }

            }
            while(need_move_bool_up == false)
            {
                up = ny - size_up;
                if(up > y || up < 0)
                {
                    error = true;
                    break;
                }
                if(maze[nx+1][up] == element.wall)
                {
                    size_up++;
                }
                else
                {
                  need_move_bool_up = true;
                }
            }
            if(size_up > size_down)
            {
                nx = up;
                for(int i = up; i < nx; i++)
                {
                    maze[nx+1][i] = element.step;
                }
                //обновляем необходимый путь движения
                znak_x = signum(nx, finish.x);
                znak_y = signum(ny, finish.y);
            }
            else
            {
                for(int i = ny; i < down; i++)
                {
                    maze[nx][i] = element.step;
                }
                nx = down;
            }
        }
        else if(maze[nx][ny] == element.wall)
        {
            bool need_move_bool_down = false;
            bool need_move_bool_up = false;

            int size_up = 0;
            int size_down = 0;

            int up;
            int down;

            while(need_move_bool_down == false)
            {
                down = ny + size_down;
                if(down > y || down < 0)
                {
                    error = true;
                    break;
                }
                if(maze[nx-1][down] == element.wall)
                {
                    size_down++;
                }
                else
                {
                  need_move_bool_down = true;
                }
            }
            while(need_move_bool_up == false)
            {
                up = ny - size_up;
                if(up > y || up < 0)
                {
                    error = true;
                    break;
                }
                if(maze[nx-1][up] == element.flour)
                {
                        size_up++;
                    }
                    else
                    {
                      need_move_bool_up = true;
                    }

            }
            if(size_up > size_down)
            {
                nx = up;
                //обновляем необходимый путь движения
                znak_x = signum(nx, finish.x);
                znak_y = signum(ny, finish.y);
            }
            else
            {
                nx = down;
                //обновляем необходимый вектор движения
                znak_x = signum(nx, finish.x);
                znak_y = signum(ny, finish.y);
            }
        }
        else if(maze[nx][ny] == element.wall)
        {
            bool need_move_bool_left = false;
            bool need_move_bool_right = false;

            int size_left = 0;
            int size_right = 0;

            int left;
            int right;

            while(need_move_bool_left == false)
            {
                left = nx + size_left;
                if(left > x || left < 0)
                {
                    error = true;
                    break;
                }
                if(maze[left][ny] == element.flour)
                {
                    if(maze[left][ny+1] == element.flour)
                    {
                        size_left++;
                    }
                    else
                    {
                      need_move_bool_left = true;
                    }

            }
            while(need_move_bool_right == false)
            {
                right = nx - size_right;
                if(right > x || right < 0)
                {
                    error = true;
                    break;
                }
                if(maze[right][ny] == element.flour)
                {
                    if(maze[right][ny+1] == element.flour)
                    {
                        size_right++;
                    }
                    else
                    {
                      need_move_bool_left = true;
                    }
                }

            }
            if(size_right > size_left)
            {
                for(int i = nx; i < right; i++)
                {
                    maze[i][ny] = element.step;
                }
                nx = right;
                //обновляем необходимый вектор движения
                znak_x = signum(nx, finish.x);
                znak_y = signum(ny, finish.y);
            }
            else
            {
                nx = left;
                for(int i = left; i < nx; i++)
                {
                    maze[i][ny] = element.step;
                }
                //обновляем необходимый вектор движения
                znak_x = signum(nx, finish.x);
                znak_y = signum(ny, finish.y);
            }
            }
        }
        else if(maze[nx][ny] == element.wall)
        {
            bool need_move_bool_left = false;
            bool need_move_bool_right = false;

            int size_left = 0;
            int size_right = 0;

            int left;
            int right;

            while(need_move_bool_left == false)
            {
                left = nx - size_left;
                if(left > x || left < 0)
                {
                    error = true;
                    break;
                }
                if(maze[left][ny] == element.flour)
                {
                    if(maze[left][ny-1] == element.flour)
                    {

                            size_left++;
                        }
                        else
                        {
                          need_move_bool_left = true;
                        }
                    }
            }
            while(need_move_bool_right == false)
            {
                right = nx + size_right;
                if(right > x || right < 0)
                {
                    error = true;
                    break;
                }
                if(maze[right][ny] == element.flour)
                {
                    if(maze[right][ny-1] == element.flour)
                    {
                        size_right++;
                    }
                    else
                    {
                        need_move_bool_left = true;
                    }
                }
            }
            if(size_right > size_left)
            {
                for(int i = nx; i < right; i++)
                {
                    maze[i][ny] = element.step;
                }
                nx = right;
                //обновляем необходимый вектор движения
                znak_x = signum(nx, finish.x);
                znak_y = signum(ny, finish.y);
            }
            else
            {
                for(int i = left; i < nx; i++)
                {
                    maze[i][ny] = element.step;
                }
                nx = left;
                //обновляем необходимый вектор движения
                znak_x = signum(nx, finish.x);
                znak_y = signum(ny, finish.y);
            }
        }
        else if(can_move(nx, ny, maze) == true)
        {
            maze[nx][ny] = element.step;
            ox = nx;
            oy = ny;
        }
        else if(can_move(ox, ny, maze) == true)
        {
            maze[ox][ny] = element.step;
            oy = ny;
        }
        else if(can_move(nx, oy, maze) == true)
        {
            maze[nx][oy] = element.step;
            ox = nx;
        }

    }


    cout << "finish" << endl;
    ofstream maze_file;
    maze_file.open("maze_walk.txt"); // создаём файл для записи матрицы

    //рисуем маршрут в конечном лабиринте
    for(int i = 0; i < maze.size(); i++){
        for(int j = 0; j < maze[i].size(); j++)
        {
            maze_file<<maze[i][j];
        }
        maze_file<<"\n";
    }

    maze_file.close();

    done:/*
        cout<<"finish"<<endl;


        ofstream maze_file;
        maze_file.open("map.txt"); // создаём файл для записи матрицы

        //рисуем маршрут в конечном лабиринт
        for(int i = 0; i < maze.size(); i++){
            for(int j = 0; j < maze[i].size(); j++)
            {
                maze_file<<map[i][j];
            }
            maze_file<<"\n";
        }

        int fin_x = finish.x;
        int fin_y = finish.y;
        wave.clear();
        while(map[fin_x][fin_y] != 0)
        {
            for(int d = 0; d < 8; ++d)
            {
                x = fin_x + step_x[d];
                y = fin_y + step_y[d];

                if((map[x][y] == map[fin_x][fin_y] - 1 || map[x][y] == map[fin_x][fin_y]) && (abs(x - start.x) < (fin_x - start.x) || abs(y - start.y) < (fin_y - start.y)) )
                {
                    x = fin_x;
                    y = fin_y;
                    wave.push_back(pair<int, int>(x, y));
                    break;
                }

            }
        }

        maze_file.close();
*/
     return wave;
}

//выводим результат работы программы в файл
void Walker::printToFIle(vector<vector<char>> maze, vector<pair<int,int>> walk)
{
        ofstream maze_file;
        maze_file.open("maze_walk.txt"); // создаём файл для записи матрицы

        //рисуем маршрут в конечном лабиринте
        //for(vector<pair<int, int>>::iterator i = walk.begin(); i !=walk.end(); ++i)
        //{
            //int x = i -> first;
            //int y = i -> second;
            // maze[x][y] = element.step;
       // }

        for(int i = 0; i < maze.size(); i++){
            for(int j = 0; j < maze[i].size(); j++)
            {
                maze_file<<maze[i][j];
            }
            maze_file<<"\n";
        }

        maze_file.close();
}



//смотрим не попали ли мы в тупик
bool Walker::dead_end_scan(coordinates coord,vector<vector<char>> &maze)
{
    //пришли слева
    if(maze[coord.x-1][coord.y-1] == element.wall
            && maze[coord.x][coord.y-1] == element.wall
            && maze[coord.x+1][coord.y-1] == element.wall
            && maze[coord.x+1][coord.y] == element.wall
            && maze[coord.x+1][coord.y+1] == element.wall
            && maze[coord.x][coord.y+1] == element.wall
            && maze[coord.x-1][coord.y+1] == element.wall)
    {
        return true;
    }
    //пришли слева-сверху
    if(maze[coord.x][coord.y-1] == element.wall
            && maze[coord.x+1][coord.y-1] == element.wall
            && maze[coord.x+1][coord.y] == element.wall
            && maze[coord.x+1][coord.y+1] == element.wall
            && maze[coord.x][coord.y+1] == element.wall
            && maze[coord.x-1][coord.y+1] == element.wall
            && maze[coord.x-1][coord.y] == element.wall)
    {
        return true;
    }
    //пришли сверху
    if(maze[coord.x+1][coord.y-1] == element.wall
            && maze[coord.x+1][coord.y] == element.wall
            && maze[coord.x+1][coord.y+1] == element.wall
            && maze[coord.x][coord.y+1] == element.wall
            && maze[coord.x-1][coord.y+1] == element.wall
            && maze[coord.x-1][coord.y] == element.wall
            && maze[coord.x-1][coord.y-1] == element.wall)
    {
        return true;
    }
    //пришли сверху-справа
    if(maze[coord.x+1][coord.y] == element.wall
            && maze[coord.x+1][coord.y+1] == element.wall
            && maze[coord.x][coord.y+1] == element.wall
            && maze[coord.x-1][coord.y+1] == element.wall
            && maze[coord.x-1][coord.y] == element.wall
            && maze[coord.x-1][coord.y-1] == element.wall
            && maze[coord.x][coord.y-1] == element.wall)
    {
        return true;
    }
    //пришли справа
    if(maze[coord.x+1][coord.y+1] == element.wall
            && maze[coord.x][coord.y+1] == element.wall
            && maze[coord.x-1][coord.y+1] == element.wall
            && maze[coord.x-1][coord.y] == element.wall
            && maze[coord.x-1][coord.y-1] == element.wall
            && maze[coord.x][coord.y-1] == element.wall
            && maze[coord.x+1][coord.y-1] == element.wall)
    {
        return true;
    }
    //пришли справа-снизу
    if(maze[coord.x][coord.y+1] == element.wall
            && maze[coord.x-1][coord.y+1] == element.wall
            && maze[coord.x-1][coord.y] == element.wall
            && maze[coord.x-1][coord.y-1] == element.wall
            && maze[coord.x][coord.y-1] == element.wall
            && maze[coord.x+1][coord.y-1] == element.wall
            && maze[coord.x+1][coord.y] == element.wall)
    {
        return true;
    }
    //пришли снизу
    if(maze[coord.x-1][coord.y+1] == element.wall
            && maze[coord.x-1][coord.y] == element.wall
            && maze[coord.x-1][coord.y-1] == element.wall
            && maze[coord.x][coord.y-1] == element.wall
            && maze[coord.x+1][coord.y-1] == element.wall
            && maze[coord.x+1][coord.y] == element.wall
            && maze[coord.x+1][coord.y+1] == element.wall)
    {
        return true;
    }
    //пришли снизу-слева
    if(maze[coord.x-1][coord.y] == element.wall
            && maze[coord.x-1][coord.y-1] == element.wall
            && maze[coord.x][coord.y-1] == element.wall
            && maze[coord.x+1][coord.y-1] == element.wall
            && maze[coord.x+1][coord.y] == element.wall
            && maze[coord.x+1][coord.y+1] == element.wall
            && maze[coord.x][coord.y+1] == element.wall)
    {
        return true;
    }
    else
    {
        return false;
    }

}
