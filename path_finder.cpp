#include <path_finder.h>


QVector<pair<int, int>> Path_finder::tracePath(Cell cellTraceInfo[][28], Pair dest){
    QVector<pair<int, int>> output;
    int row = dest.first;
    int col = dest.second;

    stack<Pair> Path;
    while (!(cellTraceInfo[row][col].parent_i == row
             && cellTraceInfo[row][col].parent_j == col))
    {
        Path.push(make_pair(row, col));
        int tr = cellTraceInfo[row][col].parent_i;
        int tc = cellTraceInfo[row][col].parent_j;
        row = tr;
        col = tc;
    }

    Path.push(make_pair(row, col));

    while (!Path.empty())
    {
        pair<int, int> p = Path.top();
        Path.pop();

        output.push_back(p);
    }

    return output;
}

bool Path_finder::isValidCell(int row, int col){
    return (row >= 0) && (row < ROW) && (col >= 0)
           && (col < COL);
}

bool Path_finder::isNotWall(int row, int col){
    if (maze[row][col] == 1)
        return (true);
    else
        return (false);
}

bool Path_finder::isDestination(int row, int col, Pair dest){
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}

double Path_finder::calculateEuclideanDistance(int row, int col, Pair dest) {
        return ((double)sqrt(
            (row - dest.first) * (row - dest.first)
            + (col - dest.second) * (col - dest.second)));
}

void Path_finder::aStarValidation(Pair src, Pair dest) {
    if (isValidCell(src.first, src.second) == false) {
            loggingMessage("Source is invalid\n");
            return;
    }

    if (isValidCell(dest.first, dest.second) == false) {
            loggingMessage("Destination is invalid\n");
            return;
    }

    if (isNotWall(src.first, src.second) == false
        || isNotWall(dest.first, dest.second)
               == false) {
            loggingMessage("Source or the destination is blocked\n");
            return;
    }
}

Path_finder::Path_finder (QVector<QVector<int>> grid){
    ROW = 31;
    COL = 28;

    for (int i = 0; i < grid.size(); i++)
    {
            for (int j = 0; j < grid[i].size(); j++)
            {
                maze[i][j] = grid[i][j];
            }
    }
}

QVector<pair<int, int>> Path_finder::aStar(Pair src, Pair dest){
    aStarValidation(src, dest);

    if (isDestination(src.first, src.second, dest)
        == true)
    {
            loggingMessage("We are already at the destination\n");

            QVector<pair<int, int>> output;
            output.push_back(make_pair(dest.first, dest.second));
            return output;
    }

    bool closedList[31][28];
    memset(closedList, false, sizeof(closedList));

    Cell cellTraceInfo[31][28];
    int i, j;

    for (i = 0; i < ROW; i++)
    {
            for (j = 0; j < COL; j++)
            {
                cellTraceInfo[i][j].f = FLT_MAX;
                cellTraceInfo[i][j].g = FLT_MAX;
                cellTraceInfo[i][j].h = FLT_MAX;
                cellTraceInfo[i][j].parent_i = -1;
                cellTraceInfo[i][j].parent_j = -1;
            }
    }

    i = src.first, j = src.second;
    cellTraceInfo[i][j].f = 0.0;
    cellTraceInfo[i][j].g = 0.0;
    cellTraceInfo[i][j].h = 0.0;
    cellTraceInfo[i][j].parent_i = i;
    cellTraceInfo[i][j].parent_j = j;

    set<InfoPair> openList;
    openList.insert(make_pair(0.0, make_pair(i, j)));

    bool foundDest = false;

    while (!openList.empty())
    {
            InfoPair p = *openList.begin();
            openList.erase(openList.begin());

            i = p.second.first;
            j = p.second.second;
            closedList[i][j] = true;

            double gNew, hNew, fNew;

            if (isValidCell(i-1, j) == true)
            {
                if (isDestination(i-1, j, dest) == true)
                {
                    cellTraceInfo[i - 1][j].parent_i = i;
                    cellTraceInfo[i - 1][j].parent_j = j;
                    loggingMessage("The destination cell is found\n");
                    return tracePath(cellTraceInfo, dest);
                }
                else if (closedList[i - 1][j] == false
                         && isNotWall(i - 1, j)
                                == true)
                {
                    gNew = cellTraceInfo[i][j].g + 1.0;
                    hNew = calculateEuclideanDistance(i - 1, j, dest);
                    fNew = gNew + hNew;

                    if (cellTraceInfo[i - 1][j].f == FLT_MAX
                        || cellTraceInfo[i - 1][j].f > fNew)
                    {
                        openList.insert(make_pair(
                            fNew, make_pair(i - 1, j)));

                        cellTraceInfo[i - 1][j].f = fNew;
                        cellTraceInfo[i - 1][j].g = gNew;
                        cellTraceInfo[i - 1][j].h = hNew;
                        cellTraceInfo[i - 1][j].parent_i = i;
                        cellTraceInfo[i - 1][j].parent_j = j;
                    }
                }
            }

            if (isValidCell(i+1, j) == true)
            {
                if (isDestination(i+1, j, dest) == true)
                {
                    cellTraceInfo[i + 1][j].parent_i = i;
                    cellTraceInfo[i + 1][j].parent_j = j;
                    loggingMessage("The destination cell is found\n");
                    return tracePath(cellTraceInfo, dest);
                }
                else if (closedList[i + 1][j] == false
                         && isNotWall(i + 1, j)
                                == true)
                {
                    gNew = cellTraceInfo[i][j].g + 1.0;
                    hNew = calculateEuclideanDistance(i + 1, j, dest);
                    fNew = gNew + hNew;

                    if (cellTraceInfo[i + 1][j].f == FLT_MAX
                        || cellTraceInfo[i + 1][j].f > fNew)
                    {
                        openList.insert(make_pair(
                            fNew, make_pair(i + 1, j)));

                        cellTraceInfo[i + 1][j].f = fNew;
                        cellTraceInfo[i + 1][j].g = gNew;
                        cellTraceInfo[i + 1][j].h = hNew;
                        cellTraceInfo[i + 1][j].parent_i = i;
                        cellTraceInfo[i + 1][j].parent_j = j;
                    }
                }
            }

            if (isValidCell(i, j + 1) == true)
            {
                if (isDestination(i, j + 1, dest) == true)
                {
                    cellTraceInfo[i][j + 1].parent_i = i;
                    cellTraceInfo[i][j + 1].parent_j = j;
                    loggingMessage("The destination cell is found\n");
                    return tracePath(cellTraceInfo, dest);
                }
                else if (closedList[i][j + 1] == false
                         && isNotWall(i, j+1)
                                == true)
                {
                    gNew = cellTraceInfo[i][j].g + 1.0;
                    hNew = calculateEuclideanDistance(i, j+1, dest);
                    fNew = gNew + hNew;

                    if (cellTraceInfo[i][j+1].f == FLT_MAX
                        || cellTraceInfo[i - 1][j+1].f > fNew)
                    {
                        openList.insert(make_pair(
                            fNew, make_pair(i, j+1)));

                        cellTraceInfo[i][j+1].f = fNew;
                        cellTraceInfo[i][j+1].g = gNew;
                        cellTraceInfo[i][j+1].h = hNew;
                        cellTraceInfo[i][j+1].parent_i = i;
                        cellTraceInfo[i][j+1].parent_j = j;
                    }
                }
            }


            if (isValidCell(i, j - 1) == true)
            {
                if (isDestination(i, j - 1, dest) == true)
                {
                    cellTraceInfo[i][j - 1].parent_i = i;
                    cellTraceInfo[i][j - 1].parent_j = j;
                    loggingMessage("The destination cell is found\n");
                    return tracePath(cellTraceInfo, dest);
                }
                else if (closedList[i][j - 1] == false
                         && isNotWall(i, j-1)
                                == true)
                {
                    gNew = cellTraceInfo[i][j].g + 1.0;
                    hNew = calculateEuclideanDistance(i, j-1, dest);
                    fNew = gNew + hNew;

                    if (cellTraceInfo[i][j-1].f == FLT_MAX
                        || cellTraceInfo[i - 1][j-1].f > fNew)
                    {
                        openList.insert(make_pair(
                            fNew, make_pair(i, j-1)));

                        cellTraceInfo[i][j-1].f = fNew;
                        cellTraceInfo[i][j-1].g = gNew;
                        cellTraceInfo[i][j-1].h = hNew;
                        cellTraceInfo[i][j-1].parent_i = i;
                        cellTraceInfo[i][j-1].parent_j = j;
                    }
                }
            }
    }

    if (foundDest == false) {
            loggingMessage("Failed to find the Destination Cell\n");

            QVector<pair<int, int>> garbageOutput;
            return garbageOutput;
    }
}
