
#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include <string>
#include <vector>
#include <limits>
#include <stack>
#include <set>
#include <float.h>

#include <QVector>
#include <QDebug>

using namespace std;

typedef pair<int, int> Pair;
typedef pair<double, pair<int, int>> InfoPair;


struct Cell
{
    int parent_i, parent_j;
    double f, g, h; // f = g + h
};


class Path_finder
{
public:
    Path_finder (QVector<QVector<int>> grid);
    QVector<pair<int, int>> aStar(Pair src, Pair dest);

private:
    int maze[31][28];
    int ROW;
    int COL;

    QVector<pair<int, int>> tracePath(Cell cellTraceInfo[][28], Pair dest);

    bool isValidCell(int row, int col);
    bool isNotWall(int row, int col);
    bool isDestination(int row, int col, Pair dest);

    double calculateEuclideanDistance(int row, int col, Pair dest);

    void aStarValidation(Pair src, Pair dest);
    void loggingMessage(string msg) {
        qDebug() << msg;
    }
};

#endif // PATH_FINDER_H
