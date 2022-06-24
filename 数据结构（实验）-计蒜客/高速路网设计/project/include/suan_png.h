#ifndef SUAN_PNG_H_
#define SUAN_PNG_H_

#include <string>
#include <png.h>
#include "pxl.h"

class PNG {
private:
    pxl * image;
    int width_;
    int height_;
public:
    PNG();
    PNG(int w, int h);
    ~PNG();
    int load(std::string &file_name);
    int save(std::string &file_name);
    pxl *get_pxl(int x, int y);
    int get_width() const;
    int get_height() const;
};

#endif
