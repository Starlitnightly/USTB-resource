#include "suan_png.h"
#include "pxl.h"
#include "state.h"
#include <string>
#include <iostream>

int solve_algo();

int main() {
    solve_algo();
    return 0;
}


int solve_algo() {
    PNG *png = new PNG();
    std::string s("pic/test2.png");
    png->load(s);
    State *state = new State();
    state->parse(png);
    std::cout << state->solve() << std::endl;
    png->save(s);
    delete state;
    delete png;
    return -1;
}
