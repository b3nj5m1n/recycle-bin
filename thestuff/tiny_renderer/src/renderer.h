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
  friend std::ostream &operator<<(std::ostream &os, const Color &obj) {
    os << "rgb(" << obj.red << ", " << obj.green << ", " << obj.blue << ")";
    return os;
  }
};

struct Point {
  int x, y, z;
  Point(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
  Point(Vertex vertex, int width, int height) {
    this->x = (vertex.x + 1) * ( width-1 ) / 2;
    this->y = (vertex.y + 1) * ( height-1 ) / 2;
    this->z = vertex.z;
  }
  friend std::ostream &operator<<(std::ostream &os, const Point &obj) {
    os << "(" << obj.x << "|" << obj.y << "|" << obj.z << ")";
    return os;
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
  void draw_line(Point p1, Point p2, Color color) {
    this->draw_line(p1.x, p1.y, p2.x, p2.y, color);
  }
  void draw_face(Face face, Model model, Color color) {
    Point points[3] = {
        Point(model.get_vertex_at(face.l1.vertex), this->config.width,
              this->config.height),
        Point(model.get_vertex_at(face.l2.vertex), this->config.width,
              this->config.height),
        Point(model.get_vertex_at(face.l3.vertex), this->config.width,
              this->config.height),
    };
    this->draw_line(points[0], points[1], color);
    this->draw_line(points[1], points[2], color);
    this->draw_line(points[2], points[0], color);
  }
  void draw_wireframe(Model model, Color color) {
    // Loop over faces
    for (auto face : model.get_faces()) {
      this->draw_face(face, model, color);
    }
  }
};

#endif
