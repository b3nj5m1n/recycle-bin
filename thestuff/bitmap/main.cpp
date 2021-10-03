#include "bitmap.h"
#include <iostream>

// Something is really wrong here, when you change the height on the gradient or
// pride flag test the image is very much fucked, I'm not sure whether the issue
// is in the bitmap lib or the test code though

void test_spectrum_ish() {
  int width = 256;
  int height = 256;
  Bitmap test(width, height, 24);
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      test.set_pixel(x, y, Pixel<uint8_t>(x % 255, y % 255, x * y % 255));
    }
  }
  test.write("./spectrum_ish.bmp");
}
void test_pride_flag() {
  int width = 1920;
  int height = 1080;
  Bitmap test(width, height, 24);
  Pixel<uint8_t> colors[6] = {
      Pixel<uint8_t>(255, 0, 24),   Pixel<uint8_t>(255, 165, 44),
      Pixel<uint8_t>(255, 255, 65), Pixel<uint8_t>(0, 128, 24),
      Pixel<uint8_t>(0, 0, 249),    Pixel<uint8_t>(134, 0, 125),
  };
  int ratio = ceil(width / 6.0);
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int color_index = floor((double)x / (double)ratio);
      test.set_pixel(x, y, colors[color_index]);
    }
  }
  test.write("./pride-flag.bmp");
}
void test_chess_board() {
  int width = 8;
  int height = 8;
  Bitmap test(width, height, 24);
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      if ((x + y) % 2 == 0) {
        test.set_pixel(x, y, Pixel<uint8_t>(0, 0, 0));
      } else {
        test.set_pixel(x, y, Pixel<uint8_t>(255, 0, 102));
      }
    }
  }
  test.write("./chess_board.bmp");
}
void test_gradient() {
  int width = 1920;
  int height = 1080;
  uint8_t r1 = 255, g1 = 0, b1 = 102;
  uint8_t r2 = 0, g2 = 255, b2 = 102;
  Bitmap test(width, height, 24);
  for (int x = 0; x < width; x++) {
    uint8_t r = r1 * ((double)x / width) + r2 * (1 - ((double)x / width));
    uint8_t g = g1 * ((double)x / width) + g2 * (1 - ((double)x / width));
    uint8_t b = b1 * ((double)x / width) + b2 * (1 - ((double)x / width));
    Pixel<uint8_t> color(r, g, b);
    for (int y = 0; y < height; y++) {
      test.set_pixel(x, y, color);
    }
  }
  test.write("./gradient.bmp");
}
void test_two_colors() {
  int width = 8;
  int height = 4;
  Bitmap test(width, height, 24);
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      Pixel<uint8_t> color = x < (width / 2) ? Pixel<uint8_t>(0, 0, 0)
                                              : Pixel<uint8_t>(255, 255, 255);
      test.set_pixel(x, y, color);
    }
  }
  test.write("./two-colors.bmp");
}

int main(int argc, char *argv[]) {
  test_spectrum_ish();
  test_chess_board();
  test_pride_flag();
  test_gradient();
  test_two_colors();
}
