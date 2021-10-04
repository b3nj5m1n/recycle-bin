#ifndef MODEL
#define MODEL

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Vertex {
  double x;
  double y;
  double z;
  double w;
  Vertex(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = 1.0;
  }
  Vertex(double x, double y, double z, double w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
  }
  friend std::ostream &operator<<(std::ostream &os, const Vertex &obj) {
    os << "v " << obj.x << ' ' << obj.y << ' ' << obj.z;
    if (obj.w != 1.0) {
      os << obj.w;
    }
    return os;
  }
};

struct FaceList {
  int vertex, texture, normal;
  FaceList() {}
  FaceList(int vertex, int texture, int normal) {
    this->vertex = vertex;
    this->texture = texture;
    this->normal = normal;
  }
  friend std::ostream &operator<<(std::ostream &os, const FaceList &obj) {
    os << obj.vertex;
    os << '/';
    if (obj.texture != -1) {
      os << obj.texture;
    }
    os << '/';
    if (obj.normal != -1) {
      os << obj.normal;
    }
    return os;
  }
};

struct Face {
  FaceList l1, l2, l3;
  Face(FaceList l1, FaceList l2, FaceList l3) {
    this->l1 = l1;
    this->l2 = l2;
    this->l3 = l3;
  }
  friend std::ostream &operator<<(std::ostream &os, const Face &obj) {
    os << "f " << obj.l1 << ' ' << obj.l2 << ' ' << obj.l3;
    return os;
  }
};

class Model {
private:
  std::string filename;
  std::vector<Vertex> vertices;
  std::vector<Face> faces;

public:
  Model(std::string filename) {
    this->filename = filename;
    this->read();
  }
  const int stoi(std::string s) {
    if (s == "") {
      return -1;
    } else {
      return std::stoi(s);
    }
  }
  std::vector<Face> get_faces() { return this->faces; }
  Vertex get_vertex_at(int index) { return this->vertices.at(index - 1); }
  const std::vector<std::string> split_line(std::string *line,
                                            std::string delimiter) {
    std::vector<std::string> result;
    size_t pos = 0;
    while ((pos = line->find(delimiter)) != std::string::npos) {
      result.push_back(line->substr(0, pos));
      line->erase(0, pos + delimiter.length());
    }
    result.push_back(*line);
    return result;
  }
  void parse_line(std::vector<std::string> line) {
    // Get the type of information given in the line
    std::string type = line[0];
    if (type == "v") {
      this->parse_line_vertex(line);
    } else if (type == "f") {
      this->parse_line_face(line);
    }
  }
  void parse_line_vertex(std::vector<std::string> line) {
    // The line contains a vertex, convert the points to doubles
    std::vector<double> points;
    for (int i = 1; i < line.size(); i++) {
      points.push_back(stod(line[i]));
    }
    this->vertices.push_back(Vertex(points[0], points[1], points[2]));
  }
  void parse_line_face(std::vector<std::string> line) {
    // The line contains a face, each word contains
    // vertex_index/texture_index/normal_index
    std::vector<FaceList> face_list;
    for (int i = 1; i < line.size(); i++) {
      // Split the line by /
      std::vector<std::string> list = this->split_line(&line[i], "/");
      face_list.push_back(
          FaceList(this->stoi(list[0]), this->stoi(list[1]), this->stoi(list[2])));
    }
    // Create new face
    this->faces.push_back(Face(face_list[0], face_list[1], face_list[2]));
  }
  void read() {
    std::fstream file;
    file.open(this->filename, std::ios::in);
    if (file.is_open()) {
      std::string line;
      while (getline(file, line)) {
        // Splits the line by whitespace
        std::vector<std::string> values = this->split_line(&line, " ");
        this->parse_line(values);
      }
      file.close();
    }
  }
};

#endif
