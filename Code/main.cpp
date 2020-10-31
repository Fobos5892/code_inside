#include <QCoreApplication>
#include <iostream>
#include "generation.h"
#include "walker.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Generation *gen = new Generation();

        //gen->Maze_Generator();

        Walker *walk = new Walker();

        vector<vector<char>>maze = gen->Maze_read();

        cout<<"maze is read" << endl;
        //vector<pair<int,int>> way =
        walk->Walking(maze);
        if(maze.size() == 0)
        {
            cout<<"sorry program stoped"<<endl;
        }
        else {


            cout<<"walk is done"<< endl;

            //walk->printToFIle(maze);

            cout<<"done"<<endl;
        }


        maze.clear();
        //way.clear();

    return a.exec();
}
