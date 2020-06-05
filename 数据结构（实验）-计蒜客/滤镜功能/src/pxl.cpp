#include "pxl.h"

pxl::pxl() {
    red = 255;
    green = 255;
    blue = 255;
    alpha = 255;
}

pxl::pxl(uint8_t red_, uint8_t green_, uint8_t blue_, uint8_t alpha_) {
    red = red_;
    green = green_;
    blue = blue_;
    alpha = alpha_;
}
