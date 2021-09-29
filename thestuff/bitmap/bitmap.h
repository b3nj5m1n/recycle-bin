#include <bitset>
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <vector>

#ifndef BITMAP_LIB
#define BITMAP_LIB

#define byte uint8_t
#define t_bytes uint16_t
#define f_bytes uint32_t

template <class T> class Pixel {
private:
  T red;
  T green;
  T blue;

public:
  Pixel() {
    this->red = 0;
    this->green = 0;
    this->blue = 0;
  }
  Pixel(T red, T green, T blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
  }
};

class PixelMap {
private:
  std::vector<Pixel<uint16_t>> pixels;
  int width;
  int height;
  int row_size;

public:
  PixelMap() {}
  PixelMap(int width, int height, int row_size) {
    this->width = width;
    this->height = height;
    this->row_size = row_size;
    this->pixels = std::vector<Pixel<uint16_t>>(this->height * this->row_size,
                                                Pixel<uint16_t>());
  }
  std::vector<Pixel<uint16_t>> get_pixel_map() { return this->pixels; }
};

struct BITMAPFILEHEADER {
  t_bytes type; // Type of the file as ASCII text, standard is 42'4D ("BM")
  f_bytes size; // Size of the file in bytes, for example if it's 105 bytes (69
                // in hex) 69'00'00'00
  t_bytes res1; // Reserved for specific applications
  t_bytes res2; // Reserved for specific applications
  f_bytes
      offset; // Offset where the pixel bytes begin, for example: 36'00'00'00
};
struct BITMAPINFOHEADER {
  f_bytes struc_size; // Number of bytes required for the bitmapinfoheader
  f_bytes width;      // Width of the image in pixels, for example 05'00'00'00
  f_bytes height;     // Height of the image in pixels, for example 05'00'00'00,
                  // this can be negative (> 0: bottom-up, origin lower-left, <
                  // 0: top-down, origin upper-left)
  t_bytes num_plans; // Number of color plans on target device, usually 1
  t_bytes num_bits_per_pixel; // Number of bits per pixel, either 1, 4, 8, or 24
  f_bytes compression;    // Type of compression, 00'00'00'00 for no compression
  f_bytes num_bytes_img;  // Total number of bytes making up the image
  f_bytes resolution_hor; // Horizontal resolution (pixels per meter for target
                          // device)
  f_bytes resolution_ver; // Vertical resolution (pixels per meter for target
                          // device)
  f_bytes num_colors;   // Number of used colors (when 0, the maximum number of
                        // colors corresponding to num_bits_per_pixel is used)
  f_bytes num_i_colors; // Number of important colors (when 0, all colors are
                        // important)
};

class Bitmap {
private:
  int width;
  int height;
  int bits_per_pixel;
  int row_size;
  BITMAPFILEHEADER header_file;
  BITMAPINFOHEADER header_info;
  PixelMap pixel_map;

public:
  Bitmap(int width, int height, int bits_per_pixel) {
    this->width = width;
    this->height = height;
    this->bits_per_pixel = bits_per_pixel;
    this->row_size = ceil((this->bits_per_pixel * this->width) / 32) * 4;
    this->header_file = this->get_header_file();
    this->header_info = this->get_header_info();
    this->pixel_map = PixelMap(this->width, this->height, this->row_size);
  }

  BITMAPFILEHEADER get_header_file() {
    BITMAPFILEHEADER result;
    result.type = 0x4D42;
    result.size = 0x28 + (this->row_size * this->height);
    result.res1 = 0x0;
    result.res2 = 0x0;
    result.offset = 0x36;
    return result;
  }
  BITMAPINFOHEADER get_header_info() {
    BITMAPINFOHEADER result;
    result.struc_size = 0x28;
    result.width = this->width;
    result.height = this->height;
    result.num_plans = 0x1;
    result.num_bits_per_pixel = this->bits_per_pixel;
    result.compression = 0x0;
    result.num_bytes_img = (this->row_size * this->height);
    result.resolution_hor = 0xC40E;
    result.resolution_ver = 0xC40E;
    result.num_colors = 0x0;
    result.num_i_colors = 0x0;
    return result;
  }

  int write(std::string filename) {
    FILE *file = std::fopen(filename.c_str(), "wb");
    // File Header
    std::fwrite(&this->header_file.type, 2, 1, file);
    std::fwrite(&this->header_file.size, 4, 1, file);
    std::fwrite(&this->header_file.res1, 2, 1, file);
    std::fwrite(&this->header_file.res2, 2, 1, file);
    std::fwrite(&this->header_file.offset, 4, 1, file);
    // Info Header
    std::fwrite(&this->header_info.struc_size, 4, 1, file);
    std::fwrite(&this->header_info.width, 4, 1, file);
    std::fwrite(&this->header_info.height, 4, 1, file);
    std::fwrite(&this->header_info.num_plans, 2, 1, file);
    std::fwrite(&this->header_info.num_bits_per_pixel, 2, 1, file);
    std::fwrite(&this->header_info.compression, 4, 1, file);
    std::fwrite(&this->header_info.num_bytes_img, 4, 1, file);
    std::fwrite(&this->header_info.resolution_hor, 4, 1, file);
    std::fwrite(&this->header_info.resolution_ver, 4, 1, file);
    std::fwrite(&this->header_info.num_colors, 4, 1, file);
    std::fwrite(&this->header_info.num_i_colors, 4, 1, file);
    for (auto i : this->pixel_map.get_pixel_map()) {
      std::fwrite(&i, sizeof(i), 1, file);
    }
    fclose(file);
    return 0;
  }
};

#endif
