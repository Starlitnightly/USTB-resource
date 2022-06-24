#ifndef PXL_H_
#define PXL_H_
#include <cstdint>

struct pxl {
public:
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
    pxl();
    pxl(uint8_t red_, uint8_t green_, uint8_t blue_, uint8_t alpha_);
};

#endif
