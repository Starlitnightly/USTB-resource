#ifndef STATE_H_
#define STATE_H_
#include "suan_png.h"
#include "pxl.h"
#include <set>
#include <vector>
#include <queue>

#define MAXNODE 2000
#define INF 0x3f3f3f3f

class State
{
private:
    int pic[MAXNODE][MAXNODE];
    bool vis[MAXNODE][MAXNODE];
    int dis[MAXNODE][MAXNODE];
    int row;
    int line;

public:
    State();
    State(State &other);
    State(State &&other);
    ~State();
    State &operator=(State &&other);
    State &operator=(State &other);
    void parse(PNG *p);
    int solve();
    // void print();
};

#endif
