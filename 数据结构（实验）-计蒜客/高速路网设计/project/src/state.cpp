#include "state.h"
#include <iostream>
#include <climits>
#include <queue>
#include <vector>

State::State()
{
    for (int i = 0; i < MAXNODE; i++)
    {
        for (int j = 0; j < MAXNODE; j++)
        {
            dis[i][j] = INF;
            vis[i][j] = 0;
        }
    }
    row = 0;
    line = 0;
}

State::State(State &other)
{
    row = other.row;
    line = other.line;
    for (int i = 0; i < MAXNODE; i++)
    {
        for (int j = 0; j < MAXNODE; j++)
        {
            pic[i][j] = other.pic[i][j];
            dis[i][j] = INF;
            vis[i][j] = 0;
        }
    }
    return;
}

State::State(State &&other)
{
    row = other.row;
    line = other.line;
    for (int i = 0; i < MAXNODE; i++)
    {
        for (int j = 0; j < MAXNODE; j++)
        {
            pic[i][j] = other.pic[i][j];
            dis[i][j] = INF;
            vis[i][j] = 0;
        }
    }
    return;
}

State::~State()
{
    //TODO
}

State &State::operator=(State &other)
{
    row = other.row;
    line = other.line;
    for (int i = 0; i < MAXNODE; i++)
    {
        for (int j = 0; j < MAXNODE; j++)
        {
            pic[i][j] = other.pic[i][j];
            dis[i][j] = INF;
            vis[i][j] = 0;
        }
    }
    return *this;
}

State &State::operator=(State &&other)
{
    row = other.row;
    line = other.line;
    for (int i = 0; i < MAXNODE; i++)
    {
        for (int j = 0; j < MAXNODE; j++)
        {
            pic[i][j] = other.pic[i][j];
            dis[i][j] = INF;
            vis[i][j] = 0;
        }
    }
    return *this;
}

void State::parse(PNG *p)
{
    int height = p->get_height();
    int width = p->get_width();
    row = 0;
    int line_max = 0;
    for (int h = 6; h < height; h += 8, row++)
    {
        line = 0;
        for (int w = 1, j = -1; w < width; w++)
        {
            int r, g, b;
            r = p->get_pxl(w, h)->red;
            g = p->get_pxl(w, h)->green;
            b = p->get_pxl(w, h)->blue;
            if (r == 0 && g == 0 && b == 0)
            {
                line++;
                continue;
            }
            pic[row][line] = 255 * 255 * 3 - r * r - g * g - b * b;
            if (line == 0 && pic[row][line] == 0)
                pic[row][line] = -1;
        }
        line_max = std::max(line, line_max);
    }
    line = line_max;
    return;
}

struct Point
{
    int x, y, data;

    friend bool operator<(const Point& a,const Point &b)
    {
        return a.data > b.data;
    }
    friend bool operator>(const Point& a, const Point& b)
    {
        return a.data < b.data;
    }
    Point(int x, int y, int data) : x(x), y(y), data(data) {}
};

int State::solve()
{
    std::priority_queue<Point> q;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < line; j++)
        {
            dis[i][j] = INF;
        }
    }
    if (pic[0][0] != 0)
    {
        q.push(Point(0, 0, 0));
    }
    else
    {
        q.push(Point(0, 1, 0));
    }

    int even_x[6]{-1, 1, 0, 0, -1, 1};
    int even_y[6]{0, 0, -1, 1, 1, 1};

    int odd_x[6]{-1, 1, 0, 0, -1, 1};
    int odd_y[6]{0, 0, -1, 1, -1, -1};

    while (q.size())
    {
        Point cur = q.top();
        q.pop();
        if(vis[cur.x][cur.y] == 1)
            continue;
        vis[cur.x][cur.y] = 1;
        dis[cur.x][cur.y] = cur.data;
        if (cur.x % 2 == 0)
        {
            //even
            for (int i = 0; i < 6; i++)
            {
                int next_x = cur.x + even_x[i];
                int next_y = cur.y + even_y[i];
                if (next_x < 0 || next_x >= row || next_y < 0 || next_y >= line || vis[next_x][next_y] == 1 || pic[next_x][next_y] == -1)
                {
                    continue;
                }
                q.push(Point(next_x, next_y, dis[cur.x][cur.y] + pic[next_x][next_y]));
            }
        }
        else
        {
            //odd
            for (int i = 0; i < 6; i++)
            {
                int next_x = cur.x + odd_x[i];
                int next_y = cur.y + odd_y[i];
                if (next_x < 0 || next_x >= row || next_y < 0 || next_y >= line || vis[next_x][next_y] == 1 || pic[next_x][next_y] == -1)
                {
                    continue;
                }
                q.push(Point(next_x, next_y, dis[cur.x][cur.y] + pic[next_x][next_y]));
            }
        }
    }
    if (row > 0 && line > 0) 
    {
        return dis[row - 1][line - 1];
    }
    else 
    {
        return 0;
    }
}

// void State::print()
// {
//     for (int i = 0; i < row; i++)
//     {
//         for (int j = 0; j < line; j++)
//         {
//             printf("%d ", pic[i][j]);
//         }
//         printf("\n");
//     }
//     for (int i = 0; i < row; i++)
//     {
//         for (int j = 0; j < line; j++)
//         {
//             printf("%d ", dis[i][j]);
//         }
//         printf("\n");
//     }
//     for (int i = 0; i < row; i++)
//     {
//         for (int j = 0; j < line; j++)
//         {
//             printf("%d ", vis[i][j]);
//         }
//         printf("\n");
//     }
// }
