#include "suan_png.h"

PNG::PNG() {
    width_ = 0;
    height_ = 0;
    image = nullptr;
}

PNG::PNG(int w, int h) {
    width_ = w;
    height_ = h;
    image = new pxl[w * h];
    for (int y = 0; y < height_; y++) {
        for (int x = 0; x < width_; x++) {
            pxl *curr = get_pxl(x, y);
            curr->red = 255;
            curr->green = 255;
            curr->blue = 255;
            curr->alpha = 255;
        }
    }
}

PNG::~PNG() {
    delete[] image;
}

int PNG::load(std::string &file_name) {
    FILE* fp = fopen(file_name.c_str(), "rb");
    if (!fp) {
        perror("Fopen failed: ");
        return 1;
    }
    png_byte header[8];
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)) {
        fclose(fp);
        perror("Not a valid PNG file: ");
        return 1;
    }
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        fclose(fp);
        perror("png jmpBuf Failed: ");
        return 1;
    }
    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);
    png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    if (bit_depth == 16) {
        png_set_strip_16(png_ptr);
    }
    png_byte color_type = png_get_color_type(png_ptr, info_ptr);
    if (color_type != PNG_COLOR_TYPE_RGB && color_type != PNG_COLOR_TYPE_RGBA) {
        if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
            if (bit_depth < 8) {
                png_set_expand(png_ptr);
            }
            png_set_gray_to_rgb(png_ptr);
        }
        if (color_type == PNG_COLOR_TYPE_PALETTE) {
            png_set_palette_to_rgb(png_ptr);
        }
    }
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(png_ptr);
    }
    size_t width = png_get_image_width(png_ptr, info_ptr);
    size_t height = png_get_image_height(png_ptr, info_ptr);
    pxl* new_pixs = nullptr;
    png_byte *row = nullptr;
    png_read_update_info(png_ptr, info_ptr);
    if (setjmp(png_jmpbuf(png_ptr))) {
        delete[] new_pixs;
        delete[] row;
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        fclose(fp);
        perror("png_jmpbuf failed: ");
        return 1;
    }
    int bpr = png_get_rowbytes(png_ptr, info_ptr);
    new_pixs = new pxl[height * width];
    row = new png_byte[bpr];
    int numchannels = png_get_channels(png_ptr, info_ptr);
    for (size_t y = 0; y < height; y++) {
        png_read_row(png_ptr, row, nullptr);
        png_byte* pix = (png_byte*)row;
        for (size_t x = 0; x < width; x++) {
            pxl& px = new_pixs[width * y + x];
            if (numchannels == 1 || numchannels == 2) {
                unsigned char color = (unsigned char)*pix++;
                px.red = color;
                px.green = color;
                px.blue = color;
                if (numchannels == 2) {
                    px.alpha = (unsigned char)*pix++;
                } else {
                    px.alpha = 255;
                }
            }
            else if (numchannels == 3 || numchannels == 4) {
                px.red = (unsigned char)*pix++;
                px.green = (unsigned char)*pix++;
                px.blue = (unsigned char)*pix++;
                if (numchannels == 4) {
                    px.alpha = (unsigned char)*pix++;
                } else {
                    px.alpha = 255;
                }
            }
        }
    }
    delete[] image;
    image = new_pixs;
    width_ = width;
    height_ = height;
    delete[] row;
    png_read_end(png_ptr, nullptr);
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    fclose(fp);
    return 0;
}

int PNG::save(std::string &file_name) {
    FILE* fp = fopen(file_name.c_str(), "wb");
    if (!fp) {
        perror("fopen Failed: ");
        return 1;
    }
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        perror("png jmpBuf Failed: ");
        return 1;
    }
    png_init_io(png_ptr, fp);
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        perror("png jmpBuf Failed: ");
        return 1;
    }
    png_set_IHDR(png_ptr, info_ptr, width_, height_, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(png_ptr, info_ptr);
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        perror("png_jmpbuf failed: ");
        return 1;
    }
    int bpr = png_get_rowbytes(png_ptr, info_ptr);
    png_byte* row = new png_byte[bpr];
    for (int y = 0; y < height_; y++) {
        for (int x = 0; x < width_; x++) {
            png_byte* blah = row + (x * 4);
            blah[0] = image[width_ * y + x].red;
            blah[1] = image[width_ * y + x].green;
            blah[2] = image[width_ * y + x].blue;
            blah[3] = image[width_ * y + x].alpha;
        }
        png_write_row(png_ptr, row);
    }
    png_write_end(png_ptr, nullptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    delete[] row;
    fclose(fp);
    return 0;
}

pxl *PNG::get_pxl(int x, int y) {
    if(x >= width_ || y >= height_) {
        return NULL;
    }
    return &image[width_ * y + x];
}

int PNG::get_width() const {
    return width_;
}

int PNG::get_height() const {
    return height_;
}
