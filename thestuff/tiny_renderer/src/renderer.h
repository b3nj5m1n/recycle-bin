#ifndef RENDERER
#define RENDERER

#include "bitmap.h"
#include "model.h"
#include <string>

struct Color {
  int red;
  int green;
  int blue;
  Color(int red, int green, int blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
  }
};

struct RendererConfig {
  int width;
  int height;
  std::string output_filename;
  RendererConfig(int width, int height, std::string output_filename) {
    this->width = width;
    this->height = height;
    this->output_filename = output_filename;
  }
};

class Renderer {
private:
  RendererConfig config;
  Bitmap bitmap;

public:
  Renderer(int width, int height, std::string output_filename)
      : bitmap(width, height, 24), config(width, height, output_filename) {}
  void render() { this->bitmap.write(this->config.output_filename); }
  void draw_pixel(int x, int y, Color color) {
    // Because bitmaps are constructed bottom up, this puts the origin at the
    // top-left
    y = (this->config.height - (y)) - 1;
    this->bitmap.set_pixel(x, y,
                           Pixel<uint8_t>(color.red, color.green, color.blue));
  }
  void draw_line(int x0, int y0, int x1, int y1, Color color) {
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
      std::swap(x0, y0);
      std::swap(x1, y1);
      steep = true;
    }
    if (x0 > x1) {
      std::swap(x0, x1);
      std::swap(y0, y1);
    }
    for (int x = x0; x <= x1; x++) {
      // Percentage of the way
      float t = (x - x0) / (float)(x1 - x0);
      int y = y0 * (1. - t) + y1 * t;
      if (!steep) {
        this->draw_pixel(x, y, color);
      } else {
        this->draw_pixel(y, x, color);
      }
    }
  }
  void draw_line_vertex(Vertex vertex0, Vertex vertex1, Color color) {
    int x0 = (vertex0.x+1) * this->config.width / 4.;
    int y0 = (vertex0.y+1) * this->config.height / 4.;
    int x1 = (vertex1.x+1) * this->config.width / 4.;
    int y1 = (vertex1.y+1) * this->config.height / 4.;
        std::cout << "From " << x0 << ", " << y0 << " to " << x1 << ", " << y1 << std::endl;
    this->draw_line(x0, y0, x1, y1, color);
  }
  void draw_wireframe(Model model, Color color) {
    // Loop over faces
    for (auto face : model.get_faces()) {
      Vertex vertex0 = model.get_vertex_at(face.vertex1);
      Vertex vertex1 = model.get_vertex_at(face.vertex2);
      Vertex vertex2 = model.get_vertex_at(face.vertex3);
      this->draw_line_vertex(vertex0, vertex1, color);
    }
  }
};

#endif
